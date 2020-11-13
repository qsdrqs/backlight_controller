#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH "/sys/class/backlight/intel_backlight"

int max_light;
char up[5] = { 'A', 'k' };   //鼠标滚轮上中有A字符
char down[5] = { 'B', 'j' }; //鼠标滚轮下中有B字符

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
    for (int i = 1; i <= light / (max_light / 75); ++i) {
        addch('#');
    }
    for (int i = light / (max_light / 75); i <= max_light / (max_light / 75); ++i) {
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
    char bright_path[60] = PATH;
    FILE* bright_file = fopen(strcat(bright_path, "/brightness"), "r+");
    char buffer[20];
    fread(&buffer, 1, 20, bright_file);
    int light = atoi(buffer);

    char max_path[60] = PATH;
    FILE* max_file = fopen(strcat(max_path, "/max_brightness"), "r");
    char buffer_max[20];
    fread(&buffer_max, 1, 20, max_file);
    max_light = atoi(buffer_max);

    char operater;
    initscr(); //清屏
    noecho();  //不显示输入
    while (true) {
        print_light(light);
        operater = getch();
        if (char_in_str(down, operater)) {
            if(light-(max_light/75)<0){ //亮度不能小于0
                continue;
            }
            light -= (max_light / 75);
            fseek(bright_file, 0, 0);
            fprintf(bright_file, "%d", light);
        } else if (char_in_str(up, operater)) {
            if(light+(max_light/75)>max_light){ //亮度能大于最大值
                continue;
            }
            light += (max_light / 75);
            fseek(bright_file, 0, 0);
            fprintf(bright_file, "%d", light);
        } else if (operater == 'q') {
            endwin();
            return 0;
        }
    }
}
