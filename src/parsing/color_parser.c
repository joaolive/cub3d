#include "parsing.h"

uint32_t	parse_rgb_to_hex(const char *rgb_str)
{
	char	**parts;
	int		r;
	int		g;
	int		b;
	uint32_t	result;

	if (!rgb_str)
		return (0);
	parts = ft_split(rgb_str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_split(parts);
		return (0);
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_split(parts);
	if (validate_rgb_values(r, g, b) != 0)
		return (0);
	result = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (result);
}
