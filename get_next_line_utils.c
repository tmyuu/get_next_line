/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:26 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/24 17:17:44 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_strlcpy(t_list *lst)
{
	ssize_t	i;
	char	*tmp;

	lst->next->line = lst->line;
	tmp = lst->next->line;
	lst->line = ft_malloc_line(lst->call);
	if (!lst->line)
		return (-1);
	i = 0;
	while (lst->line[i] != '\0')
	{
		lst->line[i] = lst->next->line[i];
		i++;
	}
	lst->next->line = ft_malloc_line(lst->next->call);
	if (!lst->next->line)
		i = -1;
	else
	{
		i = 0;
		while (lst->next->line[i] != '\0')
			lst->next->line[i++] = tmp[lst->call++];
	}
	return (i);
}

t_list	*ft_split(t_list *lst)
{
	ssize_t	i;

	i = 0;
	if (!lst)
		return (NULL);
	while (lst->line[i] != '\0')
	{
		if (lst->line[i] == '\n' || lst->line[i + 1] == '\0')
		{
			i++;
			break ;
		}
		i++;
	}
	lst->next = ft_malloc_lst();
	if (!lst->next)
		return (NULL);
	lst->next->call = lst->call - i;
	lst->call = i;
	if (lst->next->call > 0)
		lst->next->call = ft_strlcpy(lst);
	if (lst->next->call < 0)
		return (NULL);
	return (lst);
}

t_list	*ft_free_lst(t_list *lst, ssize_t call)
{
	t_list	*tmp;

	tmp = NULL;
	if (lst)
	{
		if (lst->next)
			tmp = lst->next;
		if (lst->line)
			free(lst->line);
		lst->line = NULL;
		free(lst);
		lst = tmp;
	}
	if (!tmp && call == -1)
		lst = ft_free_lst(lst, -1);
	return (lst);
}

t_list	*ft_malloc_lst(void)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->call = 0;
	lst->line = NULL;
	lst->next = NULL;
	return (lst);
}

char	*ft_malloc_line(ssize_t bytesize)
{
	char	*line;

	if (bytesize > 0)
	{
		line = (char *)malloc(sizeof(char) * (bytesize + 1));
		if (!line)
			return (NULL);
		line[bytesize] = '\0';
	}
	else
		return (NULL);
	return (line);
}
