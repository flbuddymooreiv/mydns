rm test mydns.so
gcc -ldl -shared -fPIC mydns.c -o mydns.so && \
gcc -g -o test test.c && \
echo "WITHOUT PRELOAD" && \
./test && \
echo && \
echo "WITH PRELOAD" && \
LD_PRELOAD=/home/buddy/dev/mydns/mydns.so ./test
