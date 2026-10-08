/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pq_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:48:16 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:48:18 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	pq_peek(t_pq *pq)
{
	if (!pq || pq_is_empty(pq))
		return (-1);
	return (pq->heap[0].value);
}

bool	pq_is_empty(t_pq *pq)
{
	if (!pq || pq->count == 0)
		return (true);
	return (false);
}
