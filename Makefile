# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 18:40:32 by eguelin           #+#    #+#              #
#    Updated: 2024/03/18 19:00:34 by eguelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
.SILENT:

# **************************************************************************** #
#                                   Variable                                   #
# **************************************************************************** #

NAME		= libasm.a
EXEC		= run
EXEC_BONUS	= run_bonus
OBJS_DIR	= .objs/
SRCS_DIR	= srcs/
INCS_DIR	= includes/
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INC			= -I $(INCS_DIR)
LIB			= -L. -lasm
AS			= nasm
AFLAGS		= -f elf64
ARC			= ar -rcs
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

COMP_MSG		= "$(GREEN)Compilation $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"
BONUS_COMP_MSG	= "$(BLUE)Compilation $(NAME) bonus $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"
CLEAN_MSG		= "$(RED)Cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"
FULL_CLEAN_MSG	= "$(PURPLE)Full cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"

# **************************************************************************** #
#                                    Sources                                   #
# **************************************************************************** #

ALL_FILES	= ft_read.s \
			  ft_strcmp.s \
			  ft_strcpy.s \
			  ft_strdup.s \
			  ft_strlen.s \
			  ft_write.s \

BONUS_DIR	= bonus/
BONUS_FILES	= ft_atoi_base.s \
			  ft_list_push_front.s \
			  ft_list_size.s

ALL_BONUS_FILES	= $(addprefix $(BONUS_DIR), $(BONUS_FILES))

OBJS_FILES	= $(addprefix $(OBJS_DIR), $(ALL_FILES:.s=.o))

BONUS_OBJS_FILES	= $(addprefix $(OBJS_DIR), $(ALL_BONUS_FILES:.s=.o))

# **************************************************************************** #
#                                     Rules                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS_FILES)
	$(ARC) $(NAME) $(OBJS_FILES)
	echo $(COMP_MSG)

bonus: all $(OBJS_DIR)$(BONUS_DIR) $(BONUS_OBJS_FILES)
	$(ARC) $(NAME) $(BONUS_OBJS_FILES)
	echo $(BONUS_COMP_MSG)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s | $(OBJS_DIR)
	$(AS) $(AFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	echo $(CLEAN_MSG)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(EXEC)
	$(RM) $(EXEC_BONUS)
	echo $(FULL_CLEAN_MSG)

re: fclean all

run: all
	$(CC) main.c $(INC) $(LIB) -o $(EXEC)
	./$(EXEC)

run_bonus: bonus
	$(CC) main_bonus.c $(INC) $(LIB) -o $(EXEC_BONUS)
	./$(EXEC_BONUS)

leaks: all
	$(CC) main.c $(INC) $(LIB) -o $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./$(EXEC)

leaks_bonus: bonus
	$(CC) main_bonus.c $(INC) $(LIB) -o $(EXEC_BONUS)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./$(EXEC_BONUS)

$(OBJS_DIR):
	mkdir -p $@

$(OBJS_DIR)$(BONUS_DIR):
	mkdir -p $@
