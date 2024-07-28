/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:47:11 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 00:37:35 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	init_helper(int i, t_data *data)
{
	t_philo	*philo;

	philo = &data->philos[i];
	philo->data = data;
	philo->id = i + 1;
	philo->full = false;
	philo->needs2eat = data->need2eat;
	if (i % 2 == 0)
	{
		philo->uno_fork = &data->forks[i];
		philo->dos_fork = &data->forks[(i + 1) % data->philo_num];
	}
	else
	{
		philo->dos_fork = &data->forks[i];
		philo->uno_fork = &data->forks[(i + 1) % data->philo_num];
	}
}

// initializing forks
// initializing philos
// assigning id to forks
// 1 if malloc or mutex error
////////////////////////////////MALLOC SHOULD BE DONE!!!!!!!!!
int	initialize(t_data *data)
{
	int	i;

	data->game_over = false;
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->philo_num);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (!data->forks || !data->philos)
		return (my_err("MALLOC ERROR!!!!!", 1));
	i = 0;
	while (i < data->philo_num)
	{
		data->forks[i].fork_id = i;
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (my_err("MUTEX ERROR!!!!!", 1));
		init_helper(i, data);
		i++;
	}
	return (0);
}
