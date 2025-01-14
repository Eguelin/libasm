/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:27:51 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/14 15:28:28 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

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
