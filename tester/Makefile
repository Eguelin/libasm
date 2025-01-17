# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 18:40:32 by eguelin           #+#    #+#              #
#    Updated: 2025/01/17 10:31:01 by eguelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re libasm libasm_bonus
.SILENT:

# **************************************************************************** #
#                                   Variable                                   #
# **************************************************************************** #

NAME		= test
BONUS		= test_bonus
OBJS_DIR	= .objs/
SRCS_DIR	= srcs/
INCS_DIR	= includes/
BONUS_DIR	= bonus/
LIB_DIR		= ../
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCS		= -I $(INCS_DIR) -I $(LIB_DIR)$(INCS_DIR)
INCS_BONUS	= $(INCS) -I $(INCS_DIR)$(BONUS_DIR) -I $(LIB_DIR)$(INCS_DIR)$(BONUS_DIR)
LIB			= -L$(LIB_DIR) -lasm
RM			= rm -fr

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

# **************************************************************************** #
#                                    Sources                                   #
# **************************************************************************** #

ALL_FILES	= test.c \
			  test_utils.c

OBJS_FILES	= $(addprefix $(OBJS_DIR), $(ALL_FILES:.c=.o))

DEP_FILES	= $(OBJS_FILES:.o=.d)

BONUS_FILES	= test_bonus.c \
			  test_utils_bonus.c

ALL_BONUS_FILES	= test_utils.c \
				  $(addprefix $(BONUS_DIR), $(BONUS_FILES))

BONUS_OBJS_FILES	= $(addprefix $(OBJS_DIR), $(ALL_BONUS_FILES:.c=.o))

BONUS_DEP_FILES		= $(BONUS_OBJS_FILES:.o=.d)

# **************************************************************************** #
#                                     Rules                                    #
# **************************************************************************** #

all: $(NAME) $(BONUS)

$(NAME): $(OBJS_FILES) libasm
	$(CC) $(CFLAGS) $(OBJS_FILES) $(INCS) $(LIB) -o $(NAME)
	printf $(COMP_MSG)
	./$(NAME)

$(BONUS): $(BONUS_OBJS_FILES) libasm_bonus
	$(CC) $(CFLAGS) $(BONUS_OBJS_FILES) $(INCS_BONUS) $(LIB) -o $(BONUS)
	printf $(BONUS_COMP_MSG)
	./$(BONUS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@

$(OBJS_DIR)$(BONUS_DIR)%.o: $(SRCS_DIR)$(BONUS_DIR)%.c | $(OBJS_DIR)$(BONUS_DIR)
	$(CC) $(CFLAGS) $(INCS_BONUS) -MMD -MP -c $< -o $@

clean:
	$(MAKE) clean -sC $(LIB_DIR)
	$(RM) $(OBJS_DIR)
	printf $(CLEAN_MSG)

fclean: clean
	$(MAKE) fclean -sC $(LIB_DIR)
	$(RM) $(NAME)
	$(RM) $(BONUS)
	printf $(FULL_CLEAN_MSG)

re: fclean all

libasm:
	$(MAKE) -sC $(LIB_DIR)

libasm_bonus:
	$(MAKE) bonus -sC $(LIB_DIR)

$(OBJS_DIR):
	mkdir -p $@

$(OBJS_DIR)$(BONUS_DIR):
	mkdir -p $@

-include $(DEP_FILES) $(BONUS_DEP_FILES)
