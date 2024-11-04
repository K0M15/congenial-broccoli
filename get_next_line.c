/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:36:21 by afelger           #+#    #+#             */
/*   Updated: 2024/11/04 15:25:01 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	extract_string(char **str, char *remainder, int pos)
{
	char	*result;
	int		c;

	result = malloc(pos + 1);
	if (result == NULL)
		return (ft_cleanup(str, &remainder), 0);
	result[pos] = 0;
	c = 0;
	while (c < pos)
	{
		result[c] = (*str)[c];
		c++;
	}
	result[c] = 0;
	c = 0;
	while ((*str)[pos + c] && c < BUFFER_SIZE)
	{
		(remainder)[c] = (*str)[pos + c];
		c++;
	}
	if (c < BUFFER_SIZE)
		(remainder)[c] = 0;
	free(*str);
	*str = result;
	return (1);
}

void	handle_eof(char **remainder, char **str)
{
	free(*remainder);
	*remainder = NULL;
	if ((*str)[0] == 0)
	{
		free(*str);
		*str = NULL;
	}
}

int	setup_remainder(char **remainder, char **str)
{
	int	rem_length;

	if ((*remainder) == NULL)
	{
		rem_length = BUFFER_SIZE + 1;
		*remainder = malloc(rem_length);
		if (*remainder == NULL)
			return (0);
		while (--rem_length > -1)
			(*remainder)[rem_length] = 0;
	}
	*str = malloc(1);
	if (*str == NULL)
		return (ft_cleanup(remainder, NULL), 0);
	(*str)[0] = 0;
	if (cat_and_free(str, *remainder, ft_strlen(*remainder)) == 0)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*str;
	int			pos;
	int			status;

	if (read(fd, remainder, 0) == -1)
		return (ft_cleanup(&remainder, NULL), NULL);
	if (!setup_remainder(&remainder, &str))
		return (NULL);
	while (!ft_has_char(str, '\n', &pos) && str)
	{
		status = read(fd, remainder, BUFFER_SIZE);
		if (status == -1)
			return (ft_cleanup(&remainder, &str), NULL);
		else if (status == 0)
			return (handle_eof(&remainder, &str), str);
		if (cat_and_free(&str, remainder, status) == 0)
			return (NULL);
	}
	if (extract_string(&str, remainder, pos) == 0)
		return (NULL);
	return (str);
}
