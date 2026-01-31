/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:14:51 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/31 15:25:15 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_rgba	unpack_rgba(uint32_t color)
{
	t_rgba	rgba;

	rgba.r = ((color >> 24) & 0xFF);
	rgba.g = ((color >> 16) & 0xFF);
	rgba.b = ((color >> 8) & 0xFF);
	rgba.a = ((color >> 0) & 0xFF);
	return (rgba);
}

static uint8_t	interpolate_channel(uint8_t chanel_1, uint8_t chanel_2, float t)
{
	return (chanel_1 + (int32_t)(chanel_2 - chanel_1) * t);
}

uint32_t	lerp(uint32_t color, uint32_t fog_color, uint32_t t)
{
	t_rgba	c;
	t_rgba	f;
	t_rgba	lerp;

	c = unpack_rgba(color);
	f = unpack_rgba(fog_color);
	lerp.r = interpolate_channel(c.r, f.r, t);
	lerp.g = interpolate_channel(c.g, f.g, t);
	lerp.b = interpolate_channel(c.b, f.b, t);
	lerp.a = c.a;
	return ((lerp.r << 24) | (lerp.g << 16) | (lerp.b << 8) | lerp.a);
}
