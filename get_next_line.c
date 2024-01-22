/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/22 14:00:07 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (i == 0 && line[i] == '\n')
			return (i + 1);
		else if (line[i] == '\n')
			return (i);
		i++;
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
			line++;
			break ;
		}
		*tmp++ = *line++;
	}
	*tmp = '\0';
	return (line);
}

ssize_t	ft_copy_line(t_list *lst, char *line)
{
	while (*line != '\0')
	{
		if (!lst)
		{
			lst = ft_malloc_lst();
			if (!lst)
				return (-1);
			printf("NULL");
		}
		else if (lst->call > 0)
		{
			lst->next = ft_malloc_lst();
			if (!lst->next)
				return (-1);
			lst = lst->next;
		}
		line = ft_strdup_line(lst, line);
		if (!lst->line)
			return (-1);
		lst->call = 1;
	}
	return (1);
}

ssize_t	ft_read_line(int fd, t_list *lst)
{
	ssize_t	bytesize;
	ssize_t	call;
	char	*line;

	line = ft_malloc_line(BUFFER_SIZE);
	if (!line)
		return (-1);
	bytesize = read(fd, line, BUFFER_SIZE);
	line[bytesize] = '\0';
	if (bytesize == -1)
		free(line);
	else if (bytesize == 0)
	{
		free(line);
		return (0);
	}
	call = ft_copy_line(lst, line);
	free(line);
	if (call < 0)
		return (-1);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = ft_malloc_lst();
		if (!lst)
			return (NULL);
	}
	else if (lst->next)
	{
		lst = ft_free_lst(lst);
		return (lst->line);
	}
	else
	{
		lst->next = ft_malloc_lst();
		lst = lst->next;
	}
	lst->call = ft_read_line(fd, lst);
	if (lst->call <= 0)
	{
		lst = ft_free_lst(lst);
		return (NULL);
	}
	return (lst->line);
}

int	main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}