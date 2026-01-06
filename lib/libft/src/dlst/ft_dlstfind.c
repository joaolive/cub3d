/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstfind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:18:55 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Finds the first node in the list whose content matches data_ref.
 *
 * @param lst The list to search in.
 * @param ref The data to search for.
 * @param cmp A function pointer that compares two contents.
 * @return A pointer to the first matching node, or NULL if not found.
 */
t_dnode	*ft_dlstfind(t_dlist *lst, void *ref, int (*cmp)(void *, void *))
{
	t_dnode	*current;

	if (!lst || !ref || !cmp)
		return (NULL);
	current = lst->head;
	while (current)
	{
		if (cmp(current->content, ref) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
