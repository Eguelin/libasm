# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 18:40:32 by eguelin           #+#    #+#              #
#    Updated: 2025/01/17 13:42:33 by eguelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus clean fclean re re_bonus all_$(TESTS) $(TESTS) $(TESTS_BONUS) clean_$(TESTS) fclean_$(TESTS) re_$(TESTS)

# **************************************************************************** #
#                                   Variable                                   #
# **************************************************************************** #

NAME		= libasm.a
OBJS_DIR	= .objs/
SRCS_DIR	= srcs/
BONUS_DIR	= bonus/
AS			= nasm
AFLAGS		= -f elf64
ARC			= ar -rcs
RM			= rm -fr
PRINTF		= @printf

# ********************************   tests   ********************************* #

TESTS		= test
TESTS_BONUS	= test_bonus
INCS_DIR	= includes/
TESTS_DIR	= tests/
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCS		= -I $(INCS_DIR) -I $(INCS_DIR)$(TESTS_DIR)
INCS_BONUS	= $(INCS) -I $(INCS_DIR)$(BONUS_DIR) -I $(INCS_DIR)$(TESTS_DIR)$(BONUS_DIR)
LIB			= -L. -lasm

# **************************************************************************** #
#                                    Colors                                    #
# **************************************************************************** #

BLACK	= \033[30m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
PURPLE	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
DEFAULT	= \033[0m

# **************************************************************************** #
#                                    Message                                   #
# **************************************************************************** #

COMP_MSG		= "$(GREEN)Compilation $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
BONUS_COMP_MSG	= "$(BLUE)Compilation $(NAME) bonus $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
CLEAN_MSG		= "$(RED)Cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
FULL_CLEAN_MSG	= "$(PURPLE)Full cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"

# ********************************   tests   ********************************* #

TESTS_MSG				= "$(GREEN)Compilation $(TESTS) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
TESTS_BONUS_MSG			= "$(BLUE)Compilation $(TESTS_BONUS) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
TESTS_CLEAN_MSG			= "$(RED)Cleaning $(TESTS) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
TESTS_FULL_CLEAN_MSG	= "$(PURPLE)Full cleaning $(TESTS) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"

# **************************************************************************** #
#                                    Sources                                   #
# **************************************************************************** #

FILES	= ft_read.s \
		  ft_strcmp.s \
		  ft_strcpy.s \
		  ft_strdup.s \
		  ft_strlen.s \
		  ft_write.s \

BONUS_FILES	= ft_atoi_base_bonus.s \
			  ft_list_push_front_bonus.s \
			  ft_list_size_bonus.s \
			  ft_list_sort_bonus.s \
			  ft_list_remove_if_bonus.s

PATH_BONUS_FILES	= $(addprefix $(BONUS_DIR), $(BONUS_FILES))

OBJS_FILES	= $(addprefix $(OBJS_DIR), $(FILES:.s=.o))

BONUS_OBJS_FILES	= $(addprefix $(OBJS_DIR), $(PATH_BONUS_FILES:.s=.o))

# ********************************   tests   ********************************* #

TESTS_FILES	= test.c \
			  test_utils.c

TESTS_BONUS_FILES	= test_bonus.c \
					  test_utils_bonus.c

PATH_TESTS_BONUS_FILES	= test_utils.c \
						  $(addprefix $(BONUS_DIR), $(TESTS_BONUS_FILES))

OBJS_TESTS_FILES	= $(addprefix $(OBJS_DIR)$(TESTS_DIR), $(TESTS_FILES:.c=.o))

OBJS_TESTS_BONUS_FILES	= $(addprefix $(OBJS_DIR)$(TESTS_DIR), $(PATH_TESTS_BONUS_FILES:.c=.o))

DEP_TESTS_FILES	= $(OBJS_TESTS_FILES:.o=.d)

DEP_TESTS_BONUS_FILES	= $(OBJS_TESTS_BONUS_FILES:.o=.d)

# **************************************************************************** #
#                                     Rules                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS_FILES)
	$(ARC) $(NAME) $(OBJS_FILES)
	$(PRINTF) $(COMP_MSG)

bonus: all $(OBJS_DIR)$(BONUS_DIR) $(BONUS_OBJS_FILES)
	$(ARC) $(NAME) $(BONUS_OBJS_FILES)
	$(PRINTF) $(BONUS_COMP_MSG)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s | $(OBJS_DIR)
	$(AS) $(AFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	$(PRINTF) $(CLEAN_MSG)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TESTS) $(TESTS_BONUS)
	$(PRINTF) $(FULL_CLEAN_MSG)

re: fclean all

re_bonus: fclean bonus

$(OBJS_DIR):
	mkdir -p $@

$(OBJS_DIR)$(BONUS_DIR):
	mkdir -p $@

# ********************************   tests   ********************************* #

all_$(TESTS): $(TESTS) $(TESTS_BONUS)

$(TESTS): all $(OBJS_TESTS_FILES)
	$(CC) $(CFLAGS) $(INCS) $(OBJS_TESTS_FILES) $(LIB) -o $(TESTS)
	$(PRINTF) $(TESTS_MSG)
	./$(TESTS)

$(TESTS_BONUS): bonus $(OBJS_TESTS_BONUS_FILES)
	$(CC) $(CFLAGS) $(INCS_BONUS) $(OBJS_TESTS_BONUS_FILES) $(LIB) -o $(TESTS_BONUS)
	$(PRINTF) $(TESTS_BONUS_MSG)
	./$(TESTS_BONUS)

$(OBJS_DIR)$(TESTS_DIR)%.o: $(TESTS_DIR)%.c | $(OBJS_DIR)$(TESTS_DIR)
	$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $<  -o $@

$(OBJS_DIR)$(TESTS_DIR)$(BONUS_DIR)%.o: $(TESTS_DIR)$(BONUS_DIR)%.c | $(OBJS_DIR)$(TESTS_DIR)$(BONUS_DIR)
	$(CC) $(CFLAGS) $(INCS_BONUS) -MMD -MP -c $< -o $@

$(OBJS_DIR)$(TESTS_DIR):
	mkdir -p $@

$(OBJS_DIR)$(TESTS_DIR)$(BONUS_DIR):
	mkdir -p $@

clean_$(TESTS):
	$(RM) $(OBJS_DIR)$(TESTS_DIR)
	$(PRINTF) $(TESTS_CLEAN_MSG)

fclean_$(TESTS): clean_$(TESTS)
	$(RM) $(TESTS) $(TESTS_BONUS)
	$(PRINTF) $(TESTS_FULL_CLEAN_MSG)

re_$(TESTS): fclean all_$(TESTS)

-include $(DEP_TESTS_FILES) $(DEP_TESTS_BONUS_FILES)
