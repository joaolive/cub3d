/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:50:07 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 11:29:09 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	snprintf_char(t_buffer *buffer, va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	snprintf_putchar(c, 1);
	return (0);
}
