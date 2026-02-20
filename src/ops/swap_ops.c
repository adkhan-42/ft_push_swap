/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:36:22 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/18 19:40:17 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	*stack = second;
	first->next = second->next;
	if (first->next != NULL)
		first->next->prev = first;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
}

void	sa(t_stack **a)
{
	swap(a);
	write(1, "sa\n", 3);
	return ;
}

void	sb(t_stack **b)
{
	swap(b);
	write(1, "sb\n", 3);
	return ;
}

void	ss(t_stack **a, t_stack **b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
	return ;
}
