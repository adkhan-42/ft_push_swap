/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:34:24 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/18 19:34:33 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	optimize(t_stack **a, t_stack **b, int cost_a, int cost_b)
{
	while (cost_a > 0 && cost_b > 0)
	{
		cost_a--;
		cost_b--;
		rr(a, b);
	}
	while (cost_a < 0 && cost_b < 0)
	{
		cost_a++;
		cost_b++;
		rrr(a, b);
	}
	while (cost_a > 0 && cost_a--)
		ra(a);
	while (cost_a < 0 && cost_a++)
		rra(a);
	while (cost_b > 0 && cost_b--)
		rb(b);
	while (cost_b < 0 && cost_b++)
		rrb(b);
}

void	do_move(t_stack **a, t_stack **b)
{
	t_stack	*cheapest_node;

	cheapest_node = get_cheapest_cost(*b);
	optimize(a, b, cheapest_node->cost_a, cheapest_node->cost_b);
	pa(a, b);
}
