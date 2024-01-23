/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:26 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/23 12:12:10 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_strjoin(t_list *lst)
{
	char	*line;
	char	*nextline;
	char	*tmp;
	char	*head;

	line = lst->line;
	nextline = lst->next->line;
	tmp = ft_malloc_line(ft_strlen(line) + ft_strlen(nextline));
	if (!tmp)
		return (NULL);
	head = tmp;
	while (*line != '\0')
		*tmp++ = *line++;
	if (nextline)
		while (*nextline != '\0')
			*tmp++ = *nextline++;
	*tmp = '\0';
	lst = ft_free_lst(lst);
	free(lst->line);
	lst->line = head;
	return (lst);
}

t_list	*ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	if (lst)
	{
		tmp = lst->next;
		free(lst->line);
		free(lst);
		return (tmp);
	}
	return (NULL);
}

t_list	*ft_malloc_lst(void)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->call = 0;
	tmp->line = NULL;
	tmp->next = NULL;
	return (tmp);
}

char	*ft_malloc_line(size_t bytesize)
{
	char	*tmp;

	if (bytesize > 0)
	{
		tmp = (char *)malloc(sizeof(char) * (bytesize + 1));
		if (!tmp)
			return (NULL);
		tmp[bytesize] = '\0';
	}
	else
		return (NULL);
	return (tmp);
}
