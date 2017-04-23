#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ships.h"

int main()
{
	Setup();
	printf("Let us BEGIN!\n");
	while(!GameOver)
	{	
		printf("Player one:\n");
		Gameplay(&targeted_fields1, &targeted_fields1_end, tanker2, big2, medium2, small2);
		Draw(tanker1, big1, medium1, small1, targeted_fields1);
		getchar();
		printf("Press ENTER to finish your move!\n");
		getchar();
		system("clear");

		if(GameOver==1) break;
		printf("Player two:\n");
		Gameplay(&targeted_fields2, &targeted_fields2_end, tanker1, big1, medium1, small1);
		Draw(tanker2, big2, medium2, small2, targeted_fields2);
		getchar();
		printf("Press ENTER to finish your move!\n");
		getchar();
		system("clear");
	}


	printf("The END!\n");
	End();
	return 0;
}