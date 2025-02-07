/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 11:34:05 by vde-dios          #+#    #+#             */
/*   Updated: 2020/06/30 11:36:31 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

int		get_next_line(int fd, char **line);
int		ft_analyse(char *buffer);
char	*ft_realloc_content(char *line, char *buffer);
char	*ft_cut_line(char *buffer, char **line);
void	ft_free_memory(char **p);

#endif
