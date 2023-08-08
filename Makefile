NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror #-I/Users/bsouhar/.brew/opt/readline/include
#LDFLAGS = -L/Users/bsouhar/.brew/opt/readline/lib
LDLIBS = -lreadline

CFILES =  main.c utils.c split.c utils2.c tokenizer.c     \
		  handle_quotes.c ft_add_list.c syntax_errors.c   \
		  parser.c open_files.c execution.c execution2.c  \
		  builtins.c echo.c cd.c expand.c utils3.c free.c \
		  signal.c utils4.c utils5.c utils6.c utils7.c \
		  utils8.c utils9.c utils10.c ft_init.c parser2.c \
		  split2.c utils11.c utils12.c utils13.c


OBJDIR = obj


OBJS = $(addprefix $(OBJDIR)/,$(CFILES:.c=.o))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)


clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
