/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:30 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/23 16:37:01 by ymatsui          ###   ########.fr       */
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

size_t				ft_strlen(char *line);
char				*ft_strdup_line(t_list *lst, char *line);
ssize_t				ft_copy_line(t_list *lst, char *line);
ssize_t				ft_read_line(int fd, t_list *lst);
t_list				*ft_strjoin(t_list *lst);
t_list				*ft_free_lst(t_list *lst);
t_list				*ft_malloc_lst(void);
char				*ft_malloc_line(size_t size);
void				*malloc(size_t size);
char				*get_next_line(int fd);