#include "parsing.h"
#include <stdio.h>

static int			check_lines_and_config_sep(char **lines, int map_start);
static int			check_process_and_extract_map(char **lines, int map_start, t_game *game);
static int			validate_map_and_player(char **lines, t_game *game);
static int			initial_file_read_check(char **lines);

static int initial_file_read_check(char **lines)
{
	if (!lines)
	{
		ft_putstr_fd("Error\nCould not read file.\n", 2);
		return (-1);
	}
	return (0);
}

static int check_lines_and_config_sep(char **lines, int map_start)
{
	if (!lines)
	{
		ft_putstr_fd("Error\nCould not read file.\n", 2);
		return (-1);
	}
	if (map_start > 0 && !is_empty_line(lines[map_start - 1]))
	{
		free_file_array(lines);
		ft_putstr_fd("Error\nConfig must be separated from map by an empty line.\n", 2);
		return (-1);
	}
	return (0);
}

static int check_process_and_extract_map(char **lines, int map_start, t_game *game)
{
	if (map_start < 0 || process_configurations(lines, map_start, game) != 0)
	{
		free_file_array(lines);
		return (-1);
	}
	if (extract_map(lines, map_start, &game->map) != 0)
	{
		free_file_array(lines);
		ft_putstr_fd("Error\nFailed to extract map.\n", 2);
		return (-1);
	}
	return (0);
}

static int validate_map_and_player(char **lines, t_game *game)
{
	if (validate_map_characters(&game->map) != 0)
	{
		free_file_array(lines);
		ft_putstr_fd("Error\nInvalid map characters.\n", 2);
		return (-1);
	}
	if (validate_map_is_closed(&game->map) != 0)
	{
		free_file_array(lines);
		ft_putstr_fd("Error\nMap not closed.\n", 2);
		return (-1);
	}
	if (validate_single_player(game) != 0)
	{
		free_file_array(lines);
		ft_putstr_fd("Error\nInvalid player setup.\n", 2);
		return (-1);
	}
	return (0);
}

int	parse_map_file(const char *filename, t_game *game)
{
	char	**lines;
	int		map_start;
	int		status;

	ft_bzero(game, sizeof(t_game));
	lines = read_file_to_array(filename);
	status = initial_file_read_check(lines);
	if (status != 0)
		return (status);
	map_start = find_map_start_index(lines);
	status = check_lines_and_config_sep(lines, map_start);
	if (status != 0)
		return (status);
	status = check_process_and_extract_map(lines, map_start, game);
	if (status != 0)
		return (status);
	status = validate_map_and_player(lines, game);
	if (status != 0)
		return (status);
	free_file_array(lines);
	return (0);
}
