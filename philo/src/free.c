/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:51:28 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/21 20:24:40 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

//All data in a big container so we just free it
int	free_data(t_data **all_data, int return_val)
{
	t_data	*data;
	int		i;

	data = *all_data;
	if (data)
	{
		if (data->philos)
			free(data->philos);
		if (data->forks)
		{
			i = 0;
			while (i < data->philo_num)
			{
				if (data->forks[i].fork)
					free(data->forks[i].fork);
				i++;
			}
			free(data->forks);
		}
		free(data);
	}
	return (return_val);
}
