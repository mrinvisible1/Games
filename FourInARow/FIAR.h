#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct{
	char character;
}Field;


#define MAX_X 10
#define MAX_Y 10

#define MSG1 1
#define MSG2 2
#define MSG3 3
#define MSG4 4

static WINDOW *create_newwin(int h, int w, int start_y, int start_x);

void print_notification(int y, char *msg);
void print_on_window(WINDOW *win, int y,int x, char *msg);

//Basic game Functions
void Setup();
void Gameplay();
void Input(char c);
void Draw();
void Logic(char c);
void End();

//Checking functions
int check(int incrementi, int incrementj, int limiti, int limitj, char c, int start);
void checkVertical(char c);
void CheckHorizontal(char c);
void checkSlantedRight(char c);
void checkSlantedLeft(char c);