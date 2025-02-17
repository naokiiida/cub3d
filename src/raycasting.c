/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:00 by sasano            #+#    #+#             */
/*   Updated: 2025/02/14 17:50:34 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 壁に当たったか判定
static bool	is_hit_wall(int **map, t_ray *ray)
{
	if (0 < map[ray->x_map][ray->y_map]
		&& map[ray->x_map][ray->y_map] <= 9)
		return (true);
	return (false);
}

// カメラ平面上の位置を計算するための正規化用変数の生成関数
double calculateCameraX(int x) {
	double cameraX;

	cameraX = 2.0 * x / (double)SCREEN_WIDTH - 1;
	return cameraX;
}

// レイの方向を計算する関数
t_vector2d calculateRayDir(t_vector2d dir, t_vector2d plane, double cameraX) {
    t_vector2d rayDir;
    rayDir.x = dir.x + plane.x * cameraX;
    rayDir.y = dir.y + plane.y * cameraX;
    return rayDir;
}

// レイの移動量を計算する関数
t_vector2d calculateDeltaDist(t_vector2d rayDir)
{
	t_vector2d deltaDist;

	if (rayDir.x == 0)
		deltaDist.x = 1e30;
	else
		deltaDist.x = fabs(1 / rayDir.x);
	if (rayDir.y == 0)
		deltaDist.y = 1e30;
	else
		deltaDist.y = fabs(1 / rayDir.y);
	return deltaDist;
}

// rayの移動量の初期化と始めの整数座標までの値を求めray->side_distに代入
void calculateStepAndSideDist(t_ray *ray, t_player *player)
{
	if(ray->dir.x < 0) {
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
	} else {
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist.x;
	}
	if(ray->dir.y < 0) {
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map.y) * ray->delta_dist.y;
	} else {
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y) * ray->delta_dist.y;
	}
}

// DDAアルゴリズムによる壁の衝突判定
void performDDA(t_ray *ray, int **map)
{
	while (is_hit_wall(map, ray->map)) {
		if (ray->side_dist.x < ray->side_dist.y) {
			ray->side_dist.x += ray->delta_dist.x;
			//現在地のrayの次の整数座標までの値を追加する
			ray->map.x += ray->step.x;
			ray->side = X_AXIS;
		} else {
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = Y_AXIS;
		}
	}
}

// rayの初期化
static void	init_ray(t_vars *vars, int x)
{
	double cameraX;
	t_vector2d rayDir;

	// カメラ平面上の位置を計算
	cameraX = calculateCameraX(x);
	// rayの方向を計算
	rayDir = calculateRayDir(vars->ray->dir, vars->ray->plane, cameraX);
	// マップ上の初期座標を取得
	vars->ray->map.x = (int)vars->player->pos.x;
	vars->ray->map.y = (int)vars->player->pos.y;
	// rayの方向によって、x,y方向の移動量を計算
	vars->ray->delta_dist = calculateDeltaDist(rayDir);
	//始めの整数座標までの値を求め、ray->side_distに代入
	calculateStepAndSideDist(vars->ray, vars->player);
}

// 壁までの距離を計算
void calculatePerpWallDist(t_ray *ray)
{
	if (ray->side == X_AXIS)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

// 描画する壁の大きさの判定
void calculateWallSize(t_ray *ray, t_texture *texture)
{
	int line_height;

	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	texture->draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (texture->draw_start < 0)
		texture->draw_start = 0;
	texture->draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (texture->draw_end >= SCREEN_HEIGHT)
		texture->draw_end = SCREEN_HEIGHT - 1;
	// 画面ピクセルあたりのテクスチャ座標の増分を計算
	texture->step = 1.0 * TEXTURE_HEIGHT / line_height;
}

//壁の東西南北のテクスチャの決定
void	decide_draw_texture(t_ray *ray, t_texture *texture)
{
	if (ray->side == X_AXIS)
	{
		if (ray->dir.x < 0)
			texture->tex_num = WEST_WALL;
		else
			texture->tex_num = EAST_WALL;
	}
	else
	{
		if (ray->dir.y < 0)
			texture->tex_num = NORTH_WALL;
		else
			texture->tex_num = SOUTH_WALL;
	}
}

// ヒットしたx座標を特定
int get_wall_x(t_ray *ray, t_player *player)
{
	if (ray->side == X_AXIS)
		return (player->pos.y + ray->perp_wall_dist * ray->dir.y);
	else
		return (player->pos.x + ray->perp_wall_dist * ray->dir.x);
}

// ヒットした壁のローカル座標を特定
void get_texture_x(t_ray *ray, t_player *player,t_texture *texture)
{
	int wall_x;

	wall_x = get_wall_x(ray, player);
	texture->tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == X_AXIS && ray->dir.x > 0)
		texture->tex_x = TEXTURE_WIDTH - texture->tex_x - 1;
	if (ray->side == Y_AXIS && ray->dir.y < 0)
		texture->tex_x = TEXTURE_WIDTH - texture->tex_x - 1;
}

// フレームごとに描画を更新する関数
void    raycasting(t_vars *vars)
{
	int x;

	x = -1;
	// 描画バッファの初期化
	init_buffer(vars);
	// x方向にrayを飛ばす
	while (++x < WIN_WIDTH)
	{
		// rayの初期化
		init_ray(vars, x);
		// DDAによる壁の衝突判定
		performDDA(vars->ray, vars->map);
		// 壁までの距離を計算
		calculatePerpWallDist(vars->ray);
		// 描画する壁の大きさの判定
		calculateWallSize(vars->ray, vars->texture);
		// 壁のテクスチャ判定	
		decide_draw_texture(vars->ray, vars);	
		// ヒットした壁のローカル座標を特定
		get_wall_hit_point(vars->ray, vars->player);
		// 描画バッファに壁を描画
		draw_buffer(vars, x);
	}
	// バッファを画面に描画
	draw(vars);
}