/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:26 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/18 11:07:03 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	check_duplicates(int value, t_node *n)
{
	t_node *current;

	current = n;
	while (current)
	{
		if (current->value == value)
		{
			ft_putstr_fd("Duplicates\n", 2);
			exit(EXIT_FAILURE);
			// TODO: FREE AND DELETE ENTIRE STACK
		}
		else
			current = current->next;
	}
}

bool	is_valid_arg(char *s)
{
	// rozdel na jednotlive cisla a potom atoi a pridaj do stacku
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (*s == 32 || ft_isdigit(*s))
	{
		i++;
		s++;
	}
	return (i == len);
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

void find_values(t_stack *s)
{
	t_node *temp;

	s->first = s->head;
	s->min = s->head;
	s->max = s->head;
	temp = s->head;
	while(temp->next != NULL)
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

// selects r or rr depending on which is faster to get the node n to top
int	select_r_or_rr(t_node *n, t_stack *s)
{
	int	operation;

	if (n->i <= s->size / 2)
		operation = 1; // r
	else
		operation = 2; // rr

	return (operation);
}
// OR implement index_from_top and index_from_bottom and depending on which is bigger, either ra, ra, ra (top) or rra, rra, rra(bottom)


