/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:00 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/23 19:47:40 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// カメラ平面上の位置を計算するための正規化用変数の生成関数
static double	calculate_camera_x(int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1;
	return (camera_x);
}

// レイの方向を計算する関数
static t_vector2d	calculate_ray_dir(t_vector2d dir, t_vector2d plane, double cameraX)
{
	return (vector_add(dir, vector_scale(plane, cameraX)));
}

// レイの移動量を計算する関数
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

// rayの移動量の初期化と始めの整数座標までの値を求めray->side_distに代入
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

// rayの初期化
void	init_ray(t_vars *vars, int x)
{
	double		camera_x;

	// カメラ平面上の位置を計算
	camera_x = calculate_camera_x(x);
	// rayの方向を計算
	vars->ray->dir = calculate_ray_dir(vars->player->dir, vars->player->plane, camera_x);
	// マップ上の初期座標を取得 (マップの行へプレーヤーのxを当ててる)
	vars->ray->grid.x = (int)vars->player->pos.x;
	vars->ray->grid.y = (int)vars->player->pos.y;
	// rayの方向によって、x,y方向の移動量を計算
	vars->ray->delta_dist = calculate_delta_dist(vars->ray->dir);
	// 始めの整数座標までの値を求め、ray->side_distに代入
	calculate_step_and_side_dist(vars->ray, vars->player);
}
