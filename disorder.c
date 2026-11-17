/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:44:17 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:44:17 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	count_pairs(t_stack *a, long *mistakes, long *total)
{
	t_stack	*j;

	while (a)
	{
		j = a->next;
		while (j)
		{
			(*total)++;
			if (a->value > j->value)
				(*mistakes)++;
			j = j->next;
		}
		a = a->next;
	}
}

double	compute_disorder(t_stack *a)
{
	long	mistakes;
	long	total;

	mistakes = 0;
	total = 0;
	count_pairs(a, &mistakes, &total);
	if (total == 0)
		return (0.0);
	return ((double)mistakes / (double)total);
}

t_strategy	pick_strategy(t_strategy s, double disorder, int size)
{
	if (s != ADAPTIVE)
		return (s);
	if (size <= 5 || disorder < 0.2)
		return (SIMPLE);
	if (disorder < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}
