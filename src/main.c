/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:40:44 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/22 15:19:12 by niida            ###   ########.fr       */
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
	mlx_hook(vars.win, X_EVENT_KEY_PRESS, X_KEY_PRESS_MASK, &key_press, &vars);
	mlx_hook(vars.win, X_EVENT_KEY_RELEASE, X_KEY_RELEASE_MASK, &key_release, &vars);
	mlx_hook(vars.win, X_EVENT_KEY_EXIT, X_STRUCTURE_NOTIFY_MASK, &close_win, &vars);
	// フレームごとに呼び出される関数
	mlx_loop_hook(vars.mlx, &raycasting, &vars);
	// // loopの開始update
	// raycasting(&vars);
	mlx_loop(vars.mlx);
	close_display(&vars);
	return (0);
}
