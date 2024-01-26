/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:14:50 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/26 17:27:07 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_split(t_list *lst, ssize_t i)
{
	ssize_t	j;

	j = 0;
	lst->next->str = lst->str;
	lst->str = (char *)malloc(sizeof(char) * (i + 1));
	if (!lst->str)
		lst->size = -1;
	else
	{
		lst->size = i;
		while (j < i)
		{
			lst->str[j] = lst->next->str[j];
			j++;
		}
		lst->str[j] = '\0';
		j = 0;
		while (lst->next->str[i] != '\0')
			lst->next->str[j++] = lst->next->str[i++];
		lst->next->size = j;
		while (j < i)
			lst->next->str[j++] = '\0';
	}
	return (lst->size);
}

ssize_t	ft_strjoin(t_list *lst)
{
	ssize_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (lst->size + lst->next->size + 1));
	if (!tmp)
		lst->size = -1;
	else
	{
		while (i < lst->size)
		{
			tmp[i] = lst->str[i];
			i++;
		}
		i = 0;
		while (i < lst->next->size)
			tmp[lst->size++] = lst->next->str[i++];
		tmp[lst->size] = '\0';
		free(lst->str);
		lst->str = tmp;
		lst->next = ft_free_lst(lst->next);
		lst->next = ft_malloc_lst();
	}
	return (lst->size);
}

t_list	*ft_strcheck(int fd, t_list *lst)
{
	ssize_t	i;
	ssize_t	call;

	i = 0;
	while (lst->str[i] != '\n' && lst->str[i] != '\0')
		i++;
	if (lst->str[i] == '\n')
	{
		call = ft_split(lst, i + 1);
		if (lst->next->size == 0)
			lst->next = ft_free_lst(lst->next);
	}
	else
	{
		call = ft_read(fd, lst->next);
		if (call > 0)
			call = ft_strjoin(lst);
		else if (call < 0)
			lst->size = -1;
		else if (call == 0)
			lst->next = ft_free_lst(lst->next);
	}
	if (call < 0)
		lst = ft_free_lst(lst);
	return (lst);
}

ssize_t	ft_read(int fd, t_list *lst)
{
	lst->str = (char *)malloc(sizeof(char) * ((ssize_t)BUFFER_SIZE + 1));
	if (!lst->str)
		lst->size = -1;
	else
	{
		lst->size = read(fd, lst->str, (ssize_t)BUFFER_SIZE);
		if (lst->size > 0)
		{
			lst->str[lst->size] = '\0';
			lst->next = ft_malloc_lst();
		}
		else
		{
			free(lst->str);
			lst->str = NULL;
		}
	}
	return (lst->size);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*str;

	if (fd < 0 || (ssize_t)BUFFER_SIZE <= 0)
		return (NULL);
	if (!lst)
	{
		lst = ft_malloc_lst();
		if (!lst)
			return (NULL);
		if (ft_read(fd, lst) <= 0)
			lst = ft_free_lst(lst);
	}
	else
		lst->next = ft_malloc_lst();
	while (lst && lst->next && lst->next->size == 0)
		lst = ft_strcheck(fd, lst);
	str = ft_strcpy(lst);
	if (!str)
		lst = ft_free_lst(lst);
	else
		lst = ft_next(lst);
	return (str);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
