/*
 * libnodelay - A small wrapper library to force TCP_NODELAY on all new sockets.
 * Copyright (C) 2018 Steffen Schröter
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define _GNU_SOURCE

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <dlfcn.h>

static int is_tcp_socket(const int type, const int protocol)
{
    return type == SOCK_STREAM && (protocol == IPPROTO_TCP || protocol == 0);
}

int socket(int domain, int type, int protocol)
{
    int (* const next)(int, int, int) = dlsym(RTLD_NEXT, "socket");
    const int sockfd = next(domain, type, protocol);

    /* Force TCP_NODELAY on all TCP sockets */
    if (sockfd >= 0 && is_tcp_socket(type, protocol)) {
        int optval = 1;

        setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
    }

    return sockfd;
}

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
    int (* const next)(int, int, int, const void *, socklen_t) = dlsym(RTLD_NEXT, "setsockopt");

    /* Prevent the application from removing TCP_NODELAY */
    if (optname == TCP_NODELAY && optlen == sizeof(int)) {
        int * const value = (int *)optval;

        if (*value == 0) {
            *value = 1;
        }
    }

    return next(sockfd, level, optname, optval, optlen);
}
