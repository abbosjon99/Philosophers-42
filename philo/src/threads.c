/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:40:19 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/30 11:28:45 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	ft_think(t_ph *ph)
{
	int	time;

	print_stats(ph, THINK);
	if (ph->data->ph_num % 2 != 0)
	{
		time = ph->data->time2die - ph->data->time2eat - ph->data->time2sleep;
		if (time < 0)
			time = 0;
		pro_sleep(time / 2, ph->data);
	}
}

// if philo num is even we will artificially pause some threads
static void	a_ph_helper(t_ph *ph)
{
	while (!get_bool(&ph->data->ready_mtx, &ph->data->all_ready, ph->data))
		;
	set_starttime(ph, ph->data);
	if (ph->data->ph_num % 2 == 0)
	{
		if (ph->id % 2 == 0)
		{
			print_stats(ph, THINK);
			pro_sleep(ph->data->time2eat / 2, ph->data);
		}
	}
}

// automaticly stops if over or internal error
void	*a_philo(void *philo)
{
	t_ph	*ph;

	ph = (t_ph *)philo;
	a_ph_helper(ph);
	while (ph->needs2eat != 0 && !set_get_over(ph->data, true, GET)
		&& !set_get_err(ph->data, true, GET))
	{
		safe_mtx(&ph->uno_fork->fork, ph->data, LOCK);
		print_stats(ph, FORK);
		safe_mtx(&ph->dos_fork->fork, ph->data, LOCK);
		print_stats(ph, FORK);
		print_stats(ph, EAT);
		pro_sleep(ph->data->time2eat, ph->data);
		if (--ph->needs2eat == 0)
			set_bool(&ph->ph_mtx, &ph->full, true, ph->data);
		set_lastmeal(ph, ph->data);
		safe_mtx(&ph->dos_fork->fork, ph->data, UNLOCK);
		safe_mtx(&ph->uno_fork->fork, ph->data, UNLOCK);
		print_stats(ph, SLEEP);
		pro_sleep(ph->data->time2sleep, ph->data);
		ft_think(ph);
	}
	return (NULL);
}

void	*ph_watchdog(void *all_data)
{
	t_data	*d;
	int		i;

	d = (t_data *)all_data;
	while (!get_bool(&d->ready_mtx, &d->all_ready, d))
		;
	usleep(d->time2die * 333);
	while (!set_get_over(d, true, GET) && !set_get_err(d, true, GET))
	{
		i = -1;
		while (++i < d->ph_num)
		{
			if (get_bool(&d->phs[i].ph_mtx, &d->phs[i].full, d))
				continue ;
			if (get_time(true, d) - get_lastmeal(&d->phs[i], d) >= d->time2die)
			{
				set_get_over(d, true, SET);
				print_stats(&d->phs[i], DIED);
				return (NULL);
			}
			if (set_get_over(d, true, GET) || set_get_err(d, true, GET))
				return (NULL);
		}
	}
	return (NULL);
}
