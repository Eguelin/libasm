/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/10 19:24:12 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "libasm.h"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

sigjmp_buf env;

void	segfault_handler(int sig);
void	test_strlen(char **tab);
void	test_strcpy(char **tab);
void	exit_error(char *str, char **tab, int size);
void	free_tab_str(char **tab, int size);
void	test_strcmp(char **tab);

#define TEST(expr) \
	if (sigsetjmp(env, 1) == 0 && (expr)) \
		write(STDOUT_FILENO, GREEN"[OK] ", 13); \
	else \
		write(STDOUT_FILENO, RED"[KO] ", 13);

#define TEST_SEG(expr) \
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
	char *tab[] = {
		"Hello, World!",
		"lorem ipsum dolor sit amet",
		"test",
		"3 + 3 = 9",
		"",
		NULL};

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = segfault_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGSEGV, &sa, NULL);
	test_strlen(tab);
	test_strcpy(tab);
	test_strcmp(tab);
	return (0);
}

void	segfault_handler(int sig)
{
	siglongjmp(env, 1);
}

void	test_strlen(char **tab)
{
	int		i = 0;
	char	*str;

	// Classic tests
	printf(PURPLE"\t--- ft_strlen ---\n"RESET);
	while (tab[i])
	{
		TEST(strlen(tab[i]) == ft_strlen(tab[i]));
		printf(BLUE"ft_strlen(\"%s\")\n"RESET, tab[i]);
		i++;
	}

	// NULL tests
	TEST_SEG(ft_strlen(NULL));
	printf(BLUE"ft_strlen(NULL)\n"RESET);

	// Ferry big string test
	str = calloc(sizeof(char), UINT_MAX);
	if (!str)
	{
		printf(RED"failed to allocate str[UINT_MAX]\n"RESET);
		return;
	}
	str = memset(str, 'c', UINT_MAX - 1);
	TEST(strlen(str) == ft_strlen(str));
	printf(BLUE"ft_strlen(str[UINT_MAX])\n"RESET);
	free(str);
}

void test_strcpy(char **tab)
{
	int		i = 0;
	char	*str[3];
	char	destNULL[1];

	// Classic tests
	printf(PURPLE"\t--- ft_strcpy ---\n"RESET);
	while (tab[i])
	{
		for (int j = 0; j < 2; j++)
		{
			str[j] = calloc(sizeof(char), strlen(tab[i]) + 1);
			if (!str[j])
				exit_error("failed to allocate str", str, j);
		}
		TEST(!strcmp(strcpy(str[0], tab[i]), ft_strcpy(str[1], tab[i])));
		printf(BLUE"ft_strcpy(dest, \"%s\")\n"RESET, tab[i]);
		free_tab_str(str, 2);
		i++;
	}

	// Overlapping test
	for (int j = 0; j < 2; j++)
	{
		str[j] = strdup("Hello, World!");
		if (!str[j])
			exit_error("failed to allocate str", str, j);
	}
	TEST(!strcmp(strcpy(str[0], str[0] + 6), ft_strcpy(str[1], str[1] + 6)));
	printf(BLUE"ft_strcpy(dest, str + 6) (overlapping)\n"RESET);
	free_tab_str(str, 2);

	// NULL tests
	TEST_SEG(ft_strcpy(destNULL, NULL));
	printf(BLUE"ft_strcpy(dest, NULL)\n"RESET);
	TEST_SEG(ft_strcpy(NULL, destNULL));
	printf(BLUE"ft_strcpy(NULL, src)\n"RESET);

	// Ferry big string test
	for (int j = 0; j < 3; j++)
	{
		str[j] = calloc(sizeof(char), UINT_MAX);
		if (!str[j])
			exit_error("failed to allocate str", str, j);
	}
	str[0] = memset(str[0], 'c', UINT_MAX - 1);
	TEST(!strcmp(strcpy(str[1], str[0]), ft_strcpy(str[2], str[0])));
	printf(BLUE"ft_strcpy(dest, str[UINT_MAX])\n"RESET);
	free_tab_str(str, 3);
}

void	exit_error(char *str, char **tab, int size)
{
	if (tab && size)
		free_tab_str(tab, size);
	printf(RED"%s\n"RESET, str);
	exit(1);
}

void	free_tab_str(char **tab, int size)
{
	int i = 0;

	while (i < size)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
}

void test_strcmp(char **tab)
{
	int		i = 0;
	int		j;
	char	destNULL[1];
	char	*str;

	// Classic tests
	printf(PURPLE"\t--- ft_strcmp ---\n"RESET);
	while (tab[i])
	{
		j = 0;
		while (tab[j])
		{
			TEST(ft_strcmp(tab[i], tab[j]) == strcmp(tab[i], tab[j]));
			printf(BLUE"ft_strcmp(\"%s\", \"%s\")\n"RESET, tab[i], tab[j]);
			j++;
		}
		i++;
	}

	// NULL tests
	TEST_SEG(ft_strcmp(destNULL, tab[i]));
	printf(BLUE"ft_strcmp(dest, NULL)\n"RESET);
	TEST_SEG(ft_strcmp(tab[i], destNULL));
	printf(BLUE"ft_strcmp(NULL, src)\n"RESET);

	// Ferry big string test
	str = calloc(1, UINT_MAX);
	if (!str)
		exit_error("failed to allocate str", NULL, 0);
	str = memset(str, 'c', UINT_MAX - 1);
	TEST(!ft_strcmp(str, str));
	printf(BLUE"ft_strcmp(str[UINT_MAX], str[UINT_MAX])\n"RESET);
	TEST(ft_strcmp(str, str + 1) > 0);
	printf(BLUE"ft_strcmp(str[UINT_MAX], str[UINT_MAX - 1])\n"RESET);
	TEST(ft_strcmp(str + 1, str) < 0);
	printf(BLUE"ft_strcmp(str[UINT_MAX - 1], str[UINT_MAX])\n"RESET);
	free(str);
}

