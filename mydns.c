#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
 
typedef struct hostent *(*orig_ghbn2_type)(const char *name, int af);

struct hostent *gethostbyname2(const char *name, int af)
{
    //printf("gethostbyname2\n");
    orig_ghbn2_type orig_ghbn2;
    orig_ghbn2 = (orig_ghbn2_type)dlsym(RTLD_NEXT, "gethostbyname2");
    struct hostent *ent = orig_ghbn2(name, af);
    ent->h_addr_list[0] = "123.123.123.123";
    ent->h_addr_list[1] = "123.123.123.123";
    printf("%s", ent->h_length);
    return ent;
}

typedef struct hostent *(*orig_ghba_type)(const char *addr, 
    socklen_t len, int type);

struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type)
{
    //printf("gethostbyaddr\n");
    orig_ghba_type orig_ghba;
    orig_ghba = (orig_ghba_type)dlsym(RTLD_NEXT, "gethostbyaddr");
    struct hostent *ent = orig_ghba(addr, len, type);
    ent->h_addr_list[0] = "123.123.123.123";
    ent->h_addr_list[1] = "123.123.123.123";
    printf("%s", ent->h_length);
    return ent;
}

typedef int (*orig_gai_type)(const char *node, const char *service,
               const struct addrinfo *hints,
               struct addrinfo **res);

int getaddrinfo(const char *node, const char *service,
               const struct addrinfo *hints,
               struct addrinfo **res)
{
    //printf("getaddrinfo\n");
    res[0] = malloc(sizeof(struct addrinfo));
    res[0]->ai_next = NULL;
    res[0]->ai_addrlen = 16;
    res[0]->ai_addr = malloc(sizeof(struct sockaddr));
    inet_aton("123.123.123.123", 
        &((struct sockaddr_in *)res[0]->ai_addr)->sin_addr);
    return 0;
}
