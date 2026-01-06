/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:34:45 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	cc;
	char			*pos;
	size_t			i;

	cc = (unsigned char)c;
	pos = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			pos = (char *) &s[i];
		i++;
	}
	if (s[i] == cc)
		pos = (char *) &s[i];
	return (pos);
}
