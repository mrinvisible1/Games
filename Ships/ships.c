#include "ships.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_fields()
{
	int num, num1;

	for(num=0;num<4;num++)
	{
		tanker1[num]=set_default_coords(-1);
		tanker2[num]=set_default_coords(-1);
		small1[num]=set_default_coords(-1);
		small2[num]=set_default_coords(-1);
	}
	for(num=0;num<2;num++)
	{
		for(num1=0;num1<3;num1++)
		{
			big1[num][num1]=set_default_coords(-1);
			big2[num][num1]=set_default_coords(-1);
		}
	}

	for(num=0;num<3;num++)
	{
		for(num1=0;num1<2;num1++)
		{
			medium1[num][num1]=set_default_coords(-1);
			medium2[num][num1]=set_default_coords(-1);
		}
	}
}


void Setup()
{
	initialize_fields();

	GameOver=0;

	printf("Enter x then y positions of your ships.\n");

	printf("Player one: ");
	ship_entry(tanker1, big1, medium1, small1);
	putchar('\n');
	Draw(tanker1, big1, medium1, small1, targeted_fields1);
	printf("Press ENTER to finish entry.\n");
	getchar();
	getchar();
	system("clear");

	printf("Player two: ");
	ship_entry(tanker2, big2, medium2, small2);
	putchar('\n');
	Draw(tanker2, big2, medium2, small2, targeted_fields2);
	printf("Press ENTER to finish entry.\n");
	getchar();
	getchar();
	system("clear");
}

void Draw(Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[], Node* targeted_fields)
{
	int i, j, tmp;
	char character;
	printf("   YOUR FIELD: \t\t OPPONENTS FIELD: \n");

	for(i=0;i<height;i++){
		putchar('|');
		for(j=0;j<=width*2+3;j++){

			// this if is for players filed
			if(j<width)
			{
				if(_tanker(j, i, tanker, 0)) character='T';
				else if(_big(j, i, big, 0)) character='B';
				else if(_medium(j, i, medium, 0)) character= 'M';
				else if(_small(j, i, small, 0)) character='S';
				else character='-';
			}
			//this if is for opponents field
			if(j>width+3)
			{
				tmp=already_targeted(j-(width+4), i, targeted_fields);
				if(tmp==1) character='O';
				else if(tmp == 2) character='X';
				else character='-';
			}
			
			//border for two fields begins here
			if(j == width +1) printf("%d", i);//printing numbers betwen fields
			else if(j == width || j == width +2) putchar(' ');
			else if(j == width + 3) putchar('|');
			//ends here

			else printf("%c|", character);
		}
		printf("\n");
	}

	//printing number below field
	for(i=0;i<=width*2+3;i++)
	{
		if(i<width)
		{
			printf(" %d", i);
		}
		else if(i>=width && i<=width + 3) putchar(' ');
		else if(i > width+3) printf(" %d", i-(width+4)); 
	}
	putchar('\n');
}

void Gameplay(Node **adress_targeted_fields,Node **adress_targeted_fields_end, Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[])
{
	int x, y, invalid_target_ind=0, hit_indicator=0;
	do
	{
		do
		{
			printf("Enter field you want to target(x then y): ");
			scanf("%d %d", &x, &y);	

			if(x<0)
			{
				printf("Negative x coordinate, enter again!\n");
				invalid_target_ind=1;
			}
			else if(y<0)
			{
				printf("Negative y coordinate, enter again!!\n");
				invalid_target_ind=1;
			}
			else if(x>width)
			{
				printf("x coordinate bigger than %d, enter again!\n", width);
				invalid_target_ind=1;
			}
			else if(y>height)
			{
				printf("y coordinate bigger than %d, enter again!\n", height);
				invalid_target_ind=1;
			}
			else if(already_targeted(x, y, *adress_targeted_fields))
			{
				printf("You have already targeted that field, enetr again\n");
				invalid_target_ind=1;
			}
			
			else invalid_target_ind=0;
		}while(invalid_target_ind);

		//adding targeted field to the end of list
		add_to_end(adress_targeted_fields, adress_targeted_fields_end, x, y);
/*
	since adress_targeted_fields_end is last targeted field
	i can set here value of hit member.
	
*/
		if(_tanker(x, y, tanker, 1))
		{
			printf("Hit!!\n");
			(*adress_targeted_fields_end)->hit=1;
			hit_indicator=1;
		}
		else if(_big(x, y, big, 1)) 
		{
			printf("Hit!!\n");
			(*adress_targeted_fields_end)->hit=1;
			hit_indicator=1;
		}
		else if(_medium(x, y, medium, 1)) 
		{
			printf("Hit!!\n");
			(*adress_targeted_fields_end)->hit=1;
			hit_indicator=1;
		}
		else if(_small(x, y, small, 1)) 
		{
			printf("Hit!!\n");
			(*adress_targeted_fields_end)->hit=1;
			hit_indicator=1;
		}
		else hit_indicator=0;

		if(is_end(tanker, big, medium, small))
		{
			printf("YOU HAVE WON!\n");
			GameOver=1;
			return;
		}
	}while(hit_indicator);


}

