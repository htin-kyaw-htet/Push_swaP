/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:43:11 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:43:11 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	set_flag(char *s, t_config *cfg)
{
	if (!ft_strcmp(s, "--simple"))
		cfg->strategy = SIMPLE;
	else if (!ft_strcmp(s, "--medium"))
		cfg->strategy = MEDIUM;
	else if (!ft_strcmp(s, "--complex"))
		cfg->strategy = COMPLEX;
	else if (!ft_strcmp(s, "--adaptive"))
		cfg->strategy = ADAPTIVE;
	else if (!ft_strcmp(s, "--bench"))
		cfg->bench = 1;
	else if (!ft_strcmp(s, "--count-only"))
		cfg->count_only = 1;
	else
		return (0);
	return (1);
}

static int	add_tokens(char *s, int *nums, int *size)
{
	char	*end;
	int		found;

	found = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (!*s)
			break ;
		end = s;
		while (*end && *end != ' ')
			end++;
		if (*end)
			*end++ = '\0';
		if (!is_number(s) || !parse_int(s, &nums[*size]))
			return (0);
		(*size)++;
		found++;
		s = end;
	}
	return (found > 0);
}

int	count_tokens(int ac, char **av)
{
	int	i;
	int	j;
	int	total;

	i = 1;
	total = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] != ' ' && (j == 0 || av[i][j - 1] == ' '))
				total++;
			j++;
		}
		i++;
	}
	return (total + 1);
}

int	parse_args(int ac, char **av, int *nums, t_config *cfg)
{
	int	i;
	int	size;

	i = 1;
	size = 0;
	while (i < ac)
	{
		if (!set_flag(av[i], cfg))
		{
			if (!add_tokens(av[i], nums, &size))
				return (-1);
		}
		i++;
	}
	return (size);
}
