# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2020/08/22 11:43:13 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
CC			=	gcc
FLAGS		=	-g -Wall -Wextra -Werror
FRAMEWORKS	=	-framework OpenGL -framework AppKit
LIBS		=	-lmlx -lft -lftprintf
LIB_FOLDER	=	lib
SRC_FOLDER	=	src
OBJ_FOLDER	=	obj
INCLUDES	=	-I $(SRC_FOLDER) -I $(LIB_FOLDER)
SRCS		=	draw_line.c event_handler.c
OBJS		=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRCS)))

all: $(NAME)

$(NAME): $(SRC_FOLDER)/$(NAME).c $(OBJS) | $(OBJ_FOLDER)
	$(CC) $(FLAGS) $(INCLUDES) -o $(NAME) $(SRC_FOLDER)/$(NAME).c $(OBJS) -L $(LIB_FOLDER) $(LIBS) $(FRAMEWORKS)

$(OBJS): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

clean:
	rm -f $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

norm:
	norminette *[ch]

.PHONY: all clean fclean re norm
