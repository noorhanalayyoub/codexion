/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:39:28 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:39:30 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	release_one(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->state = FREE;
	dongle->released_at = get_time_ms();
	pthread_mutex_unlock(&dongle->mutex);
}

void	wake_all_waiters(t_config *config)
{
	pthread_mutex_lock(&config->table_mutex);
	pthread_cond_broadcast(&config->table_cond);
	pthread_mutex_unlock(&config->table_mutex);
}

void	release_dongles(t_coder *coder)
{
	release_one(coder->left);
	release_one(coder->right);
	wake_all_waiters(coder->config);
}
