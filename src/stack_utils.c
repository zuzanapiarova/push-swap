/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:30:45 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/01 17:36:25 by zpiarova         ###   ########.fr       */
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

void	print_stack(t_stack *s)
{
	t_node	*current;

	current = s->head;
	if (current)
		printf("Stack %s, size: %d(first: %d, last: %d, min: %d, max:%d)\n",
			s->name, s->size, s->first->value, s->last->value, s->min->value,
			s->max->value);
	while (current)
	{
		ft_putnbr_fd(current->value, 1);
		ft_putstr_fd("(", 1);
		ft_putnbr_fd(current->i, 1);
		ft_putstr_fd(")", 1);
		ft_putstr_fd(" ", 1);
		current = current->next;
	}
	ft_putchar_fd('\n', 1);
}
