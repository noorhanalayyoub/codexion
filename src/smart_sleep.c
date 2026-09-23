#include "codexion.h"

int smart_sleep(t_coder* coder, long long time_in_ms)
{
    long long time_in_micro;
    time_in_micro = time_in_ms * 1000;
    long long started;
    started = get_time_ms();
    while( get_time_ms() - started < time_in_ms){
    usleep(500); // usleep is jsut sleep in microseconds
    //check if anyone got burned in hell
    }
}
