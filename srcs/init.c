/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:58:19 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/21 17:41:15 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thread(t_main *main, t_phil *philo)
{
	int	i;

	i = -1;
	while (++i < main->num_philo)
	{
		philo[i].right = philo[(i + 1) % main->num_philo].left;
		if (pthread_create(&philo[i].thread, NULL, \
		&philo_loop, &philo[i]) == -1)
			return (error_free("Error\n", main, philo, main->num_philo));
	}
	i = -1;
	main->start = get_time();
	while (++i < main->num_philo)
	{
		philo[i].t_start = main->start;
		philo[i].meal = main->start;
	}
	if (main->num_philo == 1)
		print_state(philo, "has taken a fork");
	pthread_mutex_lock(main->mutex_rdy);
	main->ready = 1;
	pthread_mutex_unlock(main->mutex_rdy);
	return (0);
}

void	init_philo(t_main *main, t_phil *philo)
{
	int	i;

	i = 0;
	while (i < main->num_philo)
	{
		philo[i].tid = i + 1;
		philo[i].eat_num = 0;
		philo[i].t_start = 0;
		philo[i].meal = 0;
		philo[i].main = main;
		philo[i].left = &main->forks[i];
		philo[i].is_die = 0;
		philo[i].right = 0;
		i++;
	}
}

int	init_mutexes(t_main *main)
{
	int	i;

	i = -1;
	main->death = 0;
	main->forks = 0;
	main->death = malloc(sizeof(pthread_mutex_t));
	main->mutex_rdy = malloc(sizeof(pthread_mutex_t));
	main->mutex_over = malloc(sizeof(pthread_mutex_t));
	main->mutex_die = malloc(sizeof(pthread_mutex_t));
	main->forks = malloc(sizeof(pthread_mutex_t) * main->num_philo);
	if (!main->death || !main->mutex_rdy || !main->mutex_over \
	|| !main->mutex_die || !main->forks)
		return (error_free("Error\n", main, 0, 0));
	if (pthread_mutex_init(main->death, NULL) == -1 \
	|| pthread_mutex_init(main->mutex_rdy, NULL) == -1 \
	|| pthread_mutex_init(main->mutex_over, NULL) == -1 \
	|| pthread_mutex_init(main->mutex_die, NULL) == -1)
		return (error_free("Error\n", main, 0, 0));
	while (++i < main->num_philo)
	{
		if (pthread_mutex_init(&main->forks[i], NULL) == -1)
			return (error_free("Error\n", main, 0, i));
	}
	return (0);
}

int	init_input(t_main *main, int argc, char *argv[])
{
	int	mutex;

	mutex = -1;
	main->num_philo = ft_atoi(argv[1]);
	main->t_die = ft_atoi(argv[2]);
	main->t_eat = ft_atoi(argv[3]);
	main->t_slp = ft_atoi(argv[4]);
	main->must_eat = -2;
	main->chk_meal = 0;
	main->start = 0;
	main->ready = 0;
	if (argc == 6)
	{
		main->chk_meal = 1;
		main->must_eat = ft_atoi(argv[5]);
	}
	main->over = 0;
	if (main->num_philo > 0)
		mutex = init_mutexes(main);
	return (mutex || main->num_philo <= 0 || main->t_die <= 0 \
	|| main->t_eat <= 0 || main->t_slp <= 0 || main->must_eat == 0);
}
