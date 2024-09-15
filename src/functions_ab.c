/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_ab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:50:31 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/04 18:51:25 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// ss : sa and sb at the same time.
void	ss(t_stack *a, t_stack *b)
{
	ft_putstr_fd("ss\n", 1);
	sa(a);
	sb(b);
}

// rr : ra and rb at the same time.
void	rr(t_stack *a, t_stack *b)
{
	ft_putstr_fd("rr\n", 1);
	ra(a);
	rb(b);
}

// rrr : rra and rrb at the same time.
void	rrr(t_stack *a, t_stack *b)
{
	ft_putstr_fd("rrr\n", 1);
	ra(a);
	rb(b);
}
