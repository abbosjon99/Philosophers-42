/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:47:11 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 11:44:51 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	init_helper(int i, t_data *data)
{
	i = 0;
	while (i < data->philo_num)
	{
		data->forks[i].fork_id = -1;
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (my_err("MUTEX ERROR!!!!!", 1));
		data->forks[i].fork_id = i;
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		data->philos[i].needs2eat = data->need2eat;
		if (i % 2 == 0)
		{
			data->philos[i].uno_fork = &data->forks[i];
			data->philos[i].dos_fork = &data->forks[(i + 1) % data->philo_num];
		}
		else
		{
			data->philos[i].dos_fork = &data->forks[i];
			data->philos[i].uno_fork = &data->forks[(i + 1) % data->philo_num];
		}
		i++;
	}
	return (0);
}

// initializing forks
// initializing philos
// assigning id to forks
// 1 if malloc or mutex error
// I say fork id is -1 if mutex is not initialized yet
////////////////////////////////MALLOC SHOULD BE DONE!!!!!!!!!
int	initialize(t_data *data)
{
	int	i;

	data->over = false;
	data->all_ready = false;
	data->internal_error = false;
	data->table_error_mtx_init = 0;
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->philo_num);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (!data->forks || !data->philos)
		return (my_err("MALLOC ERROR!!!!!", 1));
	if (pthread_mutex_init(&data->table_mtx, NULL))
		return (my_err("MUTEX ERROR!!!!!", 1));
	data->table_error_mtx_init++;
	if (pthread_mutex_init(&data->error_mtx, NULL))
		return (my_err("MUTEX ERROR!!!!!", 1));
	data->table_error_mtx_init++;
	return (init_helper(i, data));
}
