#include "parsing.h"
#include <unistd.h>

int	validate_texture_path(const char *path)
{
	int	fd;

	if (!path)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

int	validate_color_format(const char *color_str)
{
	int	count;
	int	i;

	if (!color_str)
		return (-1);
	count = 0;
	i = 0;
	while (color_str[i])
	{
		if (color_str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (-1);
	return (0);
}

int	validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (-1);
	if (g < 0 || g > 255)
		return (-1);
	if (b < 0 || b > 255)
		return (-1);
	return (0);
}

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
		while (map->grid[i][j])
		{
			if (map->grid[i][j] != '0' && map->grid[i][j] != '1' &&
				map->grid[i][j] != 'N' && map->grid[i][j] != 'S' &&
				map->grid[i][j] != 'E' && map->grid[i][j] != 'W' &&
				map->grid[i][j] != ' ' && map->grid[i][j] != '\n')
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
	while (i < map->width && map->grid[0])
	{
		if (map->grid[0][i] != '1' && map->grid[0][i] != '\n')
			return (-1);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (len > 0 && map->grid[i][len - 1] == '\n')
			len--;
		if (map->grid[i][0] != '1')
			return (-1);
		if (len > 0 && map->grid[i][len - 1] != '1')
			return (-1);
		i++;
	}
	i = 0;
	len = ft_strlen(map->grid[map->height - 1]);
	if (len > 0 && map->grid[map->height - 1][len - 1] == '\n')
		len--;
	while (i < len)
	{
		if (map->grid[map->height - 1][i] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int	validate_single_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	if (!map || !map->grid)
		return (-1);
	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
				map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				player_count++;
				map->px = j;
				map->py = i;
				map->pdir = map->grid[i][j];
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (-1);
	return (0);
}
