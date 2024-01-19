/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:28 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/19 14:36:57 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_malloc_lst(t_list *lst)
{
	if (lst == NULL)
	{
		lst = (t_list *)malloc(sizeof(t_list));
		if (!lst)
			return (NULL);
		lst->size = 0;
		lst->content = NULL;
		lst->next = NULL;
	}
	return (lst);
}

char	*ft_malloc_content(t_list *lst, t_list *tmp, char *line)
{
	size_t	i;

	i = 0;
	if (lst->size == 0)
	{
		tmp->content = (char *)malloc(sizeof(char) * (tmp->size + 1));
		if (!tmp->content)
			ft_free_lst(lst);
	}
	else if (lst->size < 0)
		ft_free_lst(lst);
	else
	{
		tmp->content = (char *)malloc(sizeof(char) * (lst->size + tmp->size
					+ 1));
		if (!tmp->content)
			ft_free_lst(lst);
	}
	while (i < tmp->size)
		tmp->content[i++] = line[lst->size++];
	tmp->content[i] = '\0';
	return (tmp->content);
}

char	*ft_malloc_line(size_t size)
{
	char	*line;

	line = (char *)malloc(sizeof(char) * (size + BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	return (line);
}

void	ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	t_list			*tmp;
	size_t			size;
	char			*line;

	tmp = NULL;
	lst = ft_malloc_lst(lst);
	tmp = ft_malloc_lst(tmp);
	size = ft_lstadd_and_sizeget(lst, tmp);
	line = ft_malloc_line(size);
	size = ft_read(fd, lst, line);
	tmp->size = ft_size(lst, line);
	tmp->content = ft_malloc_content(lst, tmp, line);
	free(line);
	if (tmp->size == 0)
		ft_free_lst(lst);
	return (tmp->content);
}

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
