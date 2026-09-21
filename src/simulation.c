#include "codexion.h"
int compile(t_coder *coder)
{
    
}

int debug(t_coder *coder)
{
}

int refactor(t_coder *coder)
{
}

void* routine(void *coder)
{
   compile(coder);
   debug(coder);
   refactor(coder);
}
int simulate(char **args)
{   
    t_config config;
    int i;
    init_config(args, &config);
    config.dongles = init_dongles(&config);
    config.coders = init_coders(&config, config.dongles);
    if (config.coders == NULL || config.dongles == NULL)
        return (FAILURE);
    i = 0;
    while(i <config.number_of_coders)
    {
        if(pthread_create(&config.coders[i].thread,NULL, routine,&config.coders[i]))
            return (FAILURE);
        i++;
    }
    // errro handling 
    return (SUCCESS);
}
