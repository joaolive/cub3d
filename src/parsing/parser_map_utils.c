#include "parsing.h"
#include <unistd.h>

static int	calculate_map_dimensions(char **lines, int start_line,
		int *height_ptr, int *max_width_ptr)
{
	int	i;
	int	width;
	int	current_max_width;
	int	current_height;

	if (!lines || !height_ptr || !max_width_ptr)
		return (-1);
	current_height = 0;
	current_max_width = 0;
	i = start_line;
	while (lines[i])
	{
		width = ft_strlen(lines[i]);
		if (width > 0 && lines[i][width - 1] == '\n')
			width--;
		if (width > current_max_width)
			current_max_width = width;
		current_height++;
		i++;
	}
	*height_ptr = current_height;
	*max_width_ptr = current_max_width;
	return (0);
}

static int	allocate_and_fill_grid(char **lines, int start_line, t_map *map)
{
	int	i;
	int	len;

	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = ft_strdup(lines[start_line + i]);
		if (map->grid[i])
		{
			len = ft_strlen(map->grid[i]);
			if (len > 0 && map->grid[i][len - 1] == '\n')
				map->grid[i][len - 1] = '\0';
		}
		i++;
	}
	map->grid[i] = NULL;
	return (0);
}

int	extract_map(char **lines, int start_line, t_map *map)
{
	if (!lines || !map)
		return (-1);
	if (calculate_map_dimensions(lines, start_line, &map->height,
			&map->width) == -1)
		return (-1);
	if (allocate_and_fill_grid(lines, start_line, map) == -1)
		return (-1);
	return (0);
}
