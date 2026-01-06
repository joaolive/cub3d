/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:37:49 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:18:41 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *arr, ...)
{
	va_list	args;
	size_t	i;
	size_t	count;

	va_start(args, arr);
	i = 0;
	count = 0;
	while (arr[i])
	{
		if (arr[i] == '%' && arr[i + 1])
		{
			count += ft_handler_format(arr[i + 1], args);
			i += 2;
		}
		else
		{
			ft_putchar_fd(arr[i], 1);
			count += 1;
			i++;
		}
	}
	va_end(args);
	return (count);
}
