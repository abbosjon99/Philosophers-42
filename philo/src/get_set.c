/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:51:54 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 11:55:10 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	set_get_over(t_data *data, bool value, t_get_set get_set)
{
	if (pthread_mutex_lock(&data->table_mtx))
	{
		set_get_error(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", value));
	}
	if (get_set == SET)
		data->over = value;
	else
		value = data->over;
	if (pthread_mutex_unlock(&data->table_mtx))
	{
		set_get_error(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", value));
	}
	return (value);
}

// No possible way to check if pthread leads to error,
// since we are not allowed to use exit()
bool	set_get_error(t_data *data, bool value, t_get_set get_set)
{
	pthread_mutex_lock(&data->error_mtx);
	if (get_set == SET)
		data->internal_error = value;
	else
		value = data->internal_error;
	pthread_mutex_unlock(&data->error_mtx);
	return (value);
}

// for setting the value
int	set_bool(t_pmt *mtx, bool *dest, bool value, t_data *data)
{
	if (pthread_mutex_lock(mtx))
	{
		set_get_error(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 1));
	}
	*dest = value;
	if (pthread_mutex_unlock(mtx))
	{
		set_get_error(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 1));
	}
	return (0);
}

// for reading
bool	get_bool(t_pmt *mtx, bool *src, t_data *data)
{
	bool	result;

	if (pthread_mutex_lock(mtx))
	{
		set_get_error(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", *src));
	}
	result = *src;
	if (pthread_mutex_unlock(mtx))
	{
		set_get_error(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", result));
	}
	return (result);
}
