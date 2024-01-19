/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/20 02:14:31 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->line);
		free(lst);
		lst = tmp;
	}
	return (tmp);
}

t_list	*ft_malloc_lst(t_list *lst)
{
	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->call = 0;
	lst->line = NULL;
	lst->next = NULL;
	return (lst);
}

char	*ft_malloc_line(char *line)
{
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	return (line);
}

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
			lstline++;
	}
	*lstline = '\0';
	return (line);
}

ssize_t	ft_read(int fd, char *buf, size_t size)
{
	ssize_t	i;

	i = read(fd, buf, size);
	if (i == -1)
		return (-1);
	else if (i == 0)
		return (-2);
	return (1);
}

void	ft_read_line(int fd, t_list *lst, char *line)
{
	if (lst->call == 0)
	{
		lst->call = ft_read(fd, line, BUFFER_SIZE);
		if (lst->call > 0)
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
		else if (*line != '\0' && lst->call == -2)
		{
			lst->call = -2;
			ft_read_line(fd, lst, line);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_list *lst = NULL;
	static t_list *head = NULL;
	static char *line = NULL;

	if (!lst)
	{
		lst = ft_malloc_lst(lst);
		head = lst;
	}
	if (lst->call == 0)
	{
		line = ft_malloc_line(line);
		ft_read_line(fd, lst, line);
		if (lst->call == -1)
		{
			head = ft_free_lst(head);
			return (NULL);
		}
		free(line);
	}
	else if (lst->call == -2)
	{
		if (lst->next != NULL)
		{
			head = ft_free_lst(head);
			return (NULL);
		}
		lst = lst->next;
	}
	else if (lst->call == 1)
		lst = lst->next;
	return (lst->line);
}