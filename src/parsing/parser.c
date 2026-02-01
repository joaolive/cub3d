#include "parsing.h"
#include <stdio.h>

static int			find_map_start_index(char **lines);
static int			process_configurations(char **lines, int map_start_line, t_game *game);
static t_line_type	get_line_type(const char *trimmed_line);
static int			process_one_line(const char *line, t_game *game);

int	parse_map_file(const char *filename, t_game *game)
{
	char		**lines;
	int		map_start;

	ft_bzero(game, sizeof(t_game));
	lines = read_file_to_array(filename);
	if (!lines)
		return (ft_putstr_fd("Error\nCould not read file.\n", 2), -1);
	map_start = find_map_start_index(lines);
	if (map_start > 0 && !is_empty_line(lines[map_start - 1]))
	{
		free_file_array(lines);
		return (ft_putstr_fd("Error\nConfig must be separated from map by an empty line.\n", 2), -1);
	}
	if (map_start < 0 || process_configurations(lines, map_start, game) != 0)
	{
		free_file_array(lines);
		return (-1);
	}
	if (extract_map(lines, map_start, &game->map) != 0)
	{
		free_file_array(lines);
		return (ft_putstr_fd("Error\nFailed to extract map.\n", 2), -1);
	}
	if (validate_map_characters(&game->map) != 0)
	{
		free_file_array(lines);
		return (ft_putstr_fd("Error\nInvalid map characters.\n", 2), -1);
	}
	if (validate_map_is_closed(&game->map) != 0)
	{
		free_file_array(lines);
		return (ft_putstr_fd("Error\nMap not closed.\n", 2), -1);
	}
	if (validate_single_player(game) != 0)
	{
		free_file_array(lines);
		return (ft_putstr_fd("Error\nInvalid player setup.\n", 2), -1);
	}
	free_file_array(lines);
	return (0);
}

static int	find_map_start_index(char **lines)
{
	int i = 0, last_idx = -1;
	char *trimmed;
	while (lines[i]) i++;
	last_idx = i - 1;
	while (last_idx >= 0 && is_empty_line(lines[last_idx])) last_idx--;
	if (last_idx < 0) return (-1);
	i = last_idx;
	while (i >= 0)
	{
		trimmed = trim_whitespace(lines[i]);
		if (!trimmed) return (-1);
		if (get_line_type(trimmed) != TYPE_MAP)
		{
			free(trimmed);
			return (i + 1);
		}
		free(trimmed);
		i--;
	}
	return (0);
}

static int	process_configurations(char **lines, int map_start_line, t_game *game)
{
	int i = 0;
	int tex_count = 0, color_count = 0;
	char *trimmed;
	t_parse_state state = STATE_EXPECT_BLOCK;
	t_line_type current_block_type = TYPE_EMPTY;

	while (i < map_start_line)
	{
		trimmed = trim_whitespace(lines[i]);
		if (!*trimmed)
		{
			if (state == STATE_EXPECT_SEPARATOR)
				state = STATE_EXPECT_BLOCK;
			i++;
			free(trimmed);
			continue;
		}
		if (state == STATE_DONE)
			return (free(trimmed), ft_putstr_fd("Error\nExtra content in config section.\n", 2), -1);
		t_line_type line_type = get_line_type(trimmed);
		if (line_type == TYPE_INVALID || line_type == TYPE_MAP)
			return (free(trimmed), ft_putstr_fd("Error\nInvalid line in config.\n", 2), -1);
		
		if (state == STATE_EXPECT_BLOCK)
		{
			current_block_type = line_type;
			state = STATE_EXPECT_SEPARATOR;
		}
		if (line_type != current_block_type)
			return (free(trimmed), ft_putstr_fd("Error\nMixed types in config block.\n", 2), -1);
		
		if (process_one_line(trimmed, game) != 0)
			return (free(trimmed), -1);
		if (line_type == TYPE_TEXTURE) tex_count++;
		else color_count++;

		if ((current_block_type == TYPE_TEXTURE && tex_count == 4) || (current_block_type == TYPE_COLOR && color_count == 2))
		{
			if (tex_count == 4 && color_count == 2)
				state = STATE_DONE;
			else
				state = STATE_EXPECT_SEPARATOR;
		}
		free(trimmed);
		i++;
	}
	if (tex_count != 4 || color_count != 2)
		return (ft_putstr_fd("Error\nIncomplete configurations.\n", 2), -1);
	return (0);
}

static t_line_type	get_line_type(const char *line)
{
	int	i;

	if (is_empty_line(line))
		return (TYPE_EMPTY);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (TYPE_TEXTURE);
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (TYPE_COLOR);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
			return (TYPE_INVALID);
		i++;
	}
	return (TYPE_MAP);
}

static int	process_one_line(const char *line, t_game *game)
{
	char		**parts;
	uint32_t	color;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1] || parts[2])
		return (free_file_array(parts), ft_putstr_fd("Error\nInvalid config format.\n", 2), -1);
	
	if (get_line_type(line) == TYPE_TEXTURE)
	{
		if (validate_texture_path(parts[1]) != 0)
			return (free_file_array(parts), ft_putstr_fd("Error\nInvalid texture path.\n", 2), -1);
		if (ft_strcmp(parts[0], "NO") == 0)
		{
			game->walls[TEX_NORTH].tex = mlx_load_png(parts[1]);
			if (!game->walls[TEX_NORTH].tex) return (free_file_array(parts), ft_putstr_fd("Error\nFailed to load NO texture.\n", 2), -1);
		}
		else if (ft_strcmp(parts[0], "SO") == 0)
		{
			game->walls[TEX_SOUTH].tex = mlx_load_png(parts[1]);
			if (!game->walls[TEX_SOUTH].tex) return (free_file_array(parts), ft_putstr_fd("Error\nFailed to load SO texture.\n", 2), -1);
		}
		else if (ft_strcmp(parts[0], "WE") == 0)
		{
			game->walls[TEX_WEST].tex = mlx_load_png(parts[1]);
			if (!game->walls[TEX_WEST].tex) return (free_file_array(parts), ft_putstr_fd("Error\nFailed to load WE texture.\n", 2), -1);
		}
		else if (ft_strcmp(parts[0], "EA") == 0)
		{
			game->walls[TEX_EAST].tex = mlx_load_png(parts[1]);
			if (!game->walls[TEX_EAST].tex) return (free_file_array(parts), ft_putstr_fd("Error\nFailed to load EA texture.\n", 2), -1);
		}
	}
	else if (get_line_type(line) == TYPE_COLOR)
	{
		if (validate_color_format(parts[1]) != 0)
			return (free_file_array(parts), ft_putstr_fd("Error\nInvalid color format.\n", 2), -1);
		color = parse_rgb_to_hex(parts[1]);
		if (color == 0xFFFFFFFF)
			return (free_file_array(parts), ft_putstr_fd("Error\nInvalid RGB color value.\n", 2), -1);
		if (ft_strcmp(parts[0], "F") == 0) game->floor = color;
		else if (ft_strcmp(parts[0], "C") == 0) game->ceiling = color;
	}
	else
		return (free_file_array(parts), ft_putstr_fd("Error\nUnknown identifier.\n", 2), -1);
	return (free_file_array(parts), 0);
}