/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:05 by eguelin           #+#    #+#             */
/*   Updated: 2025/01/16 09:05:51 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include "test_utils_bonus.h"

sigjmp_buf env;
struct sigaction sa;

void	test_atoi_base(void);
void	test_list_push_front(void);
void	test_list_size(void);
void	test_list_sort(void);
void	test_list_remove_if(void);

int main()
{
	sigemptyset(&sa.sa_mask);
	test_atoi_base();
	test_list_push_front();
	test_list_size();
	test_list_sort();
	test_list_remove_if();
	return (0);
}

void	test_atoi_base(void)
{
	int		ret;
	char	*tab[38][3] = {{"-1", "01", "-1"},
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
						{"\x7f\xff\xff\x82\xff\x7f", "\xff\x82\x7f", "497"},
						{"", "10", "0"},
						{"+++---+-9", "369", "2"},
						{"444" , "4", "0"},
						{"55", "012345+", "0"},
						{"55", "012345-", "0"},
						{"55", "012345\t", "0"},
						{"55", "012345 ", "0"},
						{"55", "0123455", "0"},
						{NULL, "01", "0"},
						{"1", NULL, "0"},
						{NULL, NULL, "0"}};

	printf(PURPLE"\t--- ft_atoi_base ---\n"RESET);
	for (int i = 0; i < 38; i++)
	{
		ASSERT_EXPR_CONDITION(ret = ft_atoi_base(tab[i][0], tab[i][1]), ret == atoi(tab[i][2]));
		printf(BLUE"ft_atoi_base(\"%s\", \"%s\") = %d\n"RESET, tab[i][0], tab[i][1], ret);
	}
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
	list_push_front_c(&list, "elem1");
	ASSERT_NO_SEGFAULT(ft_list_sort(&list, NULL));
	printf(BLUE"ft_list_sort(list, NULL)\n"RESET);
	list_clear(&list);
}

void	test_list_remove_if(void)
{
	t_list	*list = NULL;
	char	*tab[10][5] = {{"elem1", "elem3", "elem2", "elem4", "elem5"},
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
	printf(PURPLE"\t--- ft_list_remove_if ---\n"RESET);
	list_push_front_c(&list, "elem1");
	ASSERT_EXPR_CONDITION(ft_list_remove_if(&list, "elem1", &strcmp, &free), list_size(list) == 0);
	printf(BLUE"ft_list_remove_if(list, \"elem1\", &strcmp, &free) = ");
	print_list("[%s] ", list);
	printf("\n"RESET);
	list_clear(&list);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
			list_push_front_c(&list, tab[i][j]);
		ASSERT_EXPR_CONDITION(ft_list_remove_if(&list, "elem1", &strcmp, &free),
		list_size(list) == 4 && !data_in_list(list, "elem1", &strcmp));
		printf(BLUE"ft_list_remove_if(list, \"elem1\", &strcmp, &free) = ");
		print_list("[%s] ", list);
		printf("\n"RESET);
		list_clear(&list);
	}

	// NULL tests
	ASSERT_NO_SEGFAULT(ft_list_remove_if(NULL, "elem1", &strcmp, &free));
	printf(BLUE"ft_list_remove_if(NULL, \"elem1\", &strcmp, &free)\n"RESET);
	list_push_front_c(&list, "elem1");
	ASSERT_NO_SEGFAULT(ft_list_remove_if(&list,"elem1", NULL, &free));
	printf(BLUE"ft_list_remove_if(list, \"elem1\", NULL, &free)\n"RESET);
	list_clear(&list);
	list_push_front_c(&list, "elem1");
	ASSERT_NO_SEGFAULT(ft_list_remove_if(&list, "elem1", &strcmp, NULL));
	printf(BLUE"ft_list_remove_if(list, \"elem1\", &strcmp, NULL)\n"RESET);
	list_clear(&list);
}
