NAME	=	fdf1

SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

CFLAGS	+= -lsfml-graphics -lsfml-window -lsfml-system

CC	=	g++ -o

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
