/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:14:19 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/03 17:48:02 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <inttypes.h>
#include <stddef.h>
#include <unistd.h>
#include "cubed.h"

void time_debug_start(t_timedebug *state, char *name)
{
	state->start = time_get_us();
	state->name = name;
}

void time_debug_stop(t_timedebug *state)
{
	int64_t now = time_get_us();
	state->elapsed = now - state->start;
	printf("%s took %f ms\n", state->name, (float)(state->elapsed / 1000.0f));
}

// TODO: Remove for mandatory build
int64_t	time_get_us(void)
{
	int64_t			ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 10000000.0;
	ms += time.tv_usec;
	return (ms);
}

// TODO: Remove for mandatory build
int64_t	time_get_ms(void)
{
	int64_t			ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000.0;
	ms += time.tv_usec / 1000.0;
	return (ms);
}
