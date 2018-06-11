cmake_minimum_required(VERSION 3.10)
project(PSU_zappy_2017 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "-W -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra")

include_directories(include)

set(SRC_COMMON
        include/zappy.h
        include/cbuf.h
        src/cbuf.c
        src/cbuf_io.c
        include/tcp.h
        src/tcp_server.c
        src/tcp_server_conn.c
        src/tcp_server_serve.c
        src/tcp_sock.c
        src/tcp_sock_client.c
        src/tcp_sock_server.c
        src/tcp_sock_io.c
        src/tcp_sock_info.c
        src/tcp_sock_rinfo.c)

add_executable(zappy_ai
        ${SRC_COMMON}
        src/ai/main.cpp)

add_executable(zappy_server
        ${SRC_COMMON}
        include/zappy_server.h
        src/server/main.c
        src/server/conn.c
        src/server/dispatch.c
        src/server/cmd_movement.c)
