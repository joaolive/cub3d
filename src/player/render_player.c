#include "cub3d.h"

void	render_player(t_game *game)
{
	game->player.img = load_image(game->mlx, "./assets/player/player-f0.png");
	mlx_image_to_window(game->mlx, game->player.img, 0, 0);
	game->player.img->instances[0].x = (game->mlx->width >> 1) - (game->player.img->width >> 1);
	game->player.img->instances[0].y = game->mlx->height - game->player.img->height;
}
