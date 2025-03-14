/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:00 by naokiiida         #+#    #+#             */
/*   Updated: 2025/03/14 17:31:03 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_hit_wall(int **map, t_grid grid)
{
	if (map[grid.y][grid.x] != MAP_BLANK)
		return (true);
	return (false);
}

void	perform_dda(t_ray *ray, int **map)
{
	while (!is_hit_wall(map, ray->grid))
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->grid.x += ray->step.x;
			ray->side = X_AXIS;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->grid.y += ray->step.y;
			ray->side = Y_AXIS;
		}
	}
}

int	raycasting(t_vars *vars)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(vars, x);
		perform_dda(vars->ray, vars->map);
		calculate_perp_wall_dist(vars->ray);
		calculate_wall_size(vars->ray, vars->texture);
		decide_draw_texture(vars->ray, vars->texture, vars->player);
		vars->texture->tex_x = get_texture_x(vars->ray, vars->player);
		draw_buffer(vars, x);
	}
	draw(vars);
	return (0);
}
