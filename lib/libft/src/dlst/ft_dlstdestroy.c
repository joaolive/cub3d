/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdestroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:21:48 by joaolive          #+#    #+#             */
/*   Updated: 2025/08/15 09:10:51 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees all memory used by a list and its contents,
 * then sets the list pointer to NULL.
 *
 * @param lst Pointer to the list pointer to be destroyed.
 * @param del Function used to free the content of each node.
 *            If NULL, node contents are not freed.
 */
void	ft_dlstdestroy(t_dlist **lst, void (*del)(void *))
{
	if (!lst || !*lst)
		return ;
	ft_dlstclear(*lst, del);
	free(*lst);
	*lst = NULL;
}
