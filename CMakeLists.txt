cmake_minimum_required(VERSION 3.10)
project(PSU_zappy_2017 C)

set(CMAKE_C_STANDARD 11)

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

add_executable(zappy_client
        ${SRC_COMMON}
        src/client/client.c testing.c)

add_executable(zappy_server
        ${SRC_COMMON}
        include/zappy_server.h
        src/server/server.c
        src/server/conn.c
        src/server/dispatch.c)
