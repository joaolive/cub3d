/* ************************************************************************** */
/* */
/* mock.c                                             :+:      :+:    :+:   */
/* Inicializa dados falsos para teste de renderização e física.             */
/* */
/* ************************************************************************** */

#include "cub3d.h"

static char *mock_strdup(const char *s)
{
    char    *d;
    size_t  len;

    len = ft_strlen(s);
    d = malloc(len + 1);
    if (!d)
        return (NULL);
    ft_strlcpy(d, s, len + 1);
    return (d);
}

void init_mock_map(t_game *game)
{
    // --- 1. Dimensões do Mapa ---
    game->map.width = 10;
    game->map.height = 10;

    // --- 2. Alocação do Grid ---
    game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
    if (!game->map.grid)
        return ; // Tratar erro real em prod

    // --- 3. Preenchimento do Mapa (1=Parede, 0=Chão) ---
    // Mapa fechado simples
    game->map.grid[0] = mock_strdup("1111111111");
    game->map.grid[1] = mock_strdup("1000000001");
    game->map.grid[2] = mock_strdup("1000000001");
    game->map.grid[3] = mock_strdup("1000000001");
    game->map.grid[4] = mock_strdup("1000N00001"); // N = Player Start
    game->map.grid[5] = mock_strdup("1000000001");
    game->map.grid[6] = mock_strdup("1000000001");
    game->map.grid[7] = mock_strdup("1001001001"); // Pilares para teste
    game->map.grid[8] = mock_strdup("1000000001");
    game->map.grid[9] = mock_strdup("1111111111");

    // --- 4. Configuração do Player (Hardcoded para N) ---
    // Posição: 4.5, 4.5 (Centro do bloco [4][4])
    game->player.pos_x = 4.5;
    game->player.pos_y = 4.5;

    // Vetores para Norte (Y negativo na tela)
    game->player.dir_x = 0.0;
    game->player.dir_y = -1.0;

    // Plano da câmera (Perpendicular à direção)
    // Para FOV de 66 graus, o plano deve ser ~0.66 da direção
    game->player.plane_x = 0.66;
    game->player.plane_y = 0.0;

    game->player.mov_flags = 0; // Parado inicialmente

    // --- 5. Cores (Hex RGBA) ---
    // Teto: Azul Céu (Sky Blue)
    game->tex.ceiling = 0x87CEEBFF;

    // Chão: Verde Grama (Forest Green)
    game->tex.floor = 0x228B22FF;

    // --- 6. Texturas (NULL por enquanto) ---
    // Importante zerar para não dar segfault se tentar acessar antes de carregar
    game->tex.walls[TEX_NORTH].tex = NULL;
    game->tex.walls[TEX_SOUTH].tex = NULL;
    game->tex.walls[TEX_EAST].tex = NULL;
    game->tex.walls[TEX_WEST].tex = NULL;

    printf("Mock Map Loaded! Player at [%f, %f]\n", game->player.pos_x, game->player.pos_y);
}
