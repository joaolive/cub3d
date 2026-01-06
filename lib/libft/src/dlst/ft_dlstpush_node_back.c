/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpush_node_back.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:36:15 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds an existing node at the end of the list.
 *
 * @param lst List to modify.
 * @param node Node to add.
 * @return 1 on success, 0 on error.
 */
int	ft_dlstpush_node_back(t_dlist *lst, t_dnode *node)
{
	if (!lst || !node)
		return (0);
	node->next = NULL;
	node->prev = lst->tail;
	if (lst->size == 0)
		lst->head = node;
	else
		lst->tail->next = node;
	lst->tail = node;
	lst->size++;
	return (1);
}
