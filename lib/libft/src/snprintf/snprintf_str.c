/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:08:46 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 11:14:12 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	snprintf_str(t_buffer *buffer, va_list args)
{
	char	*str;

	str = (char *)va_arg(args, char *);
	if (!str)
		str = "(null)";
	snprintf_putstr(buffer, str);
	return (0);
}
