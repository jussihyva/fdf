# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 10:35:04 by ubuntu            #+#    #+#              #
#    Updated: 2020/08/22 11:20:07 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG					=	/var/tmp/fdf_lib_make.log
LIBFT_H				=	libft.h
FT_PRINTF_H			=	ft_printf.h
LIBFT_A				=	libft.a
FT_PRINTF_A			=	libftprintf.a

LIBFT_FOLDER		=	./libft
FT_PRINTF_FOLDER	=	./ft_printf/src

all: rm_log libft ft_printf headers archives

headers: $(LIBFT_H) $(FT_PRINTF_H)

$(LIBFT_H): $(LIBFT_FOLDER)/$(LIBFT_H)
	cp $(LIBFT_FOLDER)/$(LIBFT_H) ./ | tee $(LOG)

$(FT_PRINTF_H): $(FT_PRINTF_FOLDER)/$(FT_PRINTF_H)
	cp $(FT_PRINTF_FOLDER)/$(FT_PRINTF_H) ./ | tee $(LOG)

archives: $(LIBFT_A) $(FT_PRINTF_A)

$(LIBFT_A): $(LIBFT_FOLDER)/$(LIBFT_A)
	cp $(LIBFT_FOLDER)/$(LIBFT_A) ./ | tee $(LOG)

$(FT_PRINTF_A): $(FT_PRINTF_FOLDER)/../$(FT_PRINTF_A)
	cp $(FT_PRINTF_FOLDER)/../$(FT_PRINTF_A) ./ | tee $(LOG)

libft:
	@make -C ${LIBFT_FOLDER} >> $(LOG)

ft_printf:
	@make -C ${FT_PRINTF_FOLDER}/.. >> $(LOG)

rm_log:
	@\rm -f $(LOG)

log: all
	@cat $(LOG)

.PHONY: all libft ft_printf headers arcaives rm_log log
