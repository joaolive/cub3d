/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 19:05:35 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 15:40:36 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	wall_assets(t_game *game)
// {
// 	char	key[7];
// 	char	path[30];
// 	uint8_t	i;

// 	ft_strlcpy(key, "wall_0", sizeof(key));
// 	ft_strlcpy(path, "./assets/wall/wall_0.png", sizeof(path));
// 	i = -1;
// 	while (++i < 4)
// 	{
// 		key[5] = '0' + i;
// 		path[21] = '0' + i;
// 		ft_htabinsert(game->assets, key,
// 			load_image(game->mlx, path));
// 	}
// }

// static int  load(t_game *game, char *key, char *path, uint32_t count)
// {
//     char    *key_idx;
//     char    *path_idx;
//     uint8_t i;
//     void    *img_ptr;

//     key_idx = key + ft_strlen(key) - 1;
//     path_idx = ft_strrchr(path, '.') - 1;
//     i = -1;
//     while (++i < count)
//     {
//         *key_idx = i + '0';
//         *path_idx = i + '0';

//         // LOG DE DEPURAÇÃO: Verifique se o caminho impresso está correto
//         // printf("Carregando [%s] do arquivo: %s\n", key, path);

//         img_ptr = load_image(game->mlx, path);
//         if (!img_ptr)
//         {
//             printf("Erro: Arquivo não encontrado ou inválido: %s\n", path);
//             return (1);
//         }
//         if (ft_htabinsert(game->assets, key, img_ptr))
//             return (1);
//     }
//     return (0);
// }

mlx_image_t	*load_image(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (NULL);
	if (!mlx_resize_image(image, 512, 512))
	{
		mlx_delete_image(mlx, image);
		return (NULL);
	}
	return (image);
}

static uint8_t	load(t_game *game, char *key, char *path, uint32_t count)
{
	mlx_image_t	*img;
	char		*key_idx;
	char		*path_idx;
	uint8_t		i;

	key_idx = key + ft_strlen(key) -1;
	path_idx = ft_strrchr(path, '.') - 1;
	i = -1;
	while (++i < count)
	{
		*key_idx = i + '0';
		*path_idx = i + '0';
		img = load_image(game->mlx, path);
		if (!img || ft_htabinsert(game->assets, key, img))
		{
			//ft_terminate(game); // TODO
			return (1);
		}
	}
	return (0);
}

uint8_t	load_images(t_game *game, char *key, char *path, uint32_t count)
{
	char	*k;
	char	*p;
	uint8_t	res;

	k = ft_strdup(key);
	p = ft_strdup(path);
	res = 0;
	if (k && p)
		res = load(game, k, p, count);
	free(k);
	free(p);
	return (res);
}
