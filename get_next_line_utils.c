/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymatsui <ymatsui@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:26 by ymatsui           #+#    #+#             */
/*   Updated: 2024/01/19 14:36:53 by ymatsui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_lstadd_and_sizeget(t_list *lst, t_list *new)
{
	size_t	size;

	size = 0;
	if (lst->size == 0)
		lst = new;
	else
	{
		size = lst->size;
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	return (size);
}

size_t	ft_read(int fd, t_list *lst, char *line)
{
	size_t	size;

	size = 0;
	size = read(fd, line, (lst->size + BUFFER_SIZE));
	if (size < 0)
	{
		free(line);
		return (-1);
	}
	else if (size == 0)
		return (0);
	line[size] = '\0';
	printf("line = %s\n", line);
	return (size);
}

size_t	ft_size(t_list *lst, char *line)
{
	size_t	i;

	i = 0;
	if (lst->size > 0)
		i = lst->size + 1;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			break ;
		}
		printf("line[%zu] = %c\n", i, line[i]);
		i++;
	}
	return (i);
}
