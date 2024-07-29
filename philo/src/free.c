/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:51:28 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 11:26:57 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	free_data_forks(t_data *data, int return_val)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->philo_num)
		{
			if (data->forks[i].fork_id != -1)
			{
				if (pthread_mutex_destroy(&data->forks[i].fork))
					return_val = my_err("MUTEX FREEING ERROR!!!!!", 1);
				i++;
			}
		}
		free(data->forks);
	}
	return (return_val);
}

// All data in a big container so we just free it
// Fork id is -1 if mutex is not initialized yet
int	free_data(t_data **all_data, int return_val)
{
	t_data	*data;
	int		i;

	data = *all_data;
	if (data)
	{
		if (data->philos)
			free(data->philos);
		if (data->table_error_mtx_init)
		{
			if (pthread_mutex_destroy(&data->table_mtx))
				return_val = my_err("MUTEX FREEING ERROR!!!!!", 1);
			if (data->table_error_mtx_init == 2
				&& pthread_mutex_destroy(&data->table_mtx))
				return_val = my_err("MUTEX FREEING ERROR!!!!!", 1);
		}
		return_val = free_data_forks(data, return_val);
		free(data);
	}
	return (return_val);
}
