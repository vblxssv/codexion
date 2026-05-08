#include "time_utils.h"
#include <sys/time.h>

long long	ft_get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
long long	ft_get_relative_time(long long start_time)
{
	return (ft_get_current_time() - start_time);
}
