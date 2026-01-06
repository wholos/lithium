all:
        @gcc -o lithium src/main.c -lconfig

clean:
        @rm lithium
