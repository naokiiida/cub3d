/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:42:34 by niida             #+#    #+#             */
/*   Updated: 2025/03/05 13:22:36 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "cub3d.h"

// #ifdef LEAK_CHECK

// __attribute__((destructor)) static void	destructor(void)
// {
// 	system("leaks -q cub3D");
// }
// #endif

// static void	print_map(int **map, t_grid map_size);

// static int	err(char *function_name, const char *msg)
// {
// 	ft_putendl_fd("Error", 2);
// 	ft_putstr_fd(function_name, 2);
// 	ft_putstr_fd(":\t", 2);
// 	perror(msg);
// 	return (EXIT_FAILURE);
// }
int	ft_atoi_mod(const char *str)
{
	long	result;
	long	sign;
	int		digits;

	result = 0;
	sign = 1;
	digits = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	while (*str >= '0' && *str <= '9' && digits++ < 19)
	{
		result = result * 10 + (*str++ - '0');
		if ((result > LONG_MAX / 10 || (result == LONG_MAX / 10 && *str > '7'))
			&& sign == 1)
			errno = ERANGE;
		if ((result > LONG_MAX / 10 || (result == LONG_MAX / 10 && *str > '8'))
			&& sign == -1)
			errno = ERANGE;
	}
	if (*str && (!(*str >= '0' && *str <= '9')))
		errno = EINVAL;
	return ((int)(sign * result));
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

static int	set_player(t_vars *vars, int x, int y, char c)
{
	t_player	*p;
	t_vector2d	dirs[4];
	t_vector2d	planes[4];
	int			idx;

	p = vars->player;
	if (!(p->pos.x == 0 && p->pos.y == 0) && !(p->dir.x == 0 && p->dir.y == 0))
		return (err("load_map", "player already positioned"));
	dirs[0] = (t_vector2d){0, -1};
	dirs[1] = (t_vector2d){0, 1};
	dirs[2] = (t_vector2d){-1, 0};
	dirs[3] = (t_vector2d){1, 0};
	planes[0] = (t_vector2d){0.66, 0};
	planes[1] = (t_vector2d){-0.66, 0};
	planes[2] = (t_vector2d){0, -0.66};
	planes[3] = (t_vector2d){0, 0.66};
	idx = ft_strchr("NSWE", c) - "NSWE";
	p->dir = dirs[idx];
	p->plane = planes[idx];
	p->pos = (t_vector2d){x, y};
	p->move_speed = 0.05;
	p->rot_speed = 0.05;
	return (EXIT_SUCCESS);
}

static int	process_cell(char c, t_vars *vars, int *curr_cols)
{
	printf("%c", c);
	if (ft_strchr("01 ", c))
		(*curr_cols)++;
	else if (c == '\n')
	{
		vars->map_size.y++;
		if (vars->map_size.x < *curr_cols)
			vars->map_size.x = *curr_cols;
		*curr_cols = 0;
	}
	else if (ft_strchr("NSWE", c))
	{
		if (set_player(vars, vars->map_size.y, *curr_cols, c) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(*curr_cols)++;
	}
	else
		return (err("load_map", "invalid character in map"));
	return (EXIT_SUCCESS);
}

int	load_map(char *map_data, t_vars *vars)
{
	int	curr_cols;

	vars->map_size = (t_grid){0, 0};
	curr_cols = 0;
	printf("\nloading...\n");
	while (*map_data)
	{
		if (process_cell(*map_data, vars, &curr_cols) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		map_data++;
	}
	if (vars->player->move_speed == 0 || vars->player->rot_speed == 0)
		return (err("load_map", "player not set"));
	if (curr_cols > 0)
	{
		vars->map_size.y++;
		if (vars->map_size.x < curr_cols)
			vars->map_size.x = curr_cols;
	}
	return (EXIT_SUCCESS);
}
