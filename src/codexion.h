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

typedef struct s_config{
int number_of_coders;
int time_to_burnout;
int time_to_compile;
int time_to_debug;
int time_to_refactor;
int number_of_compiles_required;
int dongle_cooldown;
char *scheduler;
int start_of_simulation;
}t_config;

typedef struct s_coder{
    int time_to_burnout;
    int number;
    int compiles_left;
    int time_of_last_compile;
}t_coder;

void init_config(char **args, t_config* config);
int init_coder(t_coder *coder, int i, t_config* config);
int init_threads(t_config *config);

#endif
