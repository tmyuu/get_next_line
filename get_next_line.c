/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/20 00:21:29 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_copy_line(char *line, char *lstline)
{
	while (*line != '\0')
	{
		*lstline = *line;
		if (*line == '\n')
		{
			line++;
			lstline++;
			break ;
		}
		line++;
		lstline++;
		if (*line == '\0')
		{
			*lstline = '\n';
			lstline++;
		}
	}
	*lstline = '\0';
	return (line);
}

void	ft_read_line(int fd, t_list *lst, char *line)
{
	if (lst->call == 0)
	{
		lst->call = 1;
		read(fd, line, BUFFER_SIZE);
		ft_read_line(fd, lst, line);
	}
	else
	{
		lst->line = ft_malloc_line(lst->line);
		line = ft_copy_line(line, lst->line);
		if (*line == '\0')
			lst->call = 0;
		lst->next = ft_malloc_lst(lst->next);
		lst = lst->next;
		if (*line != '\0')
		{
			lst->call = 1;
			ft_read_line(fd, lst, line);
		}
		else
			lst->call = 0;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	static char		*line = NULL;

	if (!lst)
		lst = ft_malloc_lst(lst);
	if (lst->call == 0)
	{
		line = ft_malloc_line(line);
		ft_read_line(fd, lst, line);
		free(line);
	}
	else
	{
		lst = lst->next;
	}
	return (lst->line);
}
