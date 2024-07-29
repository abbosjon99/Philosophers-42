/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:40:02 by akeldiya          #+#    #+#             */
/*   Updated: 2024/07/29 16:09:56 by akeldiya         ###   ########.fr       */
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
typedef struct s_data	t_data;

// needs2eat; // how many time philo needs to eat
typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	bool				full;
	long				needs2eat;
	long				last_meal;
	t_fork				*uno_fork;
	t_fork				*dos_fork;
	t_data				*data;
}						t_philo;

typedef pthread_mutex_t	t_pmt;

struct					s_fork
{
	int					fork_id;
	t_pmt				fork;
};

struct					s_data
{
	long				philo_num;
	long				time2die;
	long				time2eat;
	long				time2sleep;
	long				need2eat;
	long				start_time;
	bool				over;
	bool				all_ready;
	bool				internal_error;
	t_pmt				error_mtx;
	int					table_error_mtx_init;
	t_pmt				table_mtx;
	t_fork				*forks;
	t_philo				*philos;
};

typedef enum e_get_set
{
	GET,
	SET
}						t_get_set;

typedef enum e_print
{
	FORK,
	EAT,
	THINK,
	DIED
}						t_print;

int						err_arguments(void);
int						load_argv(t_data **data_result, int argc, char **argv);
int						err_wrong_arg(t_data **data);
int						initialize(t_data *data);
int						data_process(t_data *data);
int						free_data(t_data **all_data, int return_val);
int						my_err(char *str, int for_return);
int						set_bool(t_pmt *mtx, bool *dest, bool value,
							t_data *data);
long					get_time(bool isit_millisecond, t_data *data);
bool					get_bool(t_pmt *mtx, bool *src, t_data *data);
void					till_all_ready(t_data *data);
bool					set_get_error(t_data *data, bool value,
							t_get_set get_set);
bool					set_get_over(t_data *data, bool value,
							t_get_set get_set);
void					pro_sleep(long need2sleep, t_data *data);

#endif
