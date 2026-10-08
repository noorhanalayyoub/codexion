#include "codexion.h"

t_pq* init_pq(size_t capacity)
{
    t_pq *pq;

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
    pq->ticket = 0;
    return (pq);
}

void free_pq(t_pq *pq)
{
    if (!pq)
        return ;
    if (pq->heap)
        free(pq->heap);
    free(pq);
}

bool pq_is_empty(t_pq* pq)
{
    if (!pq || pq->count == 0)
        return (true);
    return (false);
}

bool pq_insert(t_pq* pq, int value, size_t priority)
{
    if (!pq)
        return (false);
    if (pq->count >= pq->capacity)
        return (false);
    pq->heap[pq->count].value = value;
    pq->heap[pq->count].priority = priority;
    pq->heap[pq->count].ticket_id = pq->ticket++;
    pq->count++;
    pq_sift_up(pq);
    return (true);
}

bool pq_pop(t_pq* pq, int *id)
{
    if (!pq || !id || pq_is_empty(pq))
        return (false);
    *id = pq->heap[0].value;
    pq->count--;
    pq->heap[0] = pq->heap[pq->count];
    pq_sift_down(pq);
    return (true);
}

int pq_peek(t_pq *pq)
{
    if (!pq || pq_is_empty(pq))
        return (-1);
    return (pq->heap[0].value);
}
