/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/15 10:52:26 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include "libasm_bonus.h"

sigjmp_buf env;
struct sigaction sa;

void	test_atoi_base(void);
void	test_list_push_front(void);
void	test_list_size(void);
void	test_list_sort(void);
// void	test_list_remove_if(void);

int main()
{
	sigemptyset(&sa.sa_mask);
	test_atoi_base();
	test_list_push_front();
	test_list_size();
	test_list_sort();
	// test_list_remove_if();
	return (0);
}

t_list	*list_push_front_c(t_list **begin_list, void *data)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->data = data;
	new->next = *begin_list;
	*begin_list = new;
	return (new);
}

void	list_clear(t_list **begin_list)
{
	t_list	*tmp;

	while (*begin_list)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
}

int	list_is_sort(t_list *begin_list, int (*cmp)())
{
	t_list	*tmp;

	tmp = begin_list;
	while (tmp && tmp->next)
	{
		if (cmp(tmp->data, tmp->next->data) > 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	list_size(t_list *begin_list)
{
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = begin_list;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

void	print_list(char *format, t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (tmp)
	{
		while (tmp)
		{
			printf(format, (char *)tmp->data);
			tmp = tmp->next;
		}
	}
}

void	test_atoi_base(void)
{
	int		ret;
	char	*tab[][3] = {{"-1", "01", "-1"},
						{"1", "01", "1"},
						{"-1", "0123456789", "-1"},
						{ "1", "0123456789", "1"},
						{"-1", "0123456789abcdef", "-1"},
						{"1", "0123456789abcdef", "1"},
						{"-1", "0123456789ABCDEF", "-1"},
						{"1", "0123456789ABCDEF", "1"},
						{"10111f", "01", "23"},
						{"-10111f", "01", "-23"},
						{"10111f", "0123456789", "10111"},
						{"-10111f", "0123456789", "-10111"},
						{"10111f", "0123456789abcdef", "1052959"},
						{"-10111f", "0123456789abcdef", "-1052959"},
						{"10111f", "0123456789ABCDEF", "65809"},
						{"-10111f", "0123456789ABCDEF", "-65809"},
						{"-10000000000000000000000000000000", "01", "-2147483648"},
						{"1111111111111111111111111111111", "01", "2147483647"},
						{"-2147483648", "0123456789", "-2147483648"},
						{"2147483647", "0123456789", "2147483647"},
						{"-7fffffff", "0123456789abcdef", "-2147483647"},
						{"7fffffff", "0123456789abcdef", "2147483647"},
						{"-7FFFFFFF", "0123456789ABCDEF", "-2147483647"},
						{"7FFFFFFF", "0123456789ABCDEF", "2147483647"},
						{"\t   7", "0123456789", "7"},
						{"\t   -7", "0123456789", "-7"},
						{"", "10", "0"},
						{"+++---+-9", "369", "2"},
						{"444" , "4", "0"},
						{"55", "012345+", "0"},
						{"55", "012345\t", "0"},
						{NULL, "01", "0"},
						{"1", NULL, "0"},
						{NULL, NULL, "0"}};

	printf(PURPLE"\t--- ft_atoi_base ---\n"RESET);
	for (int i = 0; i < 33; i++)
	{
		ASSERT_EXPR_CONDITION(ret = ft_atoi_base(tab[i][0], tab[i][1]), ret == atoi(tab[i][2]));
		printf(BLUE"ft_atoi_base(\"%s\", \"%s\") = %d\n"RESET, tab[i][0], tab[i][1], ret);
	}

	return ;
}

void	test_list_push_front(void)
{
	t_list	*list = NULL;
	char	*tab[] = {"elem1", "elem2", "elem3", "elem4", "elem5", "elem6", "elem7", "elem8", "elem9", "elem10"};

	// Classic tests
	printf(PURPLE"\t--- ft_list_push_front ---\n"RESET);
	for (int i = 0; i < 10; i++)
	{
		ASSERT_EXPR_CONDITION(ft_list_push_front(&list, tab[i]),
		list->data == tab[i] && (list->next == NULL || (list->next->data == tab[i - 1] && list_size(list) == i + 1)));
		printf(BLUE"ft_list_push_front(&list, \"%s\") = ", tab[i]);
		print_list("[%s] ", list);
		printf("\n"RESET);
	}
	list_clear(&list);

	// NULL tests
	ASSERT_NO_SEGFAULT(ft_list_push_front(NULL, "elem1"));
	printf(BLUE"ft_list_push_front(NULL, \"elem1\")\n"RESET);

	return ;
}

void	test_list_size(void)
{
	t_list	*list = NULL;
	char	*tab[1] = {"elem1"};
	char	*tab2[3] = {"elem1", "elem2", "elem3"};
	char	*tab3[5] = {"elem1", "elem2", "elem3", "elem4", "elem5"};
	char	*tab4[10] = {"elem1", "elem2", "elem3", "elem4", "elem5", "elem6", "elem7", "elem8", "elem9", "elem10"};
	char	**all_tab[4] = {tab, tab2, tab3, tab4};
	int		size;
	int		size_tab[4] = {1, 3, 5, 10};


	// Classic tests
	printf(PURPLE"\t--- ft_list_size ---\n"RESET);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < size_tab[i]; j++)
			list_push_front_c(&list, all_tab[i][j]);
		ASSERT_EXPR_CONDITION(size = ft_list_size(list), size == size_tab[i]);
		printf(BLUE"ft_list_size(list) = %d (", size);
		print_list("[%s] ", list);
		printf(")\n"RESET);
		list_clear(&list);
	}

	// NULL tests
	ASSERT_EXPR_CONDITION(size = ft_list_size(NULL), size == 0);
	printf(BLUE"ft_list_size(NULL) = %d\n"RESET, size);
}


void	test_list_sort(void)
{
	t_list	*list = NULL;
	char	*tab[3][1] = {{"elem1"}, {"elem2"}, {"elem3"}};
	char	*tab2[6][3] = {{"elem1", "elem3", "elem2"},
						{"elem3", "elem2", "elem1"},
						{"elem2", "elem1", "elem3"},
						{"elem2", "elem3", "elem1"},
						{"elem3", "elem1", "elem2"},
						{"elem1", "elem2", "elem3"}};
	char	*tab3[10][5] = {{"elem1", "elem3", "elem2", "elem4", "elem5"},
						{"elem3", "elem2", "elem1", "elem5", "elem4"},
						{"elem2", "elem1", "elem3", "elem4", "elem5"},
						{"elem2", "elem3", "elem1", "elem5", "elem4"},
						{"elem3", "elem1", "elem2", "elem4", "elem5"},
						{"elem1", "elem2", "elem3", "elem4", "elem5"},
						{"elem1", "elem3", "elem2", "elem5", "elem4"},
						{"elem3", "elem2", "elem1", "elem4", "elem5"},
						{"elem2", "elem1", "elem3", "elem5", "elem4"},
						{"elem2", "elem3", "elem1", "elem4", "elem5"}};

	// Classic tests
	printf(PURPLE"\t--- ft_list_sort ---\n"RESET);
	for (int i = 0; i < 3; i++)
	{
		list_push_front_c(&list, tab[i][0]);
		ASSERT_EXPR_CONDITION(ft_list_sort(&list, &strcmp), list_is_sort(list, &strcmp) && list_size(list) == 1);
		printf(BLUE"ft_list_sort(list, &strcmp) = ");
		print_list("[%s] ", list);
		printf("\n"RESET);
		list_clear(&list);
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
			list_push_front_c(&list, tab2[i][j]);
		ASSERT_EXPR_CONDITION(ft_list_sort(&list, &strcmp), list_is_sort(list, &strcmp) && list_size(list) == 3);
		printf(BLUE"ft_list_sort(list, &strcmp) = ");
		print_list("[%s] ", list);
		printf("\n"RESET);
		list_clear(&list);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
			list_push_front_c(&list, tab3[i][j]);
		ASSERT_EXPR_CONDITION(ft_list_sort(&list, &strcmp), list_is_sort(list, &strcmp) && list_size(list) == 5);
		printf(BLUE"ft_list_sort(list, &strcmp) = ");
		print_list("[%s] ", list);
		printf("\n"RESET);
		list_clear(&list);
	}

	// NULL tests
	ASSERT_NO_SEGFAULT(ft_list_sort(NULL, &strcmp));
	printf(BLUE"ft_list_sort(NULL, &strcmp)\n"RESET);
}
