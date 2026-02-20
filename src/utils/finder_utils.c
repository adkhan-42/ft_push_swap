/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:34:45 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/20 18:03:34 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static long	abs_val(long nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

static long	calc_combined_cost(long a, long b)
{
	if ((a > 0 && b > 0) || (a < 0 && b < 0))
	{
		if (abs_val(a) > abs_val(b))
			return (abs_val(a));
		return (abs_val(b));
	}
	return (abs_val(a) + abs_val(b));
}

t_stack	*get_cheapest_cost(t_stack *b)
{
	long	cheapest;
	long	current_cost;
	t_stack	*cheapest_node;

	cheapest = LONG_MAX;
	cheapest_node = NULL;
	while (b)
	{
		current_cost = calc_combined_cost(b->cost_a, b->cost_b);
		if (current_cost < cheapest)
		{
			cheapest = current_cost;
			cheapest_node = b;
		}
		b = b->next;
	}
	return (cheapest_node);
}

int	get_min_index_pos(t_stack *a)
{
	long	min_index;
	int		target_pos;

	min_index = LONG_MAX;
	while (a)
	{
		if (a->index < min_index)
		{
			min_index = a->index;
			target_pos = a->pos;
		}
		a = a->next;
	}
	return (target_pos);
}

int	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->index > stack->next->index)
			return (0);
		stack = stack->next;
	}
	return (1);
}
