/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 14:05:33 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 14:05:33 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_strategy
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX
}	t_strategy;

typedef struct s_config
{
	t_strategy	strategy;
	t_strategy	used;
	double		disorder;
	int			bench;	int		count_only;}	t_config;

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

typedef enum e_op
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}	t_op;

typedef struct s_stats
{
	int	count[11];
	int	total;
	int	count_only;
}	t_stats;

/* parse.c / parse_utils.c */
int			ft_strcmp(const char *s1, const char *s2);
int			is_number(char *s);
int			parse_int(char *s, int *out);
int			has_duplicate(int *nums, int size);
int			set_flag(char *s, t_config *cfg);
int			parse_args(int ac, char **av, int *nums, t_config *cfg);
int			count_tokens(int ac, char **av);

/* output helpers */
void		ft_putstr_fd(char *s, int fd);
void		fill_names(char **n);
void		init_stats(t_stats *s);
void		print_op(t_stats *s, int id);
void		print_total_count(int n);
void		print_bench(t_config *cfg, t_stats *s);

/* stack helpers */
t_stack		*new_node(int value);
void		add_back(t_stack **stack, t_stack *node);
int			stack_size(t_stack *stack);
void		free_stack(t_stack **stack);
int			is_sorted(t_stack *stack);

/* basic moves (no printing) */
void		swap_top(t_stack **s);
void		push_top(t_stack **src, t_stack **dst);
void		rotate_up(t_stack **s);
void		rotate_down(t_stack **s);

/* the 11 operations (move + print + count) */
void		sa(t_stack **a, t_stats *s);
void		sb(t_stack **b, t_stats *s);
void		ss(t_stack **a, t_stack **b, t_stats *s);
void		pa(t_stack **a, t_stack **b, t_stats *s);
void		pb(t_stack **a, t_stack **b, t_stats *s);
void		ra(t_stack **a, t_stats *s);
void		rb(t_stack **b, t_stats *s);
void		rr(t_stack **a, t_stack **b, t_stats *s);
void		rra(t_stack **a, t_stats *s);
void		rrb(t_stack **b, t_stats *s);
void		rrr(t_stack **a, t_stack **b, t_stats *s);

/* build.c */
int			build_stack(t_stack **a, int *nums, int size);
int			load_stack(int ac, char **av, t_stack **a, t_config *cfg);

double		compute_disorder(t_stack *a);
void		selection_sort(t_stack **a, t_stack **b, t_stats *s);

int			ft_sqrt(int n);
void		assign_index(t_stack *a);
void		medium_sort(t_stack **a, t_stack **b, t_stats *s);

void		radix_sort(t_stack **a, t_stack **b, t_stats *s);

t_strategy	pick_strategy(t_strategy s, double disorder, int size);

#endif