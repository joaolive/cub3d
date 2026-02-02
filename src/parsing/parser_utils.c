#include "parsing.h"
#include <stdio.h>

// Moved from src/parsing/parser.c
static int free_trimmed_and_return(char *trimmed, int ret_val)
{
	free(trimmed);
	return (ret_val);
}

// Moved from src/parsing/parser.c
int	find_map_start_index(char **lines)
{
	int		i;
	int		last_idx;
	char	*trimmed;

	i = 0;
	last_idx = -1;
	while (lines[i])
		i++;
	last_idx = i - 1;
	while (last_idx >= 0 && is_empty_line(lines[last_idx]))
		last_idx--;
	if (last_idx < 0)
		return (-1);
	i = last_idx;
	while (i >= 0)
	{
		trimmed = trim_whitespace(lines[i]);
		if (!trimmed)
			return (-1);
		if (get_line_type(trimmed) != TYPE_MAP)
			return (free_trimmed_and_return(trimmed, i + 1));
		free(trimmed);
		i--;
	}
	return (0);
}
