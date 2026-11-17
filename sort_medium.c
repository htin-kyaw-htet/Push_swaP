/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:42:11 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:42:11 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_chunks(t_stack **a, t_stack **b, int chunk, t_stats *s)
{
	int	pushed;

	pushed = 0;
	while (*a)
	{
		if ((*a)->index < pushed + chunk)
		{
			pb(a, b, s);
			pushed++;
			if ((*b)->index < pushed && (*b)->next)
				rb(b, s);
		}
		else
			ra(a, s);
	}
}

static int	max_position(t_stack *b)
{
	int	pos;
	int	max_pos;
	int	max;

	pos = 0;
	max_pos = 0;
	max = b->index;
	while (b)
	{
		if (b->index > max)
		{
			max = b->index;
			max_pos = pos;
		}
		pos++;
		b = b->next;
	}
	return (max_pos);
}

static void	bring_b_to_top(t_stack **b, int pos, t_stats *s)
{
	int	size;

	size = stack_size(*b);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			rb(b, s);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			rrb(b, s);
	}
}

void	medium_sort(t_stack **a, t_stack **b, t_stats *s)
{
	if (is_sorted(*a))
		return ;
	assign_index(*a);
	push_chunks(a, b, ft_sqrt(stack_size(*a)) * 2, s);
	while (*b)
	{
		bring_b_to_top(b, max_position(*b), s);
		pa(a, b, s);
	}
}
