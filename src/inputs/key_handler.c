/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 10:26:20 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/11 15:40:28 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_handler(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		//terminate(game); //TODO
		return ;
	}
	player_controls(key, game);
}
