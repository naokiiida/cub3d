/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano.stu>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:07:21 by sasano            #+#    #+#             */
/*   Updated: 2023/11/27 14:28:00 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(int fd, char *tmp)
{
	char	*buffer;
	ssize_t	bytesread;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + (size_t)1));
	if (!buffer)
		return (NULL);
	bytesread = 1;
	while (judge_read(tmp) && bytesread != 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytesread] = '\0';
		tmp = gnl_strjoin(tmp, buffer);
	}
	free(buffer);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*tmp[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp[fd] = get_line(fd, tmp[fd]);
	if (!tmp[fd])
		return (NULL);
	line = take_out_line(tmp[fd]);
	tmp[fd] = new_tmp(tmp[fd]);
	return (line);
}

// int	main(void)
// {
// 	char *line;
// 	int fd;
// 	int fd1;

// 	fd = open("test.txt", O_RDONLY);
// 	fd1 = open("test1.txt", O_RDONLY);
// 	line = get_next_line(4);
// 	printf("read:%s\n", line);
// 	line = get_next_line(fd);
// 	printf("read:%s\n", line);
// 	line = get_next_line(fd1);
// 	printf("read:%s\n", line);
// 	line = get_next_line(fd);
// 	printf("read:%s\n", line);
// 	line = get_next_line(fd1);
// 	printf("read:%s\n", line);
// 	line = get_next_line(fd);
// 	printf("read:%s\n", line);
// 	line = get_next_line(fd1);
// 	printf("read:%s\n", line);
// 	close(fd);
// 	close(fd1);
// 	return (0);
// }