/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_ab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:50:31 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/21 09:00:05 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
// ss : sa and sb at the same time.
void    ss(t_stack *a, t_stack *b)
{
   t_node  *temp1a;
   t_node  *temp2a;
   t_node  *temp1b;
   t_node  *temp2b;


   ft_putstr_fd("ss\n", 1);
   a->head->i++;
   if (a->head && a->head->next)
   {
       temp1a = a->head;
       temp2a = a->head->next;
       temp1a->next = temp2a->next;
       temp2a->next = temp1a;
       a->head = temp2a;
       a->first = a->head;
       if (temp1a->next == NULL)
           a->last = temp1a;
   }
   a->head->i--;
   b->head->i++;
   if (b->head && b->head->next)
   {
       temp1b = b->head;
       temp2b = b->head->next;
       temp1b->next = temp2b->next;
       temp2b->next = temp1b;
       b->head = temp2b;
       b->first = b->head;
       if (temp1b->next == NULL)
           b->last = temp1b;
   }
   b->head->i--;
}


// rr : ra and rb at the same time.
void    rr(t_stack *a, t_stack *b)
{
   t_node  *temp1;
   t_node  *temp2;


   ft_putstr_fd("rr\n", 1);
   if (a->head && a->head->next)
   {
       temp1 = a->head;
       a->head = a->head->next;
       temp1->next = NULL;
       ft_stackadd_back(a, temp1);
       a->first = a->head;
       a->last = temp1;
   }
   if (b->head && b->head->next)
   {
       temp2 = b->head;
       b->head = b->head->next;
       temp2->next = NULL;
       ft_stackadd_back(b, temp2);
       b->first = b->head;
       b->last = temp2;
   }
   index_stack(a);
   index_stack(b);
}


// rrr : rra and rrb at the same time.
void    rrr(t_stack *a, t_stack *b)
{
   t_node  *new_last1;
   t_node  *last1;
   t_node  *new_last2;
   t_node  *last2;


   ft_putstr_fd("rrr\n", 1);
   if (a->head && a->head->next)
   {
       new_last1 = a->head;
       while (new_last1->next->next != NULL)
           new_last1 = new_last1->next;
       last1 = new_last1->next;
       new_last1->next = NULL;
       last1->next = a->head;
       a->head = last1;
       a->first = a->head;
       a->last = new_last1;
   }
   if (b->head && b->head->next)
   {
       new_last2 = b->head;
       while (new_last2->next->next != NULL)
           new_last2 = new_last2->next;
       last2 = new_last2->next;
       new_last2->next = NULL;
       last2->next = b->head;
       b->head = last2;
       b->first = b->head;
       b->last = new_last2;
   }
   index_stack(a);
   index_stack(b);
}
