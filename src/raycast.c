/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:00 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/23 19:56:39 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
