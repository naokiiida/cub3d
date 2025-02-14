/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano.stu>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:09:20 by sasano            #+#    #+#             */
/*   Updated: 2023/11/27 11:28:28 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *tmp, char *buffer)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc(sizeof(char) * (gnl_strlen(tmp) + gnl_strlen(buffer) + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (tmp)
	{
		while (tmp[i])
		{
			str[i] = tmp[i];
			i++;
		}
		free(tmp);
	}
	j = 0;
	while (buffer[j])
	{
		str[i++] = buffer[j++];
	}
	str[i] = '\0';
	return (str);
}

int	judge_read(char *tmp)
{
	if (!tmp)
		return (1);
	while (*tmp)
	{
		if (*tmp == '\n')
			return (0);
		tmp++;
	}
	return (1);
}

char	*take_out_line(char *tmp)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!tmp[i])
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (tmp[++i] != '\n' && tmp[i] != '\0')
		line[i] = tmp[i];
	if (tmp[i] == '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*new_tmp(char *tmp)
{
	size_t	i;
	size_t	j;
	char	*new_tmp;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (NULL);
	}
	i++;
	new_tmp = malloc(sizeof(char) * (gnl_strlen(tmp) - i + 1));
	if (!new_tmp)
		return (NULL);
	j = 0;
	while (tmp[i])
		new_tmp[j++] = tmp[i++];
	new_tmp[j] = '\0';
	free(tmp);
	return (new_tmp);
}
