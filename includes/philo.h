/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:13:53 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/21 15:08:47 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_main	t_main;
typedef struct s_phil	t_phil;

# define MAX_INT	2147483647
# define MIN_INT	-2147483648

struct s_main
{
	int				num_philo;
	int				ready;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				must_eat;
	int				chk_meal;
	int				over;
	long long		start;
	pthread_mutex_t	*death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex_rdy;
	pthread_mutex_t	*mutex_over;
	pthread_mutex_t	*mutex_die;
};

struct s_phil
{
	int				tid;
	int				is_die;
	int				eat_num;
	long long		t_start;
	long long		meal;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_main			*main;
};

int			ft_atoi(const char *str);
int			error_free(char *str, t_main *main, t_phil *philo, int cnt);
void		ft_error_arg(void);
int			init_input(t_main *main, int argc, char *argv[]);
void		init_philo(t_main *main, t_phil *philo);
int			init_thread(t_main *main, t_phil *philo);
long long	get_time(void);
int			philo_start(t_main *main);
int			ft_usleep(int time);
int			philo_start(t_main *main);
void		*philo_loop(void *ptr);
void		check_thread(t_main *main, t_phil *philo);
void		print_state(t_phil *philo, char *str);
void		thread_end(t_main *main, t_phil *philo);
int			check_rdy(t_main *main);
int			check_over(t_main *main);

#endif
