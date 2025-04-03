#include <stdio.h>
#include <graphics.h>
#include <time.h>

void coverPage();
void resetGame();
void drawGrid();
void handleMouseClick();
void handleMultiplayerClick();
void displayCurrentPlayer();
void aiMove();
void checkWin();
void displayWinner(char winner);
void winTrophy();

char board[3][3];
char currentPlayer = 'X'; // Player starts as X
int moves;
int gameOver;
int gameMode; // 0 for multiplayer 1 for single-player

int main()
{
    initwindow(1100, 700, "Tic Tac Toe");
    gameMode = -1; // start game as no mode chosen
    resetGame();

    while (gameMode == -1) 
    {
        coverPage(); 
    }

    cleardevice();
    drawGrid(); 

    while (1) 
    {
        if (!gameOver) 
        {
            displayCurrentPlayer(); // Display current player
            if (gameMode == 0) {
                handleMultiplayerClick(); // Handle multiplayer moves
            } else {
                handleMouseClick(); // Handle single-player moves
            }
        }
    }
}

void coverPage()
{
    rectangle(30, 30, 1070, 670);
    rectangle(50, 50, 1050, 650);
    setcolor(WHITE);
    settextstyle(MONO_FONT, HORIZ_DIR, 7);
    outtextxy(320, 70, "TIC TAC TOE");
    outtextxy(460, 150, "GAME");
    
    setcolor(RED);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    
    rectangle(340, 370, 810, 415); 
    outtextxy(350, 380, "1. Single Player (vs AI)");
    
    rectangle(340, 445, 810, 490); 
    outtextxy(350, 450, "2. Multiplayer (Local)");

    setcolor(WHITE);
    settextstyle(SCRIPT_FONT, HORIZ_DIR, 5);
    outtextxy(280, 550, "Click on the option to select!!");

    if (ismouseclick(WM_LBUTTONDOWN)) {
        int x, y;
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if (y > 370 && y < 415) {
            gameMode = 1; // Give value for Single Player
        } else if (y > 450 && y < 495) {
            gameMode = 0; // Multiplayer
        }
    }
}

void resetGame()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void drawGrid()
{
    setbkcolor(BLACK);
    cleardevice();
    line(420, 100, 420, 600); // Vertical line 1
    line(660, 100, 660, 600); // Vertical line 2
    line(215, 250, 885, 250); // Horizontal line 1
    line(215, 450, 885, 450); // Horizontal line 2
}

void displayCurrentPlayer() 
{
    setcolor(WHITE);
    char text[20];
    sprintf(text, "%c's Turn", currentPlayer);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(450, 50, text);
}

void handleMouseClick()
{
    if (ismouseclick(WM_LBUTTONDOWN)) 
    {
        int x, y;
        getmouseclick(WM_LBUTTONDOWN, x, y);
        int row, col;

        if (x > 200 && x < 420)
        {
            col = 0;
            if (y > 100 && y < 250) row = 0;
            else if (y > 250 && y < 450) row = 1;
            else if (y > 450 && y < 600) row = 2;
        }
        else if (x > 420 && x < 660)
        {
            col = 1;
            if (y > 100 && y < 250) row = 0;
            else if (y > 250 && y < 450) row = 1;
            else if (y > 450 && y < 600) row = 2;
        }
        else if (x > 660 && x < 900)
        {
            col = 2;
            if (y > 100 && y < 250) row = 0;
            else if (y > 250 && y < 450) row = 1;
            else if (y > 450 && y < 600) row = 2;
        }

        if (board[row][col] == ' ' && !gameOver)
        {
            char text[2] = { currentPlayer, '\0' };
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
            
            if (col == 0) outtextxy(300, 175 + 175 * row, text);
            else if (col == 1) outtextxy(540, 175 + 175 * row, text);
            else if (col == 2) outtextxy(780, 175 + 175 * row, text);

            board[row][col] = currentPlayer;
            moves++;
            checkWin();

            if (!gameOver) 
            {
                delay(600); // Delay for 0.6 sec before AI plays
                currentPlayer = 'O'; // Switch to AI
                aiMove(); // AI move
                currentPlayer = 'X'; // Switch back to player
            }
        }
    }
}

