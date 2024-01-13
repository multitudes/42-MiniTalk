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
LIBFT_INCLUDES = -Ilibft

LDLIBS = -lm
UNAME = $(shell uname -s)
ARCH := $(shell arch)
ifeq ($(UNAME), Linux)
    LDLIBS += -lbsd
endif
ifeq ($(UNAME), Darwin)
	 ifeq ($(ARCH), arm64)
        CC += -arch arm64
    else
        CC += -arch x86_64
    endif
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

$(CLIENT_NAME): LDLIBS += $(LIBFT)
$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) $(LDLIBS)

%.o: %.c
	gcc $(CCFLAGS) $(LIBFT_INCLUDES) -c $< -o $@

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	$(MAKE) -C $(LIBFTDIR) clean
	
fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
