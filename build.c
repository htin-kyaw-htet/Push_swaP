/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:39:45 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:39:45 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	build_stack(t_stack **a, int *nums, int size)
{
	t_stack	*node;
	int		i;

	i = 0;
	while (i < size)
	{
		node = new_node(nums[i]);
		if (!node)
		{
			free_stack(a);
			return (0);
		}
		add_back(a, node);
		i++;
	}
	return (1);
}

int	load_stack(int ac, char **av, t_stack **a, t_config *cfg)
{
	int	*nums;
	int	size;
	int	ok;

	nums = malloc(sizeof(int) * count_tokens(ac, av));
	if (!nums)
		return (0);
	size = parse_args(ac, av, nums, cfg);
	ok = (size >= 0 && !has_duplicate(nums, size));
	if (ok)
		ok = build_stack(a, nums, size);
	free(nums);
	return (ok);
}
