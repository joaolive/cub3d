#include "cub3d.h"
#include "MLX42/MLX42.h"

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

static void	free_wall_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->walls[i].tex)
			mlx_delete_texture(game->walls[i].tex);
		if (game->tex_paths[i])
			free(game->tex_paths[i]);
		i++;
	}
}

void	free_game_resources(t_game *game)
{
	if (!game)
		return ;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	free_wall_textures(game);
	destroy_assets(game);
	free_map(&game->map);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
