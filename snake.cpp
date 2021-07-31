#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width=20;
const int height=20;
int x,y,foodX,foodY,score;
int tailX[100],tailY[100];
int nTail;
enum eDirecton {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirecton dir;

void Print()
{
    printf("\tWelcome to play...(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");

    printf("\n=>\nUse W key to move the snake to Up.\nUse Z key to move the snake to Down.\nUse A key to move the snake to Left.\nUse S keys to move the snake to Right.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat.\nEverytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> If you hit the snake body,then the game will over.\n");

    printf("\n\nPress any key to play game...");
    if(getch()==27)
        exit(0);
}

void Load()
{
    system("cls");
    printf("\n\n\n\n\n\n\n                                  LOADING.....");
    for(int r=1; r<=20; r++)
    {
        for(int q=0; q<=100000000; q++);
        printf("%c",177);
    }
    getch();
}

void Setup()
{
    gameOver=false;
    dir=STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(j==0)
                cout<<"#";
            if(i==y && j==x)
                cout<<"O";
            else if(i==foodY && j==foodX)
                cout<<"F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if(j==width-1)
                cout<<"#";

        }
        cout<<endl;
    }
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'z':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1; i<nTail; i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];

        tailX[i]=prevX;
        tailY[i]=prevY;

        prevX=prev2X;
        prevY=prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    for(int i=0; i<nTail; i++)
    {
        if(tailX[i]==x && tailY[i]==y)
        {
            gameOver=true;
        }
    }
    if(x==foodX && y==foodY)
    {
        score+=10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}

int Score()
{
    int score;
    score=nTail-1;
    printf("SCORE : %d",score*10);
    return score*10;
}

int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}

void Record()
{
    char plname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);
    fprintf(info,"Player Name :%s\n",plname);
    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    fprintf(info,"Score:%d\n",px=Scoreonly());
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("wanna see past records press 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}

int main()
{
    system("color 5f");
    Print();
    Load();
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(20);
    }
    system("cls");
    printf("\n\n\n    Game OVER!!!\nScore:%d\nPress any key to quit the game.\n",score);
    getch();
    Record();
}
