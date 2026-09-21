#include "codexion.h"

void* monitor(void* config)
{
    while(1)
    {
        int i;
        i = 0;
        while(i < config->number_of_coders)
        {
            if(config->time_to_burnout == get_time_ms() -config->coders[i].time_of_last_compile ){
                printf("a coder burned out\n");
                config->state_of_sim = 0;
                return
        }
}
