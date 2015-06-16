gcc -shared -fPIC mydns.c -o mydns.so && \
LD_PRELOAD=/home/buddy/dev/mydns/mydns.so nslookup google.com
