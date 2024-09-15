/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_upgraded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:52:29 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/15 21:53:18 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_stackadd_back(t_stack *stack, t_node *new_node)
{
	t_node	*temp;

	if (!stack || !new_node)
		return ;
	if (stack->head == NULL)
		stack->head = new_node;
	else
	{
		temp = stack->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_node	*ft_stacknew(int value)
{
	t_node	*result;

	result = (t_node *)malloc(sizeof(t_node));
	if (!result)
		return (NULL);
	result->value = value;
	result->next = NULL;
	return (result);
}

t_node	*ft_stacklast(t_stack *s)
{
	t_node *temp;

	if (!s)
		return (NULL);
	temp = s->head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	index_stack(t_stack *s)
{
	t_node *temp;
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

	printf("Stack %s, size: %d (first: %d, last: %d, min: %d, max:%d)\n", s->name, s->size, s->first->value, s->last->value, s->min->value, s->max->value);
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
