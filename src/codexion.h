#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

int parsing_args(char **args);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

typedef enum r_value{
    SUCCESS,
    FAILURE
}t_value;

typedef enum s_scheduler{
    FIFO,
    EDF
}t_scheduler;

typedef struct s_config{
int number_of_coders;
int time_to_burnout;
int time_to_compile;
int time_to_debug;
int time_to_refactor;
int number_of_compiles_required;
int dongle_cooldown;
t_scheduler scheduler;
int start_of_simulation;
}t_config;

typedef struct s_dongle{
    int state;
    int cooldown;
}t_dongle;

typedef struct s_coder{
    int time_to_burnout;
    int number;
    int compiles_left;
    int time_of_last_compile;
    pthread_t thread;
    t_dongle *left;
    t_dongle *right;
}t_coder;

void init_config(char **args, t_config* config);
int init_coder(t_coder *coder, int i, t_config* config);
int init_threads(t_config *config);

#endif
