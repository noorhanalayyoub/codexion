/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:25:28 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:25:30 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	announce_burnout(t_config *config, int i)
{
	pthread_mutex_lock(&config->print_mutex);
	printf("%lld %d burned out\n",
		get_time_ms() - config->start_of_simulation, i + 1);
	pthread_mutex_unlock(&config->print_mutex);
}

static int	check_coder(t_config *config, int i, int *all_compiled)
{
	pthread_mutex_lock(&config->simulation_mutex);
	if (config->time_to_burnout <= get_time_ms()
		- config->coders[i].time_of_last_compile)
	{
		config->state_of_sim = 0;
		pthread_mutex_unlock(&config->simulation_mutex);
		announce_burnout(config, i);
		wake_all_waiters(config);
		return (1);
	}
	if (config->coders[i].compiles_left > 0)
		*all_compiled = 0;
	pthread_mutex_unlock(&config->simulation_mutex);
	return (0);
}

static int	check_all_coders(t_config *config, int *all_compiled)
{
	int	i;

	i = 0;
	*all_compiled = 1;
	while (i < config->number_of_coders)
	{
		if (check_coder(config, i, all_compiled))
			return (1);
		i++;
	}
	return (0);
}

static void	end_simulation(t_config *config)
{
	pthread_mutex_lock(&config->simulation_mutex);
	config->state_of_sim = 0;
	pthread_mutex_unlock(&config->simulation_mutex);
	wake_all_waiters(config);
}

void	*monitor(void *uncasted_config)
{
	t_config	*config;
	int			all_compiled;

	config = (t_config *)uncasted_config;
	all_compiled = 1;
	while (1)
	{
		if (check_all_coders(config, &all_compiled))
			return (NULL);
		if (all_compiled)
		{
			end_simulation(config);
			return (NULL);
		}
		usleep(1000);
	}
}
