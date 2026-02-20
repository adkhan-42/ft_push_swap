/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:35:51 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/18 19:41:48 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	push(t_stack **src, t_stack **dest)
{
	t_stack	*node_to_move;

	if (!*src)
		return ;
	node_to_move = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	node_to_move->prev = NULL;
	if (!*dest)
	{
		*dest = node_to_move;
		node_to_move->next = NULL;
	}
	else
	{
		node_to_move->next = *dest;
		(*dest)->prev = node_to_move;
		*dest = node_to_move;
	}
}

void	pa(t_stack **a, t_stack **b)
{
	push(b, a);
	write(1, "pa\n", 3);
	return ;
}

void	pb(t_stack **b, t_stack **a)
{
	push(a, b);
	write(1, "pb\n", 3);
	return ;
}
