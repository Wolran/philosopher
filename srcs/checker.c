/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 02:09:30 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/21 16:16:33 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_rdy(t_main *main)
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

int	check_over(t_main *main)
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
		return (usleep(50), 1);
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
