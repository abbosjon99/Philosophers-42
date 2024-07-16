/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:46:14 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/16 21:19:30 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"


void *one_philo(void **arg) 
{
  t_data *data = *(t_data **)arg;

  pthread_mutex_lock(data->forks[0].fork);
  pthread_mutex_lock(data->forks[1].fork);

  unsigned long i = 0;
  printf("\n Job 1 has started by thread \n");

  for (i = 0; i < (0xFFFFFFFF); i++)
    ;

  printf("\n Job 1 has finished by thread \n");

  // Unlock both mutexes
  pthread_mutex_unlock(data->forks[1].fork);
  pthread_mutex_unlock(data->forks[0].fork);

  return NULL;
}

int	data_process(t_data **data_result)
{
	t_data	*data;
	int i;

	data = *data_result;
	i = 0;
	// while (i < data->philo_num)
	// {
		
	// 	i++;
	// }
	one_philo((void **)data_result);
	return (0);
}