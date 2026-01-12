all:
        @gcc -o lithium src/main.c -lconfig

clean:
        @rm lithium

build: all

install:
        @echo 'Depend root!'
        @cp lithium.conf /etc/ && cp lithium /bin/
