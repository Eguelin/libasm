/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:13:39 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/15 11:25:56 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_BONUS_H
# define TEST_UTILS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include "libasm_bonus.h"

t_list	*list_push_front_c(t_list **begin_list, void *data);
void	list_clear(t_list **begin_list);
int	list_is_sort(t_list *begin_list, int (*cmp)());
int	list_size(t_list *begin_list);
int	data_in_list(t_list *begin_list, void *data, int (*cmp)());
void	print_list(char *format, t_list *list);

#endif
