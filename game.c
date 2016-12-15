#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

#define BAR 	"-------------" //바 
#define BLANK	"             " //바 빈칸

#define MOVE_FRONT 'w'

#define MOVE_RIGHT 'd'
#define MOVE_LEFT 'a'

#define GAME_QUIT 'q'

void frame(int sigNum ); 
void ball_frame(); 
void block_frame();
void bar_frame();

int set_tick(int time);
void initialize();
void endFrame();
void crmode2();
void readStage(char* fileName, int array[100][100], int* stageStartHeight, int* stageStartWidth, int* stageHeight, int* stageWidth, int* barHeight);

void draw_start();


struct ball
{
	int xPos,yPos; //공의 위치
	int xDirection,yDirection; //공이 이동할 방향
};

struct bar
{
	int x_pos;
	char *symbol;	
};

int stageStartHeight;
int stageStartWidth;
int stageHeight;
int stageWidth;
struct ball ball;
struct bar bar;
int command;

int map[100][100]; // 0 = 허공 , 1 = 벽  , 2 = 벽돌
int barStart; //바의 높이

int main()
{
	initialize();
	
	signal(SIGALRM,frame);	
	
	draw_start();
	while((command = getchar()))
	{
		if(command == '1')
		{
			crmode2();
			clear();
			set_tick(50);
			break;
		}

		else if(command == '2')
		{
			endwin();
			exit(0);
		}
	}
	
	while((command = getchar()))
	{
		if( command == GAME_QUIT )
		{
			endwin();
			exit(1);
		}
		else if( command == MOVE_LEFT && bar.x_pos > 8)
			bar.x_pos -= 2;
		else if( command == MOVE_RIGHT && bar.x_pos < 2 + stageWidth - strlen(bar.symbol)/2 )
			bar.x_pos += 2;
		
		if ( ball.xDirection == 0 && ball.yDirection == 0 )
		{
			if( command == MOVE_FRONT)
			{
				ball.xDirection = 1;
				ball.yDirection = -1;
			}

			else if ( command == MOVE_RIGHT)	
				ball.xPos = ball.xPos + 2;
			else if ( command == MOVE_LEFT)
				ball.xPos = ball.xPos - 2 ;
			

		}
	}
	return 0;
}

void initialize()
{
	initscr();

	readStage("./1.stage", map, &stageStartHeight, &stageStartWidth, &stageHeight, &stageWidth, &barStart);
	barStart = barStart + stageStartHeight;

	bar.symbol = BAR;
        bar.x_pos = stageStartWidth + stageWidth / 2;

        ball.xPos = bar.x_pos + 3;
        ball.yPos = barStart - 1;
	ball.xDirection = 0;
	ball.yDirection = 0;

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
	

}

void frame(int sigNum)
{
	int i, j;
	clear();
	
	block_frame();
	ball_frame();
	bar_frame();

	endFrame();
}

int set_tick(int time)
{
	struct itimerval timeSet;
	long sec,min;
	
	sec = time / 1000;
	min = ( time % 1000 ) * 1000L;
	
	timeSet.it_interval.tv_sec = sec;
	timeSet.it_interval.tv_usec = min;
	
	timeSet.it_value.tv_sec = sec;
	timeSet.it_value.tv_usec = min;

	return setitimer(ITIMER_REAL, &timeSet,NULL);
}


void block_frame()
{
	int i,j, x,y;
		

	for(i = stageStartHeight,x=0 ; i < stageStartHeight + stageHeight ; i++, x++)
	{
		for(j = stageStartWidth,y=0 ; j <stageStartWidth + stageWidth ; j++,y++)
		{
			move(i,j);
			if(map[x][y] == 1)
			{	
				attron(COLOR_PAIR(6));
				printw(" ");
		
			}

			else if(map[x][y] == 2)
			{
				attron(COLOR_PAIR(3));
				printw(" ");
			
			}

		}
	}

}

void ball_frame()
{
	int i, j;	
	int futureX = ball.xPos + ball.xDirection; //앞으로 갈 공의 x
	int futureY = ball.yPos + ball.yDirection; //앞으로 갈 공의 y

	attron(COLOR_PAIR(5)); 

	if(map[ball.yPos - stageStartHeight][futureX - stageStartWidth] > 0 ) // x방향만 계산했을때 그곳에  뭐가 있을때
		ball.xDirection = -ball.xDirection;
	if(map[futureY - stageStartHeight][ball.xPos - stageStartWidth] > 0 ) // ,y방향만 계산햇을시 그곳에 뭐 있을때
		ball.yDirection = -ball.yDirection;
	if( map[ball.yPos - stageStartHeight][futureX - stageStartWidth] == 0 && map[futureY - stageStartHeight][ball.xPos - stageStartWidth] == 0 && map[futureY - stageStartHeight][futureX - stageStartWidth] > 0)
	{ // x 방향만 계산하고 y방향만 계산했을때 각각은  둘다에 뭐가 없지만 , x,y방향을 한번에 계산하여  앞으로 갈곳에 뭐가 있을때
		ball.yDirection = -ball.yDirection;
		ball.xDirection = -ball.xDirection;
	}
	

	ball.xPos = ball.xPos + ball.xDirection;
	ball.yPos = ball.yPos + ball.yDirection;
	
	if (ball.yPos + ball.yDirection - 1 == barStart)
	{
		if (ball.xPos >= bar.x_pos && ball.xPos < bar.x_pos + strlen(bar.symbol))
		{
			ball.yDirection = -1;
			ball.xPos = ball.xPos + ball.xDirection;
			ball.yPos = ball.yPos + ball.yDirection;
		}
	}
	move(ball.yPos,ball.xPos);
	addstr("o");

	
}

void bar_frame()
{
	if(command == MOVE_LEFT)
		move(barStart, bar.x_pos+1);
	else if(command == MOVE_RIGHT)
		move(barStart,bar.x_pos - strlen(bar.symbol));
	//addstr(BLANK);
	move(barStart,bar.x_pos);
	addstr(bar.symbol);
}

void crmode2()
{
	struct termios tty;
	tcgetattr(0, &tty);
	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO;

	tcsetattr(0,TCSANOW,&tty);
}

void endFrame()
{
	move(LINES-1,0);
	refresh();
}
