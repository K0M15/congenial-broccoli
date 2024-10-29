/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:36:21 by afelger           #+#    #+#             */
/*   Updated: 2024/10/29 17:43:23 by afelger          ###   ########.fr       */
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
 * Concats one string to another, requres that src is the size of BUFFER_SIZE or less.
 * Input Memory will be free'd
 * @param dest	(char**) freeable string, zero terminated
 * @param src	(const char*) string of size BUFFER_SIZE
 * @return (int) 
 */
int		cat_and_free(char **dest, const char *src)
{
	int		dest_len;
	char	*dest_new;
	int		c;

	dest_len = ft_strlen(*dest) + 1;
	dest_new = malloc(dest_len + BUFFER_SIZE);
	c = 0;
	while(dest[c])
	{
		dest_new[c] = (*dest)[c];
		c++;
	}
	while(c - dest_len < BUFFER_SIZE)
		dest_new[c] = src[c - dest_len];
	dest_new[c] = 0;
	free(*dest);
	*dest = dest_new;
	return 0;
}

int	has_char(char *str, char c, int *pos)
{
	while (*str)
	{
		*pos = c - 1;
		if(*str == c)
			return (c-1);
		str++;
	}
	return (0);
}

int extract_string(char **str, char **remainder, int pos)
{
	char	*result;
	int		c;

	result = malloc(pos + 2);
	result[pos + 1] = 0;
	c = 0;
	while (c <= pos)
	{
		result[c] = (*str)[c];
		c++;
	}
	c = 1;
	while(str[pos + c] && c <= BUFFER_SIZE)
	{
		(*remainder)[c] = (*str)[pos+c];
		pos++;
	}
	free(*str);
	*str = result;
	return (c);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*str;
	int			pos;

	str = malloc(1);
	str[0] = 0;
	if (remainder == NULL)
	{
		remainder = malloc(BUFFER_SIZE + 1);
		if (remainder == NULL)
			return (NULL);
	}
	else
		cat_and_free(&str, remainder);
	while (!has_char(str, '\n', &pos))
	{
		if (read(fd, remainder, BUFFER_SIZE) == -1)
			return (NULL);
		if (remainder == NULL)
			assert(0); // Fileending
		cat_and_free(&str, remainder);
	}
	return (extract_string(&str, &remainder, pos), str);
}
