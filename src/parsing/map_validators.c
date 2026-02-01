#include "parsing.h"

int	validate_map_characters(const t_map *map)
{
	int	i;
	int	j;
	int	len;

	if (!map || !map->grid)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		if (!map->grid[i])
			return (-1);
		j = 0;
		len = ft_strlen(map->grid[i]);
		while (j < len && map->grid[i][j])
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

int	validate_map_surrounded(const t_map *map)
{
	int	i;
	int	len;

	if (!map || !map->grid || map->height == 0 || map->width == 0)
		return (-1);
	i = 0;
	while (i < map->width && i < (int)ft_strlen(map->grid[0]))
	{
		if (map->grid[0][i] != '1')
			return (-1);
		i++;
	}
	i = 1;
	while (i < map->height - 1)
	{
		if (!map->grid[i])
			return (-1);
		len = ft_strlen(map->grid[i]);
		if (map->grid[i][0] != '1')
			return (-1);
		if (len > 0 && map->grid[i][len - 1] != '1')
			return (-1);
		i++;
	}
	if (map->height > 1)
	{
		i = 0;
		len = ft_strlen(map->grid[map->height - 1]);
		while (i < len && i < map->width)
		{
			if (map->grid[map->height - 1][i] != '1')
				return (-1);
			i++;
		}
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
