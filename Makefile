NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = src/check_sim_status.c \ 
	  src/main.c \    
	  src/print.c \           
	  src/smart_sleep.c \
	  src/codexion.h \      
	  src/monitor.c \ 
	  src/priority_queue.c \
	  src/utils.c \
	  src/init_struct.c \
	  src/parse.c \ 
	  src/simulation.c 

OBJS = $(SRC:.c=.o) # take all .c files in src and change their extension to .o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ # i dont understand how this works

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
