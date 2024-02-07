/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:30 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/26 17:45:04 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE LONG_MAX
# endif

typedef struct s_list
{
	ssize_t			size;
	char			*str;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
ssize_t				ft_read(int fd, t_list *lst);
t_list				*ft_strcheck(int fd, t_list *lst);
ssize_t				ft_split(t_list *lst, ssize_t i);
ssize_t				ft_strjoin(t_list *lst);
char				*ft_strcpy(t_list *lst);
t_list				*ft_next(t_list *lst);
t_list				*ft_free_lst(t_list *lst);
t_list				*ft_malloc_lst(void);
#endif