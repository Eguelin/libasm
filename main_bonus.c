/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/18 19:07:10 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libasm_bonus.h"

int main(void)
{
	printf("ft_atoi_base(\"-100\", \"01\") = %d\n", ft_atoi_base("-100", "01"));

	printf("ft_atoi_base(\"-2147483648\", \"0123456789\") = %d\n", ft_atoi_base("-2147483648", "0123456789"));

	printf("ft_list_size(NULL) = %d\n", ft_list_size(NULL));

	t_list	*list = NULL;

	ft_list_push_front(NULL, "elem1");

	ft_list_push_front(&list, "elem1");

	printf("list->data = %s\n", (char *)list->data);
	printf("list->next = %p\n", list->next);

	printf("ft_list_size(elem1) = %d\n", ft_list_size(list));

	free(list);

	return (0);
}

