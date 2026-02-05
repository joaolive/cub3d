/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:27:59 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/31 18:00:14 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	if (parse_map_file(argv[1], &game))
	{
		free_game_resources(&game); // Adicionado: Libera recursos em caso de falha no parsing
		return (1);
	}
	if (init_window(&game))
	{
		free_game_resources(&game); // Adicionado: Libera recursos em caso de falha na inicialização da janela
		return (1);
	}

	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	free_game_resources(&game); // Substituído: Chamada à nova função de liberação de recursos
	return (0);
}
