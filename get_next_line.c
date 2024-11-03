/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:36:21 by afelger           #+#    #+#             */
/*   Updated: 2024/11/03 19:07:56 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	c;
	c = 0;
	while(str[c])
		c++;
	return (c);
}
/**
 * Concats one string to another, requres that src is the size of read_size or less.
 * Input Memory will be free'd
 * @param dest		(char**) freeable string, zero terminated
 * @param src		(const char*) string of size read_size
 * @param read_size	(int) length of src
 * @return (int) 
 */
int		cat_and_free(char **dest, const char *src, int read_size)
{
	int		dest_len;
	char	*dest_new;
	int		c;
	int		i;

	dest_len = ft_strlen(*dest) + 1;
	dest_new = malloc(dest_len + read_size);
	c = 0;
	while((*dest)[c])
	{
		dest_new[c] = (*dest)[c];
		c++;
	}
	i = 0;
	while(i < read_size)
	{
		dest_new[c + i] = src[i];
		i++;
	}
	dest_new[c + i] = 0;
	free(*dest);
	*dest = dest_new;
	return 0;
}

int	has_char(char *str, char c, int *pos)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(str[i] == c)
		{
			*pos = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int extract_string(char **str, char *remainder, int pos)
{
	char	*result;
	int		c;

	result = malloc(pos + 1);
	if (result == NULL)
	{
		*str = NULL;
		return (0);
	}
	result[pos] = 0;
	c = 0;
	while (c < pos)
	{
		result[c] = (*str)[c];
		c++;
	}
	result[c] = 0;
	c = 0;
	while((*str)[pos + c] && c < BUFFER_SIZE)
	{
		(remainder)[c] = (*str)[pos+c];
		c++;
	}
	if (c < BUFFER_SIZE)
		(remainder)[c] = 0;
	free(*str);
	*str = result;
	return (c);
}

void handle_eof(char **remainder, char **str)
{
	free(*remainder);
	*remainder = NULL;
	if((*str)[0] == 0)
	{
		free(*str);
		*str = NULL;
	}
}

int setup_remainder(char **remainder, char **str)
{
	int rem_length;

	if ((*remainder) == NULL)
	{
		rem_length = BUFFER_SIZE + 1;
		*remainder = malloc(rem_length);
		if (*remainder == NULL)
			return (0);
		while(--rem_length > -1)
			(*remainder)[rem_length] = 0;
	}
	*str = malloc(1);
	if (*str == NULL)
	{
		free(*remainder);
		*remainder = NULL;
		return (0);
	}
	(*str)[0] = 0;
	cat_and_free(str, *remainder, ft_strlen(*remainder));
	return (1);
}

void cleanup(char **remainder, char **str)
{
	free(*remainder);
	*remainder = NULL;
	free(*str);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*str;
	int			pos;
	int			status;

	if (read(fd, remainder, 0) == -1)
		cleanup();
		return (NULL);
	if (!setup_remainder(&remainder, &str))
		return (NULL);
	while (!has_char(str, '\n', &pos) && str)
	{
		status = read(fd, remainder, BUFFER_SIZE);
		if (status == -1)
		{
	// cleanup
			return (NULL);
		}
		else if (status == 0)
			return (handle_eof(&remainder, &str), str);
		cat_and_free(&str, remainder, status);
	}
	return (extract_string(&str, remainder, pos), str);
}
