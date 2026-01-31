/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:57:57 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/28 08:30:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_htab	*ft_tabinit(size_t size)
{
	t_htab	*htable;

	htable = (t_htab *) malloc(sizeof(t_htab));
	if (!htable)
		return (NULL);
	htable->buckets = ft_calloc(size, sizeof(t_hnode *));
	if (!htable->buckets)
	{
		free(htable);
		return (NULL);
	}
	htable->size = size;
	htable->count = 0;
	return (htable);
}
