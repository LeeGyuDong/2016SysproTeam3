#include	<stdio.h>
#include	<curses.h>

void draw_over();
void over_title();
void over_manu();
void t_box();
void printV(int, int, int);
void printH(int, int, char*);

extern int score;
void draw_over()
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

	over_title();
	over_manu();
	t_box();
	refresh();
}

void over_title()
{
	
	attron(COLOR_PAIR(1));
	printH(40,20,"     ");
	printV(43,21,3);
	printV(44,21,3);
	printH(46,20,"     ");
	printV(49,21,3);
	printV(50,21,3);

	printH(38,25,"                 ");

	printH(41,27,"            ");
	printV(41,28,1);
	printV(42,28,1);
	printH(41,29,"            ");
	printV(41,30,1);
	printV(42,30,1);
	printH(41,31,"            ");
	
}


void over_manu()
{
	move(40,35);
	attron(COLOR_PAIR(5));
	addstr("Press any key to exit!!");
	mvprintw(42,35,"Your Score is : %d ",score);
	
	if (score < 1000)
		mvprintw(43,35,"More Practice");
	else
		mvprintw(43,35,"Good ! You're Gosu!!!");
}
