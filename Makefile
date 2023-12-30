CFLAGS=-Wall -Werror -Wextra

CC=cc

SERVER_SRCS=server.c server_utils.c 
CLIENT_SRCS=client.c client_utils.c 
SERVER_OBJS=$(SERVER_SRCS:.c=.o)
CLIENT_OBJS=$(CLIENT_SRCS:.c=.o)

SERVER_NAME=server
CLIENT_NAME=client

# target
all: $(SERVER_NAME) $(CLIENT_NAME)


$(SERVER_NAME):$(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER_NAME) $(SERVER_OBJS)

$(CLIENT_NAME):$(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT_NAME) $(CLIENT_OBJS)

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean:
	rm -f $(CLIENT_NAME) $(SERVER_NAME)

re:fclean all

.PHONY: all clean fclean all