/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/16 19:26:01 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "libasm.h"

int main(int argc, char const **argv)
{
	printf("return %ld\n", ft_write(1, "Hello World!\n", 13));
	perror("errno");

	printf("return %ld\n", ft_write(-1, "Hello World!\n", 13));
	perror("errno");

	int	fd = open("main.c", O_RDONLY);

	char	buf[5000];

	ssize_t	size = ft_read(fd, buf, 5000);
	perror("errno");
	if (size == 5000)
		buf[size - 1] = '\0';
	else
		buf[size] = '\0';

	close (fd);

	printf("return %ld\n", size);
	printf("%s\n", buf);

	printf("return %ld\n", ft_read(-1, buf, 5000));
	perror("errno");

	printf("return %ld\n", ft_strlen(""));

	printf("return %d\n", ft_strcmp("kkkkkk0", "kkkkkk"));

	printf("return %s\n", ft_strcpy(buf, "bonjour"));
	printf("return %s\n", buf);

	char	*s = ft_strdup("const char *s");

	printf("return %s\n", s);

	free(s);

	return (0);
}

