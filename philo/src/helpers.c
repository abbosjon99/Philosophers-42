/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:10:51 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 20:47:48 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_stats(t_philo *philo, t_print option)
{
	long	timestamp;

	timestamp = get_time(true, philo->data) - philo->data->start_time;
	if (option == DIED && !set_get_error(philo->data, false, GET))
		printf("%-6ld %d died\n", timestamp, philo->id);
	else if (set_get_over(philo->data, false, GET)
		|| set_get_error(philo->data, false, GET))
		return ;
	if (option == FORK)
		printf("%-6ld %d has taken a fork\n", timestamp, philo->id);
	else if (option == EAT)
		printf("%-6ld %d is eating\n", timestamp, philo->id);
	else if (option == SLEEP)
		printf("%-6ld %d  is sleeping\n", timestamp, philo->id);
	else if (option == THINK)
		printf("%-6ld %d is thinking\n", timestamp, philo->id);
}

// how many milliseconds we need to sleep
void	pro_sleep(long need2sleep, t_data *data)
{
	long	start;
	long	rem;

	start = get_time(false, data);
	need2sleep *= 1e3;
	while (get_time(false, data) - start < need2sleep)
	{
		if (set_get_over(data, true, GET) || set_get_error(data, true, GET))
			return ;
		rem = need2sleep - (get_time(false, data) - start);
		if (rem > 1000)
			usleep(need2sleep / 2);
		else
		{
			while (get_time(false, data) - start < need2sleep)
				;
			return ;
		}
	}
}

// returns in milliseconds or microseconds
long	get_time(bool isit_millisecond, t_data *data)
{
	struct timeval	tval;

	if (gettimeofday(&tval, NULL))
	{
		set_get_error(data, true, SET);
		return (my_err("GETTIMEOFDAY ERROR!!!!!", 0));
	}
	if (isit_millisecond)
		return (tval.tv_sec * 1e3 + tval.tv_usec / 1e3);
	return (tval.tv_sec * 1e6 + tval.tv_usec);
}

void	till_all_ready(t_data *data)
{
	while (!get_bool(&data->table_mtx, &data->all_ready, data))
		;
}

// for setting the lastmeal
long	set_lastmeal(t_philo *philo, t_data *data)
{
	if (pthread_mutex_lock(&philo->philo_mtx))
	{
		set_get_error(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 1));
	}
	philo->last_meal = get_time(true, data);
	if (pthread_mutex_unlock(&philo->philo_mtx))
	{
		set_get_error(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 1));
	}
	return (0);
}
