/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:45:39 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/06 11:24:52 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include "libft.h"
# include "MLX42/MLX42.h"

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
}	t_map;

