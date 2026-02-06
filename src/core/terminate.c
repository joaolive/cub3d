#include "cub3d.h"
#include "MLX42/MLX42.h" // Incluir explicitamente para mlx_delete_image/texture

static void	destroy_assets(t_game *game)
{
	size_t	i;
	t_hnode	*node;
	t_hnode	*next;

	if (!game->assets)
		return ;
	i = 0;
	while (i < game->assets->size)
	{
		node = game->assets->buckets[i];
		while (node)
		{
			next = node->next;
			if (node->value)
				mlx_delete_image(game->mlx, (mlx_image_t *)node->value);
			free((void *)node->key);
			free(node);
			node = next;
		}
		i++;
	}
	free(game->assets->buckets);
	free(game->assets);
	game->assets = NULL;
}

void	free_game_resources(t_game *game)
{
	int	i;

	if (!game)
		return ;

	// 1. Liberar recursos MLX
	if (game->img)
		mlx_delete_image(game->mlx, game->img); // Corrigido: mlx e imagem

	i = 0;
	while (i < 4)
	{
		if (game->walls[i].tex)
			mlx_delete_texture(game->walls[i].tex);
		if (game->tex_paths[i])
			free(game->tex_paths[i]);
		i++;
	}

	// 2. Liberar assets do hash table (guardam mlx_image_t*)
	destroy_assets(game);

	// 3. Liberar o mapa
	free_map(&game->map);

	// 4. Terminar MLX (destrói janela e display internamente)
	if (game->mlx)
		mlx_terminate(game->mlx); 

	// 5. A estrutura t_game é alocada na pilha em main.c, não precisa de free(game) aqui.
}
