#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*** defines ***/
void die(const char* s);
void enableRawMode();
char readKey();
void editorRefreshScreen();
void processKeypress();

struct termios orig_termios;

/*** terminal ***/

void die(const char* s) {
    perror(s);
    exit(1);
    editorRefreshScreen();
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
    raw.c_iflag &= ~(IXON | ICRNL);
    raw.c_oflag &= ~(OPOST);

    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 1;

    //sets the attributes from raw
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr at enableRawMode()");
}

char readKey() {
    int nread;
    char c;
    while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if(nread == -1) die("read at readKey()");
    }
    return c;
}

/*** output ***/
void editorRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
}

/*** input ***/

void processKeypress() {
    char c = readKey();
    switch (c) {
    //ctrl q
    case 17:
        exit(0);
        break;

    //enter
    case 13:
        write(STDOUT_FILENO, "\r\n", 2);
        break;

    //backspace
    case 127:
        write(STDOUT_FILENO, "\b \b", 3);
        break;

    default:
        write(STDOUT_FILENO, &c, 1);
        break;
    }
    
}


/*** init ***/

int main() {
    enableRawMode();

    while(1) {
        processKeypress();
    }

    editorRefreshScreen();
    disableRawMode();

    return 0;
}