void handleMultiplayerClick()
{
    if (ismouseclick(WM_LBUTTONDOWN)) 
    {
        int x, y;
        getmouseclick(WM_LBUTTONDOWN, x, y);
        int row, col;

        if (x > 200 && x < 420)
        {
            col = 0;
            if (y > 100 && y < 250) row = 0;
            else if (y > 250 && y < 450) row = 1;
            else if (y > 450 && y < 600) row = 2;
        }
        else if (x > 420 && x < 660)
        {
            col = 1;
            if (y > 100 && y < 250) row = 0;
            else if (y > 250 && y < 450) row = 1;
            else if (y > 450 && y < 600) row = 2;
        }
        else if (x > 660 && x < 900)
        {
            col = 2;
            if (y > 100 && y < 250) row = 0;
            else if (y > 250 && y < 450) row = 1;
            else if (y > 450 && y < 600) row = 2;
        }

        if (board[row][col] == ' ' && !gameOver)
        {
            char text[2] = { currentPlayer, '\0' };
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);

            if (col == 0) outtextxy(300, 175 + 175 * row, text);
            else if (col == 1) outtextxy(540, 175 + 175 * row, text);
            else if (col == 2) outtextxy(780, 175 + 175 * row, text);

            board[row][col] = currentPlayer;
            moves++;
            checkWin();

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

void checkWin()
{
	//for rows and columns
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            displayWinner(board[i][0]);
            return;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            displayWinner(board[0][i]);
            return;
        }
    }
	//for diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        displayWinner(board[0][0]);
        return;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        displayWinner(board[0][2]);
        return;
    }

    if (moves == 9)
    {
        displayWinner('T'); // Tie
    }
}

void displayWinner(char winner)
{
    setcolor(WHITE);
    settextstyle(10, HORIZ_DIR, 6);
    gameOver = 1;

    if (winner == 'T')
    {
        outtextxy(395, 40, "It's a Tie!");
    }
    else 
    {
        char text[20];
        sprintf(text, "%c Won!!", winner);
        outtextxy(440, 40, text);
        winTrophy();
    }
}

void winTrophy() 
{
    ellipse(200,150,170,8,50,100);//left edge of trophy
    rectangle(144,129,255,137);//trophy mathi ko rectangle
    
	//color filling for second last rectangle
    setfillstyle(SOLID_FILL,RED);
    floodfill(150,133,WHITE);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(200,240,WHITE);
	
	arc(88,268,318,16,100);//left arc of trophy
	arc(88,268,319,13,100);
	arc(310,268,163,222,100);//right arc of trophy
	arc(310,268,168,221,100);
	rectangle(151,334,245,343);// trophy muni ko second last rectangle
	
	//color filling for second last rectangle
	setfillstyle(SOLID_FILL,BROWN);
	floodfill(160,340,WHITE);
	setfillstyle(SOLID_FILL,BROWN);
	floodfill(160,340,WHITE);
    
	rectangle(125,343,271,378);//trophy muni ko last rectangle
    
	//color filling for last recangle
	setfillstyle(SOLID_FILL,BROWN);
  	floodfill(130,370,WHITE);
 	
	line(178,162,216,162);//up line inside the trophy
	line(182,199,216,199);//down line inside the trophy
	line(172,187,172,173);//left line
	line(226,185,226,175);//right line
	arc(162,157,301,346,20);//left up arc
	arc(162,203,7,63,20);//left down arc
	arc(235,157,198,244,20);//right up arc
	arc(235,203,113,164,20);//right down arc
 	
	setfillstyle(SOLID_FILL,RED);
 	floodfill(180,178,WHITE);
 	
	ellipse(172,185,115,256,50,25);
	ellipse(162,185,103,270,50,30);
    
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(119,180,WHITE);
	
	ellipse(226,186,286,64,50,25);
    ellipse(233,187,276,72,50,30); 
    
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(279,185,WHITE);
	
	setcolor(WHITE);
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	outtextxy(149,348,"WINNER!");
	
	//color filling for inside neck of the trophy
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(200,280,WHITE);
	
	setcolor(RED);
	ellipse(200,150,170,172,50,100);

}

void aiMove()
{
    if (gameOver) return;
    srand(time(NULL)); // Seed for random number generation as of current time

    int row, col;
    do {
        row = rand() % 3;	//this generates random number and gets remainder upon divided by 3
        col = rand() % 3;
    } while (board[row][col] != ' '); // Keep trying until a valid move is found

    board[row][col] = 'O'; // AI is 'O'
    char text[2] = { 'O', '\0' };

    if (col == 0) outtextxy(300, 175 + 175 * row, text);
    else if (col == 1) outtextxy(540, 175 + 175 * row, text);
    else if (col == 2) outtextxy(780, 175 + 175 * row, text);

    moves++;
    checkWin();
}
