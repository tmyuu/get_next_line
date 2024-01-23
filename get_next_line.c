/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/23 16:36:41 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *line)
{
	size_t	i;

	i = 0;
	if (line)
	{
		while (line[i] != '\0')
		{
			if (line[i] == '\n')
				return (i + 1);
			i++;
		}
	}
	return (i);
}

char	*ft_strdup_line(t_list *lst, char *line)
{
	char	*tmp;

	tmp = ft_malloc_line(ft_strlen(line));
	if (!tmp)
		return (NULL);
	lst->line = tmp;
	while (*line != '\0')
	{
		if (*line == '\n')
		{
			*tmp++ = *line++;
			lst->call = 1;
			break ;
		}
		*tmp++ = *line++;
	}
	*tmp = '\0';
	return (line);
}

ssize_t	ft_copy_line(t_list *lst, char *line)
{
	ssize_t	call;

	call = 1;
	while (*line != '\0')
	{
		if (lst->line)
		{
			lst->next = ft_malloc_lst();
			if (!lst->next)
				return (-1);
			lst = lst->next;
		}
		line = ft_strdup_line(lst, line);
		if (!lst->line || !line)
			return (-1);
	}
	return (call);
}

ssize_t	ft_read_line(int fd, t_list *lst)
{
	ssize_t	bytesize;
	ssize_t	call;
	char	*line;

	call = 0;
	line = ft_malloc_line(BUFFER_SIZE);
	if (!line)
		return (-1);
	bytesize = read(fd, line, BUFFER_SIZE);
	if (bytesize < 0)
		return (-1);
	else if (bytesize > 0)
	{
		line[bytesize] = '\0';
		call = ft_copy_line(lst, line);
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = ft_malloc_lst();
		if (!lst->next)
			return (-1);
		else
			call = ft_read_line(fd, lst->next);
	}
	free(line);
	return (call);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = ft_malloc_lst();
		if (!lst)
			return (NULL);
		if (ft_read_line(fd, lst) < 0)
		{
			while (lst->next != NULL)
				lst = ft_free_lst(lst);
		}
	}
	else if (lst->call == 1)
		lst = ft_free_lst(lst);
	if (lst->call == 0)
	{
		if (lst->next == NULL)
			lst = ft_free_lst(lst);
		else
			while (lst->call == 0 && lst->next != NULL)
				lst = ft_strjoin(lst);
	}
	if (!lst)
		return (NULL);
	return (lst->line);
}
