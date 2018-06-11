##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME_AI		=	zappy_ai
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
SRCS_AI		=	ai/main.cpp
SRCS_SRV	=	server/main.c					\
			server/conn.c					\
			server/cmd_movement.c				\
			server/dispatch.c
INCS		=	zappy.h						\
			zappy_server.h					\
			cbuf.h						\
			tcp.h
LIBS		=
OBJS		=	$(SRCS:.c=.o)
OBJS_AI		=	$(SRCS_AI:.cpp=.o)
OBJS_SRV	=	$(SRCS_SRV:.c=.o)

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include
SUBDIRS		=	ai server

CC		=	gcc
CFLAGS		=	-c -W -Wall -Wextra -I$(INCDIR)

CXX		=	g++
CXXFLAGS	=	-c -W -Wall -Wextra -std=c++17

LDFLAGS		=	$(addprefix -L,$(LIBS))

MKDIR		=	mkdir
RM		=	rm -rf

all: $(NAME_AI) $(NAME_SRV)

$(NAME_AI): $(addprefix $(OBJDIR)/,$(OBJS) $(OBJS_AI))
	$(CXX) $^ $(LDFLAGS) -o $@

$(NAME_SRV): $(addprefix $(OBJDIR)/,$(OBJS) $(OBJS_SRV))
	$(CC) $^ $(LDFLAGS) -o $@

$(addprefix $(OBJDIR)/,$(OBJS) $(OBJS_SRV)): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(addprefix $(INCDIR)/,$(INCS)) | $(OBJDIR) $(addprefix $(OBJDIR)/,$(SUBDIRS))
	$(CC) $< $(CFLAGS) -o $@

$(addprefix $(OBJDIR)/,$(OBJS_AI)): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(addprefix $(INCDIR)/,$(INCS)) | $(OBJDIR) $(addprefix $(OBJDIR)/,$(SUBDIRS))
	$(CXX) $< $(CXXFLAGS) -o $@

$(OBJDIR) $(addprefix $(OBJDIR)/,$(SUBDIRS)): %:
	$(MKDIR) $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME_CLT) $(NAME_SRV)

re: fclean all

.PHONY: all clean fclean re
