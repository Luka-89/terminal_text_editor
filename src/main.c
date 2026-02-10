#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct termios orig_termios;

void die(const char* s) {
    perror(s);
    exit(1);
}

void disableRawMode() {
    //sets the attributes back to the original
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) die("tcsetattr at disableRawMode()");
}

void enableRawMode() {
    //puts the attributes into struct original termios
    if(tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr at enableRawMode()");
    atexit(disableRawMode);

    struct termios raw = orig_termios;

    //turns off a bunch of default flags as well as echo and canonical mode
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_iflag &= ~(IXON);
    raw.c_oflag &= ~(OPOST);

    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 1;

    //sets the attributes from raw
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr at enableRawMode()");
}

int main() {
    enableRawMode();
    char c;
    const char* msg = "debug";

    while(1) {
        if(read(STDIN_FILENO, &c, 1) == -1) die("read");
        if(c == 'q') break;
        else if(c == '\n')write(STDOUT_FILENO, "\r\n", 2);
        else if(c == 127 || c == 8) write(STDOUT_FILENO, "\b \b", 3);
        else write(STDOUT_FILENO, &c, 1);
    }

    disableRawMode();

    return 0;
}