#include "codexion.h"

int	main(int argc, char **argv)
{
		int return_value;

	if (argc != 9)
	{
		printf("number of command line arguments must be exactly 8\n");
		printf("usage:/.codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler");
		return (1);
	}
	else
	{
		return_value = parsing_args(argv);
		if (return_value == FAILURE)
		{
			printf("invalid number\n");
			return (1);
		}
		if (strcmp(argv[8], "fifo") && strcmp(argv[8], "edf"))
		{
			printf("invalid scheduler\n");
			return (1);
		}
        if (atoi(argv[1]) == 1)
        {
        printf("number of coders cant be zero\n");
        return (1);
        }
		simulate(argv);
	}
}
