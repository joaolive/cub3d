#include "cub3d.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		if (parse_map_file(argv[1], &game) != 0)
		{
			ft_putstr_fd("Error\n", 2);
			return (1);
		}
	}
	else
	{
		init_mock_map(&game);
	}
	if (init_graphics(&game))
		return (1);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
