/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:39:28 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:39:30 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	enqueue(t_coder *coder)
{
	long long	priority;

	priority = get_coder_priority(coder);
	pq_insert(coder->left->waiters, coder->number, priority);
	pq_insert(coder->right->waiters, coder->number, priority);
}

static void	leave_queues(t_coder *coder)
{
	pq_remove(coder->left->waiters, coder->number);
	pq_remove(coder->right->waiters, coder->number);
}

static void	take_one(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->state = BUSY;
	pthread_mutex_unlock(&dongle->mutex);
}

static void	grant(t_coder *coder)
{
	take_one(coder->left);
	take_one(coder->right);
	leave_queues(coder);
	pthread_mutex_lock(&coder->config->simulation_mutex);
	coder->time_of_last_compile = get_time_ms();
	pthread_mutex_unlock(&coder->config->simulation_mutex);
}

t_value	acquire_dongles(t_coder *coder)
{
	t_config	*config;

	config = coder->config;
	pthread_mutex_lock(&config->table_mutex);
	if (!check_sim_state(coder))
	{
		pthread_mutex_unlock(&config->table_mutex);
		return (FAILURE);
	}
	enqueue(coder);
	wait_turn(coder);
	if (!check_sim_state(coder))
	{
		leave_queues(coder);
		pthread_mutex_unlock(&config->table_mutex);
		return (FAILURE);
	}
	grant(coder);
	pthread_mutex_unlock(&config->table_mutex);
	return (SUCCESS);
}
