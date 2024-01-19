/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/19 20:29:44 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_get_bytesize(t_list *lst)
{
	size_t	bytesize;

	bytesize = 0;
	while (lst->line) //大事
	{
		bytesize += lst->bytesize;
		lst = lst->next;
	}
	if (bytesize == 0)
		return (bytesize);
	return (bytesize + 1);
}

size_t	ft_get_next_bytesize(char *line, t_list *lst)
{
	size_t	bytesize;
	char	*tmp;

	bytesize = 0;
	while (line)
	{
		if (*line == '\n')
			break ;
		else if (*line == '\0')
			break ;
		line++;
		bytesize++;
	}
	return (bytesize);
}

size_t	ft_read_line(int fd, t_list *lst, char *line)
{
	size_t	i;
	size_t	bytesize;

	if (ft_get_bytesize(lst) % BUFFER_SIZE == 0)
	{
		bytesize = read(fd, line, BUFFER_SIZE);
		if (bytesize < 0)
		{
			free(line);
			return (-1);
		}
		else if (bytesize == 0)
			return (0);
		line[bytesize] = '\0';
	}
	bytesize = ft_get_next_bytesize(line, lst);
	return (bytesize);
}

char	*ft_copy_line(t_list *lst, char *line)
{
	char	*tmp;
	char	*head;

	tmp = ft_malloc_line(tmp);
	head = tmp;
	while (line)
	{
		if (*line == '\n')
			break ;
		else if (*line == '\0')
			break ;
		*tmp = *line;
		tmp++;
		line++;
	}
	*tmp = '\0';
	return (head);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	static t_list	*head = NULL;
	static t_list	*point = NULL;
	char			*line;

	if (!lst)
	{
		lst = ft_malloc_lst(lst);
		head = lst;
	}
	else if (lst->next)
		lst = lst->next;
	line = ft_malloc_line(line);
	while (line)
	{
		lst->bytesize = ft_read_line(fd, head, line);
		lst->line = ft_copy_line(head, line);
		line += (lst->bytesize + 1);
		lst->next = ft_malloc_lst(lst->next);
		lst = lst->next;
		if (*line == '\0')
			break ;
	}
	if (!point)
	{
		point = head;
		return (point->line);
	}
	point = point->next;
	free(line);
	return (point->line);
}

int	main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("line = %s\n", line);
	line = get_next_line(fd);
	printf("line = %s\n", line);
	line = get_next_line(fd);
	printf("line = %s\n", line);
	line = get_next_line(fd);
	printf("line = %s\n", line);
	line = get_next_line(fd);
	printf("line = %s\n", line);
	line = get_next_line(fd);
	printf("line = %s\n", line);
}