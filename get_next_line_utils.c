/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:26 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/20 02:10:48 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->line);
		free(lst);
		lst = tmp;
	}
	return (NULL);
}

t_list	*ft_malloc_lst(t_list *lst)
{
	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->call = 0;
	lst->line = NULL;
	lst->next = NULL;
	return (lst);
}

char	*ft_malloc_line(char *line)
{
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	return (line);
}
