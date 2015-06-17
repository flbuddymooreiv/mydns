# mydns
This program will change the IP address for a given host in a network program. This can be done by modifying `/etc/hosts` but if you do not have system administration privileges, you can use this method by utilizing the `LD_PRELOAD` environment variable for the loader.

It will replace the following library calls:
- gethostbyname2
- gethostbyaddr
- getaddrinfo

Build the sources
```Shell
gcc -o mydns.so -ldl -shared -fPIC mydns.c
```
```Shell
gcc -o test test.c
```

Demo:
```Shell
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

Of course the hostname and the IP address could be specified in a config file, or command line parameters, but for now, simply change the strings in mydns.c to fit your needs.
