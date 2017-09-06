//Подлючение собственной библиотеки
#include "lib.h"

int main(void){
    char **board = malloc(MAX*sizeof(*board));
    for(int index = 0; index<MAX; index++){
        board[index] = malloc(MAX*sizeof(char));
    }
    
    char win = ' ';
    
    int tile_one;
    int tile_two;
    int move = 2;
    
    int number_symbol;
    
    char symbol_1;
    char symbol_2;
    
    //Очистка доски
    clear();
    
    //Открытие лог файла
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 0;
    }
    do{
        printf("Choose 1 - X or 2 - O: ");
        number_symbol = get_int();
        if(number_symbol == 1 || number_symbol == 2){
            break;
        }
    }
    while(true);
    
    if(number_symbol == 1){
        symbol_1 = 'X';
        symbol_2 = 'O';
    }
    else if(number_symbol == 2) {
        symbol_1 = 'O';
        symbol_2 = 'X';
    }
    
    //Приведствие
    greet();
    
    //Инициализация доски
    init(board);
    
    while(true){
        
        //Очистка консоли
        clear();
        
        //Отрисовка доски
        draw(board);

        for (int i = 0; i < MAX; i++){
            for (int j = 0; j < MAX; j++){
                fprintf(file, "%2c", board[i][j]);
                
            }
            fprintf(file, "\n");
        }
        fflush(file);

        if(won(&win, &move, board)){
            printf("WIN - %c \n", win);
            fprintf(file, "WIN - %c \n", win);
            fflush(file);
            fclose(file);
            free(board);
            return 1;
        }
        if(move%2 == 0){
            printf("Input -%c- - row: ", symbol_1);
            tile_one = get_int();
            printf("\n");
            
            // quit if user inputs 0 (for testing)
            if (tile_one == 0){
                fclose(file);
                free(board);
                return 1;
            }
            printf("Input -%c- - col: ", symbol_1);
            tile_two = get_int();
            printf("\n");
        }
        else{
            printf("Input -%c- - row: ", symbol_2);
            tile_one = get_int();
            printf("\n");
            
            //Выход из програмы при вводе '0'
            if (tile_one == 0){
                fclose(file);
                free(board);
                return 1;
            }
            printf("Input -%c- - col: ", symbol_2);
            tile_two = get_int();;
            printf("\n");
        }
        
        fprintf(file, "\n");
        fprintf(file, "%i - %i\n", tile_one, tile_two);
        fflush(file);
            
        if(!srokeCheck(&symbol_1, &symbol_2, &move, board, &tile_one, &tile_two)){
            printf("Wrong move, enter again!\n");
            fprintf(file, "Wrong move, enter again!\n");
            fprintf(file, "\n");
            fflush(file);
            usleep(1000000);
        }

        usleep(500000);
    }
}

//Очистка консоли
void clear(void){
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

//Инструкции и приведствие
void greet(void){
    clear();
    printf("WELCOME TO GAME OF Tic-tac-toe\n");
    usleep(2000000);
}

//Инициализация доски
void init(char **board){
int col = 1;
int row = 1;
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            if((i == 1 || i == 3 || i == 5) && j == 0){
                board[i][j] = col + '0';
                col++;
            }
            else if((j == 1 || j == 3 || j == 5) && i == 0){
                board[i][j] = row + '0';
                row++;
            }
            else{
                board[i][j] = ' ';
            }
        }
    }

    
    for(int i = 1; i < MAX; i++){
        for(int j = 1; j < MAX; j++){
            if((j == 2 || j == 4) && i == 1){
                board[i][j] = '|';
            }
            else if((j == 2 || j == 4) && i == 3){
                board[i][j] = '|';
            }
            else if((j == 2 || j == 4) && i == 5){
                board[i][j] = '|';
            }
            else if(i == 2){
                board[i][j] = '-';
            }
            else if(i == 4){
                board[i][j] = '-';
            }
            else{
                board[i][j] = ' ';
            }
        }
    }
}

//Вывод доски в консоль
void draw(char **board){
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            printf("%2c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

//Проверка хода
bool srokeCheck(const char *symbol_1, const char *symbol_2, int *move, char **board, const int *tile_one, const int *tile_two){
    
    int temp_1;
    int temp_2;

    if(*tile_one > 0 && *tile_one < 4 && *tile_two >0 && *tile_two < 4){
        if(*tile_one == 1){
            temp_1 = 1;
        }
        if(*tile_one == 2){
            temp_1 = 3;
        }
        if(*tile_one == 3){
            temp_1 = 5;
        }
        if(*tile_two == 1){
            temp_2 = 1;
        }
        if(*tile_two == 2){
            temp_2 = 3;
        }
        if(*tile_two == 3){
            temp_2 = 5;
        }
    }
    else{
        return false;
    }
    
    if(board[temp_1][temp_2] == ' '){
        if(*move%2 == 0){
            board[temp_1][temp_2] = *symbol_1;
            *move = *move + 1;
        }
        else{
            board[temp_1][temp_2] = *symbol_2;
            *move += + 1;
        }
        return true;
    }
    return false;
}

//Проверка победы
bool won(char *win, int *move, char **board){
    if(*move > 6){
        if(board[1][1] != ' ' && board[1][3] != ' ' && board[1][5] != ' ' && board[3][1] != ' ' && board[3][3] != ' ' && board[3][5] != ' ' && board[5][1] != ' ' && board[5][3] != ' ' && board[5][5] != ' '  ){
            *win = 'F';
            printf("Friendship won!\n");
            return true;
        }
        for(int i = 1; i < MAX; i++){
            for(int j = 1; j < MAX; j++){
                if((i == 1 || i == 3 || i == 5) && j == 1){
                    if(board[i][j] == board[i][j+2] && board[i][j] == board[i][j+4]){
                        if(board[i][j] == ' '){
                            return false;
                        }
                        else if(board[i][j] == 'X'){
                            *win = 'X';
                        }
                        else{
                            *win = 'O';
                        }
                        return true;
                    }
                }
                if((j == 1 || j == 3 || j == 5) && i == 1){
                    if(board[i][j] == board[i+2][j] && board[i][j] == board[i+4][j]){
                        if(board[i][j] == ' '){
                            return false;
                        }
                        else if(board[i][j] == 'X'){
                            *win = 'X';
                        }
                        else{
                            *win = 'O';
                        }
                        return true;
                    }
                }
                if(i == 1 && j == 1){
                    if(board[i][j] == board[i+2][j+2] && board[i+2][j+2] == board[i+4][j+4]){
                        if(board[i][j] == ' '){
                            return false;
                        }
                        else if(board[i][j] == 'X'){
                            *win = 'X';
                        }
                        else{
                            *win = 'O';
                        }
                        return true;
                    }
                }
                if(i == 5 && j == 1){
                    if(board[i][j] == board[i-2][j+2] && board[i][j] == board[i-4][j+4]){
                        if(board[i][j] == ' '){
                            return false;
                        }
                        else if(board[i][j] == 'X'){
                            *win = 'X';
                        }
                        else{
                            *win = 'O';
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}