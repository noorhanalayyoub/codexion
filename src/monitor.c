#include "codexion.h"

void* monitor(void* uncasted_config)
{
    t_config *config = (t_config*)uncasted_config;
    int all_compiled;
    all_compiled = 1;
    while(1)
    {
        int i;
        i = 0;
        all_compiled = 1;
        while(i < config->number_of_coders)
        {
            if(config->time_to_burnout == get_time_ms() -config->coders[i].time_of_last_compile ){
                printf("coder %d burned out\n", i);
                config->state_of_sim = 0;
                return NULL;
            }
            if(config->coders[i].compiles_left)
                all_compiled = 0;
            i++;
        }
        if(all_compiled){
            config->state_of_sim = 1;
            return NULL;
        }


    }
}
