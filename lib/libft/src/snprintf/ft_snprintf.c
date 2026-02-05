/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:37:49 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 11:45:56 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handler_format_buf(t_buffer *buffer, char specifier, va_list args)
{
	size_t						i;
	static const t_handler_buf	table[] = {
		{'c', &snprintf_char},
		{'s', &snprintf_str},
		{'p', &snprintf_ptr},
		{'d', &snprintf_num},
		{'i', &snprintf_num},
		{'u', &snprintf_unum},
		{'x', &snprintf_lhex},
		{'X', &snprintf_chex},
		{'%', &snprintf_percent},
		{'\0', NULL}
	};

	i = 0;
	while (table[i].specifier)
	{
		if (table[i].specifier == specifier)
			return (table[i].handler_func(buffer, args));
		i++;
	}
	return (0);
}

void	perform_snprinf(t_buffer *buffer, const char *format, va_list args)
{
	size_t		i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			handler_format_buf(buffer, format[i + 1], args);
			i += 2;
		}
		else
			snprintf_putchar(buffer, format[i++]);
	}
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list		args;
	t_buffer	buffer;


	buffer.str = str;
	buffer.size = size;
	buffer.written = 0;
	va_start(args, format);
	perform_snprinf(&buffer, format, args);
	va_end(args);
	if (size > 0)
	{
		if (buffer.written < size)
			str[buffer.written] = '\0';
		else
			str[size - 1] = '\0';
	}
	return (buffer.written);
}
