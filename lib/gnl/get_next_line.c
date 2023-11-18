/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:34:27 by clovell           #+#    #+#             */
/*   Updated: 2023/04/19 16:11:08 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct s_state
{
	char	*store;
	char	*prev;
	int		prev_fd;
	int		remaining;
}			t_state;

static char	*clear_state(t_state *state, int prev)
{
	if (prev && state->prev)
		free(state->prev);
	if (state->store)
		free(state->store);
	state->store = NULL;
	state->prev_fd = -1;
	return (NULL);
}

static void	concat(char **dest, char *start, char *second)
{
	char	*old;

	old = *dest;
	if (old == NULL)
		start = "";
	if (second == NULL)
		second = "";
	*dest = gnl_strjoin(start, second);
	if (old != NULL)
		free(old);
}

static char	*setup_state(t_state *state)
{
	char	*nlloc;
	int		i;

	if (state->store != NULL)
	{
		nlloc = gnl_strchr(state->store, '\n');
		if (nlloc)
			concat(&state->store, nlloc + 1, "");
		return (state->store);
	}
	state->remaining = 0;
	state->store = malloc(BUFFER_SIZE * sizeof(char));
	if (!state->store)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		state->store[i] = 0;
		i++;
	}
	return (state->store);
}

static void	*read_state(int fd, int *success, ssize_t *size, t_state *state)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*nlloc;

	nlloc = gnl_strchr(state->store, '\n');
	if (nlloc)
		*size = 1;
	while (!nlloc)
	{
		*size = read(fd, buffer, BUFFER_SIZE);
		if (*size < 0)
			return (NULL);
		if (*size == 0)
			break ;
		state->remaining += *size;
		*success = 1;
		buffer[*size] = 0;
		concat(&state->store, state->store, buffer);
		if (!state->store)
			return (NULL);
		nlloc = gnl_strchr(buffer, '\n');
	}
	return ((void *)0x1);
}

char	*get_next_line(int fd)
{
	static t_state	state;
	ssize_t			size;
	char			*nlloc;
	int				success;

	success = 0;
	nlloc = NULL;
	if (fd != state.prev_fd)
		clear_state(&state, 0);
	success = !(fd < 0 || !setup_state(&state));
	if (!success || !read_state(fd, &success, &size, &state))
		return (clear_state(&state, 0));
	state.prev_fd = fd;
	nlloc = gnl_strchr(state.store, '\n');
	if (!nlloc)
		nlloc = gnl_strchr(state.store, '\0');
	if (state.remaining <= 0)
		return (clear_state(&state, 0));
	state.prev = gnl_strldup(state.store, (nlloc - state.store) + !!*nlloc);
	if (state.prev == NULL)
		return (clear_state(&state, 0));
	state.remaining -= 1;
	if (nlloc - state.store > 0)
		state.remaining -= ((nlloc + 1) - state.store) - 1;
	return (state.prev);
}
