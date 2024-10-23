/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:50:38 by afelger           #+#    #+#             */
/*   Updated: 2024/10/23 12:15:01 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	shift_buffer(t_lasttime *data, long startpos)
{
	long	count;

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

int	get_string(t_lasttime *data, char **res, int endpos)
{
	size_t		counter;

	counter = 0;
	*res = malloc(endpos + 1);
	if (!*res)
		return (FT_IO_ERROR);
	while (data->buffer[counter] != '\n')
	{
		(*res)[counter] = data->buffer[counter];
		counter++;
	}
	(*res)[counter] = '\n'; 
	(*res)[counter + 1] = '\0';
	shift_buffer(data, counter + 1);
	return (FT_FOUND_STR);
}

int	read_into_buffer(t_lasttime *data, long amount, int fd)
{
	long long		amount_read;
	long			pos;
	
	while(1)
	{
		if (amount + data->filled > data->allocated)
			assert(0); // not implemented dynamic buffer scaling
		amount_read = read(fd, &(data->buffer[data->filled]), amount);
		if (amount_read == -1)
			return (FT_IO_ERROR);	//error
		data->filled += amount_read;
		if (amount_read != amount)
			return FT_EOF_FOUND;
		pos = 0;
		while(data->buffer[pos] != '\n' && pos < data->filled + 1)
			pos++;
		if (data->buffer[pos] == '\n')
			return FT_IO_SUCCESS;
	}
}

int	check_buffer_string(const t_lasttime *data, long *size)
{
	*size = 0;
	while(data->buffer[*size] != '\n' && data->buffer[*size] && *size < data->allocated)
		(*size)++;
	if (data->buffer[*size] != '\n')
		return (FT_FOUND_NO_STR);
	return (FT_FOUND_STR);
}

char	*handle_eof(t_lasttime *data)
{
	char	*lastline;
	long	count;

	if(data->filled == 0)
		return (NULL);
	if(check_buffer_string(data, &count) == FT_FOUND_STR)
	{
		if (get_string(data, &lastline, count) == FT_IO_ERROR)
			return (NULL);
	}
	else
	{
		lastline = malloc(count + 1);
		count = -1;
		while(++count < data->filled)
			lastline[count] = data->buffer[count];
		lastline[count] = 0;
		shift_buffer(data, count);
	}
	return (lastline);
}

void free_buffer(t_lasttime *data)
{
	free(data->buffer);
	free(data);
}

char	*get_next_line(int fd)
{
	static t_lasttime	*data;
	char				*res;
	int					status;
	long				len;
	
	if (fd <= -1 || read(fd, 0, 0))
		return (NULL);
	if (data == NULL)
		if(create_new_buffer(&data) == NULL)
			return (NULL);
	while(check_buffer_string(data, &len) == FT_FOUND_NO_STR)
	{
		status = read_into_buffer(data, BUFFER_SIZE, fd);
		if(status == FT_EOF_FOUND)
			return (handle_eof(data));
	}
	if (get_string(data, &res, len) == FT_FOUND_STR)
		return (res);
	return (NULL);
}
