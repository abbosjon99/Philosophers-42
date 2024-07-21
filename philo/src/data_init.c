/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:47:11 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/21 20:34:18 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// initializing forks
// initializing philos
// assigning id to forks
////////////////////////////////MALLOC SHOULD BE DONE!!!!!!!!!
int	data_loader(t_data **data_result)
{
	t_data	*data;
	int		i;

	data = *data_result;
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->philo_num);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	i = 0;
	while (i < data->philo_num)
	{
		data->forks[i].fork_id = i;
		data->forks[i].fork = malloc(sizeof(t_pmt));
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		data->philos[i].needs2eat = data->need2eat;
		data->philos[i].r_fork = &data->forks[i];
		if (i + 1 < data->philo_num)
			data->philos[i].l_fork = &data->forks[i + 1];
		else
			data->philos[i].l_fork = &data->forks[i];
		i++;
	}
	return (0);
}
