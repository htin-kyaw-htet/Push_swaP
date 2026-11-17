/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:42:17 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:42:17 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	min_position(t_stack *a)
{
	int	pos;
	int	min_pos;
	int	min;

	pos = 0;
	min_pos = 0;
	min = a->value;
	while (a)
	{
		if (a->value < min)
		{
			min = a->value;
			min_pos = pos;
		}
		pos++;
		a = a->next;
	}
	return (min_pos);
}

static void	bring_to_top(t_stack **a, int pos, t_stats *s)
{
	int	size;

	size = stack_size(*a);
	if (pos <= size / 2)
	{
		while (pos > 0)
		{
			ra(a, s);
			pos--;
		}
	}
	else
	{
		pos = size - pos;
		while (pos > 0)
		{
			rra(a, s);
			pos--;
		}
	}
}

static void	sort_three(t_stack **a, t_stats *s)
{
	int	x;
	int	y;
	int	z;

	x = (*a)->value;
	y = (*a)->next->value;
	z = (*a)->next->next->value;
	if (x > y && y < z && x < z)
		sa(a, s);
	else if (x > y && y > z)
	{
		sa(a, s);
		rra(a, s);
	}
	else if (x > y)
		ra(a, s);
	else if (y > z && x < z)
	{
		sa(a, s);
		ra(a, s);
	}
	else if (y > z)
		rra(a, s);
}

void	selection_sort(t_stack **a, t_stack **b, t_stats *s)
{
	while (stack_size(*a) > 3 && !is_sorted(*a))
	{
		bring_to_top(a, min_position(*a), s);
		pb(a, b, s);
	}
	if (stack_size(*a) == 3 && !is_sorted(*a))
		sort_three(a, s);
	else if (stack_size(*a) == 2 && !is_sorted(*a))
		sa(a, s);
	while (*b)
		pa(a, b, s);
}
