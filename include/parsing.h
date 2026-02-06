#ifndef PARSING_H
# define PARSING_H

# include "./cub3d.h"

typedef enum e_line_type
{
	TYPE_TEXTURE,
	TYPE_COLOR,
	TYPE_MAP,
	TYPE_EMPTY,
	TYPE_INVALID
}	t_line_type;

typedef enum e_parse_state
{
	STATE_EXPECT_BLOCK,
	STATE_EXPECT_SEPARATOR,
	STATE_DONE
}	t_parse_state;

typedef struct s_config_parsing_state
{
	int				tex_count;
	int				color_count;
	t_parse_state	state;
	t_line_type		current_block_type;
}	t_config_parsing_state;

int			parse_map_file(const char *filename, t_game *game);
int			process_configurations(char **lines, int map_start_line, t_game *game);
t_line_type	get_line_type(const char *line);
int			process_one_line(const char *line, t_game *game);
int			find_map_start_index(char **lines);
void		update_parsing_state(t_config_parsing_state *parse_state);

char		*trim_whitespace(char *str);
char		**read_file_to_array(const char *filename);
void		free_file_array(char **arr);
int			count_lines(char **arr);
int			is_empty_line(const char *line);
uint32_t	parse_rgb_to_hex(const char *rgb_str);
int			validate_texture_path(const char *path);
int			validate_color_format(const char *color_str);
int			validate_rgb_values(int r, int g, int b);
int			extract_map(char **lines, int start_line, t_map *map);

int			validate_map_characters(const t_map *map);
int			validate_map_is_closed(const t_map *map);
int			validate_single_player(t_game *game);

#endif
