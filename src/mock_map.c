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

#include "cub3d.h"

static int  load_game_assets(t_game *game)
{
    // Carrega as paredes (count 1: busca apenas o arquivo _0)
    if (load_textures(game, "n_0", "./assets/wall/north_0.png", 1)
        || load_textures(game, "s_0", "./assets/wall/south_0.png", 1)
        || load_textures(game, "w_0", "./assets/wall/west_0.png", 1)
        || load_textures(game, "e_0", "./assets/wall/east_0.png", 1))
        return (1);

    // Carrega os 5 frames do player automaticamente (p_0 até p_4)
    if (load_images(game, "p_0", "./assets/player/p_0.png", 5))
        return (1);

    return (0);
}

static void map_wall_textures(t_game *game)
{
    // Esta ordem é CRUCIAL para bater com o IDs do tex_info: {W, E, N, S}
    char *keys[4] = {"w_0", "e_0", "n_0", "s_0"};
    int  i;

    i = 0;
    while (i < 4)
    {
        game->walls[i].tex = ft_tabget(game->assets, keys[i]);

        // Se a Hash Table falhar, o programa para aqui com erro claro
        if (!game->walls[i].tex)
        {
            printf("Erro Crítico: Chave '%s' não encontrada na Hash Table!\n", keys[i]);
            exit(1);
        }

        // Preenche os metadados que o tex_info usa
        game->walls[i].width_mask = game->walls[i].tex->width - 1;
        game->walls[i].height_mask = game->walls[i].tex->height - 1;
        i++;
    }
}

void    init_mock_map(t_game *game)
{
    int i;

    // 1. Inicializa a Hash Table (ajuste o tamanho conforme necessário)
    game->assets = ft_calloc(1, sizeof(t_htab));
    game->assets->size = 31;
    game->assets->buckets = ft_calloc(game->assets->size, sizeof(t_hnode *));

    // 2. Carrega e Mapeia os Assets
    if (load_game_assets(game))
    {
        ft_putstr_fd("Error: Failed to load assets from files.\n", 2);
        exit(1);
    }
    map_wall_textures(game);

    // 3. Configura o Grid do Mapa
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

    // 4. Cálculo dinâmico do Width para colisão e render
    game->map.width = 0;
    i = -1;
    while (game->map.grid[++i])
    {
        int len = ft_strlen(game->map.grid[i]);
        if (len > game->map.width)
            game->map.width = len;
    }

    // 5. Configuração do Player e Ambiente
    game->player.pos = (t_vec){3.5, 1.5};
    game->player.dir = (t_vec){0, 1};
    game->player.plane = (t_vec){-0.66, 0};
    game->floor = 0x87CEEBFF;
    game->ceiling = 0x228B22FF;
}
