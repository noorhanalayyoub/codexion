#include "codexion.h"

void init_pq(t_pq* priority_queue)
{
   priority_queue->head = NULL;
   priority_queue->last = NULL;
   priority_queue->length = 0;
}
// i want to initialize the pq 
// add the first element and work from there 
// priority is determined by time of arrival (request for resource) 
// i must add a value to priority idk how 
void init_node(t_node* node, t_coder* coder, int priority)
{
    node->value = coder->number;
    node->next = NULL;
    node->priority = priority;
}
void append_element(t_pq* priority_queue,t_coder* coder)
{
    t_node current_node; // create a node 
    int priority;

    priority = priority_queue->length;
    init_node(&current_node, coder, priority); // send this node by ref
 if(!priority_queue->length){
        priority_queue->length++;
        priority_queue->head = current_node;
        priority_queue->last = current_node; 
 }
 else 
 {
     t_node* temp_node;
     temp_node = priority_queue->last;
     temp_node->next = current_node;
     priority_queue->last = current_node;
     priority_queue->length++;
    
 }
// aooend to th end and move last pointer
}

int extract(t_pq* priority_queue)
{
    int result;
    result = priority_queue->head->value;
    priority_queue->head = priority_queue->head->next;
    return result;
// remove the first element an dchnage head pointer 
}


