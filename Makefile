CFLAGS = -Wall -Werror -Wextra
CC = cc

MINI_LIBFT_SRCS = mini_libft/mini_libft.c

SERVER_SRCS = $(addprefix server_src/, server.c server_utils.c)
CLIENT_SRCS = $(addprefix client_src/,client.c client_utils.c)

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

MINI_LIBFT_OBJ = $(MINI_LIBFT_SRCS:.c=.o)

SERVER_NAME = build/server
CLIENT_NAME = build/client

UNAME = $(shell uname -s)
ARCH := $(shell arch)

ifeq ($(UNAME), Darwin)
	 ifeq ($(ARCH), arm64)
        CC += -arch arm64
    else
        CC += -arch x86_64
    endif
endif

# targets
all: build $(SERVER_NAME) $(CLIENT_NAME)

build:
	@mkdir -p build

# Static pattern rule for compilation
$(SERVER_OBJS) $(CLIENT_OBJS) $(MINI_LIBFT_OBJ): %.o: %.c
	 $(CC) $(CFLAGS) -c $< -o $@

$(SERVER_NAME): $(SERVER_OBJS) $(MINI_LIBFT_OBJ)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) $(MINI_LIBFT_OBJ)

$(CLIENT_NAME): $(CLIENT_OBJS) $(MINI_LIBFT_OBJ)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) $(MINI_LIBFT_OBJ)

%.o: %.c
	CC $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(MINI_LIBFT_OBJ)
	
fclean: clean
	rm -rf build $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

.PHONY: all clean fclean re
