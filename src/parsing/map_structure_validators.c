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
			return (-1);
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

static int	check_cell_neighbors(const t_map *map, int y, int x)
{
	size_t	len_up;
	size_t	len_down;
	size_t	len_curr;

	if (y == 0 || y == map->height - 1 || x == 0)
		return (-1);
	len_curr = ft_strlen(map->grid[y]);
	if ((size_t)x == len_curr - 1)
		return (-1);
	len_up = ft_strlen(map->grid[y - 1]);
	if ((size_t)x >= len_up || map->grid[y - 1][x] == ' ')
		return (-1);
	len_down = ft_strlen(map->grid[y + 1]);
	if ((size_t)x >= len_down || map->grid[y + 1][x] == ' ')
		return (-1);
	if (map->grid[y][x - 1] == ' ')
		return (-1);
	if (map->grid[y][x + 1] == ' ')
		return (-1);
	return (0);
}

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
				if (check_cell_neighbors(map, y, x) != 0)
					return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
