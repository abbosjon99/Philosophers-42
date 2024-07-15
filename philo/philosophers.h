/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:40:02 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/03 18:32:55 by akeldiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// number_of_philosophers	time_to_die	time_to_eat	time_to_sleep
// [number_of_times_each_philosopher_must_eat]

typedef struct s_fork	t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	bool				full;
	long				needs2eat;
	long				last_meal;
	t_fork				*l_fork;
	t_fork				*r_fork;
	struct s_philo		*philo_nxt;
}						t_philo;

typedef pthread_mutex_t	t_pmt;

struct					s_fork
{
	int					fork_id;
	t_pmt				fork;
};

typedef struct s_data
{
	long				philo_num;
	long				time2die;
	long				time2eat;
	long				time2sleep;
	long				need2eat;
	long				start_time;
	t_fork				*forks;
	t_philo				*philos;
}						t_data;

int						err_arguments(void);
int						load_argv(t_data **data_result, int argc, char **argv);
int						err_wrong_arg(t_data **data);

#endif
