/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:50:38 by afelger           #+#    #+#             */
/*   Updated: 2024/10/21 16:47:18 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <assert.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif /* BUFFER_SIZE */

#ifndef STRING_BUFF_SIZE
# define STRING_BUFF_SIZE 2*1000*1000
#endif /* STRING_BUFF_SIZE */

void	*create_new_buffer(t_lasttime **data)
{
	*data = malloc(sizeof(t_lasttime));
	if (*data == NULL)
		return (NULL);
	(*data)->buffer = malloc(STRING_BUFF_SIZE);
	if ((*data)->buffer == NULL)
		return (NULL);
	(*data)->allocated = STRING_BUFF_SIZE;
	(*data)->filled = 0;
	return (*data);
}

void	shift_buffer(t_lasttime *data, size_t startpos)
{
	size_t	count;

	count = 0;
	while(startpos + count < data->filled)
	{
		data->buffer[count] = data->buffer[startpos + count];
		count++;
	}
	while(count < data->filled)
	{
		data->buffer[count] = 0;
		count++;
	}
	data->filled -= startpos;
}

int	get_string(t_lasttime *data, char **res)
{
	size_t		counter;

	counter = 0;
	while(data->buffer[counter] != '\n' && data->buffer[counter] && counter < data->allocated)
		counter++;
	if (data->buffer[counter] != '\n')
		return (0);
	*res = malloc(counter + 1);
	if (!*res)
		return (-1);
	counter = 0;
	while (data->buffer[counter] != '\n')
	{
		(*res)[counter] = data->buffer[counter];
		counter++;
	}
	(*res)[counter] = '\n'; 
	(*res)[counter + 1] = '\0';
	shift_buffer(data, counter + 1);
	return (1);
}

void	*read_into_buffer(t_lasttime *data, size_t amount, int fd)
{
	long long		amount_read;
	unsigned long	pos;
	
	while(1)
	{
		if (amount + data->filled > data->allocated)
			assert(0); // not implemented dynamic buffer scaling
		amount_read = read(fd, &(data->buffer[data->filled]), amount);
		if (amount_read == -1)
			return (NULL);	//error
		data->filled += amount_read;
		if ((size_t) amount_read != amount)
			assert(0); // Fileending, not implemented
		pos = 0;
		while(data->buffer[pos] != '\n' && pos < data->filled + 1)
			pos++;
		if (data->buffer[pos] == '\n')
		{
			return NULL;
		}
	}
}

void free_buffer(t_lasttime *data)
{
	free(data->buffer);
	free(data);
}

char	*get_next_line(int fd)
{
	static t_lasttime	*data;
	
	if (fd == -1)
		return (NULL);
	if (data == NULL)
		if(create_new_buffer(&data) == NULL)
			return (NULL);
	// do read into buffer
	// if lineend is detected, return line
	// cleanup buffer
	return "";
}
