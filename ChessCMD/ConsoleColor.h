#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

#define CC_BLACK 0
#define CC_DARKBLUE 1
#define CC_DARKGREEN 2
#define CC_DARKCYAN 3
#define CC_DARKRED 4
#define CC_DARKMAGENTA 5
#define CC_DARKYELLOW 6
#define CC_GRAY 7
#define CC_DARKGRAY 8 
#define CC_BLUE 9
#define CC_GREEN 10
#define CC_CYAN 11
#define CC_RED 12
#define CC_MAGENTA 13
#define CC_YELLOW 14
#define CC_WHITE 15
#define CC_ORIGINAL CC_WHITE
#define CC_ORIGINALFONT 7
#define CC_ORIGINALBG CC_BLACK

namespace ConsoleColor
{

    //색상 설정
    void set_color(int color, int bgcolor);

    //색상 초기화
    void reset_color();
}

#endif
