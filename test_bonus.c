/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/12 17:47:41 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "libasm_bonus.h"
#include <string.h>
#include <setjmp.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define RESET "\033[0m"

sigjmp_buf env;

void	segfault_handler(int sig);

int main()
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = segfault_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGSEGV, &sa, NULL);
	return (0);
}

void	segfault_handler(int sig)
{
	(void)sig;
	siglongjmp(env, 1);
}


	// printf("ft_atoi_base(\"-100\", \"01\") = %d\n", ft_atoi_base("-100", "01"));

	// printf("ft_atoi_base(\"\t -2147483648\", \"0123456789\") = %d\n", ft_atoi_base("\t -2147483648", "0123456789"));

	// printf("ft_list_size(NULL) = %d\n", ft_list_size(NULL));

	// t_list	*list = NULL;

	// ft_list_push_front(NULL, "elem1");

	// ft_list_push_front(&list, "elem1");
	// ft_list_push_front(&list, "elem3");
	// ft_list_push_front(&list, "elem2");

	// printf("list->data = %s\n", (char *)list->data);

	// printf("ft_list_size(elem1) = %d\n", ft_list_size(list));

	// ft_list_sort(NULL, &ft_strcmp);

	// ft_list_sort(&list, &ft_strcmp);


	// printf("list->data = %s\n", (char *)list->data);
	// printf("list->next->data = %s\n", (char *)list->next->data);
	// printf("list->next->next->data = %s\n", (char *)list->next->next->data);

	// ft_list_remove_if(&list, "elem3", &ft_strcmp, &free);
	// ft_list_remove_if(&list, "elem1", &ft_strcmp, &free);
	// ft_list_remove_if(&list, "elem2", &ft_strcmp, &free);

	// printf("list = %p\n", list);
