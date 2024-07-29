/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:46:14 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 16:02:31 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// automaticly stops if over or internal error
static void	*a_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->needs2eat != 0 && !set_get_over(philo->data, true, GET)
		&& !set_get_error(philo->data, true, GET))
	{
		pthread_mutex_lock(&philo->uno_fork->fork);
		printf("%d has taken %d fork\n", philo->id, philo->uno_fork->fork_id);
		pthread_mutex_lock(&philo->dos_fork->fork);
		printf("%d has taken %d fork\n", philo->id, philo->dos_fork->fork_id);
		printf("%d is eating\n", philo->id);
		usleep(philo->data->time2eat * 1000);
		philo->full = true;
		pthread_mutex_unlock(&philo->dos_fork->fork);
		pthread_mutex_unlock(&philo->uno_fork->fork);
		philo->needs2eat--;
		printf("%d  is sleeping\n", philo->id);
		usleep(philo->data->time2sleep * 1000);
		printf("%d is thinking\n", philo->id);
	}
	return (NULL);
}

// return 1 if any error
int	data_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, a_philo,
				&data->philos[i]))
			return (my_err("PTHREAD ERROR!!!!!", 1));
		i++;
	}
	data->start_time = get_time(true, data);
	set_bool(&data->table_mtx, &data->all_ready, true, data);
	// need to implement watchdog!!!
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}
