#include "parsing.h"

uint32_t	parse_rgb_to_hex(const char *rgb_str)
{
	char	**tmp;
	int		r;
	int		g;
	int		b;
	uint32_t	result;
	int		i;

	if (!rgb_str)
		return (0xFFFFFFFF);
	tmp = ft_split(rgb_str, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		i = 0;
		while (tmp && tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0xFFFFFFFF);
	}
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	i = 0;
	while (tmp && tmp[i])
		free(tmp[i++]);
	free(tmp);
	if (validate_rgb_values(r, g, b) != 0)
		return (0xFFFFFFFF);
	result = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (result);
}
