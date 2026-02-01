#include "parsing.h"

static int	find_map_start(char **lines)
{
	int	i;
	int	found_empty;

	if (!lines)
		return (-1);
	i = 0;
	found_empty = 0;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
		{
			found_empty = 1;
		}
		else if (found_empty)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	parse_map_file(const char *filename, t_game *game)
{
	char	**lines;
	int		map_start;

	if (!filename || !game)
	{
		ft_putstr_fd("Error\nArquivo ou estrutura de jogo inválidos\n", 2);
		return (-1);
	}
	lines = read_file_to_array(filename);
	if (!lines)
	{
		ft_putstr_fd("Error\nNão foi possível ler o arquivo\n", 2);
		return (-1);
	}
	if (extract_textures(lines, game) != 0)
	{
		ft_putstr_fd("Error\nFalha ao extrair texturas\n", 2);
		free_file_array(lines);
		return (-1);
	}
	if (extract_colors(lines, game) != 0)
	{
		ft_putstr_fd("Error\nFalha ao extrair cores\n", 2);
		free_file_array(lines);
		return (-1);
	}
	map_start = find_map_start(lines);
	if (map_start < 0)
	{
		ft_putstr_fd("Error\nNão foi possível encontrar o mapa\n", 2);
		free_file_array(lines);
		return (-1);
	}
	if (extract_map(lines, map_start, &game->map) != 0)
	{
		ft_putstr_fd("Error\nFalha ao extrair mapa\n", 2);
		free_file_array(lines);
		return (-1);
	}
	if (validate_map_characters(&game->map) != 0)
	{
		ft_putstr_fd("Error\nCaracteres inválidos no mapa\n", 2);
		free_file_array(lines);
		return (-1);
	}
	if (validate_map_surrounded(&game->map) != 0)
	{
		ft_putstr_fd("Error\nMapa não está cercado por paredes\n", 2);
		free_file_array(lines);
		return (-1);
	}
	if (validate_single_player(game) != 0)
	{
		ft_putstr_fd("Error\nDeve haver exatamente um jogador no mapa\n", 2);
		free_file_array(lines);
		return (-1);
	}
	free_file_array(lines);
	return (0);
}
