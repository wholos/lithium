all:
        @gcc -o lithium src/main.c -lconfig

build: all

clean:
        @rm lithium

install:
        @cp lithium.conf /etc/ && cp lithium /bin/
