/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:53:19 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/21 15:11:52 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_phil *philo, char *str)
{
	pthread_mutex_lock(philo->main->death);
	if (check_over(philo->main))
	{
		pthread_mutex_unlock(philo->main->death);
		return ;
	}
	printf("%lld %d %s\n", get_time() - philo->t_start, philo->tid, str);
	pthread_mutex_unlock(philo->main->death);
}

void	sleep_think(t_phil *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->main->t_slp);
	print_state(philo, "is thinking");
}

void	eating(t_phil *philo)
{
	pthread_mutex_lock(philo->left);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right);
	print_state(philo, "has taken a fork");
	philo->meal = get_time();
	print_state(philo, "is eating");
	ft_usleep(philo->main->t_eat);
	philo->eat_num++;
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	*philo_loop(void *job)
{
	t_phil	*philo;

	philo = (t_phil *)job;

	while (!check_rdy(philo->main))
		continue ;
	if ((philo->tid & 1) == 0)
		ft_usleep(philo->main->t_eat * 0.9 + 1);
	while (!check_over(philo->main))
	{
		eating(philo);
		sleep_think(philo);
	}
	return (NULL);
}

int	philo_start(t_main *main)
{
	t_phil	*philo;

	philo = malloc(sizeof(t_phil) * main->num_philo);
	if (!philo)
		return (1);
	init_philo(main, philo);
	if (init_thread(main, philo))
		return (1);
	check_thread(main, philo);
	thread_end(main, philo);
	return (0);
}
