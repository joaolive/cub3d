#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return;
	i = 0;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}
