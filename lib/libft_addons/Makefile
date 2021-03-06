# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/03/23 08:20:18 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft_addons.a

# Folders
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
FOLDERS			=	$(OBJ) $(SRC) $(INCLUDE)
INCLUDES		=	-I $(INCLUDE) -I ../libft -I ../libft_printf/include

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-std=gnu17 -g -Wall -Wextra -Werror $(INCLUDES)

# C (Source code) and H (Header) files
SRC_C_FILES		=	ft_radian.c ft_max_int.c ft_min_int.c \
					ft_mod_int.c ft_mod_double.c \
					ft_matrix_vector_double.c \
					ft_max_double.c ft_min_double.c ft_isdigit_base.c \
					ft_strtoi.c ft_login_event_1.c ft_login_event_2.c \
					ft_login_event_3.c ft_login_event_4.c
SRC_H_FILES		=	libft_addons.h

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

.PHONY: all
all: $(NAME)
	@echo "$(GREEN)Done!$(END)"

$(NAME): $(FOLDERS) $(H_FILES) $(C_FILES) $(O_FILES)
	ar -rcs $(NAME) $(O_FILES)

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile
	$(CC) -c -o $@ $< $(C_FLAGS)

$(FOLDERS):
	mkdir $@

$(C_FILES):
	touch $@

$(H_FILES):
	touch $@

.PHONY: clean
clean:
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	rm -f $(NAME_1)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	norminette $(SRC)/* $(INCLUDE)/*
