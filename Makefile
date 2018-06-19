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
			list/create.c					\
			list/destroy.c					\
			list/find.c					\
			list/get.c					\
			list/insert.c					\
			list/pop.c					\
			list/push.c					\
			list/remove.c					\
			tcp_client.c					\
			tcp_server.c					\
			tcp_server_serve.c				\
			tcp_server_conn.c				\
			tcp_conn_io.c					\
			tcp_conn_io2.c					\
			tcp_sock.c					\
			tcp_sock_client.c				\
			tcp_sock_server.c				\
			tcp_sock_io.c					\
			tcp_sock_info.c					\
			tcp_sock_rinfo.c

SRCS_AI		=	ai/Exception/Exception.cpp			\
			ai/CBuffer.cpp					\
			ai/Drone.cpp					\
			ai/Inventory.cpp				\
			ai/RequestConstructor.cpp			\
			ai/RequestHandler.cpp				\
			ai/Tile.cpp					\
			ai/Vertex.cpp					\
			ai/Vision.cpp					\
			ai/main.cpp

SRCS_SRV	=	server/main.c					\
			server/main_args.c				\
			server/conn.c					\
			server/dispatch.c				\
			server/graphic.c				\
			server/map.c					\
			server/player.c					\
			server/player_items.c				\
			server/player_move.c				\
			server/teams.c					\
			server/cmd_ai/cmd_move.c			\
			server/cmd_ai/cmd_look.c			\
			server/cmd_ai/cmd_inventory.c			\
			server/cmd_ai/cmd_broadcast.c			\
			server/cmd_ai/cmd_connect.c			\
			server/cmd_ai/cmd_fork.c			\
			server/cmd_ai/cmd_eject.c			\
			server/cmd_ai/cmd_take.c			\
			server/cmd_ai/cmd_set.c				\
			server/cmd_ai/cmd_incantation.c			\
			server/cmd_graphic/cmd_map.c

INCS		=	zappy.h						\
			zappy_server.h					\
			cbuf.h						\
			list.h						\
			tcp.h

INCS_AI		=	ai/Exception/Exception.hpp		\
			ai/CBuffer.hpp				\
			ai/Drone.hpp				\
			ai/Inventory.hpp			\
			ai/Memory.hpp				\
			ai/RequestConstructor.hpp		\
			ai/RequestHandler.hpp			\
			ai/RequestParser.hpp			\
			ai/Tile.hpp				\
			ai/Vertex.hpp				\
			ai/Vision.hpp

LIBS		=
OBJS		=	$(SRCS:.c=.o)
OBJS_AI		=	$(SRCS_AI:.cpp=.o)
OBJS_SRV	=	$(SRCS_SRV:.c=.o)

SRCDIR		=	src
OBJDIR		=	obj
INCDIR		=	include
SUBDIRS		=	ai server ai/Exception list server/cmd_ai server/cmd_graphic

CC		=	gcc
CFLAGS		=	-c -g -W -Wall -Wextra -I$(INCDIR)

CXX		=	g++
CXXFLAGS	=	-c -W -Wall -Wextra -std=c++17 -I$(INCDIR)

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

$(addprefix $(OBJDIR)/,$(OBJS_AI)): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(addprefix $(INCDIR)/,$(INCS)) $(addprefix $(SRCDIR)/,$(INCS_AI)) | $(OBJDIR) $(addprefix $(OBJDIR)/,$(SUBDIRS))
	$(CXX) $< $(CXXFLAGS) -o $@

$(OBJDIR) $(addprefix $(OBJDIR)/,$(SUBDIRS)): %:
	$(MKDIR) $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME_AI) $(NAME_SRV)

re: fclean all

.PHONY: all clean fclean re
