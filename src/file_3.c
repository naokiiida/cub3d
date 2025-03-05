/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:42:34 by niida             #+#    #+#             */
/*   Updated: 2025/03/05 15:58:48 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <errno.h>

static int	count_strings(char **arr)
{
	int	count;

	count = 0;
	while (*arr++)
		count++;
	return (count);
}

int	validate_file(char *file, const char *expect_ext)
{
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (ext == NULL)
		return (err("validate_file", "No file extension"));
	if (ft_strcmp(ext, expect_ext) != 0)
		return (err("validate_file", "Invalid file extension"));
	return (EXIT_SUCCESS);
}

void	remove_trailing(char *line, char delim)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
		i++;
	while (i > 0 && line[i - 1] == delim)
		i--;
	line[i] = '\0';
}

int	parse_rgb(int *color, char *input)
{
	char	**rgb;
	int		i;
	int		num;

	rgb = ft_split(input, ',');
	if (count_strings(rgb) != 3)
		return (err("parse_rgb", "Invalid RGB format"));
	i = -1;
	while (rgb[++i])
		remove_trailing(rgb[i], ' ');
	i = 0;
	while (rgb[i])
	{
		errno = 0;
		num = ft_atoi_mod(rgb[i]);
		if (num < 0 || num > 255 || errno)
			return (err("parse_rgb", "RGB values must be between 0-255"));
		*color = (*color << 8) | num;
		i++;
	}
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	return (EXIT_SUCCESS);
}

int	handle_texture_path(char **kv, char **path_ptr)
{
	if (count_strings(kv) != 2)
		return (err("check_elements", "More than one key pair"));
	if (validate_file(kv[1], ".xpm") == EXIT_FAILURE)
		return (err("check_elements", "No .xpm extension found"));
	*path_ptr = ft_strdup(kv[1]);
	if (!path_ptr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
