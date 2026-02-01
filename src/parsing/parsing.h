#ifndef PARSING_H
# define PARSING_H

# include "../include/cub3d.h"

typedef struct s_parsing_state
{
	int	has_north;
	int	has_south;
	int	has_west;
	int	has_east;
	int	has_floor;
	int	has_ceiling;
	int	map_start;
}	t_parsing_state;

int	extract_textures(char **lines, t_game *game);
int	extract_colors(char **lines, t_game *game);
int	extract_map(char **lines, int start_line, t_map *map);

int	validate_texture_path(const char *path);
int	validate_color_format(const char *color_str);
int	validate_rgb_values(int r, int g, int b);

int	validate_map_characters(const t_map *map);
int	validate_map_surrounded(const t_map *map);
int	validate_single_player(t_game *game);

char	*trim_whitespace(char *str);
char	**read_file_to_array(const char *filename);
void	free_file_array(char **arr);
int		count_lines(char **arr);
int		is_empty_line(const char *line);
uint32_t	parse_rgb_to_hex(const char *rgb_str);

#endif
