# mydns
This program will change the IP address for a given host in a network program by using the `LD_PRELOAD` environment for the loader.

It will replace the following library calls:
- gethostbyname2
- gethostbyaddr
- getaddrinfo

Build the sources
```
gcc -o mydns.so -ldl -shared -fPIC mydns.c
```
```
gcc -o test test.c
```

Demo:
```
user@host:~/dev/mydns$ ./test
74.125.198.147
74.125.198.99
74.125.198.103
74.125.198.104
74.125.198.105
74.125.198.106
0.0.0.0

user@host:~/dev/mydns$ LD_PRELOAD=/path/to/compiled/mydns.so ./test
123.123.123.123
```
