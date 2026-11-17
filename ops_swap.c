/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:38:58 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:38:58 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack **a, t_stats *s)
{
	swap_top(a);
	print_op(s, SA);
}

void	sb(t_stack **b, t_stats *s)
{
	swap_top(b);
	print_op(s, SB);
}

void	ss(t_stack **a, t_stack **b, t_stats *s)
{
	swap_top(a);
	swap_top(b);
	print_op(s, SS);
}
