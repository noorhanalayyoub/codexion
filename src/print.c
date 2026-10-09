/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:07:44 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:07:45 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_state(t_coder *coder, char *state)
{
	if (!check_sim_state(coder))
		return ;
	pthread_mutex_lock(&coder->config->print_mutex);
	if (!check_sim_state(coder))
	{
		pthread_mutex_unlock(&coder->config->print_mutex);
		return ;
	}
	printf("%lld %d %s\n", get_time_ms()
		- coder->config->start_of_simulation, coder->number, state);
	pthread_mutex_unlock(&coder->config->print_mutex);
}
