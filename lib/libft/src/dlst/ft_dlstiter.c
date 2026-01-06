/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:52:30 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function 'f' to the content of each node in the list.
 *
 * @param lst The list to traverse.
 * @param f The function to apply to each element.
 */
void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	t_dnode	*current;

	if (!lst || !f)
		return ;
	current = lst->head;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}
