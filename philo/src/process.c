/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:46:14 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 00:38:30 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*a_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->needs2eat != 0)
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

int	data_process(t_data **data_result)
{
	t_data	*data;
	int		i;

	data = *data_result;
	i = 0;
//	data->start_time = gettimeofday();
	while (i < data->philo_num)
	{
		pthread_create(&data->philos[i].thread_id, NULL, a_philo,
			&data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}
