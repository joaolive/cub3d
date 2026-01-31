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

// // Helper para carregar textura e calcular as masks
// static void	load_texture(t_game *game, int idx, char *path)
// {
// 	mlx_texture_t	*tex;

// 	tex = mlx_load_png(path);
// 	if (!tex)
// 	{
// 		fprintf(stderr, "Erro: Não foi possível carregar a textura: %s\n", path);
// 		exit(EXIT_FAILURE);
// 	}
// 	game->walls[idx].tex = tex;
// 	// Otimização: Se a textura for potência de 2 (64, 128...),
// 	// a mask é (tamanho - 1). Útil para o cálculo de textura wrapping.
// 	game->walls[idx].width_mask = tex->width - 1;
// 	game->walls[idx].height_mask = tex->height - 1;
// }

// static void	init_mock_textures(t_game *game)
// {
// 	// Caminhos sugeridos - altere conforme seus arquivos reais
// 	load_texture(game, TEX_NORTH, "./assets/north.png");
// 	load_texture(game, TEX_SOUTH, "./assets/south.png");
// 	load_texture(game, TEX_WEST,  "./assets/west.png");
// 	load_texture(game, TEX_EAST,  "./assets/east.png");

// 	// Cores em Hex (RRGGBBAA)
// 	game->ceiling = 0x87CEEBFF; // Azul céu
// 	game->floor = 0x228B22FF;   // Verde grama
// }

// static void	init_mock_player(t_game *game)
// {
// 	// Posição inicial (centro do quadrado livre no mapa abaixo)
// 	game->player.pos.x = 3.5;
// 	game->player.pos.y = 3.5;

// 	// Vetor de Direção: Olhando para Norte (assumindo Y para cima negativo)
// 	// No cub3D, geralmente Y cresce para baixo, então Norte = (0, -1)
// 	game->player.dir.x = 0.0;
// 	game->player.dir.y = -1.0;

// 	// Plano da Câmera: Perpendicular à direção
// 	// Para FOV de ~66 graus, o plano deve ter comp ~0.66 da direção
// 	game->player.plane.x = 0.66;
// 	game->player.plane.y = 0.0;
// }

// static void	init_mock_grid(t_game *game)
// {
// 	int		i;

// 	game->map.width = 8;
// 	game->map.height = 8;
// 	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));

// 	// Mapa 8x8 fechado
// 	// 1 = Parede, 0 = Chão
// 	char *temp_map[] = {
// 		"11111111",
// 		"10101001",
// 		"10101001",
// 		"100N0001",
// 		"10000001",
// 		"10001001",
// 		"10000001",
// 		"11111111",
// 		NULL
// 	};

// 	i = 0;
// 	while (i < game->map.height)
// 	{
// 		game->map.grid[i] = ft_strdup(temp_map[i]);
// 		i++;
// 	}
// }

// void	init_mock_map(t_game *game)
// {
// 	init_mock_grid(game);
// 	init_mock_player(game);
// 	init_mock_textures(game);

// 	// Inicialização de flags e variáveis de controle
// 	game->player.mov_flags = 0;
// }

static int	load_world_assets(t_game *game)
{
	mlx_texture_t	*t;

	t = mlx_load_png("./assets/wall/north.png");
	if (t) ft_htabinsert(game->assets, "n", t);
	t = mlx_load_png("./assets/wall/south.png");
	if (t) ft_htabinsert(game->assets, "s", t);
	t = mlx_load_png("./assets/wall/east.png");
	if (t) ft_htabinsert(game->assets, "e", t);
	t = mlx_load_png("./assets/wall/west.png");
	if (t) ft_htabinsert(game->assets, "w", t);
	// t = mlx_load_png("./assets/door/wall-close.png");
	// if (t) ft_htabinsert(game->assets, "door_c", t);

	if (!ft_tabget(game->assets, "n"))
		return (1);
	return (0);
}

void    init_mock_map(t_game *game)
{
	mlx_texture_t   *tex;
	char            *wall_keys[4] = {"n", "s", "w", "e"};
	int             i;

	game->assets = ft_calloc(1, sizeof(t_htab));
	game->assets->size = 31;
	game->assets->buckets = ft_calloc(game->assets->size, sizeof(t_hnode *));
	if (load_world_assets(game))
		exit(1);
	//load_player_assets(game);

	game->map.height = 16;
	game->map.grid = malloc(sizeof(char *) * 17);
	game->map.grid[0]  = ft_strdup("  111111            ");
	game->map.grid[1]  = ft_strdup("  100001            ");
	game->map.grid[2]  = ft_strdup("11101111            ");
	game->map.grid[3]  = ft_strdup("10001               ");
	game->map.grid[4]  = ft_strdup("10111      1111111  ");
	game->map.grid[5]  = ft_strdup("101        1000001  ");
	game->map.grid[6]  = ft_strdup("101111111111011101  ");
	game->map.grid[7]  = ft_strdup("10000000000001 101  ");
	game->map.grid[8]  = ft_strdup("11111111111101 101  ");
	game->map.grid[9]  = ft_strdup("           101 10111");
	game->map.grid[10] = ft_strdup("      111111011101001111111");
	game->map.grid[11] = ft_strdup("      100000000000000000011");
	game->map.grid[12] = ft_strdup("      10111111000000000000011");
	game->map.grid[13] = ft_strdup("      101    1010000111111111");
	game->map.grid[14] = ft_strdup("      111    11100001   ");
	game->map.grid[15] = ft_strdup("               11111    ");
	game->map.grid[16] = NULL;

	// --- CORREÇÃO: Cálculo dinâmico do Width ---
	game->map.width = 0;
	i = -1;
	while (game->map.grid[++i])
	{
		int len = ft_strlen(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
	}

	game->player.pos = (t_vec){3.5, 1.5};
	game->player.dir = (t_vec){0, 1};
	game->player.plane = (t_vec){-0.66, 0};

	i = -1;
	while (++i < 4)
	{
		tex = ft_tabget(game->assets, wall_keys[i]);
		game->walls[i].tex = tex;
		game->walls[i].width_mask = tex->width - 1;
		game->walls[i].height_mask = tex->height - 1;
	}
	game->floor = 0x87CEEBFF;
	game->ceiling = 0x228B22FF;
}
