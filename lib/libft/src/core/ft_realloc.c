/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:38:05 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/03 15:02:50 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
	return (NULL);
}

void	*ft_realloc(void **ptr, size_t cur_sz, size_t new_sz, size_t t_sz)
{
	void	*new_ptr;
	size_t	old_total_bytes;
	size_t	new_total_bytes;
	size_t	copy_size;

	if (!ptr || !*ptr)
		return (malloc(new_sz * t_sz));
	if (new_sz == 0)
		return (ft_free(ptr));
	if (t_sz > 0 && new_sz > (size_t)-1 / t_sz)
		return (NULL);
	new_total_bytes = new_sz * t_sz;
	new_ptr = malloc(new_total_bytes);
	if (!new_ptr)
		return (NULL);
	if (t_sz > 0 && cur_sz > (size_t)-1 / t_sz)
		old_total_bytes = (size_t) - 1;
	else
		old_total_bytes = cur_sz * t_sz;
	copy_size = old_total_bytes;
	if (new_total_bytes < old_total_bytes)
		copy_size = new_total_bytes;
	ft_memmove(new_ptr, *ptr, copy_size);
	ft_free(ptr);
	return (new_ptr);
}
