# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:12:33 by pdolinar          #+#    #+#              #
#    Updated: 2022/09/15 18:10:15 by pdolinar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus
INC			=	include
HEADER		=	$(INC)/phil_bonus.h

CC			=	gcc
CFLAGS		=	-pthread -g -Wall -Wextra -Werror
RM			=	rm -rf

CLEAR = \033[0m
PR = \033[1;35m
GR = \033[1;32m

SRC_DIR		=	src/
OBJ_DIR		=	build/

SRC			=	main.c init.c utils.c args.c routine.c exit.c

OBJ = $(addprefix $(OBJ_DIR),$(notdir $(SRC:.c=.o)))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) #-fsanitize=thread
	@echo "$(GR)>> compiling ... \n Done!$(CLEAR)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADER)
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(PR)All object files deleted$(CLEAR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(PR)$(NAME) deleted$(CLEAR)"

norm:
	norminette $(SRC_DIR) $(INC)

re:	fclean all

.PHONY: all clean fclean re norm ll
