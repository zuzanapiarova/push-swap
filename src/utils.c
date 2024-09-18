/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:26 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/18 19:02:19 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	check_duplicates(int value, t_stack *s)
{
	t_node	*current;

	current = s->head;
	while (current)
	{
		if (current->value == value)
		{
			ft_putstr_fd("Duplicates\n", 2);
			ft_stackclear(s);
			exit(EXIT_SUCCESS);
		}
		else
			current = current->next;
	}
}

// iterate stack until node  is bigger than next node, or we come to end
// if the node we finish at is the last one, list is sorted, else not
bool	is_sorted(t_stack *a)
{
	t_node	*node;

	node = a->head;
	while (node && node->next && node->value < node->next->value)
		node = node->next;
	return (!node -> next);
}

void	find_values(t_stack *s)
{
	t_node	*temp;

	if (!s)
		return ;
	s->first = s->head;
	s->min = s->head;
	s->max = s->head;
	temp = s->head;
	while (temp->next != NULL)
	{
		if (temp->value > s->max->value)
			s->max = temp;
		if (temp->value < s->min->value)
			s->min = temp;
		temp = temp->next;
	}
	s->last = temp;
	if (temp->value > s->max->value)
		s->max = temp;
	if (temp->value < s->min->value)
		s->min = temp;
	index_stack(s);
}

// returns r(1) or rr(2) depending on which is faster to get the node n to top
// OR implement index_from_top and index_from_bottom and depending on which
// is bigger, either ra, ra, ra (top) or rra, rra, rra(bottom)
int	select_r_or_rr(t_node *n, t_stack *s)
{
	int	operation;

	if (n->i <= s->size / 2)
		operation = 1;
	else
		operation = 2;
	return (operation);
}

void	sort_three(t_stack *s)
{
	int	first;
	int	second;
	int	third;

	if (is_sorted(s))
		return ;
	first = s->head->value;
	second = s->head->next->value;
	third = s->head->next->next->value;
	if (first < second && second > third && first < third)
	{
		rra(s);
		sa(s);
	}
	else if (first < second && second > third && first > third)
		rra(s);
	else if (first > second && second < third && first > third)
		ra(s);
	else if (first > second && second < third && first < third)
		sa(s);
	else if (first > second && second > third && first > third)
	{
		sa(s);
		rra(s);
	}
}
