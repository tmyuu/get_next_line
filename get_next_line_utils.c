/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:14:58 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/26 17:10:31 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(t_list *lst)
{
	ssize_t	i;
	char	*tmp;

	i = 0;
	if (!lst)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (lst->size + 1));
	if (!tmp)
		return (NULL);
	while (i < lst->size)
	{
		tmp[i] = lst->str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

t_list	*ft_next(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	if (!lst)
		return (NULL);
	tmp = lst->next;
	if (lst->str)
		free(lst->str);
	free(lst);
	lst = tmp;
	return (lst);
}

t_list	*ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		if (lst->str)
			free(lst->str);
		free(lst);
		lst = tmp;
	}
	return (lst);
}

t_list	*ft_malloc_lst(void)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->size = 0;
	lst->str = NULL;
	lst->next = NULL;
	return (lst);
}
