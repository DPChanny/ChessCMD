#include<Windows.h>
#include "ConsoleColor.h";

namespace ConsoleColor
{
    //색상 설정
    void set_color(int color, int bgcolor)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (color & 0xf));
    }

    //색상 초기화
    void reset_color()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((CC_ORIGINALBG & 0xf) << 4) | (CC_ORIGINAL & 0xf));
    }
}