CFLAGS = -Wall -Werror -Wextra
CC = cc

SERVER_SRCS = server.c server_utils.c 
CLIENT_SRCS = client.c client_utils.c 
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

SERVER_NAME = server
CLIENT_NAME = client

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

LDLIBS = -lm
UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
    LDLIBS += -lbsd
endif

# target
all: $(LIBFT) $(SERVER_NAME) $(CLIENT_NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) all

# Static pattern rule for compilation
$(SERVER_OBJS) $(CLIENT_OBJS): %.o: %.c
	 $(CC) $(CFLAGS) -c $< -o $@

$(SERVER_NAME): LDLIBS += $(LIBFT)
$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) $(LDLIBS)

$(CLIENT_NAME): LDLIBS += $(LIBFT) # using this is here not necessary because I use -lft
$(CLIENT_NAME): $(CLIENT_OBJS)
	# version $(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -L$(LIBFTDIR) -lft
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) $(LDLIBS)

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	$(MAKE) -C $(LIBFTDIR) clean


fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
	$(MAKE) -C $(LIBFTDIR) fclean


re: fclean all

.PHONY: all clean fclean re