void End(){

	free_list(&targeted_fields1);
	free_list(&targeted_fields2);
	targeted_fields1_end=NULL;
	targeted_fields2_end=NULL;
	targeted_fields1=NULL;
	targeted_fields2=NULL;
}


void ship_entry(Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[])
{
	int i, direction, x, y, ind=0;
	int size=4;
	int num_of_ships=1;
	char type_of_ship[10];


	while(num_of_ships <= 4){
		for(i=0;i<num_of_ships; i++){
			switch(size){
				case 1:
					strcpy(type_of_ship, "small");
					break;
				case 2:
					strcpy(type_of_ship, "medium");
					break;
				case 3:
					strcpy(type_of_ship, "big");
					break;
				case 4:
					strcpy(type_of_ship, "tanker");
					break;
			}
			if(size != 1){
				do{
				printf("Enter direction for %s(1-right, 2-down): ", type_of_ship);
				scanf("%d", &direction);
				}while(direction > 2 || direction < 1);
			}

			do{
				printf("Enter start position for %s (x than y): ", type_of_ship);
				scanf("%d %d", &x, &y);

				if(x<0)
				{
					printf("Negative x coordinate, enter again!\n");
					ind=1;
				}
				else if(y<0)
				{
					printf("Negative y coordinate, enter again!\n");
					ind=1;
				}
				else if(x>width)
				{
					printf("x coordinate bigger than %d, enter again!\n", width);
					ind=1;
				}
				else if(y>height)
				{
					printf("y coordinate bigger than %d, enter again!n", height);
					ind=1;
				}
				else if(direction == 1 && x > (width-size))
				{	
					printf("For given direction, start position, %s does not fit on map\n", type_of_ship);
					printf("(it goes over right border).Enter again!\n");
					ind=1;
				}
				else if(direction == 2 && y > (height-size))
				{
					printf("For given direction, start position, %s does not fit on map\n", type_of_ship);
					printf("(it goes over bottom border).Enter again!\n");
					ind=1;
				}
				else if(collision(x, y, direction,size, tanker, big, medium, small))
				{	
					printf("%s is colliding with some of earlier enterd ships. Enter again start position!\n", type_of_ship);
					ind=1;
				}
				else ind=0;
			}while(ind);



			switch(size){
				case 1:
					small[i].x=x;
					small[i].y=y;
					break;
				case 2:
					medium[i][0].x=x;
					medium[i][0].y=y;
					set_direction(direction, size, medium[i]);
					break;
				case 3:
					big[i][0].x=x;
					big[i][0].y=y;
					set_direction(direction, size, big[i]);
					break;
				case 4:
					tanker[0].x=x;
					tanker[0].y=y;
					set_direction(direction, size, tanker);
					break;
			}
			Draw(tanker, big, medium, small, targeted_fields1);
		}
		size--;
		num_of_ships++;

	}
}

/*
	Ove 4 funkcije dole su za ispitivanje u Draw i Gameplay funkciji.
	Sluze da se ispita da li na datim kotama postoji neki brod i ako postoji 
	umece tu odgovarajuci karakter(videti Draw)
	set je tu zbog koriscenja u fji gameplay
	u toj funkciji se gadjaju polja, i ukoliko se u toj fji pozove neka od ovih
	ako se naidje na poklapanje kote gde je nadjeno poklapanje se postavljaju na -1
	iz istog razloga iz kog su i na pocetku bila stavljene na -1
*/


int _tanker(int x, int y, Cord tanker[], int set)
{
	int i;
		for(i=0;i<4;i++){
			if(x == tanker[i].x && y == tanker[i].y) 
				{
					if(set)
					{
						tanker[i]=set_default_coords(-1);
						if(destroyed_ship(tanker, 4)) printf("You have destroyed enemy tanker!\n");
					}

					return 1;
				}

		}

	return 0;
}
int _big(int x, int y, Cord big[][3], int set)
{

	int i, j;
	for(j=0;j<2;j++){
		for(i=0;i<3;i++){
			if(x == big[j][i].x && y == big[j][i].y) 
				{
					if(set)
					{
						big[j][i]=set_default_coords(-1);
						if(destroyed_ship(big[j], 3)) printf("SYou have destroyed enemy big!\n");

					}
					return 1;
				}

		}
	}
	return 0;
}
int _medium(int x, int y, Cord medium[][2], int set)
{

	int i, j;
		for(j=0;j<3;j++){
			for(i=0;i<2;i++){
				if(x == medium[j][i].x && y == medium[j][i].y) 
					{
						if(set)
						{
							medium[j][i]=set_default_coords(-1);
							if(destroyed_ship(medium[j], 2)) printf("You have destroyed enemy medium!\n");

						}
						return 1;
					}

			}
		}

	return 0;
}
int _small(int x, int y, Cord small[], int set)
{

	int i;
		for(i=0;i<4;i++){
			if(x == small[i].x && y == small[i].y) 
				{
					if(set)
					{
						small[i]=set_default_coords(-1);
						if(destroyed_ship(small, 1)) printf("You have destroyed enemy small!\n");

					}
					return 1;
				}

		}

	return 0;
}

