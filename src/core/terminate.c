#include "cub3d.h"
#include "MLX42/MLX42.h" // Incluir explicitamente para mlx_delete_image/texture

// Helper function to correctly free MLX textures stored in the hash table
void	free_mlx_texture_asset(void *asset_ptr)
{
	if (asset_ptr)
		mlx_delete_texture((mlx_texture_t *)asset_ptr);
}

void	free_game_resources(t_game *game)
{
	int	i;

	if (!game)
		return ;

	// 1. Liberar recursos MLX
	if (game->img)
		mlx_delete_image(game->mlx, game->img); // Corrigido: mlx e imagem
	if (game->player.img)
		mlx_delete_image(game->mlx, game->player.img); // Corrigido: mlx e imagem

	i = 0;
	while (i < 4)
	{
		if (game->walls[i].tex)
			mlx_delete_texture(game->walls[i].tex);
		i++;
	}

	// 2. Liberar assets do hash table (assumindo que guardam mlx_texture_t*)
	if (game->assets)
		ft_tabdestroy(&game->assets, free_mlx_texture_asset); // Usar a nova função auxiliar

	// 3. Liberar o mapa
	free_map(&game->map);

	// 4. Terminar MLX (destrói janela e display internamente)
	if (game->mlx)
		mlx_terminate(game->mlx); 

	// 5. A estrutura t_game é alocada na pilha em main.c, não precisa de free(game) aqui.
}
