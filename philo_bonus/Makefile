# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/27 12:08:12 by smiro             #+#    #+#              #
#    Updated: 2022/11/27 12:08:14 by smiro            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

MKFL	=	Makefile

SRC		=	philo_bonus.c utils_bonus.c init_bonus.c error_handler_bonus.c simulation_bonus.c

OBJS	=	$(SRC:.c=.o)

RM		=	rm -f
CFLAGS	=	-Wall -Wextra -Werror
LIBS	=	-lpthread

%.o: %.c $(MKFL)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	@$(MAKE) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)
	@echo DONE

clean:
	@$(RM) $(OBJS)
	
fclean:
	@$(MAKE) clean
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)

.PHONY: all clean fclean re bonus
