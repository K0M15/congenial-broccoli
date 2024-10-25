/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:45:38 by afelger           #+#    #+#             */
/*   Updated: 2024/10/25 14:18:17 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <assert.h>

# define FT_IO_SUCCESS		0x1000
# define FT_FOUND_STR		0x1001
# define FT_IO_ERROR		0xE000
# define FT_FOUND_NO_STR	0xE001
# define FT_EOF_FOUND		0xF000

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif /* BUFFER_SIZE */

# ifndef STRING_BUFF_SIZE
#  define STRING_BUFF_SIZE BUFFER_SIZE
# endif /* STRING_BUFF_SIZE */

typedef struct s_lasttime
{
	char	*buffer;
	long	filled;
	long	allocated;
}	t_lasttime;


char	*get_next_line(int fd);
/**
 * Creates a new buffer object in the data pointer
 * @param data (t_lastttime **) buffer to create object into
 */
void	*create_new_buffer(t_lasttime **data);
/**
 * Shifts the startpos and all following bytes to the start of data->buffer
 * @param data (t_lasttime **)  buffer to shift
 */
void	shift_buffer(t_lasttime *data, long startpos);
/**
 * Returns a single string from buffer and shifts the buffer afterwards
 * 
 * @param data  (t_lasttime *) the last content
 * @param res  (char **) the resulting string, it will be allocated by the function
 * @param endpos (int) the last byte, containing the '\n'
 * @return
 * FT_FOUND_STR=got string
 * FT_IO_ERROR=error
 */
int		get_string(t_lasttime *data, char **result, int endpos);
/**
 * Reads an amount of bytes into data
 * 
 * @param data  (t_lasttime *) the last content
 * @param amount  (size_t) Amount of bytes to read
 * @param fd  (int) Filedescriptor
 * @return 
 * FT_IO_ERROR = Error
 * EOF_FOUND = End of file found
 * FT_IO_SUCCESS = succesfull read
 */
int		read_into_buffer(t_lasttime *data, long amount, int fd);
/**
 * Frees all memory associated with the t_lasttime struct and itself
 * @param data (t_lastttime *) the object
 * @return (void)
 */
void	free_buffer(t_lasttime **data);
/**
 * Checks the buffer for a \n.
 * @param data (t_lasttime)  the buffer struct
 * @param size (int *)  if return is FT_FOUND_STR, the position of \\n, else the last character in buffer
 * @return (int) FT_FOUND_STR or FT_FOUND_NO_STR
 */
int		check_buffer_string(const t_lasttime *data, long *size);

#endif /* GET_NEXT_LINE_H */
