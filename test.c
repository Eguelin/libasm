/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/12 17:46:32 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "libasm.h"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define RESET "\033[0m"

sigjmp_buf env;

void	segfault_handler(int sig);
void	test_strlen(char **tab);
void	test_strcpy(char **tab);
void	exit_error(char *str, char **tab, int size, int fd);
void	free_tab_str(char **tab, int size);
void	test_strcmp(char **tab);
void	test_write(char **tab);
int		fdcmp(char *file1, char *file2);
void	test_read(char **tab);
int		create_file(char *file, char *str);
void	test_strdup(char **tab);

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
	test_write(tab);
	test_read(tab);
	test_strdup(tab);
	return (0);
}

void	segfault_handler(int sig)
{
	(void)sig;
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
	str = calloc(UINT_MAX, sizeof(char));
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
			str[j] = calloc(strlen(tab[i]) + 1, sizeof(char));
			if (!str[j])
				exit_error("failed to allocate str", str, j, -1);
		}
		TEST(!strcmp(strcpy(str[0], tab[i]), ft_strcpy(str[1], tab[i])));
		printf(BLUE"ft_strcpy(dest, \"%s\")\n"RESET, tab[i]);
		free_tab_str(str, 2);
		i++;
	}

	// NULL tests
	TEST_SEG(ft_strcpy(destNULL, NULL));
	printf(BLUE"ft_strcpy(dest, NULL)\n"RESET);
	TEST_SEG(ft_strcpy(NULL, destNULL));
	printf(BLUE"ft_strcpy(NULL, src)\n"RESET);

	// Ferry big string test
	for (int j = 0; j < 3; j++)
	{
		str[j] = calloc(UINT_MAX, sizeof(char));
		if (!str[j])
			exit_error("failed to allocate str", str, j, -1);
	}
	str[0] = memset(str[0], 'c', UINT_MAX - 1);
	TEST(!strcmp(strcpy(str[1], str[0]), ft_strcpy(str[2], str[0])));
	printf(BLUE"ft_strcpy(dest, str[UINT_MAX])\n"RESET);
	free_tab_str(str, 3);
}

void	exit_error(char *str, char **tab, int tab_size, int fd)
{
	if (tab && tab_size)
		free_tab_str(tab, tab_size);
	if (fd >= 0)
	{
		close(fd);
		remove("test.txt");
		remove("test2.txt");
	}
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
			TEST((ft_strcmp(tab[i], tab[j]) == 0 && strcmp(tab[i], tab[j]) == 0) ||
			(ft_strcmp(tab[i], tab[j]) < 0 && strcmp(tab[i], tab[j]) < 0) ||
			(ft_strcmp(tab[i], tab[j]) > 0 && strcmp(tab[i], tab[j]) > 0));
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
	str = calloc(UINT_MAX, sizeof(char));
	if (!str)
		exit_error("failed to allocate str", NULL, 0, -1);
	str = memset(str, 'c', UINT_MAX - 1);
	TEST(!ft_strcmp(str, str));
	printf(BLUE"ft_strcmp(str[UINT_MAX], str[UINT_MAX])\n"RESET);
	TEST(ft_strcmp(str, str + 1) > 0);
	printf(BLUE"ft_strcmp(str[UINT_MAX], str[UINT_MAX - 1])\n"RESET);
	TEST(ft_strcmp(str + 1, str) < 0);
	printf(BLUE"ft_strcmp(str[UINT_MAX - 1], str[UINT_MAX])\n"RESET);
	free(str);
}

