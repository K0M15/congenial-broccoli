/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:45:38 by afelger           #+#    #+#             */
/*   Updated: 2024/10/25 15:36:00 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <assert.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif /* BUFFER_SIZE */

# ifndef STRING_BUFF_SIZE
#  define STRING_BUFF_SIZE BUFFER_SIZE
# endif /* STRING_BUFF_SIZE */

char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
