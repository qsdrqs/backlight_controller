#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_light = 7500;
char up[5] = { 'A', 'l' };   //鼠标滚轮上中有A字符
char down[5] = { 'B', 'h' }; //鼠标滚轮下中有B字符
char PATH[50] = "/sys/class/backlight/intel_backlight/brightness";

bool char_in_str(char* str, char c)
{
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}
void print_light(int light)
{
    int x, y;
    getmaxyx(stdscr, y, x);
    int a = y / 2.5;
    int b = x / 4;
    move(a, b);
    addstr(" ------backlightctl-------------(use q to quit)------------------------------");
    move(a + 1, b);
    addch('|');
    for (int i = 1; i <= light / 100; ++i) {
        addch('#');
    }
    for (int i = light / 100; i <= 75; ++i) {
        addch(' ');
    }
    addstr("|");
    move(a + 2, b);
    addstr(" ----------------------------------------------------------------------------");
    move(a + 2, b + 30);
    printw("back_light:%d", light);
    wrefresh(stdscr);
}

int main(int argc, char* argv[])
{
    FILE* bright_file = fopen(PATH, "r+");
    char buffer[20];
    fread(&buffer, 1, 20, bright_file);
    int light = atoi(buffer);

    char operater;
    initscr(); //清屏
    noecho();  //不显示输入
    while (true) {
        print_light(light);
        operater = getch();
        if (char_in_str(down, operater)) {
            light -= 100;
            fseek(bright_file, 0, 0);
            fprintf(bright_file, "%d", light);
        } else if (char_in_str(up, operater)) {
            light += 100;
            fseek(bright_file, 0, 0);
            fprintf(bright_file, "%d", light);
        } else if (operater == 'q') {
            endwin();
            return 0;
        }
    }
}
