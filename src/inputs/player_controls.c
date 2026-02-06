/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 10:38:32 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/11 15:47:31 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_flag(t_game *game, uint8_t flag, int action)
{
	if (action == MLX_PRESS)
		game->player.mov_flags |= flag;
	else if (action == MLX_RELEASE)
		game->player.mov_flags &= ~flag;
}

void	player_controls(mlx_key_data_t key, t_game *game)
{
	if (key.key == MLX_KEY_W)
		set_flag(game, FLAG_MOVE_W, key.action);
	else if (key.key == MLX_KEY_A)
		set_flag(game, FLAG_MOVE_A, key.action);
	else if (key.key == MLX_KEY_S)
		set_flag(game, FLAG_MOVE_S, key.action);
	else if (key.key == MLX_KEY_D)
		set_flag(game, FLAG_MOVE_D, key.action);
	else if (key.key == MLX_KEY_LEFT)
		set_flag(game, FLAG_ROT_L, key.action);
	else if (key.key == MLX_KEY_RIGHT)
		set_flag(game, FLAG_ROT_R, key.action);
}
