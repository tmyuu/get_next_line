/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/25 01:32:18 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, t_list *lst)
{
	ssize_t	size;
	ssize_t	call;

	lst->str = ft_malloc_str(BUFFER_SIZE);
	if (!lst->str)
		return (-1);
	size = read(fd, lst->str, BUFFER_SIZE);
	if (size < 0)
		return (-1);
	else if (size == 0)
		return (0);
	else
	{
		lst->str[size] = '\0';
		lst->next = ft_malloc_lst();
		if (!lst->next)
			return (-1);
		lst = lst->next;
	}
	call = ft_read(fd, lst);
	if (call < 0)
		return (-1);
	else
		size += call;
	return (size);
}

char	*ft_strjoin(char *str, t_list *lst)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (lst)
	{
		if (lst->str[j] == '\0')
		{
			if (lst->next && lst->next->next)
				lst = lst->next;
			else
				break ;
			j = 0;
		}
		str[i++] = lst->str[j++];
	}
	return (str);
}

char	*ft_strread(int fd)
{
	ssize_t	size;
	t_list	*lst;
	char	*str;

	lst = ft_malloc_lst();
	if (!lst)
		return (NULL);
	size = ft_read(fd, lst);
	if (size > 0)
		str = ft_malloc_str(size);
	if (size <= 0 || !str)
	{
		lst = ft_free_lst(lst);
		return (NULL);
	}
	str = ft_strjoin(str, lst);
	lst = ft_free_lst(lst);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;

	// static char	*tmp = NULL;
	if (!str)
	{
		str = ft_strread(fd);
		if (!str)
			return (NULL);
	}
	// tmp = ft_strcpy(str);
	// return (tmp);
	// if (!tmp)
	// {
	// 	if (str)
	// 		free(str);
	// 	str = NULL;
	// 	return (NULL);
	// }
	// str = ft_strmove(str, tmp);
	// return (tmp);
	return (str);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	// while (line)
// 	// {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// 	line = get_next_line(fd);
// 	// }
// 	printf("%s", line);
// 	free(line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// free(line);
// 	close(fd);
// 	return (0);
// }
