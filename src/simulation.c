/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:34:48 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:34:50 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*routine(void *uncasted_coder)
{
	t_coder	*coder;
	int		compiles_required;

	coder = (t_coder *)uncasted_coder;
	compiles_required = coder->compiles_left;
	if (coder->config->number_of_coders == 1)
	{
		pthread_mutex_lock(&coder->left->mutex);
		printf("dongle acquired\n");
		printf("then you kys\n");
		smart_sleep(coder, coder->time_to_burnout);
		pthread_mutex_unlock(&coder->left->mutex);
	}
	while (compiles_required)
	{
		compile(coder);
		debug(coder);
		refactor(coder);
		compiles_required--;
		if (!check_sim_state(coder))
			break ;
	}
	return (NULL);
}

static int	start_coders(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		if (pthread_create(&config->coders[i].thread, NULL, routine,
				&config->coders[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	join_all(t_config *config, pthread_t monitor_thread)
{
	int	i;
	int	join_failed;

	join_failed = 0;
	if (pthread_join(monitor_thread, NULL))
		join_failed = 1;
	i = 0;
	while (i < config->number_of_coders)
	{
		if (pthread_join(config->coders[i].thread, NULL))
			join_failed = 1;
		i++;
	}
	return (join_failed);
}

int	simulate(char **args)
{
	t_config	config;
	pthread_t	monitor_thread;

	init_config(args, &config);
	config.dongles = init_dongles(&config);
	config.coders = init_coders(&config, config.dongles);
	if (config.coders == NULL || config.dongles == NULL)
		return (FAILURE);
	if (start_coders(&config) == FAILURE)
		return (FAILURE);
	if (pthread_create(&monitor_thread, NULL, monitor, &config))
		return (FAILURE);
	if (join_all(&config, monitor_thread))
	{
		cleanup(&config);
		return (FAILURE);
	}
	cleanup(&config);
	return (SUCCESS);
}
