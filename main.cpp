#include <iostream>
#include <ctime>
#include<stdlib.h>
#include "clui.h"
using namespace std;

struct realBoards{
    char realBoard1[20][20]{0};
    char realBoard2[20][20]{0};
    char realBoard3[20][20]{0};
    char realBoard4[20][20]{0};
};
struct myBoards{
    char myBoard1[20][20];
    int length1{0};
    char myBoard2[20][20];
    int length2{0};
    char myBoard3[20][20];
    int length3{0};
    char myBoard4[20][20];
    int length4{0};
};
struct playerInfo{
    char* playerName;
    int playerScore;
    int savedBoard;
    myBoards player_myBoard;
    realBoards player_realBoard;
};
playerInfo playerArray[10];

bool gameOver=false;
int Length;
int allMine;
int cellPos = 1;
//coordinates of terminal in game board
int board_i=3;
int board_j=2;
//index and numbers of players
int indexPlayer = 0;
char realBoard[20][20], myBoard[20][20];
//if this array is equal to 0 then it has not been checked otherwise it has been checked.
int isSelected[20][20];
bool isValid(int , int);
bool isMine(int , int);
void userMove(char*);
void placeMines();
int countMines(int , int);
void assignNumber();
void printBoard(char*);
void initialize();
void showEmptyCell(int , int);
void printFinal(int , char*);
void playMinesweeperPart1(char*);
void playMinesweeperPart2(char*);
void difficulty();
void enterName();
void mainMenu(char*);
void leaderBoard(char*);
bool checkName(char*);
void swap( playerInfo& , playerInfo& );
void saveBoards(char[20][20],char[20][20],char*);
bool compare(char*,char*);
int lengthChar(char*);
void loadGameMenu(char*);
void playSavedGame(int , char*);
int main()
{
    init_clui();
    srand(time(0));
    enterName();
    return 0;
}

void swap(playerInfo&s, playerInfo&t){
    playerInfo temp=s;
    s = t;
    t = temp;
}

int lengthChar(char* s) {
    int index = 0;
    while (s[index] != '\0')
        index++;
    return index;
}

