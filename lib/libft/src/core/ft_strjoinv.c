/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:56:11 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/10 15:47:17 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_s(const char *s)
{
	if (!s)
		return (0);
	return (ft_strlen(s));
}

static size_t	get_total_len(va_list *args, const char *sep, int count)
{
	size_t		total_len;
	size_t		sep_len;
	int			i;
	const char	*str;

	total_len = 0;
	sep_len = ft_strlen_s(sep);
	i = 0;
	while (1)
	{
		if (count != -1 && i >= count)
			break ;
		str = va_arg(*args, const char *);
		if (!str && count == -1)
			break ;
		if (sep && i > 0)
			total_len += sep_len;
		total_len += ft_strlen_s(str);
		i++;
	}
	return (total_len);
}

static void	append_str(char **dst, const char *src, size_t len)
{
	if (!len)
		return ;
	ft_memcpy(*dst, src, len);
	*dst += len;
}

static void	build_string(va_list *args, char *dst, const char *sep, int count)
{
	size_t		len;
	size_t		sep_len;
	int			i;
	const char	*str;

	sep_len = ft_strlen_s(sep);
	i = 0;
	while (1)
	{
		if (count != -1 && i >= count)
			break ;
		str = va_arg(*args, const char *);
		if (!str && count == -1)
			break ;
		if (sep && i > 0)
			append_str(&dst, sep, sep_len);
		len = ft_strlen_s(str);
		append_str(&dst, str, len);
		i++;
	}
}

char	*ft_strjoinv(const char *sep, int count, ...)
{
	va_list	args;
	char	*result;
	size_t	total_len;

	va_start(args, count);
	total_len = get_total_len(&args, sep, count);
	va_end(args);
	result = ft_calloc(total_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	va_start(args, count);
	build_string(&args, result, sep, count);
	va_end(args);
	return (result);
}
