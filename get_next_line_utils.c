/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:26 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/22 13:28:33 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