void	test_write(char **tab)
{
	int		fd;
	int		fd2;
	int		i = 0;
	char	*str;

	// Classic tests
	printf(PURPLE"\t--- ft_write ---\n"RESET);
	while (tab[i])
	{
		errno = -1;
		fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit_error("failed to open test.txt", NULL, 0, -1);
		fd2 = open("test2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd2 < 0)
			exit_error("failed to open test2.txt", NULL, 0, fd);
		TEST(write(fd, tab[i], strlen(tab[i])) == ft_write(fd2, tab[i], strlen(tab[i])) && !fdcmp("test.txt", "test2.txt"));
		printf(BLUE"ft_write(fd, \"%s\", %lu)\n"RESET, tab[i], strlen(tab[i]));
		i++;
		close(fd);
		close(fd2);
	}

	// errno test
	TEST(write(-1, "test", 4) == ft_write(-1, "test", 4) && errno == EBADF);
	printf(BLUE"ft_write(-1, \"test\", 4)\n"RESET);

	// NULL tests
	TEST(ft_write(1, NULL, 4) == -1 && errno == EFAULT);
	printf(BLUE"ft_write(1, NULL, 4)\n"RESET);

	// Ferry big string test
	str = calloc(UINT_MAX, sizeof(char));
	if (!str)
		exit_error("failed to allocate str[UINT_MAX]", NULL, 0, -1);
	str = memset(str, 'c', UINT_MAX - 1);
	fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit_error("failed to open test.txt", &str, 1, -1);
	fd2 = open("test2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd2 < 0)
		exit_error("failed to open test2.txt", &str, 1, fd);
	TEST(write(fd, str, UINT_MAX) == ft_write(fd2, str, UINT_MAX) && !fdcmp("test.txt", "test2.txt"));
	printf(BLUE"ft_write(fd, str[UINT_MAX], UINT_MAX)\n"RESET);
	close(fd);
	close(fd2);
	free(str);

	remove("test.txt");
	remove("test2.txt");
}

int	fdcmp(char *file1, char *file2)
{
	int		fd1;
	int		fd2;
	int		ret1 = 1;
	int		ret2 = 1;
	char	buf1[4096];
	char	buf2[4096];

	fd1 = open(file1, O_RDONLY);
	fd2 = open(file2, O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		if (fd1 >= 0)
			close(fd1);
		if (fd2 >= 0)
			close(fd2);
		return (1);
	}
	while (ret1 > 0 && ret2 > 0)
	{
		ret1 = read(fd1, buf1, 4096);
		ret2 = read(fd2, buf2, 4096);
		if (ret1 != ret2 || memcmp(buf1, buf2, ret1))
		{
			close(fd1);
			close(fd2);
			return (1);
		}
	}
	close(fd1);
	close(fd2);
	if (ret1 != ret2)
		return (1);
	return (0);
}

void	test_read(char **tab)
{
	int		fd;
	int		fd2;
	int		i = 0;
	char	*str[2];

	// Classic tests
	printf(PURPLE"\t--- ft_read ---\n"RESET);
	while (tab[i])
	{
		if (create_file("test.txt", tab[i]))
			exit_error("failed to create test.txt", NULL, 0, -1);
		str[0] = calloc(strlen(tab[i]) + 1, sizeof(char));
		if (!str[0])
			exit_error("failed to allocate str", NULL, 0, -1);
		str[1] = calloc(strlen(tab[i]) + 1, sizeof(char));
		if (!str[1])
			exit_error("failed to allocate str2", str, 1, -1);
		fd = open("test.txt", O_RDONLY);
		if (fd < 0)
			exit_error("failed to open test.txt", str, 2, -1);
		fd2 = open("test.txt", O_RDONLY);
		if (fd2 < 0)
			exit_error("failed to open test.txt", str, 2, fd);
		TEST(read(fd, str[0], strlen(tab[i])) == ft_read(fd2, str[1], strlen(tab[i])) && !strcmp(str[0], str[1]));
		printf(BLUE"ft_read(fd, buf, %lu)\n"RESET, strlen(tab[i]));
		free_tab_str(str, 2);
		close(fd);
		close(fd2);
		i++;
	}

	// errno test
	TEST(ft_read(-1, "test", 4) && errno == EBADF);
	printf(BLUE"ft_read(-1, \"test\", 4)\n"RESET);

	// Ferry big string test
	str[0] = calloc(UINT_MAX, sizeof(char));
	if (!str[0])
		exit_error("failed to allocate str[UINT_MAX]", NULL, 0, -1);
	str[1] = calloc(UINT_MAX, sizeof(char));
	if (!str[1])
		exit_error("failed to allocate str2[UINT_MAX]", str, 1, -1);
	str[0] = memset(str[0], 'c', UINT_MAX - 1);
	if (create_file("test.txt", str[0]))
		exit_error("failed to create test.txt", str, 2, -1);
	bzero(str[0], UINT_MAX);
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		exit_error("failed to open test.txt", str, 2, -1);
	fd2 = open("test.txt", O_RDONLY);
	if (fd2 < 0)
		exit_error("failed to open test.txt", str, 2, fd);
	TEST(read(fd, str[0], UINT_MAX) == ft_read(fd2, str[1], UINT_MAX) && !strcmp(str[0], str[1]));
	printf(BLUE"ft_read(fd, buf[UINT_MAX], UINT_MAX)\n"RESET);
	free_tab_str(str, 2);
	close(fd);
	close(fd2);
	remove("test.txt");
}

int	create_file(char *file, char *str)
{
	int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	write(fd, str, strlen(str));
	close(fd);
	return (0);
}

void	test_strdup(char **tab)
{
	int		i = 0;
	char	*str[2];

	// Classic tests
	printf(PURPLE"\t--- ft_strdup ---\n"RESET);
	while (tab[i])
	{
		TEST((str[0] = ft_strdup(tab[i])) && !strcmp(str[0], tab[i]));
		printf(BLUE"ft_strdup(\"%s\")\n"RESET, tab[i]);
		free(str[0]);
		i++;
	}

	// NULL tests
	TEST_SEG(ft_strdup(NULL));
	printf(BLUE"ft_strdup(NULL)\n"RESET);

	// Ferry big string test
	str[0] = calloc(UINT_MAX, sizeof(char));
	if (!str[0])
		exit_error("failed to allocate str[UINT_MAX]", NULL, 0, -1);
	str[0] = memset(str[0], 'c', UINT_MAX - 1);
	TEST((str[1] = ft_strdup(str[0])) && !strcmp(str[0], str[1]));
	printf(BLUE"ft_strdup(str[UINT_MAX])\n"RESET);
	free_tab_str(str, 2);
}
