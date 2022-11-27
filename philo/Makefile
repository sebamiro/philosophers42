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

NAME	=	philo

MKFL	=	Makefile

SRC		=	philosophers.c utils.c

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

clean:
	@$(RM) $(OBJS)
	
fclean:
	@$(MAKE) clean
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)

.PHONY: all clean fclean re bonus
