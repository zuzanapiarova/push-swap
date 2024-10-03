/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:26 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/03 18:08:20 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	has_duplicates(int value, t_stack *s)
{
	t_node	*current;

	current = s->head;
	while (current)
	{
		if (current->value == value)
			return (1);
		else
			current = current->next;
	}
	return (0);
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

void	index_stack(t_stack *s)
{
	t_node	*temp;
	int		index;

	index = 0;
	temp = s->head;
	while (temp)
	{
		temp->i = index;
		temp = temp->next;
		index++;
	}
}

void	print_stack(t_stack *s)
{
	t_node	*current;

	current = s->head;
	if (current)
		printf("Stack: size: %d(first: %d, last: %d, min: %d, max:%d)\n",
			s->size, s->first->value, s->last->value, s->min->value,
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
