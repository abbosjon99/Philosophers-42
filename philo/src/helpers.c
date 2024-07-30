/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:10:51 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/30 02:58:44 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_stats(t_ph *ph, t_print option)
{
	long	timestamp;

	if (pthread_mutex_lock(&ph->data->ready_mtx))
		set_get_err(ph->data, true, SET);
	timestamp = get_time(true, ph->data) - ph->data->start_time;
	if (option == DIED && !set_get_err(ph->data, false, GET))
		printf("%-6ld %d died\n", timestamp, ph->id);
	else if (set_get_over(ph->data, false, GET) || set_get_err(ph->data, false,
			GET))
		;
	else if (option == FORK)
		printf("%-6ld %d has taken a fork\n", timestamp, ph->id);
	else if (option == EAT)
		printf("%-6ld %d is eating\n", timestamp, ph->id);
	else if (option == SLEEP)
		printf("%-6ld %d is sleeping\n", timestamp, ph->id);
	else if (option == THINK)
		printf("%-6ld %d is thinking\n", timestamp, ph->id);
	if (pthread_mutex_unlock(&ph->data->ready_mtx))
		set_get_err(ph->data, true, SET);
}

// how many milliseconds we need to sleep
void	pro_sleep(long need2sleep, t_data *data)
{
	long	start;
	long	remaining;

	start = get_time(false, data);
	need2sleep *= 1e3;
	while (get_time(false, data) - start < need2sleep)
	{
		if (set_get_over(data, true, GET) || set_get_err(data, true, GET))
			return ;
		remaining = need2sleep - (get_time(false, data) - start);
		if (remaining > 1e3)
			usleep(remaining / 2);
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
		set_get_err(data, true, SET);
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
