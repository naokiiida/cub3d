/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:40:44 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/25 23:13:11 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	(void)argv;
	if (argc != 2)
	{
		printf("usage: cub3D <single.cub>\n");
		return (0);
	}

	if (get_input(argv[1], &vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// ゲームの初期化
	if (init(&vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// hookの設定　キー入力、キー解放、ウィンドウの閉じるボタン
	mlx_hook(vars.win, EVENT_KEY_PRESS, M_KEY_PRESS, &key_press, &vars);
	mlx_hook(vars.win, EVENT_KEY_RELEASE, M_KEY_RELEASE, &key_release, &vars);
	mlx_hook(vars.win, EVENT_KEY_EXIT, M_STRUCTURE_NOTIFY, &close_win, &vars);
	// フレームごとに呼び出される関数
	mlx_loop_hook(vars.mlx, &raycasting, &vars);
	// // loopの開始update
	// raycasting(&vars);
	mlx_loop(vars.mlx);
	close_display(&vars);
	return (EXIT_SUCCESS);
}
