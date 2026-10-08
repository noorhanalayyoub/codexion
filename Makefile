NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = src/check_sim_status.c \
	  src/main.c \
	  src/print.c \
	  src/smart_sleep.c \
	  src/monitor.c \
	  src/utils.c \
	  src/init_struct.c \
	  src/parse.c \
	  src/simulation.c \
	  src/pq.c \
	  src/pq_helpers.c \
	  src/server.c

OBJS = $(SRC:.c=.o) # take all .c files in src and change their extension to .o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	# this is called a linking rule
	# link allobject files together using the c compiler
	# after linking, create an executable called codexion
	# -o means create an output executable and call it name
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	# for every object file .o it depends on source file .c with the same name
	# compile source file using c compiler and flags
	# create object file as output
	# this line will execute as many times as there are .o: .c pairs

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
