/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:00 by naokiiida         #+#    #+#             */
/*   Updated: 2025/03/06 16:56:35 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calculate_camera_x(int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1;
	return (camera_x);
}

static t_vector2d	calculate_delta_dist(t_vector2d ray_dir)
{
	t_vector2d	delta_dist;

	if (ray_dir.x == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(1 / ray_dir.y);
	return (delta_dist);
}

static void	calculate_step_and_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->grid.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->grid.x + 1.0 - player->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->grid.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->grid.y + 1.0 - player->pos.y)
			* ray->delta_dist.y;
	}
}

void	init_ray(t_vars *vars, int x)
{
	double		camera_x;
	t_player	*p;

	p = vars->player;
	camera_x = calculate_camera_x(x);
	vars->ray->dir = vector_add(p->dir, vector_scale(p->plane, camera_x));
	vars->ray->grid.x = (int)p->pos.x;
	vars->ray->grid.y = (int)p->pos.y;
	vars->ray->delta_dist = calculate_delta_dist(vars->ray->dir);
	calculate_step_and_side_dist(vars->ray, p);
}
