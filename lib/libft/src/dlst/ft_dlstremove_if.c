/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:48:19 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Removes all nodes from the list that satisfy a given condition.
 *
 * @param lst List to modify.
 * @param cond Function that returns non-zero if a node should be removed.
 * @param del Function to free the content of removed nodes.
 * @return Number of nodes removed.
 */
int	ft_dlstremove_if(t_dlist *lst, int (*cond)(void *), void (*del)(void *))
{
	t_dnode	*current;
	t_dnode	*next_node;
	int		removed_count;

	if (!lst || !cond)
		return (0);
	current = lst->head;
	removed_count = 0;
	while (current)
	{
		next_node = current->next;
		if (cond(current->content))
			if (ft_dlstremove_node(lst, current, del) == 1)
				removed_count++;
		current = next_node;
	}
	return (removed_count);
}
