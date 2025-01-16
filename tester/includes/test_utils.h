/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:28:33 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/15 11:24:56 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# define _GNU_SOURCE
# include <stdio.h>
# include <setjmp.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include "libasm.h"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define RESET "\033[0m"

extern sigjmp_buf	env;
extern struct sigaction sa;

void	segfault_handler(int sig);
void	catch_segfault(void);
void	default_sigaction(void);
void	exit_error(char *str, char *free_str);
char	*fdtostr(char *file);
int		create_file(char *file, char *str);

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

#endif
