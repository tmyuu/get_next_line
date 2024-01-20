/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/20 16:06:38 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_line(t_list *lst, char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	tmp = ft_malloc_line(tmp, i);
	if (!tmp)
		return (NULL);
	lst->line = tmp;
	while (*line != '\0')
	{
		if (*line == '\n')
		{
			line++;
			break ;
		}
		*tmp++ = *line++;
	}
	*tmp = '\0';
	return (line);
}

ssize_t	ft_copy_line(t_list *lst, char *line, ssize_t bytesize)
{
	char	*tmp;

	tmp = line;
	while (*tmp != '\0')
	{
		tmp = ft_strdup_line(lst, tmp);
		if (!tmp && !lst->line)
			return (-1);
		if (bytesize > 0)
			lst->call = 1;
		else
			lst->call = 0;
		if (*tmp != '\0')
		{
			lst->next = ft_malloc_lst(lst->next);
			if (!lst->next)
				return (-1);
			lst = lst->next;
		}
	}
	if (bytesize == 0)
		return (0);
	return (1);
}

ssize_t	ft_read_line(int fd, t_list *lst)
{
	ssize_t	bytesize;
	ssize_t	call;
	char	*line;

	line = ft_malloc_line(line, BUFFER_SIZE);
	if (!line)
		return (-1);
	bytesize = read(fd, line, BUFFER_SIZE);
	if (bytesize == -1)
		free(line);
	call = ft_copy_line(lst, line, bytesize);
	free(line);
	if (call == 0)
		return (0);
	else if (call > 0)
		return (1);
	return (-1);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	static t_list	*head = NULL;

	if (!lst)
	{
		lst = ft_malloc_lst(lst);
		head = lst;
		lst->call = ft_read_line(fd, lst);
		return (lst->line);
	}
	if (lst->next)
		lst = lst->next;
	if (lst->call > 1)
	{
		lst->next = ft_malloc_lst(lst->next);
		if (!lst->next)
			lst->call = -1;
		lst->call = ft_read_line(fd, lst->next);
		return (lst->line);
	}
	if (lst->call == -1)
	{
		ft_free_lst(head);
		return (NULL);
	}
	else if (lst->call == 0 && !lst->next)
		lst = head;
	return (lst->line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	close(fd);
	return (0);
}
