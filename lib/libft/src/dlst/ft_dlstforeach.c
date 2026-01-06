/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstforeach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:52:30 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/09 14:05:21 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies function 'f' to the content of each node in the list.
 *
 * Iteration stops if 'f' returns a non-zero value.
 *
 * @param lst The list to traverse.
 * @param f The function to apply to each node's content.
 * @return 0 on success, non-zero on error, or -1 if arguments are invalid.
 */
int	ft_dlstforeach(t_dlist *lst, int (*f)(void *))
{
	t_dnode	*current;
	int		error;

	if (!lst || !f)
		return (-1);
	current = lst->head;
	while (current)
	{
		error = f(current->content);
		if (error)
			return (error);
		current = current->next;
	}
	return (0);
}
