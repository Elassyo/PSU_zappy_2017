##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME_CLT	=	zappy_ai
NAME_SRV	=	zappy_server

SRCS		=	cbuf.c						\
			cbuf_io.c					\
			tcp_server.c					\
			tcp_server_serve.c				\
			tcp_server_conn.c				\
			tcp_sock.c					\
			tcp_sock_client.c				\
			tcp_sock_server.c				\
			tcp_sock_io.c					\
			tcp_sock_info.c					\
			tcp_sock_rinfo.c
SRCS_CLT	=	client/client.c
SRCS_SRV	=	server/server.c					\
			server/conn.c					\
			server/cmd_movement.c				\
			server/dispatch.c
INCS		=	zappy.h						\
			zappy_server.h					\
			cbuf.h						\
			tcp.h
LIBS		=
OBJS		=	$(SRCS:.c=.o)
OBJS_CLT	=	$(SRCS_CLT:.c=.o)
OBJS_SRV	=	$(SRCS_SRV:.c=.o)

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include
SUBDIRS		=	client server server/cmds

CC		=	gcc
CFLAGS		=	-c -W -Wall -Wextra -I$(INCDIR)
LDFLAGS		=	$(addprefix -L,$(LIBS))

MKDIR		=	mkdir
RM		=	rm -rf

all: $(NAME_CLT) $(NAME_SRV)

$(NAME_CLT): $(addprefix $(OBJDIR)/,$(OBJS) $(OBJS_CLT))
	$(CC) $^ $(LDFLAGS) -o $@

$(NAME_SRV): $(addprefix $(OBJDIR)/,$(OBJS) $(OBJS_SRV))
	$(CC) $^ $(LDFLAGS) -o $@

$(addprefix $(OBJDIR)/,$(OBJS) $(OBJS_CLT) $(OBJS_SRV)): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(addprefix $(INCDIR)/,$(INCS)) | $(OBJDIR) $(addprefix $(OBJDIR)/,$(SUBDIRS))
	$(CC) $< $(CFLAGS) -o $@

$(OBJDIR) $(addprefix $(OBJDIR)/,$(SUBDIRS)): %:
	$(MKDIR) $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME_CLT) $(NAME_SRV)

re: fclean all

.PHONY: all clean fclean re
