#include "parsing.h"
#include <stdio.h>

void update_parsing_state(t_config_parsing_state *parse_state)
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
