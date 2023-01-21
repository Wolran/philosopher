/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:14:58 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/21 16:16:46 by vmuller          ###   ########.fr       */
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
