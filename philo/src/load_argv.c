/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:25:19 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/30 02:26:58 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// Initially checks the string and returns NULL if there any Error
// Null if it's not positive or more than length of 2147483647
// Returns first num in that string
static char	*point_to_num(char *str)
{
	short int	i;

	i = 0;
	if (!str)
		return (NULL);
	while ((8 < *str && *str < 14) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	if (*str < '0' || '9' < *str)
		return (NULL);
	while ('0' <= str[i] && str[i] <= '9')
	{
		i++;
		if (i > 10)
			return (NULL);
	}
	return (str);
}

// 0 is there any error
// our program should not take 0 as an argument btw
static long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = point_to_num(str);
	if (!str)
		return (0);
	while ('0' <= *str && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (num > INT_MAX)
		return (0);
	return (num);
}

// Function returns 0 if there any error
int	load_argv(t_data **data_result, int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (my_err("MALLOC ERROR!!!!!", 0));
	*data_result = data;
	data->phs = NULL;
	data->forks = NULL;
	data->ph_num = ft_atol(argv[1]);
	data->time2die = ft_atol(argv[2]);
	data->time2eat = ft_atol(argv[3]);
	data->time2sleep = ft_atol(argv[4]);
	data->need2eat = -1;
	if (argc == 6)
		data->need2eat = ft_atol(argv[5]);
	if (!data->ph_num || !data->time2die || !data->time2eat
		|| !data->time2sleep)
		return (0);
	return (1);
}
