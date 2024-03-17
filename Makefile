# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 18:40:32 by eguelin           #+#    #+#              #
#    Updated: 2024/03/17 19:42:35 by eguelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
.SILENT:

# **************************************************************************** #
#                                   Variable                                   #
# **************************************************************************** #

NAME		= libasm.a
EXEC		= run
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
			  bonus/ft_atoi_base.s

OBJ_FILES	= $(addprefix $(OBJS_DIR), $(ALL_FILES:.s=.o))

# **************************************************************************** #
#                                     Rules                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(ARC) $(NAME) $(OBJ_FILES)
	echo $(COMP_MSG)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s | $(OBJS_DIR)
	$(AS) $(AFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	echo $(CLEAN_MSG)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(EXEC)
	echo $(FULL_CLEAN_MSG)

re: fclean all

run: all
	$(CC) main.c $(INC) $(LIB) -o $(EXEC)
	./$(EXEC)

leaks: all
	$(CC) main.c $(INC) $(LIB) -o $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./$(EXEC)

$(OBJS_DIR):
	mkdir -p $@/bonus
