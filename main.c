/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/18 17:10:02 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "libasm.h"

int main(int argc, char const **argv)
{
	printf("ft_write(1, \"Hello World!\\n\", 13) = %ld\n", ft_write(1, "Hello World!\n", 13));
	perror("errno");

	printf("ft_write(-1, \"Hello World!\\n\", 13) = %ld\n", ft_write(-1, "Hello World!\n", 13));
	perror("errno");

	errno = 0;

	int	fd = open("main.c", O_RDONLY);

	char	buf[891];

	ssize_t	size = ft_read(fd, buf, 891);
	if (size == 891)
		buf[size - 1] = '\0';
	else
		buf[size] = '\0';

	close (fd);

	printf("tf_read(fd, buf, 891) = %ld\n", size);
	perror("errno");
	printf("%s\n", buf);

	printf("ft_read(-1, buf, 891) = %ld\n", ft_read(-1, buf, 891));
	perror("errno");

	printf("ft_strlen(\"Hello World!\") = %ld\n", ft_strlen("Hello World!"));

	printf("ft_strcmp(\"Hello World!\", \"Hello World!\") = %d\n", ft_strcmp("Hello World!", "Hello World!"));
	printf("ft_strcmp(\"Hello World!\", \"Hello World\") = %d\n", ft_strcmp("Hello World!", "Hello World"));

	printf("ft_strcpy(buf, \"Hello World!\") = %s\n", ft_strcpy(buf, "Hello World!"));

	char	*s = ft_strdup("const char *s");

	printf("ft_strdup(\"const char *s\") = %s\n", s);

	free(s);

	return (0);
}

