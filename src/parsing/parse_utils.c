#include "parsing.h"
#include <fcntl.h>
#include <unistd.h>

// Prototypes for helper functions
static int read_lines_into_array(int fd, char ***result_ptr);
static int calculate_map_dimensions(char **lines, int start_line, int *height_ptr, int *max_width_ptr);
static int allocate_and_fill_grid(char **lines, int start_line, t_map *map);

char	*trim_whitespace(char *str)
{
	int	start;
	int	end;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
		end--;
	if (end < start)
		return (ft_strdup(""));
	return (ft_substr(str, start, end - start + 1));
}

int	is_empty_line(const char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

char	**read_file_to_array(const char *filename)
{
	int		fd;
	char	**result;
    int     status;

	if (!filename)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
    result = NULL;
    status = read_lines_into_array(fd, &result);
    if (status == -1)
    {
        return (NULL);
    }
	return (result);
}

static int read_lines_into_array(int fd, char ***result_ptr)
{
    char    *line;
    char    **result;
    int     count;

    result = ft_calloc(1000, sizeof(char *));
    if (!result)
    {
        close(fd);
        return (-1);
    }
    count = 0;
    while (1)
    {
        line = ft_get_next_line(fd);
        if (!line)
            break ;
        result[count] = line;
        count++;
        if (count >= 999)
            break ;
    }
    result[count] = NULL;
    close(fd);
    *result_ptr = result;
    return (0);
}

void	free_file_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_lines(char **arr)
{
	int	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count])
		count++;
	return (count);
}

uint32_t	parse_rgb_to_hex(const char *rgb_str)
{
	char	**tmp;
	int		r;
	int		g;
	int		b;
	uint32_t	result;

	if (!rgb_str)
		return (0xFFFFFFFF);
	tmp = ft_split(rgb_str, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_file_array(tmp);
		return (0xFFFFFFFF);
	}
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	free_file_array(tmp);
	if (validate_rgb_values(r, g, b) != 0)
		return (0xFFFFFFFF);
	result = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (result);
}

int	validate_texture_path(const char *path)
{
	int	fd;

	if (!path)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

int	validate_color_format(const char *color_str)
{
	int	count;
	int	i;

	if (!color_str)
		return (-1);
	count = 0;
	i = 0;
	while (color_str[i])
	{
		if (color_str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (-1);
	return (0);
}

int	validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (-1);
	if (g < 0 || g > 255)
		return (-1);
	if (b < 0 || b > 255)
		return (-1);
	return (0);
}

static int calculate_map_dimensions(char **lines, int start_line, \
	int *height_ptr, int *max_width_ptr)
{
    int i;
    int width;
    int current_max_width;
    int current_height;

    if (!lines || !height_ptr || !max_width_ptr)
        return (-1);
    current_height = 0;
    current_max_width = 0;
    i = start_line;
    while (lines[i])
    {
        width = ft_strlen(lines[i]);
        if (width > 0 && lines[i][width - 1] == '\n')
            width--;
        if (width > current_max_width)
            current_max_width = width;
        current_height++;
        i++;
    }
    *height_ptr = current_height;
    *max_width_ptr = current_max_width;
    return (0);
}

static int allocate_and_fill_grid(char **lines, int start_line, t_map *map)
{
    int i;
    int len;

    map->grid = ft_calloc(map->height + 1, sizeof(char *));
    if (!map->grid)
        return (-1);
    i = 0;
    while (i < map->height)
    {
        map->grid[i] = ft_strdup(lines[start_line + i]);
        if (map->grid[i])
        {
            len = ft_strlen(map->grid[i]);
            if (len > 0 && map->grid[i][len - 1] == '\n')
                map->grid[i][len - 1] = '\0';
        }
        i++;
    }
    map->grid[i] = NULL;
    return (0);
}

int	extract_map(char **lines, int start_line, t_map *map)
{
	if (!lines || !map)
		return (-1);
    if (calculate_map_dimensions(lines, start_line, &map->height, &map->width) == -1)
        return (-1);
    if (allocate_and_fill_grid(lines, start_line, map) == -1)
        return (-1);
    return (0);
}
