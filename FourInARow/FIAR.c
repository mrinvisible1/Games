#include "FIAR.h"

//global variables
static Field field[10][10];
static bool game_over;
static const char player1 = '+';
static const char player2 = '*'; 

// last input position
static int last_pos_i, last_pos_j;

//terminal height/width
static int max_y, max_x; 

//used for centering window
static int begin_x, begin_y;


//NCURSES windows
static WINDOW *notification_win = NULL;
static WINDOW *game = NULL;

void Setup(){

	initscr();
	start_color();
	curs_set(FALSE);
	echo();
	cbreak();
	//raw();
	getmaxyx(stdscr, max_y, max_x);
	begin_y = max_y/2-10;
	begin_x = max_x/2-20;
	int i=0, j=0;
	for(i=0;i<MAX_X;i++){
		for(j=0;j<MAX_X;j++)
			field[i][j].character = '-';
	}
	notification_win = create_newwin(10, max_x-5, begin_y+22, 0);
	refresh();
	wrefresh(notification_win);
	game = create_newwin(30, 90, 0, 0);
	refresh();
	wrefresh(game);
	wrefresh(notification_win);
	
	game_over = false;
}
void Gameplay(){
	/*
		PLAYER ONE + 
		PLAYER TWO *
	*/
	Draw();
	while(!game_over){
		wclear(notification_win);
		print_notification(MSG2, "Player one: ");
		Input(player1);
		Draw();
	
		Logic(player1);
	
		if(true == game_over){
			wclear(notification_win);
			print_notification(MSG2, "Player one has won!");
			return;
		}
		wclear(notification_win);
		print_notification(MSG2, "Player two: ");
		Input(player2);
		Draw();
		Logic(player2);
		if(true == game_over){
			wclear(notification_win);
			print_notification(MSG2, "Player two has won!");
			return;
		}
	
	}
}
void Input(char c){

	int j = -1;
	int i;
	int pom;
	int y, x;
	bool correct = true;
	do{
		do{
			print_notification(MSG1, "Enter position for your character: ");
			pom = mvwscanw(notification_win,MSG3,1,"%d", &j);
			getyx(notification_win, y, x);
		}while(-1 == pom || 0 == pom); 
		
		if(j>9 || j<0){
			print_notification(MSG4,"Your number must be >=0 and <=9! Press ENTER to enter again:");
			getchar();
			wmove(notification_win, y-1, 0);
			wclrtobot(notification_win);
			correct = false;
		}
		else{
				i = 9;
				while(i >= 0 && (field[i][j].character == '*' || field[i][j].character == '+')){
					i--;
				}
				if(-1 == i){
					print_notification(MSG3,"There are no more available places in that row! Press ENTER to enter again: ");
					getchar();
					wmove(notification_win, y-1, 0);
					wclrtobot(notification_win);
					correct = false;
				}
				else{
					correct = true;
				}
			}
	}while(!correct);


	field[i][j].character = c;
	last_pos_i = i;
	last_pos_j = j;	
}
void Draw(){
	
	int x, y, i, j;
	int game_x, game_y;
	getmaxyx(game, game_y, game_x);
	wrefresh(notification_win);
	x = game_x/2-40;
	y = game_y/2-10;
	for(i = 0; i<MAX_X + 2;i++){
		for(j = 0; j< MAX_Y;j++, x+= 4){
			if(i == 0  || i == MAX_X + 1){
				mvwprintw(game, y, x, "%d", j);
				wrefresh(game);
				refresh();
			}
			
			else{
				mvwprintw(game, y, x, "%c", field[i-1][j].character);
				wrefresh(game);
			}
		}
		y+=2;
		x=game_x/2-40;
	}

	
}


void Logic(char c){

	checkVertical(c);
	if(true == game_over){
		return;
	}
	CheckHorizontal(c);
	if(true == game_over){
		return;
	}

	checkSlantedRight(c);
	if(true == game_over){
		return;
	}

	checkSlantedLeft(c);
	if(true == game_over){
		return;
	}


}

void checkVertical(char c){

	check(1, 0, 10, 11, c, 1);
	if(game_over)
		return;

}
void CheckHorizontal(char c){

	int numOfHits = 1;
	/****************	
	 	 right
	****************/
	numOfHits = check(0, 1, 11, 10, c, numOfHits);
	if(game_over)
		return;

	/****************	
	 	 left
	****************/
	numOfHits = check(0, -1, 11, 10, c, numOfHits);
	if(game_over)
		return;

}

void checkSlantedRight(char c){
	int numOfHits = 1;

	/****************	
	      up
	****************/
	numOfHits = check(-1, 1, 0, 10, c, numOfHits);
	if(game_over)
		return;
	/****************	
	      down
	****************/
	numOfHits = check(1, -1, 10, 0, c, numOfHits);
	if(game_over)
		return;
}
void checkSlantedLeft(char c){
	int numOfHits = 1;
	/****************	
	  		up
	****************/
	numOfHits = check(-1, -1, 0, 0, c, numOfHits);
	if(game_over)
		return;
	/****************	
		  down
	****************/
	numOfHits = check(1, 1, 10, 10, c, numOfHits);
	if(game_over)
		return;

}

int check(int incrementi, int incrementj, int limiti, int limitj, char c, int start){
	int i, j, numOfHits;
	i = last_pos_i + incrementi;
	j = last_pos_j + incrementj;
	numOfHits = start;
	
	while(i != limiti && j != limitj && field[i][j].character == c){
		numOfHits++;
		i+=incrementi;
		j+=incrementj;
		if(numOfHits >= 4){
			game_over = true;
			return numOfHits;
		}
	}
	return numOfHits;
}

WINDOW *create_newwin(int h, int w, int start_y, int start_x){
	WINDOW *local_win = newwin(h, w, start_y, start_x);
	
	wrefresh(local_win);
	refresh();

	return local_win;
}

void print_on_window(WINDOW *win, int y, int x,char *msg){
	mvwprintw(win, y, x, msg);
	wrefresh(win);
}

void print_notification(int y, char *msg){

	return print_on_window(notification_win, y, 1, msg);

}
void End(){
	Draw();
	print_notification(MSG4,"Press ENTER to exit!\n");
	getchar();
	delwin(game);
	delwin(notification_win);
	endwin();	
}