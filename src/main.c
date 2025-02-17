/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:40:44 by sasano            #+#    #+#             */
/*   Updated: 2025/02/14 17:45:56 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int main(int argc, char *argv[])
{
  t_vars vars;

  // 初期化
  init_vars(&vars);

  // hookの設定　キー入力、キー解放、ウィンドウの閉じるボタン
  // mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);  
  // mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
  // mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &close, &game);
  // フレームごとに呼び出される関数
  mlx_loop_hook(vars.mlx, &raycasting, &vars);　
  // loopの開始update
  mlx_loop(game.mlx); 
}
