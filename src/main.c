/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:40:44 by sasano            #+#    #+#             */
/*   Updated: 2025/02/15 04:02:11 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	// ゲームの初期化
	init(&vars);
	// hookの設定　キー入力、キー解放、ウィンドウの閉じるボタン
	// mlx_hook(vars.win, X_EVENT_KEY_PRESS, 0, &key_press, &vars);
	// mlx_hook(vars.win, X_EVENT_KEY_RELEASE, 0, &key_release, &vars);
	// mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &close, &vars);
	// フレームごとに呼び出される関数
	mlx_loop_hook(vars.mlx, &raycasting, &vars);
	// loopの開始update
	mlx_loop(vars.mlx);
}
