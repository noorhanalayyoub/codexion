#include "codexion.h"

int simulate(char **args)
{   
    t_config config;
    t_coder* coders;
    t_dongle* dongles;
    init_config(args, &config);
    coders = init_coders(&config);
    dongles = init_dongles(&config);
    if (coders == NULL || dongles == NULL)
        return (FAILURE);

}
