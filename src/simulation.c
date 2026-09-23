#include "codexion.h"
#include <pthread.h>
// monitor routien for monitor thread
int compile(t_coder *coder)
{
printf("compiling\n");    
return (SUCCESS);
}


int debug(t_coder *coder)
{
    printf("debugging\n");
    int result;
    smart_sleep(coder, coder->config->time_to_debug);
    check_sim_state(coder);
    if(result)
        return (SUCCESS);
    return (FAILURE);
    // the issue with this version
    // checking and sleeping arent parallel
    // checking happens after sleeping is done 
    // theres delay
 
}

int refactor(t_coder *coder)
{
    printf("refactoring\n");
    long long started;
    started = get_time_ms();
    while(get_time_ms() - started < coder->config->time_to_refactor)
    {
        pthread_mutex_lock(&coder->config->simulation_mutex);
        if(!coder->config->state_of_sim){
        pthread_mutex_unlock(&coder->config->simulation_mutex);
            return (FAILURE);
        }
        pthread_mutex_unlock(&coder->config->simulation_mutex);
    }
    return (SUCCESS);
}

void* routine(void *uncasted_coder)
{   t_coder* coder;
    coder = (t_coder*) uncasted_coder;
    if (coder->config->number_of_coders == 1)
    {
        pthread_mutex_lock(&coder->left->mutex);
        printf("dongle acquired\n");
        printf("then you kys\n");
        smart_sleep(coder,coder->time_to_burnout);
    }
   compile(coder);
   debug(coder);
   refactor(coder);
}
int simulate(char **args)
{   
    t_config config;
    int i;
    pthread_t monitor_thread;
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
    pthread_create(&monitor_thread, NULL, monitor, &config); //this was isnide while loop    
            i = 0;
    while(i <config.number_of_coders)
    {
        if (pthread_join(config.coders[i].thread, NULL))
            return (FAILURE);
        i++;
    }
 
    // errro handling 
    return (SUCCESS);
}
