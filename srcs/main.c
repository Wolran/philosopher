/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:16:10 by vmuller           #+#    #+#             */
/*   Updated: 2023/01/16 09:27:25 by vmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_main		main;

	memset(&main, 0, sizeof(main));
	if (argc > 6 || argc < 5 || init_input(&main, argc, argv))
		ft_error_arg();
	if (philo_start(&main))
		return (1);
	return (0);
}
