#include "parsing.h"

// Original static function definitions from parser.c
// Moved from src/parsing/parser.c
static void update_parsing_state(t_config_parsing_state *parse_state)
{
	int texture_block_complete;
	int color_block_complete;
	int all_configs_complete;

	texture_block_complete = (parse_state->current_block_type == TYPE_TEXTURE
			&& parse_state->tex_count == 4);
	color_block_complete = (parse_state->current_block_type == TYPE_COLOR
			&& parse_state->color_count == 2);
	if (texture_block_complete || color_block_complete)
	{
		all_configs_complete = (parse_state->tex_count == 4
				&& parse_state->color_count == 2);
		if (all_configs_complete)
			parse_state->state = STATE_DONE;
		else
			parse_state->state = STATE_EXPECT_SEPARATOR;
	}
}

// Moved from src/parsing/parser.c
static int check_config_line_errors(char *trimmed, t_game *game,
		t_config_parsing_state *parse_state, t_line_type *line_type_out)
{
	(void)game;
	if (!*trimmed)
	{
		if (parse_state->state == STATE_EXPECT_SEPARATOR)
			parse_state->state = STATE_EXPECT_BLOCK;
		return (0);
	}
	if (parse_state->state == STATE_DONE)
	{
		ft_putstr_fd("Error\nExtra content in config section.\n", 2);
		return (-1);
	}
	*line_type_out = get_line_type(trimmed);
	if (*line_type_out == TYPE_INVALID || *line_type_out == TYPE_MAP)
	{
		ft_putstr_fd("Error\nInvalid line in config.\n", 2);
		return (-1);
	}
	if (parse_state->state == STATE_EXPECT_BLOCK)
	{
		parse_state->current_block_type = *line_type_out;
		parse_state->state = STATE_EXPECT_SEPARATOR;
	}
	if (*line_type_out != parse_state->current_block_type)
	{
		ft_putstr_fd("Error\nMixed types in config block.\n", 2);
		return (-1);
	}
	return (1);
}

// Moved from src/parsing/parser.c
static int process_config_line_logic(char *trimmed, t_game *game,
		t_config_parsing_state *parse_state)
{
	t_line_type	line_type;
	int			error_check_result;

	error_check_result = check_config_line_errors(trimmed, game,
			parse_state, &line_type);
	if (error_check_result != 1)
		return (error_check_result);
	if (process_one_line(trimmed, game) != 0)
		return (-1);
	if (line_type == TYPE_TEXTURE)
		parse_state->tex_count++;
	else
		parse_state->color_count++;
	update_parsing_state(parse_state);
	return (0);
}

// Moved from src/parsing/parser.c
int	process_configurations(char **lines, int map_start_line, t_game *game)
{
	int			i;
	char		*trimmed;
	t_config_parsing_state	parse_state;
	int			status;

	i = 0;
	parse_state.tex_count = 0;
	parse_state.color_count = 0;
	parse_state.state = STATE_EXPECT_BLOCK;
	parse_state.current_block_type = TYPE_EMPTY;
	while (i < map_start_line)
	{
		trimmed = trim_whitespace(lines[i]);
		if (!trimmed)
			return (-1);
		status = process_config_line_logic(trimmed, game, &parse_state);
		free(trimmed);
		if (status != 0)
			return (status);
		i++;
	}
	if (parse_state.tex_count != 4 || parse_state.color_count != 2)
		return (ft_putstr_fd("Error\nIncomplete configurations.\n", 2), -1);
	return (0);
}

// Moved from src/parsing/parser.c
t_line_type	get_line_type(const char *line)
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
