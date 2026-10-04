#include "codexion.h"
/*
pq.c contains the implementatino for the interface that is visible to the user
these functions are everything the developer needs to know to use our PQ
they don't need to know anything about the helpers

so our functionality for this PQ simply is:
- init_pq: create the PQ
- free_pq: get rid of it
- pq_insert: add an element
- pq_pop: get the root element
- pq_is_empty: is our pq empty?

that's it, simple stuff!
*/
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

/*
pq_insert simply places the element in the next free spot in our array(at the end)
but it doesn't arrange it properly yet, it calls her helper function: pq_sift_up
this function will look at our new element, in a bottom-up approach, and will place it in the proper position
*/
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

/*
pq_pop will do something very rude, which is it will remove the top of our tree, the root
now, we have no root(belgium?), so what do we do?
we take the last element in our array, and we set it as root
but now our binary tree is not balanced, so now it's time for a helper function
the pq_sift_down will go through our binary tree in a top-down manner, balancing the tree
*/
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
