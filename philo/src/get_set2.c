/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:14:15 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 23:34:14 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	safe_mtx(t_pmt *mtx, t_data *data, t_lock_unlock option)
{
	if (option == LOCK)
	{
		if (pthread_mutex_lock(mtx))
		{
			set_get_err(data, true, SET);
			return (my_err("MUTEX ERROR!!!!!", 1));
		}
	}
	else if (option == UNLOCK)
	{
		if (pthread_mutex_unlock(mtx))
		{
			set_get_err(data, true, SET);
			return (my_err("MUTEX ERROR!!!!!", 1));
		}
	}
	return (0);
}

// for getting lastmeal
long	get_lastmeal(t_ph *philo, t_data *data)
{
	long	result;

	if (pthread_mutex_lock(&philo->ph_mtx))
	{
		set_get_err(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 0));
	}
	result = philo->last_meal;
	if (pthread_mutex_unlock(&philo->ph_mtx))
	{
		set_get_err(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 0));
	}
	return (result);
}

// for setting the lastmeal
long	set_lastmeal(t_ph *philo, t_data *data)
{
	if (pthread_mutex_lock(&philo->ph_mtx))
	{
		set_get_err(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 1));
	}
	philo->last_meal = get_time(true, data);
	if (pthread_mutex_unlock(&philo->ph_mtx))
	{
		set_get_err(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 1));
	}
	return (0);
}

// only for start
long	set_starttime(t_ph *philo, t_data *data)
{
	if (pthread_mutex_lock(&philo->ph_mtx))
	{
		set_get_err(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 1));
	}
	philo->last_meal = data->start_time;
	if (pthread_mutex_unlock(&philo->ph_mtx))
	{
		set_get_err(data, true, SET);
		return (my_err("MUTEX ERROR!!!!!", 1));
	}
	return (0);
}