bool compare(char* a , char* b){
    if(lengthChar(a)==lengthChar(b)){
        for(int i=0 ; i<lengthChar(a);i++){
            if(a[i]!=b[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool isValid(int row,int column){
    if(row>=0 && row<Length && column>=0 && column<Length){
        return true;
    }
    return false;
}
//check if selected cell is Mine or not.
bool isMine(int row,int column){
    if(realBoard[row][column]=='X'){
        return true;
    }
    return false;
}
//check cells around zero
void showEmptyCell(int i,int j){

    if(isValid(i+1 , j) && isSelected[i+1][j] == 0){
        isSelected[i+1][j] = 1;
        myBoard[i+1][j] = realBoard[i+1][j];
        if(myBoard[i+1][j] == '-'){
            showEmptyCell(i+1 , j);
        }

    }
    if(isValid(i , j+1)&& isSelected[i][j+1] == 0){
        isSelected[i][j+1] = 1;
        myBoard[i][j+1] = realBoard[i][j+1];
        if(myBoard[i][j+1] == '-'){
            showEmptyCell(i , j+1);
        }

    }
    if(isValid(i-1 , j)&& isSelected[i-1][j] == 0){
        isSelected[i-1][j] = 1;
        myBoard[i-1][j] = realBoard[i-1][j];
        if(myBoard[i-1][j] == '-'){
            showEmptyCell(i-1 , j);
        }

    }
    if(isValid(i , j-1)&& isSelected[i][j-1] == 0){
        isSelected[i][j-1] = 1;
        myBoard[i][j-1] = realBoard[i][j-1];
        if(myBoard[i][j-1] == '-'){
            showEmptyCell(i , j-1);
        }

    }
    if(isValid(i+1 , j+1)&& isSelected[i+1][j+1] == 0){
        isSelected[i+1][j+1] = 1;
        myBoard[i+1][j+1] = realBoard[i+1][j+1];
        if(myBoard[i+1][j+1] == '-'){
            showEmptyCell(i+1 , j+1);
        }

    }
    if(isValid(i-1 , j-1) && isSelected[i-1][j-1] == 0){
        isSelected[i-1][j-1] = 1;
        myBoard[i-1][j-1] = realBoard[i-1][j-1];
        if(myBoard[i-1][j-1] == '-'){
            showEmptyCell(i-1 , j-1);
        }

    }
    if(isValid(i+1 , j-1) && isSelected[i+1][j-1] == 0){
        isSelected[i+1][j-1] = 1;
        myBoard[i+1][j-1] = realBoard[i+1][j-1];
        if(myBoard[i+1][j-1] == '-'){
            showEmptyCell(i+1 , j-1);
        }

    }
    if(isValid(i-1 , j+1) && isSelected[i-1][j+1] == 0){
        isSelected[i-1][j+1] = 1;
        myBoard[i-1][j+1] = realBoard[i-1][j+1];
        if(myBoard[i-1][j+1] == '-'){
            showEmptyCell(i-1 , j+1);
        }

    }
}

void userMove(char* input_name){
    int row,column;
    int countNum = 0;
    cursor_to_pos(board_i,board_j);
    int countFlag=0;
    char moveType = getch();
    while(moveType!='f' && moveType!='o' && moveType!='q' && moveType!=' '){
        switch(moveType){
            case 119:
                if(cellPos>Length){
                    cellPos-=Length;
                    if(Length<13){
                        board_i -= 2;
                    }
                    else{
                        board_i -= 1;
                    }
                }
                break;
            case 100:
                if(cellPos%Length!=0){
                    cellPos+=1;
                    board_j+=3;
                }
                break;
            case 97:
                if(cellPos%Length!=1){
                    cellPos-=1;
                    board_j-=3;
                }
                break;
            case 115:
                if(cellPos<=Length*Length-Length){
                    cellPos+=Length;
                    if(Length<13){
                        board_i += 2;
                    }
                    else{
                        board_i += 1;
                    }
                }
                break;
        }
        column=(cellPos%Length)-1;
        row=cellPos/Length;
        if(cellPos%Length==0){
            column=Length-1;
            row=(cellPos/Length)-1;
        }
        cursor_to_pos(board_i,board_j);
        moveType = getch();

    }
    column=(cellPos%Length)-1;
        row=cellPos/Length;
        if(cellPos%Length==0){
            column=Length-1;
            row=(cellPos/Length)-1;
        }
    int terminal_row = get_window_rows();

        if(moveType=='f' || moveType=='F'){
            for(int i=0;i<Length;i++){
                for(int j=0;j<Length;j++){
                    if(myBoard[i][j]=='F'){
                        countFlag++;
                    }
                }
            }
            //error for choosing more than 6 flags
            if(countFlag==allMine){
                change_color_rgb(158,9,22);
                cursor_to_pos(terminal_row-4,1);
                printf("You cannot add any more flags! try again\n");
                reset_color();
                userMove(input_name);
            }
            else if(myBoard[row][column]=='F'){
                myBoard[row][column]='$';
            }
            else{
                myBoard[row][column]='F';
            }
        }
        else if(moveType==' '){
            if(myBoard[row][column]=='F'){
                change_color_rgb(158,9,22);
                cursor_to_pos(terminal_row-4,1);
                printf("This cell is flagged! try again\n");
                reset_color();
                userMove(input_name);
            }
            else if(isMine(row,column)==false){
                if(realBoard[row][column] == '-'){
                        showEmptyCell(row,column);
                    }
                myBoard[row][column]=realBoard[row][column];

            }
            else{
                gameOver=true;
            }
        }
        else if(moveType=='q'){

            mainMenu(input_name);
        }
        else if(moveType=='o'){
            for(int i=0;i<indexPlayer;i++){
                if(compare(playerArray[i].playerName,input_name)){

                    int num = ++playerArray[i].savedBoard;
                    //save the game
                    if(num==1)
                        saveBoards(playerArray[i].player_myBoard.myBoard1 , playerArray[i].player_realBoard.realBoard1,input_name);
                    else if(num==2)
                        saveBoards(playerArray[i].player_myBoard.myBoard2 , playerArray[i].player_realBoard.realBoard2,input_name);
                    else if(num==3)
                        saveBoards(playerArray[i].player_myBoard.myBoard3 , playerArray[i].player_realBoard.realBoard3,input_name);
                    else if(num==4)
                        saveBoards(playerArray[i].player_myBoard.myBoard4 , playerArray[i].player_realBoard.realBoard4,input_name);
                    else{
                        change_color_rgb(158,9,22);
                        cursor_to_pos(terminal_row-4,1);
                        printf("You cannot save more than 4 games");
                        reset_color();
                        userMove(input_name);
                    }
                    mainMenu(input_name);
                    break;
                    }

                }
            }
}
//putting random mines in 6 cells
void placeMines(){
    for(int i=0;i<allMine;i++){
        int rand_row=rand()%Length;
        int rand_column=rand()%Length;
        if(realBoard[rand_row][rand_column]=='X'){
            i--;
            continue;
        }
        realBoard[rand_row][rand_column]='X';
    }
}
//calculating a number for each cell
int countMines(int row,int col)
{
	int count = 0;
		if(isValid(row-1, col)==true)
		{
			if(isMine(row-1, col)==true)
			count++;
		}
		if(isValid(row+1, col)==true)
		{
			if(isMine(row+1, col)==true)
			count++;
		}

		if(isValid(row, col+1)==true)
		{
			if(isMine(row, col+1)==true)
			count++;
		}

		if(isValid(row, col-1)==true)
		{
			if(isMine(row, col-1)==true)
			count++;
		}

		if(isValid(row-1, col+1)==true)
		{
			if (isMine(row-1, col+1)==true)
			count++;
		}

		if(isValid(row-1, col-1)==true)
		{
			if(isMine(row-1, col-1)==true)
			count++;
		}

		if(isValid(row+1, col+1)==true)
		{
			if(isMine(row+1, col+1)==true)
			count++;
		}

		if(isValid(row+1, col-1)==true)
		{
			if(isMine(row+1, col-1)==true)
			count++;
		}

	return count;
}
//assigning numbers to cells
void assignNumber(){
    for(int i=0;i<Length;i++){
        for(int j=0;j<Length;j++){
            if(realBoard[i][j]!='X'){
                if(countMines(i,j)==0){
                    realBoard[i][j] = '-';
                }
                else{
                    realBoard[i][j]=countMines(i,j)+'0';
                }
            }
        }
    }

}
//printing board after each move
//and printing footer
void printBoard(char* input_name){
    clear_screen();
    printf("\n\n");
    save_cursor();

    for(int i=0;i<Length;i++){
        for(int j=0;j<Length;j++){
            //printing flags
            if(myBoard[i][j]=='F'){
                change_color_rgb(61,119,235);
                printf(" F ");
                reset_color();
            }
            else if(myBoard[i][j]=='$'){
                change_color_rgb(50,168,82);
                printf(" %c ",myBoard[i][j]);
                reset_color();
            }
            //printing numbers in cells
            else{
                change_color_rgb(255,247,15);
                printf(" %c ",myBoard[i][j]);
                reset_color();
            }

        }
        if(Length<13){
            printf("\n\n");
        }
        else{
            printf("\n");
        }
    }

    int terminal_row = get_window_rows();
    int terminal_cols = get_window_cols();
    cursor_to_pos(terminal_row - 3, 1);
    //printing footer
    change_color_rgb(156,124,214);
    for (int i = 0; i < terminal_cols; i++){
        printf("*");
    }
    reset_color();
    printf("\n");
    //counting the used flags
    int usedFlags=0;
    for(int i=0;i<Length;i++){
        for(int j=0;j<Length;j++){
            if(myBoard[i][j]=='F'){
                usedFlags++;
            }
        }
    }
    //showing Left flags
    change_color_rgb(255,247,15);
    printf("Left flags: %d\n",allMine-usedFlags);
    reset_color();
    printf("Press f to flag a cell .Press space to select a cell\n");
    printf("Press o to save the game .Press q to go to the main menu");
    restore_cursor();
    userMove(input_name);

}
//initializing arrays to start the game
void initialize(){
    for(int i=0;i<Length;i++){
        for(int j=0;j<Length;j++){
            realBoard[i][j]=myBoard[i][j]='$';
            isSelected[i][j] = 0;
        }
    }
}
//printing the board after losing or winning the game
void printFinal(int score,char* input_name){
    clear_screen();
    printf("\n\n");
    for(int i=0;i<Length;i++){
        for(int j=0;j<Length;j++){
            if(realBoard[i][j]=='X'){
                //printing mines
                change_color_rgb(150, 10, 15);
                printf(" X ");
                reset_color();
            }
            else{
                change_color_rgb(255,247,15);
                printf(" %c ",realBoard[i][j]);
                reset_color();
            }
        }
        if(Length<13){
            printf("\n\n");
        }
        else{
            printf("\n");
        }

    }
    save_cursor();
    int terminal_row = get_window_rows();
    int terminal_cols = get_window_cols();
    cursor_to_pos(terminal_row - 3, 1);
    //print footer
    change_color_rgb(156,124,214);
    for (int i = 0; i < terminal_cols; i++){
        printf("*");
    }
    reset_color();
    if(gameOver==true){
        //printing footer after losing the game
        change_color_rgb(255,247,15);
        printf("You lost!\n");
        reset_color();
        printf("Your score: %d\n",score*10);
        printf("Press space to go to main menu");
        char lost = getch();
        while(1){
            if(lost == 32){
                gameOver=false;
                mainMenu(input_name);
            }
            lost = getch();
        }
    }
    else{
        //printing the footer after winning the game
        change_color_rgb(255,247,15);
        printf("You won!\n");
        reset_color();
        printf("Your score: %d\n",score*10);
        printf("Press space to go to main menu");
        char win = getch();
        while(1){
            if(win == 32){
                gameOver=false;
                mainMenu(input_name);
            }
            win = getch();
        }
    }
    restore_cursor();
}
void difficulty(){
    clear_screen();
    printf("Press space to choose: \n\n * Beginner\n * Intermediate\n * Advanced\n * Custom\n");
    int level_i=3;
    int level_j=2;
    cursor_to_pos(3,2);
    char level = getch();
    while(level!=32){
        if(level==119){
            if(level_i>3){
                level_i-=1;
            }
        }
        else if(level == 115){
            if(level_i<6){
                level_i+=1;
            }
        }
        change_color_rgb(205, 46, 219);
        cursor_to_pos(level_i,level_j);
        level = getch();
        reset_color();
    }
    if(level==32 && level_i==3){
        Length = 5;
        allMine = 4;
    }
    else if(level==32 && level_i==4){
        Length = 12;
        allMine = 28;
    }
    else if(level==32 && level_i==5){
        Length = 20;
        allMine = 96;
    }
    //customize size and mines
    else if(level==32 && level_i==6){
        cursor_to_pos(7,1);
        printf("Enter the length:\n");
        cin>>Length;
        do{
           if(Length>=5 && Length<=20){
             break;
           }
           else{
            change_color_rgb(158,9,22);
            printf("Length must be from 5 to 20:\n");
            reset_color();
            cin>>Length;
           }
        }while(1);

        printf("Enter the number of mines:\n");
        cin>>allMine;
        do{
           if(allMine>0 && allMine<Length*Length){
             break;
           }
           else{
            change_color_rgb(158,9,22);
            printf("Try again:\n");
            reset_color();
            cin>>allMine;
           }
        }while(1);
    }
}
//printing main menu
void mainMenu(char* input_name){
    clear_screen();
    printf("Current player: ");
    change_color_rgb(205, 46, 219);
    printf("%s\n\n",input_name);
    reset_color();
    printf("Press space to choose:\n\n");
    printf(" * New game\n\n * Load game\n\n * Change name\n\n * Leaderboard\n\n * Quit");
    int menu_i = 5;
    int menu_j = 2;
    cursor_to_pos(5,2);
    char menuInput = getch();
    while(menuInput!=32){
        if(menuInput==119){
            if(menu_i>5){
                menu_i-=2;
            }
        }
        else if(menuInput == 115){
            if(menu_i<13){
                menu_i+=2;
            }
        }
        cursor_to_pos(menu_i,menu_j);
        menuInput = getch();
    }
    //start new game
    if(menuInput==32 && menu_i==5){
        board_i=3;
        board_j=2;
        cellPos=1;
        playMinesweeperPart1(input_name);
    }
    else if(menuInput==32 && menu_i==7){
        for(int i=0;i<indexPlayer;i++){
            if(compare(playerArray[i].playerName , input_name)){
                if(playerArray[i].savedBoard==0){
                    cursor_to_pos(15, 2);
                    change_color_rgb(158,9,22);
                    printf("You don't have any saved game! ");
                    reset_color();
                    delay(3000);
                    mainMenu(input_name);
                    break;
                }
                else{
                    ////
                    loadGameMenu(input_name);
                }
            }
        }

    }
    //go to enter name
    else if(menuInput==32 && menu_i==9){
        enterName();
    }
    else if(menuInput==32 && menu_i==11){
       leaderBoard(input_name);
    }
    else if(menuInput==32 && menu_i==13){
        //exit the game
            play_beep();
            clear_screen();
            change_color_rgb(205, 46, 219);
            printf("Goodbye!\n");
            reset_color();
            delay(1000);
            exit(0);
    }
}
//check if user name is new or not
bool checkName(char* input_name){
    for(int i=0;i<indexPlayer;i++){
        if(compare(playerArray[i].playerName , input_name)){
            return true;
        }
    }
    return false;
}
//a function to save boards
void saveBoards(char my[20][20],char real[20][20],char* input_name){
    for(int i=0;i<Length;i++){
        for(int j=0;j<Length;j++){
            my[i][j] = myBoard[i][j];
            real[i][j] = realBoard[i][j];
        }
    }
    for(int i=0;i<indexPlayer;i++){
        if(compare(playerArray[i].playerName , input_name)){
            int tedad = playerArray[i].savedBoard;
            if(tedad==1)
                playerArray[i].player_myBoard.length1 = Length;

            else if(tedad==2)
                playerArray[i].player_myBoard.length2 = Length;

            else if(tedad==3)
                playerArray[i].player_myBoard.length3 = Length;

            else
                playerArray[i].player_myBoard.length4 = Length;
            break;
        }
    }
}
void leaderBoard(char* input_name){
    clear_screen();
    //descending order
    for(int i=0;i<indexPlayer;i++){
        for(int j=0;j<indexPlayer-i-1;j++){
            if(playerArray[j+1].playerScore > playerArray[j].playerScore){
                swap(playerArray[j] , playerArray[j+1]);
            }
        }
    }
    change_color_rgb(205, 46, 219);
    printf("Rank   Name                 Score\n");
    reset_color();
    save_cursor();
    for(int j,index=0 ; j<10 ; j++){
        printf("       |                    |");
        if(j%2==0 && index<5 && playerArray[index].playerName!=NULL){
            printf("%d",(playerArray[index].playerScore)*10);
            index++;
        }
        printf("\n");
    }
    restore_cursor();

    for(int i=0;i<5;i++){
        if(playerArray[i].playerName!=NULL){
            printf("%d)     |%s\n\n",i+1,playerArray[i].playerName);
        }
    }
    cursor_to_pos(13,2);

    printf("\nPress space to go to main menu\n");

    char press = getch();
    if(press == 32){
        mainMenu(input_name);
    }
}
//show the menu for saved games
void loadGameMenu(char* input_name){
    clear_screen();
    printf("Current player: ");
    change_color_rgb(205, 46, 219);
    printf("%s\n\n",input_name);
    reset_color();
    printf(" * First saved game\n\n * Second saved game\n\n * Third saved game\n\n * Forth saved game\n");
    int load_i=3;
    int load_j=2;
    cursor_to_pos(load_i,load_j);
    char loadInput = getch();
    while(loadInput!=32){
        if(loadInput==119){
            if(load_i>3){
                load_i-=2;
            }
        }
        else if(loadInput == 115){
            if(load_i<9){
                load_i+=2;
            }
        }
        cursor_to_pos(load_i,load_j);
        loadInput = getch();
    }
    int loadIndex;
    for(int i=0;i<indexPlayer;i++){
        if(compare(playerArray[i].playerName , input_name)){
            loadIndex = i;
            break;
        }
    }
    if(loadInput==32 && load_i==3 && playerArray[loadIndex].player_myBoard.length1!=0){
        playSavedGame(1,input_name);
    }
    else if(loadInput==32 && load_i==5 && playerArray[loadIndex].player_myBoard.length2!=0){
        playSavedGame(2,input_name);
    }
    else if(loadInput==32 && load_i==7 && playerArray[loadIndex].player_myBoard.length3!=0){
        playSavedGame(3,input_name);
    }
    else if(loadInput==32 && load_i==9 && playerArray[loadIndex].player_myBoard.length4!=0){
        playSavedGame(4,input_name);
    }
    else{
        cursor_to_pos(11 , 2);
        change_color_rgb(158,9,22);
        printf("There is no saved game here! ");
        delay(3000);
        reset_color();
        loadGameMenu(input_name);
    }
}

void enterName(){
    clear_screen();
    change_color_rgb(205, 46, 219);
    printf("Welcome to Minesweeper!\n");
    reset_color();
    for (int i=0;i<5;i++) {
        printf(".");
        // flush output
        flush();
        delay(500);
    }
    printf("\n\n");
    printf("Enter your name:\n");
    char* input_name = new char[20];
    cin.getline(input_name,20);
    if(checkName(input_name)){
        mainMenu(input_name);
    }
    //for new names
    else{
        playerArray[indexPlayer].playerName = input_name;
        playerArray[indexPlayer].savedBoard = 0;
        playerArray[indexPlayer].playerScore = 0;
        indexPlayer++;
        mainMenu(input_name);
    }
}

void playSavedGame(int savedNum,char* input_name){
    clear_screen();
    int andaze;
    int index;
    for(int i=0;i<indexPlayer;i++){
        if(compare(playerArray[i].playerName , input_name)){
            index = i;
            break;
        }
    }
    if(savedNum==1){
        andaze = playerArray[index].player_myBoard.length1;
        for(int i=0;i<andaze;i++){
            for(int j=0;j<andaze;j++){
                myBoard[i][j]= playerArray[index].player_myBoard.myBoard1[i][j];
                realBoard[i][j]= playerArray[index].player_realBoard.realBoard1[i][j];
            }
        }

    }
    else if(savedNum==2){
        andaze = playerArray[index].player_myBoard.length2;
        for(int i=0;i<andaze;i++){
            for(int j=0;j<andaze;j++){
                myBoard[i][j]= playerArray[index].player_myBoard.myBoard2[i][j];
                realBoard[i][j]= playerArray[index].player_realBoard.realBoard2[i][j];
            }
        }
    }
    else if(savedNum==3){
        andaze = playerArray[index].player_myBoard.length3;
        for(int i=0;i<andaze;i++){
            for(int j=0;j<andaze;j++){
                myBoard[i][j]= playerArray[index].player_myBoard.myBoard3[i][j];
                realBoard[i][j]= playerArray[index].player_realBoard.realBoard3[i][j];
            }
        }
    }
    else{
        andaze = playerArray[index].player_myBoard.length4;
        for(int i=0;i<andaze;i++){
            for(int j=0;j<andaze;j++){
                myBoard[i][j]= playerArray[index].player_myBoard.myBoard4[i][j];
                realBoard[i][j]= playerArray[index].player_realBoard.realBoard4[i][j];
            }
        }
    }
    playMinesweeperPart2(input_name);
}

void playMinesweeperPart1(char* input_name){
    difficulty();
    initialize();
    placeMines();
    assignNumber();
    playMinesweeperPart2(input_name);
}

void playMinesweeperPart2(char* input_name){
    printBoard(input_name);
    int countNum=0;
    int score = 0;
    //a loop to continue the game until losing or winning
    while(gameOver!=true){
        clear_screen();
        printBoard(input_name);
        for(int i=0;i<Length;i++){
            for(int j=0;j<Length;j++){
                if( (myBoard[i][j]>=48 && myBoard[i][j]<=56) || (myBoard[i][j]=='-') ){
                    countNum++;
                }
            }
        }

        //winning the game
        if(countNum==Length*Length-allMine){
            //calculating score in each play
            for(int i=0;i<indexPlayer;i++){
                if(compare(playerArray[i].playerName , input_name)){
                    playerArray[i].playerScore += countNum;
                    score = playerArray[i].playerScore;
                    break;
                }
            }
            printFinal(countNum,input_name);
            break;
        }
        countNum=0;
    }
    //losing the game
    if(gameOver==true){
        //calculating score in each play
        for(int i=0;i<Length;i++){
            for(int j=0;j<Length;j++){
                if( (myBoard[i][j]>=48 && myBoard[i][j]<=56) || (myBoard[i][j]=='-') ){
                    countNum++;
                }
            }
        }
        for(int i=0;i<indexPlayer;i++){
            if(compare(playerArray[i].playerName , input_name)){
                playerArray[i].playerScore += countNum;
                score = playerArray[i].playerScore;
                break;
            }
        }
        printFinal(countNum,input_name);
    }
}
