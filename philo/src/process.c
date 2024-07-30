/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:46:14 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/30 03:19:45 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// automaticly stops if over or internal error
static void	*one_philo(void *data)
{
	t_ph	*ph;

	ph = (t_ph *)data;
	while (!get_bool(&ph->data->ready_mtx, &ph->data->all_ready, data))
		;
	set_starttime(ph, ph->data);
	safe_mtx(&ph->dos_fork->fork, data, LOCK);
	print_stats(ph, FORK);
	while (!set_get_over(ph->data, true, GET) && !set_get_err(ph->data, true,
			GET))
		pro_sleep(10, ph->data);
	safe_mtx(&ph->dos_fork->fork, data, UNLOCK);
	return (NULL);
}

static int	th_create(t_data *d)
{
	int	i;

	i = 0;
	if (d->ph_num == 1)
	{
		if (pthread_create(&d->phs[0].thread_id, NULL, one_philo, &d->phs[0]))
			return (1);
	}
	else
	{
		while (i < d->ph_num)
		{
			if (pthread_create(&d->phs[i].thread_id, NULL, a_philo, &d->phs[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

// return 1 if any error
int	data_process(t_data *d)
{
	int			i;
	pthread_t	wt_dog;

	if (th_create(d))
		return (my_err("PTHREAD ERROR!!!!!", 1));
	if (pthread_create(&wt_dog, NULL, ph_watchdog, d))
		return (my_err("PTHREAD ERROR!!!!!", 1));
	d->start_time = get_time(true, d);
	set_bool(&d->ready_mtx, &d->all_ready, true, d);
	i = -1;
	while (++i < d->ph_num)
		pthread_join(d->phs[i].thread_id, NULL);
	set_get_over(d, true, SET);
	pthread_join(wt_dog, NULL);
	if (d->internal_error)
		return (my_err("INTERNAL ERROR!!!!!", 1));
	return (0);
}
