/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:45:38 by afelger           #+#    #+#             */
/*   Updated: 2024/10/21 15:46:58 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_lasttime
{
	char	*buffer;
	size_t	filled;
	size_t	allocated;
}	t_lasttime;


char	*get_next_line(int fd);
void	*create_new_buffer(t_lasttime **data);
void	shift_buffer(t_lasttime *data, size_t startpos);
int		get_string(t_lasttime *data, char **result);
void	*read_into_buffer(t_lasttime *data, size_t amount, int fd);
void	free_buffer(t_lasttime *data);

#endif /* GET_NEXT_LINE_H */
