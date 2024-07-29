/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:38 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 11:00:30 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Since we are not allowed to use exit, we should handle it with diff cases
int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 5 && argc != 6)
		return (err_arguments());
	if (!load_argv(&data, argc, argv))
		return (err_wrong_arg(&data));
	if (initialize(data))
		return (free_data(&data, 1));
	if (data_process(data))
		return (free_data(&data, 1));
	return (free_data(&data, 0));
}
