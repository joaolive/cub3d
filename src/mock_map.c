/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* mock.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/01/21 12:00:00 by joaolive          #+#    #+#             */
/* Updated: 2026/01/21 12:00:00 by joaolive         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "cub3d.h"

// Helper para carregar textura e calcular as masks
static void	load_texture(t_game *game, int idx, char *path)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(path);
	if (!tex)
	{
		fprintf(stderr, "Erro: Não foi possível carregar a textura: %s\n", path);
		exit(EXIT_FAILURE);
	}
	game->tex.walls[idx].tex = tex;
	// Otimização: Se a textura for potência de 2 (64, 128...),
	// a mask é (tamanho - 1). Útil para o cálculo de textura wrapping.
	game->tex.walls[idx].width_mask = tex->width - 1;
	game->tex.walls[idx].height_mask = tex->height - 1;
}

static void	init_mock_textures(t_game *game)
{
	// Caminhos sugeridos - altere conforme seus arquivos reais
	load_texture(game, TEX_NORTH, "./assets/north.png");
	load_texture(game, TEX_SOUTH, "./assets/south.png");
	load_texture(game, TEX_WEST,  "./assets/west.png");
	load_texture(game, TEX_EAST,  "./assets/east.png");

	// Cores em Hex (RRGGBBAA)
	game->tex.ceiling = 0x87CEEBFF; // Azul céu
	game->tex.floor = 0x228B22FF;   // Verde grama
}

static void	init_mock_player(t_game *game)
{
	// Posição inicial (centro do quadrado livre no mapa abaixo)
	game->player.pos_x = 3.5;
	game->player.pos_y = 3.5;

	// Vetor de Direção: Olhando para Norte (assumindo Y para cima negativo)
	// No cub3D, geralmente Y cresce para baixo, então Norte = (0, -1)
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;

	// Plano da Câmera: Perpendicular à direção
	// Para FOV de ~66 graus, o plano deve ter comp ~0.66 da direção
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
}

static void	init_mock_grid(t_game *game)
{
	int		i;

	game->map.width = 8;
	game->map.height = 8;
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));

	// Mapa 8x8 fechado
	// 1 = Parede, 0 = Chão
	char *temp_map[] = {
		"11111111",
		"10101001",
		"10101001",
		"100N0001",
		"10000001",
		"10001001",
		"10000001",
		"11111111",
		NULL
	};

	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_strdup(temp_map[i]);
		i++;
	}
}

void	init_mock_map(t_game *game)
{
	init_mock_grid(game);
	init_mock_player(game);
	init_mock_textures(game);

	// Inicialização de flags e variáveis de controle
	game->player.mov_flags = 0;
}
