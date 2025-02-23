/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:00 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/23 18:31:07 by niida            ###   ########.fr       */
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

// 壁に当たったか判定
static bool	is_hit_wall(int map[ROWS][COLS], t_grid grid)
{
	if (map[grid.x][grid.y] != MAP_BLANK)
		return (true);
	return (false);
}

// DDAアルゴリズムによる壁の衝突判定
void	perform_dda(t_ray *ray, int map[ROWS][COLS])
{
	while (!is_hit_wall(map, ray->grid))
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			// 現在地のrayの次の整数座標までの値を追加する
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

// 壁までの距離を計算
void	calculate_perp_wall_dist(t_ray *ray)
{
	if (ray->side == X_AXIS)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

// 描画する壁の大きさの判定
void	calculate_wall_size(t_ray *ray, t_texture *texture)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	texture->draw_start = -line_height / 2 + HEIGHT / 2;
	if (texture->draw_start < 0)
		texture->draw_start = 0;
	texture->draw_end = line_height / 2 + HEIGHT / 2;
	if (texture->draw_end >= HEIGHT)
		texture->draw_end = HEIGHT - 1;
	// 画面ピクセルあたりのテクスチャ座標の増分を計算
	texture->step = 1.0 * TEXTURE_HEIGHT / line_height;
	texture->line_height = line_height;
}

// 壁の東西南北のテクスチャの決定
void	decide_draw_texture(t_ray *ray, t_texture *texture)
{
	if (ray->side == X_AXIS)
	{
		if (ray->dir.x < 0)
			texture->id = WEST_WALL;
		else
			texture->id = EAST_WALL;
	}
	else
	{
		if (ray->dir.y < 0)
			texture->id = NORTH_WALL;
		else
			texture->id = SOUTH_WALL;
	}
}

// ヒットしたx座標を特定
static double	get_wall_x(t_ray *ray, t_player *player)
{
	double	wall_x;

	if (ray->side == X_AXIS)
		wall_x = (player->pos.y + ray->perp_wall_dist * ray->dir.y);
	else
		wall_x = (player->pos.x + ray->perp_wall_dist * ray->dir.x);
	wall_x -= floor(wall_x);
	assert(wall_x >= 0.0);
	assert(wall_x <= 1.0);
	return (wall_x);
}

// ヒットした壁のローカル座標を特定
int get_texture_x(t_ray *ray, t_player *player)
{
	int		tex_x;
	double	wall_x;

	wall_x = get_wall_x(ray, player);
	tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == X_AXIS && ray->dir.x > 0)
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	if (ray->side == Y_AXIS && ray->dir.y < 0)
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	return (tex_x);
}

// フレームごとに描画を更新する関数
int	raycasting(t_vars *vars)
{
	int	x;

	x = -1;
	// 描画バッファの初期化
	// init(vars);
	// x方向にrayを飛ばす
	while (++x < WIDTH)
	{
		// rayの初期化
		init_ray(vars, x);
		// DDAによる壁の衝突判定
		perform_dda(vars->ray, vars->map);
		// 壁までの距離を計算
		calculate_perp_wall_dist(vars->ray);
		// 描画する壁の大きさの判定
		calculate_wall_size(vars->ray, vars->texture);
		// 壁のテクスチャ判定
		decide_draw_texture(vars->ray, vars->texture);
		// ヒットした壁のローカル座標を特定
		vars->texture->tex_x = get_texture_x(vars->ray, vars->player);
		// 描画バッファに壁を描画
		draw_buffer(vars, x);
	}
	draw(vars);
	return (0);
}
