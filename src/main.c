#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>

/*** defines ***/

//dynamic String
typedef struct {
    int length;
    int maxLength;
    char* data;
} dString;

struct editorConfig {
    struct termios orig;
    int width;
    int height;
    int x;
    int y;
};

void die(const char* s);
void enableRawMode();
char readKey();
void editorRefreshScreen();
void processKeypress();
void getTerminalSizeIOCTL(int* width, int* heigth);
void dStringInit(dString* str);
void dStringFree(dString* str);
void dStringPush(dString* str, char c);
void dStringExtend(dString* str);
void dStringInsertAt(dString* str, char c, int pos);
void placeCursor();
void renderScreen();

struct editorConfig E;

dString** buffer;

/*** buffer ***/

void dStringInit(dString* str) {
    str->length = 0;
    str->maxLength = 64;
    char* new = (char*) malloc(str->maxLength * sizeof(char));
    if(new == NULL) die("malloc failed at dStringInit");
    str->data = new;
}

void dStringFree(dString* str) {
    str->length = 0;
    str->maxLength = 0;
    free(str->data);
    str->data = NULL;
}

void dStringPush(dString* str, char c) {
    if(str->length == str->maxLength) dStringExtend(str);
    str->data[str->length] = c;
    str->length++;
}

void dStringExtend(dString* str) {
    char* new = (char*) realloc(str->data, str->maxLength * 2 * sizeof(char));
    if(new == NULL) {
        dStringFree(str);
        die("realloc failed at dStringExtend");
    }
    str->data = new;
    str->maxLength *= 2;
}

//0-indexed
void dStringShrink(dString* str) {
    char* new = (char*) realloc(str->data, (str->maxLength / 2) * sizeof(char));
    if(new == NULL) {
        dStringFree(str);
        die("realloc failed at dStringShrink");
    }
    str->data = new;
    str->maxLength /= 2;
}

//0-indexed
void dStringInsertAt(dString* str, char c, int pos) {
    if(pos < 0 || pos >= str->length) {
        dStringFree(str);
        die("dStringInsertAt called for illegal index");
    }
    if(str->length == str->maxLength) dStringExtend(str);
    for(int i = str->length; i > pos; i--) {
        str->data[i] = str->data[i - 1];
    }
    str->data[pos] = c;
    str->length++;
}

void dStringDeleteAt(dString* str, int pos) {
    if(pos < 0 || pos >= str->length) {
        dStringFree(str);
        die("dStringDeleteAt called out of bounds");
    }
    for(int i = pos; i < str->length - 1; i++) {
        str->data[i] = str->data[i + 1];
    }
    str->length--;
    if(str->length < str->maxLength / 4) dStringShrink(str);
}


/*** terminal ***/

void die(const char* s) {
    editorRefreshScreen();
    perror(s);
    exit(1);
}

void disableRawMode() {
    //sets the attributes back to the original
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig) == -1) die("tcsetattr at disableRawMode()");
}

void enableRawMode() {
    //puts the attributes into struct original termios
    if(tcgetattr(STDIN_FILENO, &E.orig) == -1) die("tcgetattr at enableRawMode()");
    atexit(disableRawMode);

    struct termios raw = E.orig;

    //turns off a bunch of default flags as well as echo and canonical mode
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_iflag &= ~(IXON | ICRNL);
    raw.c_oflag &= ~(OPOST);

    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

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

void getTerminalSizeIOCTL(int* width, int* height) {
    struct winsize w = {0};
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 0 && w.ws_row > 0){
        *width = w.ws_col;
        *height = w.ws_row;
    }
    else die("ioctl at getTerminalSizeIOCTL");
}

/*** input ***/

void processKeypress() {
    char c = readKey();
    switch (c) {
    //ctrl q
    case 17:
        editorRefreshScreen();
        exit(0);
        break;
        
    //enter
    case 13:
        E.y++;
        //TO DO - insert new line here
        E.x = 0;
        break;

    //backspace
    case 127:
        // TO DO
        //need to implement pop first
        break;

    //arrow keys
    //up - \x1b[A    down - \x1b[B
    //right - \x1b[C left - \x1b[D:
    case '\x1b':
        char c1; if(read(STDIN_FILENO, &c1, 1) != 1) die("read in processKeypress escape sequences");
        char c2; if(read(STDIN_FILENO, &c2, 1) != 1) die("read in processKeypress escape sequences");

        if(c1 != '[') break;
        switch(c2){
        case 'A':
            write(STDOUT_FILENO, "\x1b[1A", 4);
            break;
        case 'B':
            write(STDOUT_FILENO, "\x1b[1B", 4);
            break;
        case 'C':
            write(STDOUT_FILENO, "\x1b[1C", 4);
            break;
        case 'D':
            write(STDOUT_FILENO, "\x1b[1D", 4);
            break;
        }
        //to be implemented with buffer
        break;

    default:
        //TO DO: make it work by inserting and not pushing to the end
        dStringPush(buffer[E.y], c);
        E.x++;
        break;
    }
}

/*** output ***/

void editorRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[H", 3);
    for(int i = 0; i < E.height; i++) {
        for(int j = 0; j < E.width; j++) {
            write(STDOUT_FILENO, " ", 1);
        }
    }
    write(STDOUT_FILENO, "\x1b[H", 3);
}


void placeCursor() {
    for(int i = 0; i < E.y; i++) write(STDOUT_FILENO, "\x1b[1B", 4);
    for(int i = 0; i < E.x; i++) write(STDOUT_FILENO, "\x1b[1C", 4);
}

void renderScreen() {
    write(STDOUT_FILENO, "\x1b[H", 3);
    for(int i = 0; i < E.height - 1; i++) {
        for(int j = 0; j < buffer[i]->length; j++) {
            write(STDOUT_FILENO, &((buffer[i]->data)[j]), 1);
        }
        write(STDOUT_FILENO, "\r\n", 2);
    }
    write(STDOUT_FILENO, "\x1b[H", 3);
    placeCursor();
}
/*** init ***/

void initEditor() {
    enableRawMode();
    getTerminalSizeIOCTL(&E.width, &E.height);
    E.x = 0;
    E.y = 0;
    for(int i = 0; i < E.height; i++) write(STDOUT_FILENO, "\r\n", 2);
    write(STDOUT_FILENO, "\x1b[H", 3);

    buffer = malloc(E.height * sizeof(dString*));
    for(int i = 0; i < E.height; i++) {
        dString* newLine = malloc(sizeof(dString));
        if(newLine == NULL) die("malloc failed at allocating newLines in initEditor");
        buffer[i] = newLine;
        dStringInit(buffer[i]);
    }
}

int main() {
    initEditor();
    
    while(1) {
        processKeypress();
        //TO DO function that turns off cursor visibility
        editorRefreshScreen();
        renderScreen();
        //TO DO function that turns on cursor visibility
    }

    editorRefreshScreen();
    return 0;
}