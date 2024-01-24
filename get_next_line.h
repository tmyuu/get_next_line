/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:30 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/24 17:13:47 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 1
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	ssize_t			call;
	char			*line;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_free_lst(t_list *lst, ssize_t call);
t_list				*ft_malloc_lst(void);
char				*ft_malloc_line(ssize_t bytesize);
ssize_t				ft_read(int fd, t_list *lst);
char				*ft_strcpy(t_list *lst, t_list *new);
t_list				*ft_strjoin(t_list *lst);
ssize_t				ft_strlcpy(t_list *lst);
t_list				*ft_split(t_list *lst);
