/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 02:09:30 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/16 08:46:21 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_die(t_phil *philo)
{
	print_state(philo, "is died");
	philo->main->over = 1;
	philo->is_die = 1;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (1);
}

int	check_death(t_phil *philo)
{
	long long	now;

	pthread_mutex_lock(philo->main->death);
	now = get_time() - philo->meal;
	if (now >= philo->main->t_die)
	{
		pthread_mutex_unlock(philo->main->death);
		return (philo_die(philo));
	}
	pthread_mutex_unlock(philo->main->death);
	return (0);
}

int	check_meal(t_phil philo, int idx)
{
	if (philo.main->chk_meal && idx == philo.main->num_philo - 1 && \
	philo.eat_num == philo.main->must_eat)
		return (ft_usleep(300));
	return (0);
}

void	check_thread(t_main *main, t_phil *philo)
{
	int	i;

	while (!main->ready)
		continue ;
	while (!main->over)
	{
		i = 0;
		while (i < main->num_philo)
		{
			if (check_death(&philo[i]) || check_meal(philo[i], i))
				main->over = 1;
			i++;
		}
	}
	if (main->chk_meal && philo[main->num_philo - 1].eat_num == main->must_eat)
	{
		ft_usleep(5 * main->num_philo);
		printf("eating %d times\n", main->must_eat);
	}
}

void	thread_end(t_main *main, t_phil *philo)
{
	int	i;

	i = 0;
	while (i < main->num_philo)
	{
		pthread_join(philo[i].thread, (void *)&philo[i]);
		i++;
	}
	pthread_mutex_destroy(main->death);
	free(main->death);
	i = 0;
	while (i < main->num_philo)
	{
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	free(main->forks);
	free(philo);
}
