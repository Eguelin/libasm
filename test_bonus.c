/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/14 09:19:24 by eguelin          ###   ########.fr       */
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
void	test_atoi_base(void);
void	test_list_push_front(void);

#define ASSERT_CONDITION(condition) \
	if (sigsetjmp(env, 1) == 0) \
	{ \
		if (condition) \
			write(STDOUT_FILENO, GREEN"[OK] ", 13); \
		else \
			write(STDOUT_FILENO, RED"[KO] ", 13); \
	} \
	else \
		write(STDOUT_FILENO, RED"[SEGV] ", 15);

#define ASSERT_EXPR_CONDITION(expr, condition) \
	if (sigsetjmp(env, 1) == 0) \
	{ \
		(expr); \
		if (condition) \
			write(STDOUT_FILENO, GREEN"[OK] ", 13); \
		else \
			write(STDOUT_FILENO, RED"[KO] ", 13); \
	} \
	else \
		write(STDOUT_FILENO, RED"[SEGV] ", 15);

#define ASSERT_NO_SEGFAULT(expr) \
	if (sigsetjmp(env, 1) == 0) \
	{ \
		(expr); \
		write(STDOUT_FILENO, GREEN"[OK] ", 13); \
	} \
	else \
		write(STDOUT_FILENO, RED"[SEGV] ", 15);

#define EXPECT_SEGFAULT(expr) \
	if (sigsetjmp(env, 1) == 0) \
	{ \
		(expr); \
		write(STDOUT_FILENO, YELLOW"[WARN] ", 15); \
	} \
	else \
		write(STDOUT_FILENO, GREEN"[OK] ", 13);

int main()
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = segfault_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGSEGV, &sa, NULL);
	test_atoi_base();
	test_list_push_front();
	return (0);
}

void	segfault_handler(int sig)
{
	(void)sig;
	siglongjmp(env, 1);
}

void	test_atoi_base(void)
{
	char	*tab[][3] = {{"-1", "01", "-1"},
						{"1", "01", "1"},
						{"-1", "0123456789", "-1"},
						{ "1", "0123456789", "1"},
						{"-1", "0123456789abcdef", "-1"},
						{"1", "0123456789abcdef", "1"},
						{"-1", "0123456789ABCDEF", "-1"},
						{"1", "0123456789ABCDEF", "1"},
						{"10111f", "01", "23"},
						{"-10111f", "01", "-23"},
						{"10111f", "0123456789", "10111"},
						{"-10111f", "0123456789", "-10111"},
						{"10111f", "0123456789abcdef", "1052959"},
						{"-10111f", "0123456789abcdef", "-1052959"},
						{"10111f", "0123456789ABCDEF", "65809"},
						{"-10111f", "0123456789ABCDEF", "-65809"},
						{"-10000000000000000000000000000000", "01", "-2147483648"},
						{"1111111111111111111111111111111", "01", "2147483647"},
						{"-2147483648", "0123456789", "-2147483648"},
						{"2147483647", "0123456789", "2147483647"},
						{"-7fffffff", "0123456789abcdef", "-2147483647"},
						{"7fffffff", "0123456789abcdef", "2147483647"},
						{"-7FFFFFFF", "0123456789ABCDEF", "-2147483647"},
						{"7FFFFFFF", "0123456789ABCDEF", "2147483647"},
						{"\t   7", "0123456789", "7"},
						{"\t   -7", "0123456789", "-7"},
						{"", "10", "0"},
						{"+++---+-9", "369", "2"},
						{"444" , "4", "0"},
						{"55", "012345+", "0"},
						{"55", "012345\t", "0"},
						{NULL, "01", "0"},
						{"1", NULL, "0"},
						{NULL, NULL, "0"}};

	printf(PURPLE"\t--- ft_atoi_base ---\n"RESET);
	for (int i = 0; i < 33; i++)
	{
		ASSERT_CONDITION(ft_atoi_base(tab[i][0], tab[i][1]) == atoi(tab[i][2]));
		printf(BLUE"ft_atoi_base(\"%s\", \"%s\")\n"RESET, tab[i][0], tab[i][1]);
	}
	return ;
}

void	test_list_push_front(void)
{
	t_list	*list = NULL;
	char	*tab[] = {"elem1", "elem2", "elem3"};

	// Classic tests
	printf(PURPLE"\t--- ft_list_push_front ---\n"RESET);
	for (int i = 0; i < 3; i++)
	{
		ASSERT_EXPR_CONDITION(ft_list_push_front(&list, tab[i]),
			list->data == tab[i] && (list->next == NULL || list->next->data == tab[i - 1]));
		printf(BLUE"ft_list_push_front(&list, \"%s\")\n"RESET, tab[i]);
	}
	while (list)
	{
		t_list	*tmp = list;

		list = list->next;
		free(tmp);
	}

	// NULL tests
	ASSERT_NO_SEGFAULT(ft_list_push_front(NULL, "elem1"));
	printf(BLUE"ft_list_push_front(NULL, \"elem1\")\n"RESET);


	return ;
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
