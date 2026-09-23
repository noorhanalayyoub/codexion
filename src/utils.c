#include "codexion.h"

long long    get_time_ms(void)
{
    long long        time;
    struct timeval    tv;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    return (time);
}
void	ft_putstr_fd(char *message, int fd)
{
	write(fd, message, strlen(message));
}
