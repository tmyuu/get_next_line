/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:30 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/19 20:12:47 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 15
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	size_t			bytesize;
	char			*line;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_malloc_lst(t_list *lst);
char				*ft_malloc_line(char *line);
size_t				ft_get_bytesize(t_list *lst);
size_t				ft_get_next_bytesize(char *line, t_list *lst);
size_t				ft_read_line(int fd, t_list *lst, char *line);
char				*ft_copy_line(t_list *lst, char *line);