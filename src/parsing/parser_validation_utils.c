#include "parsing.h"
#include <fcntl.h>
#include <unistd.h>

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
