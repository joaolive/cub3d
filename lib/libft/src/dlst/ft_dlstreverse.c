/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstreverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:45:04 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Reverses the order of the nodes in a doubly linked list.
 *
 * This operation is performed in-place by swapping the existing
 * node pointers, without allocating or freeing additional memory.
 *
 * @param lst Pointer to the list to be reversed.
 */
void	ft_dlstreverse(t_dlist *lst)
{
	t_dnode	*current;
	t_dnode	*aux;

	if (!lst || !lst->head || lst->size < 2)
		return ;
	current = lst->head;
	while (current)
	{
		aux = current->prev;
		current->prev = current->next;
		current->next = aux;
		current = current->prev;
	}
	aux = lst->head;
	lst->head = lst->tail;
	lst->tail = aux;
}
