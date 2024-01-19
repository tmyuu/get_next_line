/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:30 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/20 00:22:43 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	int				call;
	char			*line;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
void				ft_read_line(int fd, t_list *lst, char *line);
t_list				*ft_malloc_lst(t_list *lst);
char				*ft_malloc_line(char *line);