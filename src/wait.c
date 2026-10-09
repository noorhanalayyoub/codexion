/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:39:28 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:39:30 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long long	ready_at(t_dongle *dongle)
{
	long long	ready;

	pthread_mutex_lock(&dongle->mutex);
	ready = 0;
	if (dongle->state == FREE)
		ready = dongle->released_at + dongle->cooldown;
	pthread_mutex_unlock(&dongle->mutex);
	return (ready);
}

static void	wait_event(t_coder *coder)
{
	t_config		*config;
	struct timespec	ts;
	long long		wake_at;
	long long		other;

	config = coder->config;
	wake_at = ready_at(coder->left);
	other = ready_at(coder->right);
	if (other > wake_at)
		wake_at = other;
	if (wake_at <= get_time_ms())
	{
		pthread_cond_wait(&config->table_cond, &config->table_mutex);
		return ;
	}
	ts.tv_sec = wake_at / 1000;
	ts.tv_nsec = (wake_at % 1000) * 1000000;
	pthread_cond_timedwait(&config->table_cond, &config->table_mutex, &ts);
}

void	wait_turn(t_coder *coder)
{
	while (check_sim_state(coder) && !is_my_turn(coder))
		wait_event(coder);
}
