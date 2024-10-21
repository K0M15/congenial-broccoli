/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:50:38 by afelger           #+#    #+#             */
/*   Updated: 2024/10/21 11:29:08 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <assert.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif /* BUFFER_SIZE */

#ifndef STRING_BUFF_SIZE
# define STRING_BUFF_SIZE 1000
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
	return (*data);
}

void	shift_buffer(t_lasttime *data)
{
	size_t	count;

	count = 0;
	while(data->pos + count < data->filled)
	{
		data->buffer[count] = data->buffer[data->pos + count];
		count++;
	}
	data->filled -= count;
	data->pos = 0;
}

char	*get_string(t_lasttime *data)
{
	char *result;

	while(data->buffer[data->pos] != '\n')
		data->pos++;
	result = malloc(data->pos + 2);
	if (!result)
		return (NULL);
	data->pos = 0;
	while (data->buffer[data->pos] != '\n')
	{
		result[data->pos] = data->buffer[data->pos];
		data->pos++;
	}
	result[data->pos + 1] = '\n'; 
	result[data->pos + 2] = '\0';
	shift_buffer(data);
	return (result);
}

void	*read_into_buffer(t_lasttime *data, size_t amount, int fd)
{
	long long	amount_read;
	if (amount + data->pos > data->allocated)
		assert(0); // not implemented dynamic buffer scaling
	while(1)
	{
		if (amount + data->filled > data->allocated)
			assert(0); // not implemented dynamic buffer scaling
		amount_read = read(fd, &(data->buffer[data->filled]), amount);
		if (amount_read == -1)
			return (NULL);	//
		data->filled += amount_read;
		if ((size_t) amount_read != amount)
			assert(0); // Fileending, not implemented
		while(data->buffer[data->pos] != '\n' && data->pos < data->filled + 1)
			data->pos++;
		if (data->buffer[data->pos] == '\n')
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
