/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:07:17 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:07:18 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup_dongles(t_dongle *dongles, int number)
{
	int	index;

	index = 0;
	while (index < number)
	{
		free_pq(dongles[index].waiters);
		pthread_mutex_destroy(&dongles[index].mutex);
		index++;
	}
}

void	cleanup(t_config *config)
{
	free(config->coders);
	cleanup_dongles(config->dongles, config->number_of_coders);
	free(config->dongles);
	pthread_cond_destroy(&config->table_cond);
	pthread_mutex_destroy(&config->table_mutex);
	pthread_mutex_destroy(&config->print_mutex);
	pthread_mutex_destroy(&config->simulation_mutex);
}
