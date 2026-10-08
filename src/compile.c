/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:39:28 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:39:30 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	pick_order(t_coder *coder, t_dongle **first, t_dongle **second)
{
	*first = coder->left;
	*second = coder->right;
	if (coder->number % 2 == 0)
	{
		*first = coder->right;
		*second = coder->left;
	}
}

static int	take_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
	if (request_dongle(coder, first) == FAILURE)
		return (FAILURE);
	print_state(coder, "has taken a dongle");
	if (request_dongle(coder, second) == FAILURE)
	{
		release_dongle(first);
		return (FAILURE);
	}
	print_state(coder, "has taken a dongle");
	return (SUCCESS);
}

static void	do_compile(t_coder *coder, t_dongle *first, t_dongle *second)
{
	print_state(coder, "is compiling");
	pthread_mutex_lock(&coder->config->simulation_mutex);
	coder->time_of_last_compile = get_time_ms();
	pthread_mutex_unlock(&coder->config->simulation_mutex);
	smart_sleep(coder, coder->config->time_to_compile);
	release_dongle(first);
	release_dongle(second);
	pthread_mutex_lock(&coder->config->simulation_mutex);
	coder->compiles_left--;
	pthread_mutex_unlock(&coder->config->simulation_mutex);
}

int	compile(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	pick_order(coder, &first, &second);
	if (take_dongles(coder, first, second) == FAILURE)
		return (FAILURE);
	do_compile(coder, first, second);
	return (SUCCESS);
}
