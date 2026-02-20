/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:36:17 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/20 14:27:19 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	push_init(t_stack **a, t_stack **b)
{
	int	stack_size;
	int	pushed;
	int	i;

	stack_size = get_stack_size(*a);
	pushed = 0;
	i = 0;
	while (stack_size > 6 && i < stack_size && pushed < stack_size / 2)
	{
		if ((*a)->index <= stack_size / 2)
		{
			pb(b, a);
			pushed++;
		}
		else
			ra(a);
		i++;
	}
	while (stack_size - pushed > 3)
	{
		pb(b, a);
		pushed++;
	}
}

t_stack	*get_min_node(t_stack *stack)
{
	while (stack)
	{
		if (stack->index == 0)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

void	move_to_top(t_stack **stack, t_stack *target_node, char stack_name)
{
	int	size;

	size = get_stack_size(*stack);
	if (target_node->pos <= size / 2)
	{
		while (*stack != target_node)
		{
			if (stack_name == 'a')
				ra(stack);
			else if (stack_name == 'b')
				rb(stack);
		}
	}
	else
	{
		while (*stack != target_node)
		{
			if (stack_name == 'a')
				rra(stack);
			else if (stack_name == 'b')
				rrb(stack);
		}
	}
}

void	min_on_top(t_stack **a)
{
	t_stack	*min_node;

	min_node = get_min_node(*a);
	set_current_pos(*a);
	if (min_node)
		move_to_top(a, min_node, 'a');
}

void	init_nodes(t_stack *a, t_stack *b)
{
	set_current_pos(a);
	set_current_pos(b);
	set_target_pos(&a, &b);
	get_cost(&a, &b);
}
