#include "parsing.h"
#include <unistd.h>

static int	process_texture_line(char *line, t_tex *tex)
{
	char	*trimmed;
	char	**parts;
	int		result;
	int		i;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	parts = ft_split(trimmed, ' ');
	free(trimmed);
	if (!parts || !parts[0])
	{
		i = 0;
		while (parts && parts[i])
			free(parts[i++]);
		free(parts);
		return (0);
	}
	result = 0;
	if (ft_strcmp(parts[0], "NO") == 0 && parts[1])
		result = validate_texture_path(parts[1]) != 0 ? -1 : (tex->walls[TEX_NORTH].tex = mlx_load_png(parts[1]), 0);
	else if (ft_strcmp(parts[0], "SO") == 0 && parts[1])
		result = validate_texture_path(parts[1]) != 0 ? -1 : (tex->walls[TEX_SOUTH].tex = mlx_load_png(parts[1]), 0);
	else if (ft_strcmp(parts[0], "WE") == 0 && parts[1])
		result = validate_texture_path(parts[1]) != 0 ? -1 : (tex->walls[TEX_WEST].tex = mlx_load_png(parts[1]), 0);
	else if (ft_strcmp(parts[0], "EA") == 0 && parts[1])
		result = validate_texture_path(parts[1]) != 0 ? -1 : (tex->walls[TEX_EAST].tex = mlx_load_png(parts[1]), 0);
	i = 0;
	while (parts && parts[i])
		free(parts[i++]);
	free(parts);
	return (result);
}

int	extract_textures(char **lines, t_tex *tex)
{
	int	i;

	if (!lines || !tex)
		return (-1);
	i = 0;
	while (lines[i] && !is_empty_line(lines[i]))
	{
		if (process_texture_line(lines[i], tex) != 0)
			return (-1);
		i++;
	}
	if (!tex->walls[TEX_NORTH].tex || !tex->walls[TEX_SOUTH].tex ||
		!tex->walls[TEX_WEST].tex || !tex->walls[TEX_EAST].tex)
		return (-1);
	return (0);
}

static int	process_color_line(char *line, t_tex *tex)
{
	char	*trimmed;
	char	**parts;
	uint32_t	color;
	int		result;
	int		i;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	parts = ft_split(trimmed, ' ');
	free(trimmed);
	if (!parts || !parts[0])
	{
		i = 0;
		while (parts && parts[i])
			free(parts[i++]);
		free(parts);
		return (0);
	}
	result = 0;
	if (ft_strcmp(parts[0], "F") == 0 && parts[1])
	{
		if (validate_color_format(parts[1]) != 0)
			result = -1;
		else if ((color = parse_rgb_to_hex(parts[1])) != 0xFFFFFFFF)
			tex->floor = color;
		else
			result = -1;
	}
	else if (ft_strcmp(parts[0], "C") == 0 && parts[1])
	{
		if (validate_color_format(parts[1]) != 0)
			result = -1;
		else if ((color = parse_rgb_to_hex(parts[1])) != 0xFFFFFFFF)
			tex->ceiling = color;
		else
			result = -1;
	}
	i = 0;
	while (parts && parts[i])
		free(parts[i++]);
	free(parts);
	return (result);
}

int	extract_colors(char **lines, t_tex *tex)
{
	int	i;

	if (!lines || !tex)
		return (-1);
	i = 0;
	while (lines[i] && !is_empty_line(lines[i]))
	{
		if (process_color_line(lines[i], tex) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	extract_map(char **lines, int start_line, t_map *map)
{
	int	i;
	int	width;
	int	max_width;
	int	height;
	int	len;

	if (!lines || !map)
		return (-1);
	height = 0;
	max_width = 0;
	i = start_line;
	while (lines[i] && !is_empty_line(lines[i]))
	{
		width = ft_strlen(lines[i]);
		if (width > 0 && lines[i][width - 1] == '\n')
			width--;
		if (width > max_width)
			max_width = width;
		height++;
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
			if (map->grid[i])
			{
				len = ft_strlen(map->grid[i]);
				if (len > 0 && map->grid[i][len - 1] == '\n')
					map->grid[i][len - 1] = '\0';
			}
			i++;
		}
		start_line++;
	}
	map->grid[i] = NULL;
	return (0);
}



