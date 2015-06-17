#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
 
#ifndef   NI_MAXHOST
#define   NI_MAXHOST 1025
#endif
 
int main(void)
{
    struct addrinfo *result;
    struct addrinfo *res;
    int error;
 
    /* resolve the domain name into a list of addresses */
    error = getaddrinfo("www.google.com", NULL, NULL, &result);
    if (error != 0)
    {   
        if (error == EAI_SYSTEM)
        {
            perror("getaddrinfo");
        }
        else
        {
            fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(error));
        }   
        exit(EXIT_FAILURE);
    }   
 
    /* loop over all returned results and do inverse lookup */
    for (res = result; res != NULL; res = res->ai_next)
    {   
        char hostname[NI_MAXHOST];
 
        struct sockaddr *ai_addr = res->ai_addr;
        struct sockaddr_in *addr_in = (struct sockaddr_in *)ai_addr;
        char ipAddress[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr_in->sin_addr), ipAddress, INET_ADDRSTRLEN);
        printf("%s\n", ipAddress);

        /*
        error = getnameinfo(res->ai_addr, res->ai_addrlen, hostname, 
            NI_MAXHOST, NULL, 0, 0); 
        if (error != 0)
        {
            fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(error));
            continue;
        }
        if (*hostname != '\0')
            printf("hostname: %s\n", hostname);
        */
    }   
 
    freeaddrinfo(result);
    return 0;
}
