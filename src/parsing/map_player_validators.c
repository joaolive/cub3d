#include "parsing.h"

static void set_player_direction(t_game *game, char direction)
{
    if (direction == 'N')
    {
        game->player.dir.x = 0;
        game->player.dir.y = -1;
    }
    else if (direction == 'S')
    {
        game->player.dir.x = 0;
        game->player.dir.y = 1;
    }
    else if (direction == 'W')
    {
        game->player.dir.x = -1;
        game->player.dir.y = 0;
    }
    else if (direction == 'E')
    {
        game->player.dir.x = 1;
        game->player.dir.y = 0;
    }
    game->player.plane.x = -0.66 * game->player.dir.y;
    game->player.plane.y = 0.66 * game->player.dir.x;
}

static int process_player_char(t_game *game, int i, int j, int *player_count)
{
    char current_char;

    current_char = game->map.grid[i][j];
    if (ft_strchr("NSEW", current_char))
    {
        (*player_count)++;
        if (*player_count > 1)
            return (-1);
        game->player.pos.x = j + 0.5;
        game->player.pos.y = i + 0.5;
        set_player_direction(game, current_char);
        return (1);
    }
    return (0);
}

int	validate_single_player(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	if (!game || !game->map.grid)
		return (-1);
	player_count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
            if (process_player_char(game, i, j, &player_count) == -1)
                return (-1);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (-1);
	return (0);
}
