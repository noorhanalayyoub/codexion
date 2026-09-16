#include "codexion.h"

int main (int argc, char **argv)
{
    if (argc != 9){
        printf("number of command line arguments must be exactly 8\n");
        printf("usage: /.codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler");
        return 0;
    }
    else{
        int return_value;
        return_value=parsing_args(argv);
        if (return_value == -1){
            printf("invalid number\n");
            return 0;
        }
        if (!strcmp(argv[8],"fifo") && !strcmp(argv[8], "edf"))
        {
            printf("invalid scheduler\n");
            return 0;
        }
//    t_config config;
 //   init_config(argv, &config);
    }
        
}
