/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/14 12:24:54 by eguelin          ###   ########.fr       */
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
struct sigaction sa;

void	segfault_handler(int sig);
void	catch_segfault(void);
void	default_sigaction(void);
void	exit_error(char *str, char *free_str);
char	*fdtostr(char *file);
int		create_file(char *file, char *str);

void	test_strlen(char **tab);
void	test_strcpy(char **tab);
void	test_strcmp(char **tab);
void	test_write(char **tab);
void	test_read(char **tab);
void	test_strdup(char **tab);

#define ASSERT_EXPR_CONDITION(expr, condition) \
	catch_segfault(); \
	if (sigsetjmp(env, 1) == 0) \
	{ \
		(expr); \
		if (condition) \
			write(STDOUT_FILENO, GREEN"[OK] ", 13); \
		else \
			write(STDOUT_FILENO, RED"[KO] ", 13); \
	} \
	else \
		write(STDOUT_FILENO, RED"[SEGV] ", 15); \
	default_sigaction();

#define ASSERT_NO_SEGFAULT(expr) \
	catch_segfault(); \
	if (sigsetjmp(env, 1) == 0) \
	{ \
		(expr); \
		write(STDOUT_FILENO, GREEN"[OK] ", 13); \
	} \
	else \
		write(STDOUT_FILENO, RED"[SEGV] ", 15); \
	default_sigaction();

#define EXPECT_SEGFAULT(expr) \
	catch_segfault(); \
	if (sigsetjmp(env, 1) == 0) \
	{ \
		(expr); \
		write(STDOUT_FILENO, YELLOW"[WARN] ", 15); \
	} \
	else \
		write(STDOUT_FILENO, GREEN"[OK] ", 13); \
	default_sigaction();

int main()
{
	char *tab[] = {
		"Hello, World!",
		"lorem ipsum dolor sit amet",
		"test",
		"3 + 3 = 9",
		"",
		NULL};

	sigemptyset(&sa.sa_mask);
	test_strlen(tab);
	test_strcpy(tab);
	test_strcmp(tab);
	test_write(tab);
	test_read(tab);
	test_strdup(tab);
	return (0);
}

void	catch_segfault(void)
{
	sa.sa_handler = segfault_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGSEGV, &sa, NULL);
}

void	default_sigaction(void)
{
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGSEGV, &sa, NULL);
}

void	segfault_handler(int sig)
{
	(void)sig;
	siglongjmp(env, 1);
}

void	exit_error(char *str, char *free_str)
{
	if (free_str)
		free(free_str);
	remove("test.txt");
	printf(RED"%s\n"RESET, str);
	exit(1);
}

char	*fdtostr(char *file)
{
	int		fd;
	int		ret;
	char	buf[4096];
	char	*str;
	size_t	size;

	size = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((ret = read(fd, buf, 4096)) > 0)
		size += ret;
	close(fd);
	str = calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(str);
		return (NULL);
	}
	read(fd, str, size);
	close(fd);
	return (str);
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

void	test_strlen(char **tab)
{
	int		i = 0;
	size_t	len;
	char	*str;

	// Classic tests
	printf(PURPLE"\t--- ft_strlen ---\n"RESET);
	while (tab[i])
	{
		len = 0;
		ASSERT_EXPR_CONDITION(len = ft_strlen(tab[i]), len == strlen(tab[i]));
		printf(BLUE"ft_strlen(\"%s\") = %lu\n"RESET, tab[i], len);
		i++;
	}

	// NULL tests
	len = 0;
	EXPECT_SEGFAULT(ft_strlen(NULL));
	printf(BLUE"ft_strlen(NULL)\n"RESET);

	// Ferry big string test
	len = 0;
	str = calloc(UINT_MAX, sizeof(char));
	if (!str)
	{
		printf(RED"failed to allocate str[UINT_MAX]\n"RESET);
		return;
	}
	str = memset(str, 'c', UINT_MAX - 1);
	ASSERT_EXPR_CONDITION(len = ft_strlen(str), len == strlen(str));
	printf(BLUE"ft_strlen(str[UINT_MAX]) = %lu\n"RESET, len);
	free(str);
}

