/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 02:09:30 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/21 15:49:37 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_die(t_phil *philo)
{
	print_state(philo, "died");
	pthread_mutex_lock(philo->main->mutex_over);
	philo->main->over = 1;
	pthread_mutex_unlock(philo->main->mutex_over);
	pthread_mutex_lock(philo->main->mutex_die);
	philo->is_die = 1;
	pthread_mutex_unlock(philo->main->mutex_die);
	return (1);
}

int check_rdy(t_main *main)
{
	pthread_mutex_lock(main->mutex_rdy);
	if (main->ready == 1)
	{
		pthread_mutex_unlock(main->mutex_rdy);
		return (1);
	}
	pthread_mutex_unlock(main->mutex_rdy);
	return (0);
}

int check_over(t_main *main)
{
	pthread_mutex_lock(main->mutex_over);
	if (main->over == 1)
	{
		pthread_mutex_unlock(main->mutex_over);
		return (1);
	}
	pthread_mutex_unlock(main->mutex_over);
	return (0);
}
/*
int check_die(t_phil *philo)
{
	pthread_mutex_lock(philo->main->mutex_die);
	if (philo->is_die == 1)
	{
		pthread_mutex_unlock(philo->main->mutex_die);
		return (1);
	}
	pthread_mutex_unlock(philo->main->mutex_die);
	return (0);
}
*/
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
		return (usleep(philo.main->t_slp), 1);
	return (0);
}

void	check_thread(t_main *main, t_phil *philo)
{
	int	i;

	while (!check_rdy(main))
		continue ;
	while (!check_over(main))
	{
		i = 0;
		while (i < main->num_philo)
		{
			if (check_death(&philo[i]) || check_meal(philo[i], i))
			{
				pthread_mutex_lock(philo->main->mutex_over);
				main->over = 1;
				pthread_mutex_unlock(philo->main->mutex_over);
			}
			i++;
		}
	}
	if (main->chk_meal && philo[main->num_philo - 1].eat_num == main->must_eat)
	{
		ft_usleep(main->num_philo);
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
	pthread_mutex_destroy(main->mutex_rdy);
	free(main->mutex_rdy);
	pthread_mutex_destroy(main->mutex_over);
	free(main->mutex_over);
	pthread_mutex_destroy(main->mutex_die);
	free(main->mutex_die);
	i = 0;
	while (i < main->num_philo)
	{
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	free(main->forks);
	free(philo);
}
