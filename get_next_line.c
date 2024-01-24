/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/24 17:15:14 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	*malloc(size_t size)
// {
// 	static int	i;

// 	if (i == 13)
// 		return (NULL);
// 	else
// 	{
// 		i++;
// 		return (calloc(size, 1));
// 	}
// }

ssize_t	ft_read(int fd, t_list *lst)
{
	ssize_t	size;

	lst->line = ft_malloc_line(BUFFER_SIZE);
	if (!lst->line)
		return (-1);
	size = read(fd, lst->line, BUFFER_SIZE);
	if (size < 0)
		return (-1);
	else if (size == 0)
		return (0);
	else
	{
		lst->line[size] = '\0';
		lst->call = size;
		lst->next = ft_malloc_lst();
		if (!lst->next)
			return (-1);
		lst = lst->next;
	}
	size = ft_read(fd, lst);
	if (size < 0)
		lst = ft_free_lst(lst, -1);
	return (size);
}

char	*ft_strcpy(t_list *lst, t_list *new)
{
	char	*lst_line;
	char	*new_line;

	lst_line = lst->line;
	new_line = new->line;
	while (lst)
	{
		if (*lst_line == '\0')
		{
			if (lst->next->call > 0)
			{
				lst = lst->next;
				lst_line = lst->line;
			}
			else
			{
				*new_line = *lst_line;
				break ;
			}
		}
		*new_line++ = *lst_line++;
	}
	return (new->line);
}

ssize_t	ft_strlen(t_list *lst)
{
	ssize_t	size;
	t_list	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		size += tmp->call;
		tmp = tmp->next;
	}
	return (size);
}

t_list	*ft_strjoin(t_list *lst)
{
	size_t	size;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	size = ft_strlen(lst);
	tmp = ft_malloc_lst();
	if (!tmp)
		return (NULL);
	tmp->line = ft_malloc_line(size);
	if (!tmp->line)
	{
		free(tmp);
		return (NULL);
	}
	tmp->call = size;
	tmp->line = ft_strcpy(lst, tmp);
	if (tmp->line)
	{
		lst = ft_free_lst(lst, -1);
		tmp->next = ft_malloc_lst();
	}
	if (!tmp->line || !tmp->next)
		tmp = ft_free_lst(tmp, 0);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = ft_malloc_lst();
		if (!lst)
			return (NULL);
		if (ft_read(fd, lst) < 0)
			return (NULL);
		lst = ft_strjoin(lst);
		lst = ft_split(lst);
		if (!lst)
			return ((char *)ft_free_lst(lst, 0));
	}
	else
	{
		lst = ft_free_lst(lst, 0);
		if (lst->line)
			lst = ft_split(lst);
		if (!lst)
			return ((char *)ft_free_lst(lst, -1));
	}
	return (lst->line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	close(fd);
	return (0);
}
