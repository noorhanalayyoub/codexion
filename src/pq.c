/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:08:30 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:08:31 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_pq	*init_pq(size_t capacity)
{
	t_pq	*pq;

	if (capacity == 0)
		return (NULL);
	pq = malloc(sizeof(t_pq));
	if (!pq)
		return (NULL);
	pq->heap = malloc(sizeof(t_node) * capacity);
	if (!pq->heap)
	{
		free(pq);
		return (NULL);
	}
	pq->capacity = capacity;
	pq->count = 0;
	pq->ticket = 1;
	return (pq);
}

void	free_pq(t_pq *pq)
{
	if (!pq)
		return ;
	if (pq->heap)
		free(pq->heap);
	free(pq);
}

bool	pq_insert(t_pq *pq, int value, size_t priority)
{
	if (!pq)
		return (false);
	if (pq->count >= pq->capacity)
		return (false);
	pq->heap[pq->count].value = value;
	pq->heap[pq->count].priority = priority;
	pq->heap[pq->count].ticket_id = pq->ticket++;
	pq->count++;
	pq_sift_up(pq, pq->count - 1);
	return (true);
}

bool	pq_pop(t_pq *pq, int *id)
{
	if (!pq || !id || pq_is_empty(pq))
		return (false);
	*id = pq->heap[0].value;
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	pq_sift_down(pq);
	return (true);
}

bool	pq_remove(t_pq *pq, int value)
{
	size_t	i;
	int		popped;

	if (!pq)
		return (false);
	i = 0;
	while (i < pq->count && pq->heap[i].value != value)
		i++;
	if (i == pq->count)
		return (false);
	pq->heap[i].priority = 0;
	pq->heap[i].ticket_id = 0;
	pq_sift_up(pq, i);
	return (pq_pop(pq, &popped));
}
