#include "codexion.h"

void	init_pq(t_pq *priority_queue)
{
	priority_queue->head = NULL;
	priority_queue->last = NULL;
	priority_queue->length = 0;
}
// i want to initialize the pq
// add the first element and work from there
// priority is determined by time of arrival (request for resource)
// i must add a value to priority idk how
void	init_node(t_node *node, t_coder *coder, int priority)
{
	node->value = coder->number;
	node->next = NULL;
	node->priority = priority;
}

int	append_element(t_pq *priority_queue, t_coder *coder)
{
	int		priority;
	t_node	*temp_node;
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return (FAILURE);
	priority = priority_queue->length;
	init_node(new_node, coder, priority); // send this node by ref
	if (!priority_queue->length)
	{
		priority_queue->length++;
		priority_queue->head = new_node;
		priority_queue->last = new_node;
	}
	else
	{
		temp_node = priority_queue->last;
		temp_node->next = new_node;
		priority_queue->last = new_node;
		priority_queue->length++;
	}
	// aooend to th end and move last pointer
	return (SUCCESS);
}

int	extract(t_pq *priority_queue)
{
	int		result;
	t_node	*old_head;

	if (priority_queue->head == NULL)
		return (FAILURE);
	old_head = priority_queue->head;
	result = old_head->value;
	priority_queue->head = old_head->next;
	priority_queue->length--;
	if (priority_queue->length == 0)
		priority_queue->last = NULL;
	free(old_head);
	return (result);
	// remove the first element an dchnage head pointer
}
