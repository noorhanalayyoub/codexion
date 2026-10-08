/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:06:46 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:06:48 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	smart_sleep(t_coder *coder, long long time_in_ms)
{
	long long	started;

	started = get_time_ms();
	while (get_time_ms() - started < time_in_ms)
	{
		usleep(500); // usleep is jsut sleep in microseconds
		pthread_mutex_lock(&coder->config->simulation_mutex);
		if (!coder->config->state_of_sim)
		{
			pthread_mutex_unlock(&coder->config->simulation_mutex);
			return ;
		}
		pthread_mutex_unlock(&coder->config->simulation_mutex);
	}
}
