NAME = minishell
SRC = 
LIBFT = libft/libft.a
HEADERFILES = -I minishell.h libft/libft.h
OBJFILES = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g3
CC = cc

$(NAME): $(OBJFILES)
#	make -c libft
	$(CC) $(CFLAGS) $(OBJFILES) ${LIBFT} -o $(NAME)

all: $(NAME)

%.o: %.c $(HEADERFILES)
	$(CC) -c $(CFLAGS) -o $@ $< 

clean:
	rm -f $(OBJFILES)

fclean:
	rm -f $(NAME) $(OBJFILES)

re: fclean all
	
.PHONY: clean fclean all re