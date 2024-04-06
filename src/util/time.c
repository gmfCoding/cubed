#include <sys/time.h>
#include <inttypes.h>
#include <stddef.h>
#include <unistd.h>

int64_t	time_get_ms(void)
{
	int64_t			ms;
	struct timeval	time;
	// TODO: Remove for mandatory build
	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000.0;
	ms += time.tv_usec / 1000.0;
	return (ms);
}