#include	<stdio.h>
#include	<curses.h>

void draw_start();
void title();
void t_box();
void manu();
void printV(int, int, int);
void printH(int, int, char*);


void draw_start()
{
	clear();
	
	if(has_colors())
	{
		start_color();

		init_pair(1,COLOR_WHITE,COLOR_RED);
		init_pair(2,COLOR_WHITE,COLOR_YELLOW);
		init_pair(3,COLOR_WHITE,COLOR_GREEN);
		init_pair(4,COLOR_WHITE,COLOR_BLUE);
		init_pair(5,COLOR_WHITE,COLOR_BLACK);
		init_pair(6,COLOR_WHITE,COLOR_WHITE);

	}

	title();
	manu();
	t_box();
	refresh();
}

void title()
{
	
	attron(COLOR_PAIR(1));
	//벽	
	printV(9,15,7);
	printV(10,15,7);
	printV(18,15,7);
	printV(19,15,7);
	printH(11,18,"        ");	
	printH(11,21,"        ");
	
	printH(21, 17, "   ");
	printH(21, 19, "   ");
	printV(24,15,7);
	printV(25,15,7);
	
	printH(13,23,"          ");
	printV(22,23,5);
	printV(23,23,5);
	
	attron(COLOR_PAIR(2));
	//돌
	printH(31,15,"              ");
	printV(31,15,3);
	printV(32,15,3);	
	printH(31,18,"              ");
	
	printV(37,20,2);
	printV(38,20,2);
	printH(29,21,"                 ");
	
	printH(32,23,"            ");
	printV(42,24,1);
	printV(43,24,1);
	printH(32,25,"            ");
	printV(32,26,1);
	printV(33,26,1);
	printH(32,27,"            ");
	
	attron(COLOR_PAIR(3));
	//깨
	printH(48,17,"     ");
	printV(51,18,8);
	printV(52,18,8);
	printH(54,17,"     ");
	printV(57,18,8);
	printV(58,18,8);

	printV(60,15,13);
	printV(61,15,13);
	printH(62,21," ");
	printV(63,15,13);
	printV(64,15,13);

	attron(COLOR_PAIR(4));
	//기
	printH(69,17,"        ");
	printV(75,18,8);
	printV(76,18,8);
	
	printV(79,15,13);
	printV(80,15,13);

}

void printV(int x, int y, int n)
{
	for(int i = 0; i < n; i++ )
	{
		move(y++,x);
		printw(" ");
	}

}

void printH(int x, int y, char *string)
{
	move(y,x);
	addstr(string);
}

void t_box()
{
	attron(COLOR_PAIR(6));	

	printV(5,5,50);
	printV(6,5,50);
	printV(86,5,50);
	printV(87,5,50);
	printH(5,5,"                                                                                  ");
	printH(5,55,"                                                                                  ");

}

void manu()
{
	move(40,40);
	attron(COLOR_PAIR(5));
	addstr("1.START");
	move(42,40);
	addstr("2.EXIT");
}
