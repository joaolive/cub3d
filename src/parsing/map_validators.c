#include "parsing.h"

int	validate_map_characters(const t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->grid)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		if (!map->grid[i])
			return (-1); // Should not happen if parsing is correct
		while (map->grid[i][j])
		{
			if (map->grid[i][j] != '0' && map->grid[i][j] != '1' &&
				map->grid[i][j] != 'N' && map->grid[i][j] != 'S' &&
				map->grid[i][j] != 'E' && map->grid[i][j] != 'W' &&
				map->grid[i][j] != ' ')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Checks if a specific cell (y, x) is valid and surrounded.
 * A cell is valid if it's not on the edge of the grid and not adjacent
 * to a space ' '. This function assumes that the character at (y,x)
 * is a floor ('0') or a player ('N','S','E','W').
 *
 * @param map The map structure.
 * @param y The row index of the cell.
 * @param x The column index of the cell.
 * @return int 0 if valid, -1 if not.
 */
static int	check_cell_neighbors(const t_map *map, int y, int x)
{
	size_t	len_up;
	size_t	len_down;
	size_t	len_curr;

	// Check boundaries (is it on the first/last row or column?)
	if (y == 0 || y == map->height - 1 || x == 0)
		return (-1); // Touches top, bottom, or left edge

	len_curr = ft_strlen(map->grid[y]);
	if ((size_t)x == len_curr - 1)
		return (-1); // Touches right edge of its own line

	// Check cell above
	len_up = ft_strlen(map->grid[y - 1]);
	if ((size_t)x >= len_up || map->grid[y - 1][x] == ' ')
		return (-1);

	// Check cell below
	len_down = ft_strlen(map->grid[y + 1]);
	if ((size_t)x >= len_down || map->grid[y + 1][x] == ' ')
		return (-1);

	// Check cell to the left
	if (map->grid[y][x - 1] == ' ')
		return (-1);

	// Check cell to the right
	if (map->grid[y][x + 1] == ' ')
		return (-1);

	return (0);
}

/**
 * @brief Validates that the map is closed/surrounded by walls.
 * Iterates through the map grid and ensures that any floor or player
 * character is not adjacent to a space or the edge of the grid.
 */
int	validate_map_is_closed(const t_map *map)
{
	int	y;
	int	x;

	if (!map || !map->grid)
		return (-1);

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '0' || map->grid[y][x] == 'N' ||
				map->grid[y][x] == 'S' || map->grid[y][x] == 'E' ||
				map->grid[y][x] == 'W')
			{
				if (check_cell_neighbors(map, y, x) != 0)
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}


static void set_player_direction(t_game *game, char direction)
{
    if (direction == 'N')
    {
        game->player.dir.x = 0;
        game->player.dir.y = -1;
        game->player.plane.x = 0.66;
        game->player.plane.y = 0;
    }
    else if (direction == 'S')
    {
        game->player.dir.x = 0;
        game->player.dir.y = 1;
        game->player.plane.x = -0.66;
        game->player.plane.y = 0;
    }
    else if (direction == 'W')
    {
        game->player.dir.x = -1;
        game->player.dir.y = 0;
        game->player.plane.x = 0;
        game->player.plane.y = -0.66;
    }
    else if (direction == 'E')
    {
        game->player.dir.x = 1;
        game->player.dir.y = 0;
        game->player.plane.x = 0;
        game->player.plane.y = 0.66;
    }
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
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' ||
				game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				player_count++;
                if (player_count > 1)
                    return (-1);
				game->player.pos.x = j + 0.5;
				game->player.pos.y = i + 0.5;
                set_player_direction(game, game->map.grid[i][j]);
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (-1);
	return (0);
}