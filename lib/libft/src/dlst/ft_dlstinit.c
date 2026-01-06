/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:28:35 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates and initializes a new empty doubly linked list.
 *
 * @return Pointer to the new list, or NULL if memory allocation fails.
 */
t_dlist	*ft_dlstinit(void)
{
	t_dlist	*dlst;

	dlst = (t_dlist *) malloc(sizeof(t_dlist));
	if (!dlst)
		return (NULL);
	dlst->head = NULL;
	dlst->tail = NULL;
	dlst->size = 0;
	return (dlst);
}
