/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:18:41 by niida             #+#    #+#             */
/*   Updated: 2025/03/05 15:57:45 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include "get_next_line.h"

static void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	process_key(int i, t_texture *tex, char *line)
{
	if (i == 4 && !tex->floor_color)
		return (parse_rgb(&tex->floor_color, &line[2]));
	else if (i == 5 && !tex->ceiling_color)
		return (parse_rgb(&tex->ceiling_color, &line[2]));
	else
		return (err("check_elements", "Already defined"));
}

static int	check_elements(char *line, t_texture *tex, char *path[4])
{
	static char	*keys[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	char		**kv;
	int			i;
	int			status;

	kv = ft_split(line, ' ');
	if (!kv)
		return (err("check_elements", "Failed to split line"));
	status = EXIT_FAILURE;
	i = -1;
	while (keys[++i] && status != EXIT_SUCCESS)
	{
		if (ft_strcmp(kv[0], keys[i]) == 0)
		{
			if (i < 4 && !path[i])
				status = handle_texture_path(kv, &path[i]);
			else
				status = process_key(i, tex, line);
		}
	}
	if (status == EXIT_FAILURE)
		status = err("check_elements", "No valid Key found");
	free_string_array(kv);
	return (status);
}

// static void	print_map(int **map, t_grid map_size)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map_size.y)
// 	{
// 		j = 0;
// 		while (j < map_size.x)
// 		{
// 			printf("%d", map[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

static _Bool	is_all_elements_loaded(t_vars *vars)
{
	return (vars->texture->ceiling_color && vars->texture->floor_color
		&& vars->path[0] && vars->path[1] && vars->path[2] && vars->path[3]);
}

int	read_elements(int fd, t_vars *vars)
{
	char	*line;
	int		status;

	while (!is_all_elements_loaded(vars))
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			close(fd);
			return (err("read_elements", "Failed to read line"));
		}
		if (ft_strcmp(line, "\n") != 0)
		{
			remove_trailing(line, '\n');
			status = check_elements(line, vars->texture, vars->path);
			if (status == EXIT_FAILURE)
			{
				free(line);
				close(fd);
				return (EXIT_FAILURE);
			}
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
