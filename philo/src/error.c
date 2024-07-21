/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:34:42 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/21 20:40:52 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// Since we can't use exit function i return 1 as an error indicator!!
int	err_arguments(void)
{
	printf("Error!\n4 or 5 arguments needed for calculation!\n");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep\n");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

int	err_wrong_arg(t_data **data)
{
	if (*data != NULL)
		free(*data);
	else
		return (1);
	printf("Error!\nProgram cannot take these arguments!\n");
	printf("Arguments should only be positive numbers\n");
	printf("They cant be more than INT_MAX or equal to 0\n");
	return (1);
}

int	my_err(char *str, int for_return)
{
	printf("%s\n", str);
	return (for_return);
}
