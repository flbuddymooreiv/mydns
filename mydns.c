#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
 
struct hostent {
   char  *h_name;            /* official name of host */
   char **h_aliases;         /* alias list */
   int    h_addrtype;        /* host address type */
   int    h_length;          /* length of address */
   char **h_addr_list;       /* list of addresses */
};

typedef struct hostent *(*orig_ghbn2_type)(const char *name, int af);

struct hostent *gethostbyname2(const char *name, int af)
{
    printf("gethostbyname2\n");
    orig_ghbn2_type orig_ghbn2;
    orig_ghbn2 = (orig_ghbn2_type)dlsym(RTLD_NEXT,"gethostbyname2");
    struct hostent *ent = orig_ghbn2(name, af);
    ent->h_addr_list[0] = "8.8.8.8";
    ent->h_addr_list[1] = "8.8.8.8";
    printf("%s", ent->h_length);
    return ent;
}

typedef int socklen_t;
typedef struct hostent *(*orig_ghba_type)(const char *addr, 
    socklen_t len, int type);

struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type)
{
    printf("gethostbyaddr\n");
    orig_ghba_type orig_ghba;
    orig_ghba = (orig_ghba_type)dlsym(RTLD_NEXT,"gethostbyaddr");
    struct hostent *ent = orig_ghba(addr, len, type);
    ent->h_addr_list[0] = "8.8.8.8";
    ent->h_addr_list[1] = "8.8.8.8";
    printf("%s", ent->h_length);
    return ent;
}

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

struct addrinfo {
   int              ai_flags;
   int              ai_family;
   int              ai_socktype;
   int              ai_protocol;
   socklen_t        ai_addrlen;
   struct sockaddr *ai_addr;
   char            *ai_canonname;
   struct addrinfo *ai_next;
};

typedef int (*orig_gai_type)(const char *node, const char *service,
               const struct addrinfo *hints,
               struct addrinfo **res);

int getaddrinfo(const char *node, const char *service,
               const struct addrinfo *hints,
               struct addrinfo **res)
{
    printf("getaddrinfo\n");
    orig_gai_type orig_gai;
    orig_gai = (orig_gai_type)dlsym(RTLD_NEXT,"getaddrinfo");
    int ret = orig_gai(node, service, hints, res);
    strcpy(res[0]->ai_addr->sa_data, "8.8.8.8");
    return ret;
}

