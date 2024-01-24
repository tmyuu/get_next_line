/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:58:54 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/25 01:31:17 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strmove(char *str, char *tmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tmp[i] != '\0')
		i++;
	if (!str || str[i] == '\0')
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	j = 0;
	while (str[i] != '\0')
		str[j++] = str[i++];
	while (str[j] != '\0')
		str[j++] = '\0';
	return (str);
}

char	*ft_strcpy(char *str)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	tmp = ft_malloc_str(i);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (tmp[i] != '\0')
		tmp[i++] = str[j++];
	return (tmp);
}

t_list	*ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (lst)
	{
		if (lst->next)
		{
			tmp = lst->next;
			lst->next = NULL;
		}
		else
			tmp = NULL;
		if (lst->str)
		{
			free(lst->str);
			lst->str = NULL;
		}
		free(lst);
		lst = tmp;
	}
	return (tmp);
}

t_list	*ft_malloc_lst(void)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->str = NULL;
	lst->next = NULL;
	return (lst);
}

char	*ft_malloc_str(size_t size)
{
	char	*str;

	if (size < 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	return (str);
}
