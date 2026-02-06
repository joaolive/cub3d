#include "parsing.h"
#include <stdio.h>

static char	**parse_line_parts(const char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		free_file_array(parts);
		ft_putstr_fd("Error\nInvalid config format.\n", 2);
		return (NULL);
	}
	return (parts);
}

static int	get_tex_index(char *direction)
{
	if (ft_strcmp(direction, "NO") == 0)
		return (TEX_NORTH);
	if (ft_strcmp(direction, "SO") == 0)
		return (TEX_SOUTH);
	if (ft_strcmp(direction, "WE") == 0)
		return (TEX_WEST);
	if (ft_strcmp(direction, "EA") == 0)
		return (TEX_EAST);
	return (-1);
}

static int	process_texture_line(char **parts, t_game *game)
{
	int	idx;

	if (validate_texture_path(parts[1]) != 0)
	{
		ft_putstr_fd("Error\nInvalid texture path.\n", 2);
		return (-1);
	}
	idx = get_tex_index(parts[0]);
	if (idx < 0 || game->tex_paths[idx])
	{
		ft_putstr_fd("Error\nDuplicate or invalid texture id.\n", 2);
		return (-1);
	}
	game->tex_paths[idx] = ft_strdup(parts[1]);
	if (!game->tex_paths[idx])
		return (-1);
	return (0);
}

static int	process_color_line(char **parts, t_game *game)
{
	uint32_t	color;

	if (validate_color_format(parts[1]) != 0)
	{
		ft_putstr_fd("Error\nInvalid color format.\n", 2);
		return (-1);
	}
	color = parse_rgb_to_hex(parts[1]);
	if (color == 0xFFFFFFFF)
	{
		ft_putstr_fd("Error\nInvalid RGB color value.\n", 2);
		return (-1);
	}
	if (ft_strcmp(parts[0], "F") == 0)
		game->floor = color;
	else if (ft_strcmp(parts[0], "C") == 0)
		game->ceiling = color;
	return (0);
}

int	process_one_line(const char *line, t_game *game)
{
	char	**parts;
	int		result;

	parts = parse_line_parts(line);
	if (!parts)
		return (-1);
	if (get_line_type(line) == TYPE_TEXTURE)
		result = process_texture_line(parts, game);
	else if (get_line_type(line) == TYPE_COLOR)
		result = process_color_line(parts, game);
	else
	{
		free_file_array(parts);
		ft_putstr_fd("Error\nUnknown identifier.\n", 2);
		return (-1);
	}
	free_file_array(parts);
	return (result);
}
