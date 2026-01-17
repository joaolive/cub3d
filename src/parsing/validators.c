#include "parsing.h"
#include <unistd.h>

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
