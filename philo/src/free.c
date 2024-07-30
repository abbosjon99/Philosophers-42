/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:51:28 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/30 01:04:18 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	free_data_forks(t_data *data, int return_val)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->ph_num)
		{
			if (data->forks[i].fork_id != -1)
			{
				if (pthread_mutex_destroy(&data->forks[i].fork) != 0)
					return_val = my_err("MUTEX DESTROYING ERROR!!!!!", 1);
				i++;
			}
		}
		free(data->forks);
	}
	return (return_val);
}

static int	free_philos(t_data *data, int return_val)
{
	int	i;

	i = 0;
	if (data->phs)
	{
		while (i < data->ph_num)
		{
			if (data->phs[i].id != -1)
			{
				if (pthread_mutex_destroy(&data->phs[i].ph_mtx) != 0)
					return_val = my_err("MUTEX DESTROYING ERROR!!!!!", 1);
				i++;
			}
		}
		free(data->phs);
	}
	return (return_val);
}

// All data in a big container so we just free it
// Fork id is -1 if mutex is not initialized yet
int	free_data(t_data **all_data, int return_val)
{
	t_data	*data;

	data = *all_data;
	if (data)
	{
		if (data->data_err_mtx_init)
		{
			if (pthread_mutex_destroy(&data->table_mtx) != 0)
				return_val = my_err("MUTEX DESTROYING ERROR!!!!!", 1);
			if (data->data_err_mtx_init >= 2
				&& pthread_mutex_destroy(&data->table_mtx) != 0)
				return_val = my_err("MUTEX DESTROYING ERROR!!!!!", 1);
			if (data->data_err_mtx_init == 3
				&& pthread_mutex_destroy(&data->ready_mtx) != 0)
				return_val = my_err("MUTEX DESTROYING ERROR!!!!!", 1);
		}
		return_val = free_philos(data, return_val);
		return_val = free_data_forks(data, return_val);
		free(data);
	}
	return (return_val);
}

int	free_only_data(t_data **all_data, int return_val)
{
	t_data	*data;

	data = *all_data;
	if (data)
	{
		free(data);
	}
	return (return_val);
}
