/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:46:14 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 22:15:59 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// automaticly stops if over or internal error
static void	*a_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!get_bool(&philo->data->ready_mtx, &philo->data->all_ready, data))
		;
	set_starttime(philo, philo->data);
	while (philo->needs2eat != 0 && !set_get_over(philo->data, true, GET)
		&& !set_get_error(philo->data, true, GET))
	{
		safe_mtx(&philo->uno_fork->fork, data, LOCK);
		print_stats(philo, FORK);
		safe_mtx(&philo->dos_fork->fork, data, LOCK);
		print_stats(philo, FORK);
		print_stats(philo, EAT);
		pro_sleep(philo->data->time2eat, philo->data);
		if (--philo->needs2eat == 0)
			set_bool(&philo->philo_mtx, &philo->full, true, data);
		set_lastmeal(philo, philo->data);
		safe_mtx(&philo->dos_fork->fork, data, UNLOCK);
		safe_mtx(&philo->uno_fork->fork, data, UNLOCK);
		print_stats(philo, SLEEP);
		pro_sleep(philo->data->time2sleep, philo->data);
		print_stats(philo, THINK);
	}
	return (NULL);
}

// automaticly stops if over or internal error
static void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!get_bool(&philo->data->ready_mtx, &philo->data->all_ready, data))
		;
	set_starttime(philo, philo->data);
	safe_mtx(&philo->dos_fork->fork, data, LOCK);
	print_stats(philo, FORK);
	while (!set_get_over(philo->data, true, GET) && !set_get_error(philo->data,
			true, GET))
		pro_sleep(10, philo->data);
	safe_mtx(&philo->dos_fork->fork, data, UNLOCK);
	return (NULL);
}

static void	ph_watchdog(t_data *data, int i)
{
	data->start_time = get_time(true, data);
	set_bool(&data->ready_mtx, &data->all_ready, true, data);
	usleep(data->time2die * 333);
	while (!set_get_over(data, true, GET) && !set_get_error(data, true, GET))
	{
		i = -1;
		while (++i < data->philo_num)
		{
			if (get_time(true, data) - get_lastmeal(&data->philos[i],
					data) >= data->time2die)
			{
				set_get_over(data, true, SET);
				print_stats(&data->philos[i], DIED);
				return ;
			}
			if (set_get_over(data, true, GET) || set_get_error(data, true, GET))
				return ;
		}
	}
}

// return 1 if any error
int	data_process(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo_num == 1 && ++i
		&& pthread_create(&data->philos[0].thread_id, NULL, one_philo,
			&data->philos[0]))
		return (my_err("PTHREAD ERROR!!!!!", 1));
	else
	{
		while (i < data->philo_num)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL, a_philo,
					&data->philos[i]))
				return (my_err("PTHREAD ERROR!!!!!", 1));
			i++;
		}
	}
	ph_watchdog(data, -1);
	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->philos[i].thread_id, NULL);
	if (data->internal_error)
		return (my_err("INTERNAL ERROR!!!!!", 1));
	return (0);
}
