/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:40:03 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:40:04 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	debug(t_coder *coder)
{
	int	result;

	print_state(coder, "is debugging");
	smart_sleep(coder, coder->config->time_to_debug);
	result = check_sim_state(coder);
	if (result)
		return (SUCCESS);
	return (FAILURE);
}
