/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:50:00 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/25 00:37:27 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #define BUFFER_SIZE 1
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_free_lst(t_list *lst);
t_list				*ft_malloc_lst(void);
char				*ft_malloc_str(size_t size);
ssize_t				ft_read(int fd, t_list *lst);
char				*ft_strjoin(char *str, t_list *lst);
char				*ft_strread(int fd);
char				*ft_strcpy(char *str);
char				*ft_strmove(char *str, char *tmp);
