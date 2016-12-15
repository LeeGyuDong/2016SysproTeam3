#include <stdio.h>
#include <string.h>

const int  MAX_ARRAY_SIZE = 1024;
const int  MAX_CHAR_SIZE = 100;


void readStage(char* fileName, int array[100][100], int* ssh, int* ssw,
		int* h , int* w, int* barH)
{
	FILE* fp = fopen(fileName,"r");
	char tempArray[MAX_ARRAY_SIZE];
	char tempChar[MAX_CHAR_SIZE];
	int inputInt;
	int i,j;
	
	fscanf(fp,"%s",tempChar);
	fscanf(fp,"%d",&inputInt);	
	*ssh = inputInt;
		
	fscanf(fp,"%s",tempChar);
	fscanf(fp,"%d",&inputInt);	
	*ssw = inputInt;

	fscanf(fp,"%s",tempChar);
	fscanf(fp,"%d",&inputInt);	
	*h = inputInt;
	
	fscanf(fp,"%s",tempChar);
	fscanf(fp,"%d",&inputInt);	
	*w = inputInt;

	fscanf(fp,"%s",tempChar);
	fscanf(fp,"%d",&inputInt);
	*barH = inputInt;

//	printf("%d %d : \n ", *ssh,*ssw);
	for( i = 0 ; i < *h ; i++ )
	{
	
		for( j = 0 ; j < *w ; j++ )
		{
			char c;
			fscanf(fp,"%c",&c);
			if ( c == '\n' )
			{	
//				printf("\n");
				j--;
				continue;
			}
			else if ( c == '-')
				array[i][j] = 0;
			else if ( c == '1')	
				array[i][j] = 1;
			else if ( c == '2')
				array[i][j] = 2;
			else if ( c == '3')
				array[i][j] = 3;
			else if ( c == '4')
				array[i][j] = 4;
			else
				array[i][j] = -1;
			
//			printf("%c",c);	
		}
	}
//	printf("\n");
}


//int main()
///{	
//	int stage[50][100];
//	int stageHeight , stageWidth;
//	int i;	
//	int j;

//	readStage("./1.stage",stage,&i,&i,
//		&stageHeight,&stageWidth);

//	for( i = 0 ; i < stageHeight ; i++)
//	{
//		for( j = 0 ; j < stageWidth ; j++)
//		{
//			printf("%d",stage[i][j]);

//		}
//		printf("\n");
//	}

	
	
//	return 0;
//}
