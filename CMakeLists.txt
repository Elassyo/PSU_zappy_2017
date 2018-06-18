cmake_minimum_required(VERSION 3.1)
project(PSU_zappy_2017 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "-W -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

include_directories(include)

set(SRC_CBUF
		include/cbuf.h
		src/cbuf.c
		src/cbuf_io.c)

set(SRC_LIST
		include/list.h
		src/list/insert.c
		src/list/create.c
		src/list/destroy.c
		src/list/get.c
		src/list/pop.c
		src/list/push.c
		src/list/remove.c)

set(SRC_TCP
		include/tcp.h
		src/tcp_client.c
		src/tcp_client_conn.c
		src/tcp_server.c
		src/tcp_server_conn.c
		src/tcp_server_serve.c
		src/tcp_conn.c
		src/tcp_sock.c
		src/tcp_sock_client.c
		src/tcp_sock_server.c
		src/tcp_sock_io.c
		src/tcp_sock_info.c
		src/tcp_sock_rinfo.c)

set(SRC_COMMON
        include/zappy.h
		${SRC_CBUF}
		${SRC_TCP})

add_executable(zappy_ai
		${SRC_COMMON}
		src/ai/main.cpp
		src/ai/CBuffer.cpp
		src/ai/CBuffer.hpp
		src/ai/Exception/Exception.cpp
		src/ai/Exception/Exception.hpp
		src/ai/Drone.cpp
		src/ai/Drone.hpp
		src/ai/Vertex.cpp
		src/ai/Vertex.hpp
		src/ai/Inventory.cpp
		src/ai/Inventory.hpp
		src/ai/RequestHandler.cpp
		src/ai/RequestHandler.hpp
		src/ai/RequestConstructor.cpp
		src/ai/RequestConstructor.hpp
		)

add_executable(zappy_server
        ${SRC_COMMON}
		${SRC_LIST}
        include/zappy_server.h
        src/server/main.c
        src/server/main_args.c
		src/server/conn.c
		src/server/dispatch.c
		src/server/cmd_move.c
		src/server/map.c
		src/server/player.c
		src/server/player_move.c
		src/server/player_items.c
		)
