# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 18:40:32 by eguelin           #+#    #+#              #
#    Updated: 2025/01/15 11:28:09 by eguelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
.SILENT:

# **************************************************************************** #
#                                   Variable                                   #
# **************************************************************************** #

NAME		= libasm.a
OBJS_DIR	= .objs/
SRCS_DIR	= srcs/
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

COMP_MSG		= "$(GREEN)Compilation $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
BONUS_COMP_MSG	= "$(BLUE)Compilation $(NAME) bonus $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
CLEAN_MSG		= "$(RED)Cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"
FULL_CLEAN_MSG	= "$(PURPLE)Full cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)\n"

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
			  ft_list_size.s \
			  ft_list_sort.s \
			  ft_list_remove_if.s

ALL_BONUS_FILES	= $(addprefix $(BONUS_DIR), $(BONUS_FILES))

OBJS_FILES	= $(addprefix $(OBJS_DIR), $(ALL_FILES:.s=.o))

BONUS_OBJS_FILES	= $(addprefix $(OBJS_DIR), $(ALL_BONUS_FILES:.s=.o))

# **************************************************************************** #
#                                     Rules                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS_FILES)
	$(ARC) $(NAME) $(OBJS_FILES)
	printf $(COMP_MSG)

bonus: all $(OBJS_DIR)$(BONUS_DIR) $(BONUS_OBJS_FILES)
	$(ARC) $(NAME) $(BONUS_OBJS_FILES)
	printf $(BONUS_COMP_MSG)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s | $(OBJS_DIR)
	$(AS) $(AFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	printf $(CLEAN_MSG)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)
	$(RM) $(TEST_BONUS)
	printf $(FULL_CLEAN_MSG)

re: fclean all

$(OBJS_DIR):
	mkdir -p $@

$(OBJS_DIR)$(BONUS_DIR):
	mkdir -p $@
