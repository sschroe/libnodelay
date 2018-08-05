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

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string.h>
#include <errno.h>

int main()
{
    const int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int optval;
    socklen_t len = sizeof(optval);

    if (sockfd < 0)
    {
        fprintf(stderr, "socket() failed: %s\n", strerror(errno));
        return 1;
    }

    if (getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, &len) != 0) {
        fprintf(stderr, "getsockopt() failed: %s\n", strerror(errno));

        close(sockfd);

        return 1;
    }

    close(sockfd);

    if (optval) {
        fprintf(stdout, "TCP_NODELAY is set.\n");
    } else {
        fprintf(stderr, "TCP_NODELAY is NOT set.\n");

        return 1;
    }

    return 0;
}