void test_strcpy(char **tab)
{
	int		i = 0;
	char	*src;
	char	*dest;
	char	destNULL[1];

	// Classic tests
	printf(PURPLE"\t--- ft_strcpy ---\n"RESET);
	while (tab[i])
	{
		dest = calloc(strlen(tab[i]) + 1, sizeof(char));
		if (!dest)
			exit_error("failed to allocate str", NULL);
		ASSERT_EXPR_CONDITION(ft_strcpy(dest, tab[i]), !strcmp(dest, tab[i]) && dest != tab[i]);
		printf(BLUE"ft_strcpy(dest, \"%s\")\n"RESET, dest);
		free(dest);
		i++;
	}

	// NULL tests
	EXPECT_SEGFAULT(ft_strcpy(destNULL, NULL));
	printf(BLUE"ft_strcpy(dest, NULL)\n"RESET);
	EXPECT_SEGFAULT(ft_strcpy(NULL, "test"));
	printf(BLUE"ft_strcpy(NULL, src)\n"RESET);

	// Ferry big string test
	src = calloc(UINT_MAX, sizeof(char));
	if (!src)
		exit_error("failed to allocate src", NULL);
	src = memset(src, 'c', UINT_MAX - 1);
	dest = calloc(UINT_MAX, sizeof(char));
	if (!dest)
		exit_error("failed to allocate dest", src);
	ASSERT_EXPR_CONDITION(ft_strcpy(dest, src), !strcmp(dest, src) && dest != src);
	printf(BLUE"ft_strcpy(dest, str[UINT_MAX])\n"RESET);
	free(src);
	free(dest);
}

void test_strcmp(char **tab)
{
	int		i = 0;
	int		j;
	int		ret;
	char	*str;

	// Classic tests
	printf(PURPLE"\t--- ft_strcmp ---\n"RESET);
	while (tab[i])
	{
		j = 0;
		while (tab[j])
		{
			ret = 0;
			ASSERT_EXPR_CONDITION(ret = ft_strcmp(tab[i], tab[j]),
			ret > 0 ? strcmp(tab[i], tab[j]) > 0 : \
			ret < 0 ? strcmp(tab[i], tab[j]) < 0 : \
			ret == strcmp(tab[i], tab[j]));
			printf(BLUE"ft_strcmp(\"%s\", \"%s\") = %d\n"RESET, tab[i], tab[j], ret);
			j++;
		}
		i++;
	}

	// NULL tests
	ret = 0;
	EXPECT_SEGFAULT(ft_strcmp("test", NULL));
	printf(BLUE"ft_strcmp(dest, NULL)\n"RESET);
	ret = 0;
	EXPECT_SEGFAULT(ft_strcmp(NULL, "test"));
	printf(BLUE"ft_strcmp(NULL, src)\n"RESET);

	// Ferry big string test
	ret = 0;
	str = calloc(UINT_MAX, sizeof(char));
	if (!str)
		exit_error("failed to allocate str", NULL);
	str = memset(str, 'c', UINT_MAX - 1);
	ASSERT_EXPR_CONDITION(ret = ft_strcmp(str, str), ret == 0);
	printf(BLUE"ft_strcmp(str[UINT_MAX], str[UINT_MAX]) = %d\n"RESET, ret);
	ret = 0;
	ASSERT_EXPR_CONDITION(ret = ft_strcmp(str, str + 1), ret > 0);
	printf(BLUE"ft_strcmp(str[UINT_MAX], str[UINT_MAX - 1]) = %d\n"RESET, ret);
	ret = 0;
	ASSERT_EXPR_CONDITION(ret = ft_strcmp(str + 1, str), ret < 0);
	printf(BLUE"ft_strcmp(str[UINT_MAX - 1], str[UINT_MAX]) = %d\n"RESET, ret);
	free(str);
}

