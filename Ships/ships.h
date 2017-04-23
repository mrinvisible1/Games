#ifndef SHIPS
#define SHIPS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct for arrays of ships
typedef struct {
	int x;
	int y;
}Cord;

//Struct for list
typedef struct node{
	int x;
	int y;
	int hit;
	struct node* next;
}Node;

int GameOver;
static const int height=10;
static const int width=10;

/*
	Coordinates of ships
	number at the and is indicator of player
*/

Cord set_default_coords(int val);

Cord tanker1[4], tanker2[4];
Cord big1[2][3], big2[2][3];
Cord medium1[3][2], medium2[3][2];
Cord small1[4], small2[4];
/*
	This initialisation below is neccessary for collision detection later on
	(look on function collision)
	Basicly, I need this because, when I create arrays, they contain some random values
	that may be valid, so function ship_entry may result in error
	Example, i could get an error in entry of big ship that it is in colliosion with medium one, which is imposible
	because medium ships are yet to be entered
*/

void initialize_fields();
/*	
	THESE ARE LISTS!!!!!
	targeted_fields1 are fields that were targeted by FISRT player!
*/
static Node *targeted_fields1=NULL, *targeted_fields2=NULL, *targeted_fields1_end=NULL, *targeted_fields2_end=NULL;

//3 main functions

void Setup();
void Draw(Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[], Node* targeted_fields);
void Gameplay(Node **adress_targeted_fields,Node **adress_targeted_fields_end, Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[]);
void End();


void ship_entry(Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[]);

int _tanker(int x, int y, Cord tanker[], int set);
int _big(int x, int y, Cord big[][3], int set);
int _medium(int x, int y, Cord medium[][2], int set);
int _small(int x, int y, Cord small[], int set);

void set_direction(int direction, int size, Cord array[]);

int collision(int x, int y, int direction, int size, Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[]);

//helper functions
int already_targeted(int x, int y, Node *head);
int is_end(Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[]);
int destroyed_ship(Cord array[], int size);

//list functions
Node *create_node(int x, int y);
int add_to_end(Node** adress_of_head, Node** adress_of_end, int x, int y);
void free_list(Node **adress_of_head);
#endif