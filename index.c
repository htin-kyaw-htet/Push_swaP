/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:44:02 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:44:02 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_sqrt(int n)
{
	int	i;

	i = 0;
	while ((i + 1) * (i + 1) <= n)
		i++;
	return (i);
}

void	assign_index(t_stack *a)
{
	t_stack	*cur;
	t_stack	*other;
	int		rank;

	cur = a;
	while (cur)
	{
		rank = 0;
		other = a;
		while (other)
		{
			if (other->value < cur->value)
				rank++;
			other = other->next;
		}
		cur->index = rank;
		cur = cur->next;
	}
}
