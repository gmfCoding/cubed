
#include "cubed.h"

int error_with(char *msg, int value, int print_error)
{
	if (print_error)
		fprintf(stderr, "Error\n");
	if (msg)
		fprintf(stderr, "- %s :", msg);
	return(value);
}

int error_return(char *msg, int exit_code, int print_error, void **free)
{
	if (print_error)
		fprintf(stderr, "Error\n");
	if (msg && ft_strncmp(msg, "::") == 0)
	{
		fprintf(stderr, "- %s :", msg);
		deallocate_list(free);
		exit(exit_code);
	}
	if (msg)
		fprintf(stderr, "- %s :", msg);
	exit(exit_code);
}
