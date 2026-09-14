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
}t_config;

struct s_coder{
    char *state;
    int time_to_burnout;
    int id;
    int compiles_left;
    int time_of_last_compile;
};

void init_config(char **args, t_config* config);

#endif