void set_direction(int direction, int size, Cord array[]){
	int i;
	switch(direction){
		case 1: 
			for(i=1;i<size;i++){
				array[i].x = array[i-1].x +1;
				array[i].y = array[i-1].y;
			}
			break;
		case 2: 
			for(i=1;i<size;i++){
				array[i].x = array[i-1].x;
				array[i].y = array[i-1].y +1;
			}
			break;
	}

}


int collision(int x, int y, int direction, int size, Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[])
{
	int i;
	if(direction == 1)
	{
		for(i=0;i<size;i++, x++)
		{
			if(_tanker(x, y, tanker, 0))
				{
					printf("Collision with %s on position(%d, %d).\n", "tanker", x, y);
				 	return 1;
				}
			else if(_big(x, y, big, 0))
				{
					printf("Collision with %s on position(%d, %d).\n","big", x, y);
				 	return 1;
				}
			else if(_medium(x, y, medium, 0)) 
				{
					printf("Collision with %s on position(%d, %d).\n","medium", x, y);
					return 1;
				}
			else if(_small(x, y, small, 0))
				{
					printf("Collision with %s on position(%d, %d).\n","small", x, y);
				 	return 1;
				}
		}
		return 0;
	}

	else 
	{
		for(i=0;i<size;i++, y++)
		{
			if(_tanker(x, y, tanker, 0))
				{
				 	printf("Collision with %s on position(%d, %d).\n", "tanker", x, y);
				 	return 1;
				}
			else if(_big(x, y, big, 0))
				{
				 	printf("Collision with %s on position(%d, %d).\n","big", x, y);
				 	return 1;
				}
			else if(_medium(x, y, medium, 0))
				{
				 	printf("Collision with %s on position(%d, %d).\n","medium", x, y);
				 	return 1;
				}
			else if(_small(x, y, small, 0))
				{
				 	printf("Collision with %s on position(%d, %d).\n","small", x, y);
				 	return 1;
				}
		}
		return 0;
	}
}

Cord set_default_coords(int val)
{
	Cord tmp;
	tmp.x=val;
	tmp.y=val;
	return tmp;
}

int already_targeted(int x, int y, Node *head)
{
	while(head)
	{
		if(x == head->x && y == head->y) 
		{
			if(head->hit==1) return 2;
			else return 1;
		}
		head=head->next;
	}
	return 0;
}
int is_end(Cord tanker[], Cord big[][3], Cord medium[][2], Cord small[])
{
	int i, j;
	for(i=0;i<4;i++)
	{
		if(tanker[i].x != -1 || tanker[i].y != -1) return 0;
		if(small[i].x != -1 || small[i].y != -1) return 0;
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			if(big[i][j].x != -1 || big[i][j].y != -1) return 0;
		}
	}

	for(i=0;i<3;i++)
	{
		for(j=0;j<2;j++)
		{
			if(medium[i][j].x != -1 || medium[i][j].y != -1) return 0;
		}
	}
	return 1;
}

int destroyed_ship(Cord array[], int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		if(array[i].x!=-1 || array[i].y != -1) return 0;
	}
	return 1;
}



Node *create_node(int x, int y)
{
	Node* new_node=(Node*)malloc(sizeof(Node));
	if(new_node==NULL) return NULL;
	new_node->x=x;
	new_node->y=y;
	new_node->next=NULL;
	return new_node;
}

int add_to_end(Node** adress_of_head, Node** adress_of_end, int x, int y)
{
	Node *new_node=create_node(x, y);
	if(new_node == NULL) return 1;

	if(*adress_of_head==NULL)
	{
		(*adress_of_head)=new_node;
		(*adress_of_end)=new_node;
		return 0;
	}
	(*adress_of_end)->next=new_node;
	(*adress_of_end)=new_node;
	return 0;
}

void free_list(Node **adress_of_head)
{
	Node* tmp=NULL;
	while(*adress_of_head){
    tmp=(*adress_of_head)->next;
    free(*adress_of_head);
    (*adress_of_head)=tmp;
  }
}