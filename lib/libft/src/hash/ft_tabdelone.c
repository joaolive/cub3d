/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:57:14 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/27 17:57:16 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdelone(t_hnode *node, void (*del)(void *))
{
	if (!node)
		return ;
	if (del)
		del(node->value);
	free((void *)node->key);
	free(node);
}
