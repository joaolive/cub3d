#include "parsing.h"
#include <unistd.h>

int	extract_textures(char **lines, t_tex *tex)
{
	int		i;
	char	*trimmed;
	char	**parts;

	if (!lines || !tex)
		return (-1);
	i = 0;
	while (lines[i] && !is_empty_line(lines[i]))
	{
		trimmed = trim_whitespace(lines[i]);
		if (!trimmed)
			return (-1);
		parts = ft_split(trimmed, ' ');
		free(trimmed);
		if (!parts)
			return (-1);
		if (ft_strcmp(parts[0], "NO") == 0 && parts[1])
		{
			if (validate_texture_path(parts[1]))
			{
				free_split(parts);
				return (-1);
			}
			tex->walls[TEX_NORTH].tex = mlx_load_png(parts[1]);
		}
		else if (ft_strcmp(parts[0], "SO") == 0 && parts[1])
		{
			if (validate_texture_path(parts[1]))
			{
				free_split(parts);
				return (-1);
			}
			tex->walls[TEX_SOUTH].tex = mlx_load_png(parts[1]);
		}
		else if (ft_strcmp(parts[0], "WE") == 0 && parts[1])
		{
			if (validate_texture_path(parts[1]))
			{
				free_split(parts);
				return (-1);
			}
			tex->walls[TEX_WEST].tex = mlx_load_png(parts[1]);
		}
		else if (ft_strcmp(parts[0], "EA") == 0 && parts[1])
		{
			if (validate_texture_path(parts[1]))
			{
				free_split(parts);
				return (-1);
			}
			tex->walls[TEX_EAST].tex = mlx_load_png(parts[1]);
		}
		free_split(parts);
		i++;
	}
	return (0);
}


int	extract_colors(char **lines, t_tex *tex)
{
	int		i;
	char	*trimmed;
	char	**parts;

	if (!lines || !tex)
		return (-1);
	i = 0;
	while (lines[i] && !is_empty_line(lines[i]))
	{
		trimmed = trim_whitespace(lines[i]);
		if (!trimmed)
			return (-1);
		parts = ft_split(trimmed, ' ');
		free(trimmed);
		if (!parts)
			return (-1);
		if (ft_strcmp(parts[0], "F") == 0 && parts[1])
		{
			if (validate_color_format(parts[1]))
			{
				free_split(parts);
				return (-1);
			}
			// TODO: Parse RGB e converter para hex
		}
		else if (ft_strcmp(parts[0], "C") == 0 && parts[1])
		{
			if (validate_color_format(parts[1]))
			{
				free_split(parts);
				return (-1);
			}
			// TODO: Parse RGB e converter para hex
		}
		free_split(parts);
		i++;
	}
	return (0);
}


int	extract_map(char **lines, int start_line, t_map *map)
{
	int	i;
	int	height;
	int	width;
	int	max_width;

	if (!lines || !map)
		return (-1);
	height = 0;
	max_width = 0;
	i = start_line;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			width = ft_strlen(lines[i]);
			if (width > 0 && lines[i][width - 1] == '\n')
				width--;
			if (width > max_width)
				max_width = width;
			height++;
		}
		i++;
	}
	map->width = max_width;
	map->height = height;
	map->grid = ft_calloc(height + 1, sizeof(char *));
	if (!map->grid)
		return (-1);
	i = 0;
	while (start_line < count_lines(lines) && lines[start_line])
	{
		if (!is_empty_line(lines[start_line]))
		{
			map->grid[i] = ft_strdup(lines[start_line]);
			i++;
		}
		start_line++;
	}
	map->grid[i] = NULL;
	return (0);
}
