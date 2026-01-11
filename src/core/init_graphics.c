/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:17:53 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/11 10:17:03 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_graphics(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, 0);
	if (!game->mlx)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		// terminate(game); // TODO
		return (1);
	}
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		// terminate(game); // TODO
		return (1);
	}
	return (0);
}
