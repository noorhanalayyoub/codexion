/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pq_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:06:27 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:06:37 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	is_first_worse(t_node *first, t_node *second)
{
	if (first->priority > second->priority
		|| (first->priority == second->priority
			&& second->ticket_id < first->ticket_id))
		return (true);
	return (false);
}

static void	pq_swap(t_node *a, t_node *b)
{
	t_node	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	pq_sift_up(t_pq *pq, size_t index)
{
	size_t	child_index;
	size_t	parent_index;
	t_node	*parent;
	t_node	*child;

	if (!pq)
		return ;
	child_index = index;
	while (child_index > 0)
	{
		parent_index = (child_index - 1) / 2;
		parent = &pq->heap[parent_index];
		child = &pq->heap[child_index];
		if (is_first_worse(parent, child))
		{
			pq_swap(parent, child);
			child_index = parent_index;
		}
		else
			break ;
	}
}

static size_t	find_min_child(t_pq *pq, size_t parent_index)
{
	size_t	left_index;
	size_t	right_index;
	t_node	*left_child;
	t_node	*right_child;

	left_index = 2 * parent_index + 1;
	right_index = 2 * parent_index + 2;
	if (right_index >= pq->count)
		return (left_index);
	left_child = &pq->heap[left_index];
	right_child = &pq->heap[right_index];
	if (is_first_worse(right_child, left_child))
		return (left_index);
	else
		return (right_index);
}

void	pq_sift_down(t_pq *pq)
{
	size_t	left;
	size_t	parent_index;
	size_t	min_child_index;
	t_node	*min_child;
	t_node	*parent;

	if (!pq)
		return ;
	parent_index = 0;
	left = (2 * parent_index + 1);
	while (left < pq->count)
	{
		parent = &pq->heap[parent_index];
		min_child_index = find_min_child(pq, parent_index);
		min_child = &pq->heap[min_child_index];
		if (is_first_worse(parent, min_child))
		{
			pq_swap(parent, min_child);
			parent_index = min_child_index;
			left = 2 * parent_index + 1;
		}
		else
			break ;
	}
}
