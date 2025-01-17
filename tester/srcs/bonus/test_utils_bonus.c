/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:14:20 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/15 11:25:11 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils_bonus.h"

t_list	*list_push_front_c(t_list **begin_list, void *data)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->data = data;
	new->next = *begin_list;
	*begin_list = new;
	return (new);
}

void	list_clear(t_list **begin_list)
{
	t_list	*tmp;

	while (*begin_list)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
}

int	list_is_sort(t_list *begin_list, int (*cmp)())
{
	t_list	*tmp;

	tmp = begin_list;
	while (tmp && tmp->next)
	{
		if (cmp(tmp->data, tmp->next->data) > 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	list_size(t_list *begin_list)
{
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = begin_list;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

int	data_in_list(t_list *begin_list, void *data, int (*cmp)())
{
	t_list	*tmp;

	tmp = begin_list;
	while (tmp)
	{
		if (cmp(tmp->data, data) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	print_list(char *format, t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (tmp)
	{
		while (tmp)
		{
			printf(format, (char *)tmp->data);
			tmp = tmp->next;
		}
	}
}
