/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:30 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/19 12:42:04 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 12
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	size_t			size;
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_malloc_lst(t_list *lst);
char				*ft_malloc_content(t_list *lst, t_list *tmp, char *line);
char				*ft_malloc_line(size_t size);
size_t				ft_lstadd_and_sizeget(t_list *lst, t_list *new);
size_t				ft_read(int fd, t_list *lst, char *line);
size_t				ft_size(t_list *lst, char *line);
void				ft_free_lst(t_list *lst);
