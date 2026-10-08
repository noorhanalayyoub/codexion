/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sim_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:06:07 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:06:10 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_sim_state(t_coder *coder)
{
	int	result;

	pthread_mutex_lock(&coder->config->simulation_mutex);
	result = coder->config->state_of_sim;
	pthread_mutex_unlock(&coder->config->simulation_mutex);
	return (result);
}
