/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:38:14 by niida             #+#    #+#             */
/*   Updated: 2025/02/15 01:25:23 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

//__attribute__((destructor)) static void destructor()
//{
//	system("leaks -q a.out");
//}
//
//void	*malloc(size_t size)
//{
//	static int	i;
//
//	if (i == 100)
//		return (NULL);
//	else
//	{
//		i++;
//		return (calloc(size, 1));
//	}
//}

int test(char *file, char *line)
{
	int		fd;
	int	i = 10;

	printf("-----fopen-----\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	printf(" fd=%d\n", fd);
	while (i-- > 0)
	{
		line = get_next_line(fd);
		printf("%s", line);
		// printf("---------GNL: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}

int test_stdin(char *line)
{
	int	fd;
	int	i;

	i = 0;
	fd = 0;
	printf("-----stdin-----\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%d]:%s\n", i++, line);
	}
	return (0);
}

int test_fd(int fd, char *line)
{
	int	i;

	i = 0;
	printf("-----fd(%d)-----\n", fd);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%d]:%s\n", i++, line);
	}
	if (!line)
		printf("ERROR: NULL\n");
	return (0);
}

int	main(void)
{
	char	*line;

	printf("[BUFFER_SIZE = %d]\n", BUFFER_SIZE);
	// test_fd(-1, line);
	 // test("newlines.txt", line);
	 // test("1.txt", line);
	 //test("2.txt", line);
	 // test("newlines.txt", line);
	 // test("1.txt", line);
	 //test("2.txt", line);
	//test_fd(3, line);
	//test_fd(256, line);
	//test_fd(1024, line);
	//test_fd(INT_MAX, line);
	//test_fd(INT_MIN, line);
	test_stdin(line);
	return (0);
}
