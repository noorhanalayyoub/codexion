/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:48:50 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:48:52 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	refactor(t_coder *coder)
{
	int	result;

	print_state(coder, "is refactoring");
	smart_sleep(coder, coder->config->time_to_refactor);
	result = check_sim_state(coder);
	if (result)
		return (SUCCESS);
	return (FAILURE);
}
