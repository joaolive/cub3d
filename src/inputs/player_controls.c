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

void	player_controls(mlx_key_data_t key, t_game *game)
{
	static const t_keymap	map[] = {
	{MLX_KEY_W, FLAG_MOVE_W},
	{MLX_KEY_A, FLAG_MOVE_A},
	{MLX_KEY_S, FLAG_MOVE_S},
	{MLX_KEY_D, FLAG_MOVE_D},
	{MLX_KEY_LEFT, FLAG_ROT_L},
	{MLX_KEY_RIGHT, FLAG_ROT_R}
	};
	uint64_t				i;

	i = -1;
	while (++i < (sizeof(map) / sizeof(map[0])))
	{
		if (key.key == map[i].key)
		{
			if (key.action == MLX_PRESS)
				game->player.mov_flags |= map[i].value;
			else if (key.action == MLX_RELEASE)
				game->player.mov_flags &= ~map[i].value;
			return ;
		}
	}
}
