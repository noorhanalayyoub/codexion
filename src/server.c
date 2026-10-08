/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:08:15 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:08:17 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_coder_priority(t_coder *coder)
{
	long long	deadline;

	if (!coder)
		return (-1);
	if (coder->config->scheduler == FIFO)
		return (0);
	deadline = coder->config->time_to_burnout + coder->time_of_last_compile;
	return (deadline);
}

static bool	check_coder_permission(t_coder *coder, t_dongle *dongle)
{
	return (check_sim_state(coder) == 1
		&& (coder->number != pq_peek(dongle->waiters) || dongle->state != FREE
			|| get_time_ms() < dongle->released_at + dongle->cooldown));
}

static void	timed_wait(t_dongle *dongle)
{
	struct timespec	ts;
	long long		remaining_cooldown;

	remaining_cooldown = dongle->released_at + dongle->cooldown;
	ts.tv_sec = remaining_cooldown / 1000;
	ts.tv_nsec = (remaining_cooldown % 1000) * 1000000;
	pthread_cond_timedwait(&dongle->dongle_cond, &dongle->mutex, &ts);
}

t_value	request_dongle(t_coder *coder, t_dongle *dongle)
{
	int	popped;

	pthread_mutex_lock(&dongle->mutex);
	pq_insert(dongle->waiters, coder->number, get_coder_priority(coder));
	while (check_coder_permission(coder, dongle))
	{
		if (get_time_ms() < dongle->released_at + dongle->cooldown)
			timed_wait(dongle);
		else
			pthread_cond_wait(&dongle->dongle_cond, &dongle->mutex);
	}
	if (check_sim_state(coder) == 0)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (FAILURE);
	}
	dongle->state = BUSY;
	popped = 1;
	pq_pop(dongle->waiters, &popped);
	pthread_mutex_unlock(&dongle->mutex);
	return (SUCCESS);
}

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->state = FREE;
	dongle->released_at = get_time_ms();
	pthread_cond_broadcast(&dongle->dongle_cond);
	pthread_mutex_unlock(&dongle->mutex);
}
