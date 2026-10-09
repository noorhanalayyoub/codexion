/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:39:28 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:39:30 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_coder_priority(t_coder *coder)
{
	long long	deadline;

	if (coder->config->scheduler == FIFO)
		return (0);
	pthread_mutex_lock(&coder->config->simulation_mutex);
	deadline = coder->config->time_to_burnout + coder->time_of_last_compile;
	pthread_mutex_unlock(&coder->config->simulation_mutex);
	return (deadline);
}

static bool	dongle_usable(t_dongle *dongle)
{
	bool	usable;

	pthread_mutex_lock(&dongle->mutex);
	usable = false;
	if (dongle->state == FREE)
		usable = get_time_ms() >= dongle->released_at + dongle->cooldown;
	pthread_mutex_unlock(&dongle->mutex);
	return (usable);
}

static bool	coder_can_run(t_coder *coder)
{
	return (dongle_usable(coder->left) && dongle_usable(coder->right));
}

static bool	blocked_by_earlier(t_coder *coder, t_dongle *dongle)
{
	int	head;

	head = pq_peek(dongle->waiters);
	if (head == -1 || head == coder->number)
		return (false);
	return (coder_can_run(&coder->config->coders[head - 1]));
}

bool	is_my_turn(t_coder *coder)
{
	return (coder_can_run(coder)
		&& !blocked_by_earlier(coder, coder->left)
		&& !blocked_by_earlier(coder, coder->right));
}
