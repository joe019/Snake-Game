#include <stdlib.h>     // clock_t
#include <stdbool.h>    // true
#include <stdio.h>   	// FILE
#include <termios.h>	// _kbhit()
#include <unistd.h>  	// _kbhit()
#include <fcntl.h>   	// _kbhit()

int gameBoard[25][50];	// defines the position of borders, snake and food
int snakeBody[2][50];	// each column gives the (x,y) coordinates of snake, starting from head [x->(0,0) y->(1,0)]
int food[2] = {0,0};	// (x,y) coordinates of food
int score = 0;
int snakeLength = 3;

struct Movement
{
	int x;
	int y;
};

struct Movement moveSnake = {1, 0};

// Set four borders within which the snake can move
void setBorders()
{
    int i;
    
    // horizontal borders
    for(i=0; i<=49; i++)
    {
        gameBoard[0][i]=1;    // top border
        gameBoard[24][i]=1;   // bottom border   
    }

    // vertical borders
    for(i=1; i<=23; i++)
    {
        gameBoard[i][0]=1;    // left border
        gameBoard[i][49]=1;   // right border   
    }        
}

// Set the initial position of snake
void setSnake()
{
    snakeBody[0][0]=3; // x
    snakeBody[1][0]=3; // y

    snakeBody[0][1]=4; // x
    snakeBody[1][1]=3; // y

    snakeBody[0][2]=5; // x
    snakeBody[1][2]=3; // y
}

// Induces delay between frames
void delayBF(int delay)
{
    clock_t delayEnds;

    delayEnds = clock() + delay * 1000;

    while (clock() < delayEnds)
    {
        // Do nothing
    }
}

int _kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

// Controls the movement of snake
void controlMovement(char key)
{
    if(key=='A')    //up
    {
        moveSnake.x = 0;
        moveSnake.y = -1;
    }
    else if(key=='B')   //down
    {
        moveSnake.x = 0;
        moveSnake.y = 1;
    }
    else if(key=='C')   //right
    {
        moveSnake.x = 1;
        moveSnake.y = 0;
    }
    else if(key=='D')   //left
    {
        moveSnake.x = -1;
        moveSnake.y = 0;
    }
}

// flag = 1 -> put;  flag = 0 -> remove
void putOrRemoveSnake(int flag)
{
    int i, snakeX, snakeY;
    for(i=0; i<snakeLength; i++)
    {
        snakeX = snakeBody[0][i];
        snakeY = snakeBody[1][i];
        if((snakeX!=0)&&(snakeY!=0))
        {
            gameBoard[snakeY][snakeX]=flag;
        }
    }
}

void printObjects()
{
    printf("\n***************TERMINAL SNAKE GAME*****************\n\n\n\n");
    printf("\nInstructions:");
    printf("\n1. Use arrow keys for navigation");
    printf("\n2. Press any other key to exit\n");
    
    int i,j,p;
    for(i=0; i<25; i++)
    {
        for(j=0; j<50; j++)
        {
            p=gameBoard[i][j];

            if(p==1)
                printf("#");
            else if (p==2)
                printf("+");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void snakeMovement()
{
    int i;
    
    for(i=snakeLength; i>0; i--)
    {
        snakeBody[0][i]=snakeBody[0][i-1];
        snakeBody[1][i]=snakeBody[1][i-1];
    }

    snakeBody[0][0] += moveSnake.x;
    snakeBody[1][0] += moveSnake.y;
}

void writeToFile()
{
   int currentScore;
   currentScore = score;

   FILE *fptr;
   fptr = (fopen("snakeFile.txt", "r"));
   if(fptr == NULL)
   {
   	   fptr = (fopen("snakeFile.txt", "w"));
   	   putw(currentScore, fptr);
   	   fclose(fptr);
   }
   else
   {
   	   int num;
   	   num = getw(fptr);
   	   fclose(fptr);

   	   if(currentScore>num)
   	   {
   	   	  fptr = (fopen("snakeFile.txt", "w"));
   	   	  putw(currentScore, fptr);
   	   	  fclose(fptr);
   	   }
   }
}

void readFromFile()
{
    int num;
    FILE *fptr;

    if ((fptr = fopen("snakeFile.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    num = getw(fptr);

    fseek(fptr, 0, SEEK_SET);
    printf("High score : %d\n", num);
    fclose(fptr);
}

void checkBorderHit()
{
    int currentX,currentY;
    currentX = snakeBody[0][0];
    currentY = snakeBody[1][0];

    if( (currentX==0) || (currentX==49) || (currentY==0) || (currentY==24) )
    {
        (score>1) ? printf("Game Over :/\nYou scored %d points!\n", score)
                  : printf("Game Over :/\nYou scored %d point!\n", score);
        writeToFile();
        readFromFile();
        exit(0);
    }
}

int getRandomNumber(int divisor)
{
	return rand() % divisor + 1;
}

void placeFood()
{
    int foodX, foodY;
    if (food[0]==0)
    {
		foodX = getRandomNumber(48);
    	foodY = getRandomNumber(23);
    
        food[0] = foodX;
        food[1] = foodY;

        gameBoard[foodY][foodX]=2;
    }
}

void checkFoodStatus()
{
    int foodX, foodY;
    foodX=food[0];
    foodY=food[1];

    if ( (foodX==snakeBody[0][0]) && (foodY==snakeBody[1][0]) )
    {
        gameBoard[foodY][foodX]=0;
        food[0]=0;
        score++;
        snakeLength++;
        placeFood();
    }
}

void repeat()
{
    int frameDelayMS = 200;   // Time delay between frames in milli seconds
    char key;
    while(true)
    {
        delayBF(frameDelayMS);
        
        if(_kbhit())   
        {
            if (getchar() == '\033')
            {
                getchar();
                key = getchar();
                controlMovement(key);
            }
            else
            {
                printf("\nExited from game!\n");
                exit(0);
            }
        }

        putOrRemoveSnake(1); 
        printObjects();         
        putOrRemoveSnake(0); 
        snakeMovement();
        checkBorderHit();       
        placeFood();                
        checkFoodStatus();             
        printf("Score : %d \n", score); 
    }

}

int main()
{
    setBorders(); 	
    setSnake();      	
    repeat();                 	

    return 0;
}