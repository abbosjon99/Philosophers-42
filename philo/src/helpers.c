/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:10:51 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 12:12:00 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	pro_sleep(long need2sleep, t_data *data)
{
	long	start;
	long	rem;

	start = get_time(false, data);
	while (get_time(false, data) - start < need2sleep)
	{
		if (!set_get_over(data, true, GET) && !set_get_error(data, true, GET))
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

// returns in milliseconds ot microseconds
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
