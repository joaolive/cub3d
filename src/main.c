/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:27:59 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/02 18:00:04 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
	t_game	game;
	ft_bzero(&game, sizeof(t_game));
	if (init_window(&game))
		return (1);
	init_mock_map(&game); // mapa mockado
	render_player(&game);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	// terminate(game); // TODO
	return (0);
}
