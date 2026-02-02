#include "parsing.h"
#include <stdio.h>

// Functions moved from src/parsing/parser_config.c

// static
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

// static
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

// public
int	process_configurations(char **lines, int map_start_line, t_game *game)
{
	int				i = 0;
	char			*trimmed;
	t_config_parsing_state	parse_state = {0, 0, STATE_EXPECT_BLOCK, TYPE_EMPTY};
	int				status = 0;

	while (i < map_start_line && status == 0)
	{
		trimmed = trim_whitespace(lines[i]);
		if (!trimmed)
			status = -1;
		else
		{
			status = process_config_line_logic(trimmed, game, &parse_state);
			free(trimmed);
		}
		i++;
	}
	if (status == 0 && (parse_state.tex_count != 4 || parse_state.color_count != 2))
	{
		ft_putstr_fd("Error\nIncomplete configurations.\n", 2);
		status = -1;
	}
	return (status);
}
