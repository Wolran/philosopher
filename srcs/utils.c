/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:53:50 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/21 16:11:23 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(int time)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time)
		usleep(50);
	return (1);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_error_arg(void)
{
	printf("Error: Bad Arg\n");
	exit(0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	j;
	int		n;

	i = 0;
	j = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			n = n * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + (str[i] - '0');
		i++;
	}
	if (j > MAX_INT || j < MIN_INT || str[i])
		ft_error_arg();
	return ((int)j * n);
}

int	error_free(char *str, t_main *main, t_phil *philo, int cnt)
{
	int	i;

	i = -1;
	if (main->num_philo > 0 && main->death)
	{
		pthread_mutex_destroy(main->death);
		free(main->death);
	}
	pthread_mutex_destroy(main->mutex_rdy);
	free(main->mutex_rdy);
	pthread_mutex_destroy(main->mutex_over);
	free(main->mutex_over);
	pthread_mutex_destroy(main->mutex_die);
	free(main->mutex_die);
	if (main->num_philo > 0 && main->forks)
	{
		while (++i < cnt)
			pthread_mutex_destroy(&main->forks[i]);
		free(main->forks);
	}
	if (philo)
		free(philo);
	printf("%s", str);
	return (1);
}