void	test_write(char **tab)
{
	int		fd;
	int		i = 0;
	ssize_t	ret;
	char	*str;

	// Classic tests
	printf(PURPLE"\t--- ft_write ---\n"RESET);
	while (tab[i])
	{
		ret = 0;
		fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit_error("failed to open test.txt", NULL);
		errno = -1;
		ASSERT_EXPR_CONDITION(ret = ft_write(fd, tab[i], strlen(tab[i])),
		ret == (ssize_t)strlen(tab[i]) && \
		(str = fdtostr("test.txt")) && \
		!strcmp(str, tab[i]) && \
		errno == -1);
		printf(BLUE"ft_write(fd, \"%s\", %lu) = %ld (\"%s\")\n"RESET, tab[i], strlen(tab[i]), ret, str);
		i++;
		if (str)
			free(str);
		close(fd);
	}
	remove("test.txt");

	// errno test
	ret = 0;
	errno = -1;
	ASSERT_EXPR_CONDITION(ret = ft_write(-1, "test", 4), ret == -1 && errno == EBADF);
	printf(BLUE"ft_write(-1, \"test\", 4) = %ld (errno = %d)\n"RESET, ret, errno);

	// NULL tests
	ret = 0;
	errno = -1;
	ASSERT_EXPR_CONDITION(ret = ft_write(1, NULL, 4), ret == -1 && errno == EFAULT);
	printf(BLUE"ft_write(1, NULL, 4) = %ld (errno = %d)\n"RESET, ret, errno);
}

void	test_read(char **tab)
{
	int		fd;
	int		i = 0;
	ssize_t	ret;
	char	*str;

	// Classic tests
	printf(PURPLE"\t--- ft_read ---\n"RESET);
	while (tab[i])
	{
		if (create_file("test.txt", tab[i]))
			exit_error("failed to create test.txt", NULL);
		str = calloc(strlen(tab[i]) + 1, sizeof(char));
		if (!str)
			exit_error("failed to allocate str", NULL);
		fd = open("test.txt", O_RDONLY);
		if (fd < 0)
			exit_error("failed to open test.txt", str);
		errno = -1;
		ASSERT_EXPR_CONDITION(ret = ft_read(fd, str, strlen(tab[i])),
		ret == (ssize_t)strlen(tab[i]) && \
		!strcmp(str, tab[i]) && \
		errno == -1);
		printf(BLUE"ft_read(fd, buf, %lu) = %ld (\"%s\")\n"RESET, strlen(tab[i]), ret, str);
		free(str);
		close(fd);
		i++;
	}
	remove("test.txt");

	// errno test
	ASSERT_EXPR_CONDITION(ret = ft_read(-1, "test", 4), ret == -1 && errno == EBADF);
	printf(BLUE"ft_read(-1, \"test\", 4) = %ld (errno = %d)\n"RESET, ret, errno);
}

void	test_strdup(char **tab)
{
	int		i = 0;
	char	*str;
	char	*dup;

	// Classic tests
	printf(PURPLE"\t--- ft_strdup ---\n"RESET);
	while (tab[i])
	{
		// TEST((str[0] = ft_strdup(tab[i])) && !strcmp(str[0], tab[i]));
		ASSERT_EXPR_CONDITION(dup = ft_strdup(tab[i]), dup && !strcmp(dup, tab[i]) && dup != tab[i]);
		printf(BLUE"ft_strdup(\"%s\") = \"%s\"\n"RESET, tab[i], dup);
		if (dup != tab[i])
			free(dup);
		i++;
	}

	// NULL tests
	EXPECT_SEGFAULT(ft_strdup(NULL));
	printf(BLUE"ft_strdup(NULL)\n"RESET);

	// Ferry big string test
	str = calloc(UINT_MAX, sizeof(char));
	if (!str)
		exit_error("failed to allocate str[UINT_MAX]", NULL);
	str = memset(str, 'c', UINT_MAX - 1);
	ASSERT_EXPR_CONDITION(dup = ft_strdup(str), dup && !strcmp(dup, str) && dup != str);
	printf(BLUE"ft_strdup(str[UINT_MAX])\n"RESET);
	if (dup != str)
		free(dup);
	free(str);
}
