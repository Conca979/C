#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
//macros
#define Board_size 6          //can change it to make the board as big as players want, by the way size must be greater than 2 and even 
#define input_size 3          // dont change it!
//code a[97] -> f[102]
//code '_' = 95
//user's disc:     O code 79 (capital o)
//computer's disc: @ code 64
//global variables
const char user_c = 'O'; //user moves first so user's turn = even
const char comp_c = '@'; //computer's turn = odd

//defining functions
void introduction(char *replay_choice);
void display_board(char board[][Board_size]);
void board_reset(char board[][Board_size]);
bool valid_move_check(char board[][Board_size], char input[], int turn);
void reallocate_grid(char board[][Board_size], int current_row, int current_column, int turn);
unsigned int disc_counter(char board[][Board_size], char player);
bool valid_check(char board[][Board_size], int turn);
int valid_move_counter(char board[][Board_size], int turn);
void take_user_input(char input[input_size]);
void take_comp_input(char board[][Board_size], char input[input_size]);
void array_of_valid_moves(char board[][Board_size], int turn);
char **return_array_of_valid_moves(char board[][Board_size], int turn);
int **return_array_of_total_disc_eaten(char board[][Board_size], char **array_of_pointer_to_valid_moves, int number_of_valid_move, int turn);//unused yet
// void take_last_valid_move(char *input, char board[][Board_size], char *last_valid_move, int turn, int time);

//execution start
int main()
{
    char board[Board_size][Board_size] = {0};                   //display board after every input
    char again = 0;                                            //replay choice input
    char input[input_size];                                             //input form user or comp?
    introduction(&again);
    board_reset(board);
    printf("====================\n");
    int i=0;
    while(valid_check(board, i)||valid_check(board, i+1))
    {
        srand(time(NULL));
        if(!valid_check(board, i))
        {
            printf("<there is no valid move for %s, so %s's turn is prioritized>", (i%2==0?"user":"computer"), ((i+1)%2==0?"user":"computer"));
            i++;
        }
        do
        {
            display_board(board);
            printf("[user's disc = %d]\n[computer's disc = %d]\n", disc_counter(board, user_c), disc_counter(board, comp_c));
            printf("%s\'s turn - %c - %d ", (i%2==0?"user":"computer"), (i%2==0?'O':'@'), valid_move_counter(board, i));
            array_of_valid_moves(board, i);
            if(i%2==1)
            {
                take_comp_input(board, input);
                printf("Move decision: \"%s\"", input);
            }
            else
            {
                take_user_input(input);
                printf("Move decision: \"%s\"", input);
            }
        } while (!valid_move_check(board, input, i)); //if invalid, ask again, if input valid then stop
        reallocate_grid(board, (int)(input[0]-'1'), (int)(input[1]-'a'), i);
        i++;
    }
    display_board(board);
    printf("#SUMMURISE\n[user's disc = %d]\n[computer's disc = %d]\n", disc_counter(board, user_c), disc_counter(board, comp_c));
    if(disc_counter(board, user_c)>disc_counter(board, comp_c))
    {
        printf("THE WINNER IS: user");
    } else if (disc_counter(board, user_c)<disc_counter(board, comp_c)) printf("THE WINNER IS: computer");
    else printf("Tie!!");

    return 0;
}

void introduction(char *replay_choice)
{
    printf("----REVERSI----\n");
    printf("You can go first on the first game, then we will take turns.\n");
    printf(" You will be white - (%c)\n I will be black - (%c).\n", user_c, comp_c);
    printf("Select a square for your move by typing a digit for the row and a lettter for the column with no spaces between!\n");
    printf("\nGood luck! Press Enter to start.\n");
    scanf("%c", replay_choice);
    fflush(stdin);                                      //clear the buffer for the next input
}

void board_reset(char board[][Board_size])
{
    for(int row=0; row<Board_size; row++)
    {
        for(int column=0; column<Board_size; column++)
        {
            board[row][column] = '_';
        }
    }
    int middle = Board_size/2-1;
    board[middle][middle] = board[middle+1][middle+1] = user_c;
    board[middle+1][middle] = board[middle][middle+1] = comp_c;
}

void display_board(char board[][Board_size])
{
    printf("\n    ");
    for(int i=0; i<Board_size; i++)
    {
        printf(" %c ", (char)(i+97));
    }
    printf("\n");
    for(int i=0; i<Board_size; i++)
    {
        printf("%3d ", i+1);
        for(int j=0; j<Board_size; j++)
        {
            printf("|%c|", board[i][j]);
        }
        printf("\n");
    }
}

bool valid_move_check(char board[][Board_size], char input[], int turn)
{
    int reference_row = 0;
    int reference_column = 0;
    char opponent = (turn%2==1?user_c:comp_c);
    // printf("input = \"%s\"\n", input);
    // printf("Test: (char)input[0]-49 = %d\n(int)input[1]-97 = %d\n", (char)input[0]-49, (int)input[1]-97);
    //set all grid to false before checking
    bool valid_moves[Board_size][Board_size] = {false};
    for(int row=0; row<Board_size; row++)
    {
        for(int column=0; column<Board_size; column++)
        {
            valid_moves[row][column] = false;
        }
    }
    //check if valid
    for(int row = 0; row<Board_size; row++ )    
    {
        for(int column = 0; column<Board_size; column++)
        {
            if(board[row][column]!='_') //if not black -> skip
            {
                continue;
            }
            for(int rowdelta = -1; rowdelta<=1; rowdelta++)
            {
                for(int columndelta = -1; columndelta<=1; columndelta++)
                {
                    if(  (row+rowdelta)<0||(row+rowdelta)>=Board_size||
                         (column+columndelta)<0||(column+columndelta)>=Board_size||
                         (rowdelta == 0 && columndelta ==0) ) //check if reference grid out of bound
                         {
                            continue;
                         }
                    reference_row = row + rowdelta;             //set the reference grid following the current gird
                    reference_column = column + columndelta;
                    if(board[reference_row][reference_column] == opponent) //if opponent counter found
                    {
                        for(;;)
                        {
                            reference_row += rowdelta;          //checking along that direction
                            reference_column += columndelta;
                            //if along that direction is out of bound or found blank -> skip
                            if(reference_row<0||reference_row>=Board_size||reference_column<0||reference_column>=Board_size||(board[reference_row][reference_column]=='_'))
                            {
                                break;
                            }
                            if(board[reference_row][reference_column]==(opponent==comp_c?user_c:comp_c)) //if found our counter -> valid move
                            {
                                valid_moves[row][column]=true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return valid_moves[input[0]-'1'][input[1]-'a'];
}

void reallocate_grid(char board[][Board_size], int current_row, int current_column, int turn)
{
    int reference_row = 0;
    int reference_column = 0;
    // char opponent = comp_c;
    char opponent = (turn%2==1?user_c:comp_c);
    board[current_row][current_column] = user_c;
    for(int rowdelta = -1; rowdelta<=1; rowdelta++)
    {
        for(int columndelta = -1; columndelta<=1; columndelta++)
        {
            if(  (current_row+rowdelta)<0||(current_row+rowdelta)>=Board_size||
                    (current_column+columndelta)<0||(current_column+columndelta)>=Board_size||
                    (rowdelta == 0 && columndelta ==0) ) //check if reference grid out of bound
                    {
                    continue;
                    }
            reference_row = current_row + rowdelta;             //set the reference grid following the current gird
            reference_column = current_column + columndelta;
            int shift_counter = 1;
            if(board[reference_row][reference_column] == opponent) //if opponent counter found
            {
                for(;;)
                {
                    reference_row += rowdelta;          //checking along that direction
                    reference_column += columndelta;
                    shift_counter++;
                    //if along that direction is out of bound or found blank -> skip
                    if(reference_row<0||reference_row>=Board_size||reference_column<0||reference_column>=Board_size||(board[reference_row][reference_column]=='_'))
                    {
                        break;
                    }
                    if(board[reference_row][reference_column]==(opponent==comp_c?user_c:comp_c)) //if found our counter -> valid move
                    {
                        for(int i=0; i<shift_counter; i++)
                        {
                            board[current_row+i*rowdelta][current_column+i*columndelta] = (opponent==comp_c?user_c:comp_c);
                        }
                        break;
                    }
                }
            }
        }
    }
}

unsigned int disc_counter(char board[][Board_size], char player)
{
    unsigned int count = 0;
    for(int i=0; i<Board_size; i++)
    {
        for(int j=0; j<Board_size; j++)
        {
            if(board[i][j]==player)
                count++;
        }
    }
    return count;
}

bool valid_check(char board[][Board_size], int turn)
{
    char dummy_input[] = "1a";
    int reference_row = 0;
    int reference_column = 0;
    char opponent = (turn%2==1?user_c:comp_c);
    int valid_move_count = 0;
    //set all grid to false before checking
    bool valid_moves[Board_size][Board_size] = {false};
    //check if valid
    for(int row = 0; row<Board_size && !valid_move_count; row++ )    
    {
        for(int column = 0; column<Board_size && !valid_move_count; column++)
        {
            if(board[row][column]!='_') //if not black -> skip
            {
                continue;
            }
            for(int rowdelta = -1; rowdelta<=1 && !valid_move_count; rowdelta++)
            {
                for(int columndelta = -1; columndelta<=1 && !valid_move_count; columndelta++)
                {
                    if(  (row+rowdelta)<0||(row+rowdelta)>=Board_size||
                         (column+columndelta)<0||(column+columndelta)>=Board_size||
                         (rowdelta == 0 && columndelta ==0) ) //check if reference grid out of bound
                         {
                            continue;
                         }
                    reference_row = row + rowdelta;             //set the reference grid following the current gird
                    reference_column = column + columndelta;
                    if(board[reference_row][reference_column] == opponent) //if opponent counter found
                    {
                        for(;!valid_move_count;)
                        {
                            reference_row += rowdelta;          //checking along that direction
                            reference_column += columndelta;
                            //if along that direction is out of bound or found blank -> skip
                            if(reference_row<0||reference_row>=Board_size||reference_column<0||reference_column>=Board_size||(board[reference_row][reference_column]=='_'))
                            {
                                break;
                            }
                            if(board[reference_row][reference_column]==(opponent==comp_c?user_c:comp_c)) //if found our counter -> valid move
                            {
                                valid_move_count++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if(valid_move_count==0)
    {
        return false;
    }
    else return true;
}

void take_user_input(char input[input_size])
{
    printf("\nEnter input: ");
    fgets(input, input_size, stdin);
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

void take_comp_input(char board[][Board_size], char input[input_size])
{
    char opponent = user_c; //computer turn always 1 - odd
    int number_of_valid_move = valid_move_counter(board, 1);
    char **valid_move = return_array_of_valid_moves(board, 1);
    int **eaten_disc_count = return_array_of_total_disc_eaten(board, valid_move, number_of_valid_move, 1);
    int max = eaten_disc_count[0][0];
    int position = 0;
    for(int i=1; i<number_of_valid_move; i++)
    {
        if((*eaten_disc_count[i])>max)
        {
            max = *eaten_disc_count[i];
            position = i;
        }
        else if((*eaten_disc_count[i])==max)
        {
            if((rand()%2) == 1)
            {
                max = *eaten_disc_count[i];
                position = i;
            }
        }
    }
    strcpy(input, valid_move[position]);
}

void array_of_valid_moves(char board[][Board_size], int turn)
{
    int number_of_valid_move = valid_move_counter(board, turn);
    char **valid_move = return_array_of_valid_moves(board,turn);//array of pointers
    int **disc_eaten = return_array_of_total_disc_eaten(board, valid_move, number_of_valid_move, turn);
    printf("valid move%c: ", number_of_valid_move==0?'!':(number_of_valid_move==1?:'s'));
    for(int i=0; i<number_of_valid_move; i++)
    {
        printf("-[%s][%d]-", valid_move[i], *disc_eaten[i]);
    }
}

int valid_move_counter(char board[][Board_size], int turn)
{
    int reference_row = 0;
    int reference_column = 0;
    char opponent = (turn%2==1?user_c:comp_c);
    int valid_move_count = 0;
    bool valid = false;
    //check if valid
    for(int row = 0; row<Board_size ; row++ )    
    {
        for(int column = 0; column<Board_size; column++)
        {
            if(board[row][column]!='_') //if not black -> skip
            {
                continue;
            }
            for(int rowdelta = -1; rowdelta<=1 && !valid; rowdelta++)
            {
                for(int columndelta = -1; columndelta<=1 && !valid; columndelta++)
                {
                    if(  (row+rowdelta)<0||(row+rowdelta)>=Board_size||
                         (column+columndelta)<0||(column+columndelta)>=Board_size||
                         (rowdelta == 0 && columndelta ==0) ) //check if reference grid out of bound
                         {
                            continue;
                         }
                    reference_row = row + rowdelta;             //set the reference grid following the current gird
                    reference_column = column + columndelta;
                    if(board[reference_row][reference_column] == opponent) //if opponent counter found
                    {
                        for(;!valid;)
                        {
                            reference_row += rowdelta;          //checking along that direction
                            reference_column += columndelta;
                            //if along that direction is out of bound or found blank -> skip
                            if(reference_row<0||reference_row>=Board_size||reference_column<0||reference_column>=Board_size||(board[reference_row][reference_column]=='_'))
                            {
                                break;
                            }
                            if(board[reference_row][reference_column]==(opponent==comp_c?user_c:comp_c)) //if found our counter -> valid move
                            {
                                valid = true;
                                break;
                            }
                        }
                    }
                }
            }
            if(valid) 
                valid_move_count++;
                valid = false;
        }
    }
    return valid_move_count;
}

char **return_array_of_valid_moves(char board[][Board_size], int turn)
{
    int reference_row = 0;
    int reference_column = 0;
    char opponent = (turn%2==1?user_c:comp_c);
    int number_of_valid_move = valid_move_counter(board, turn);
    char **array_of_valid_moves = calloc(number_of_valid_move, sizeof(char*));
    int indexing = 0;
    bool valid = false;
    //check if valid
    for(int row = 0; row<Board_size && indexing<number_of_valid_move; row++ )    
    {
        for(int column = 0; column<Board_size && indexing<number_of_valid_move; column++)
        {
            if(board[row][column]!='_') //if not black -> skip
            {
                continue;
            }
            for(int rowdelta = -1; rowdelta<=1 && !valid; rowdelta++)
            {
                for(int columndelta = -1; columndelta<=1 && !valid; columndelta++)
                {
                    if(  (row+rowdelta)<0||(row+rowdelta)>=Board_size||
                         (column+columndelta)<0||(column+columndelta)>=Board_size||
                         (rowdelta == 0 && columndelta ==0) ) //check if reference grid out of bound
                         {
                            continue;
                         }
                    reference_row = row + rowdelta;  //set the reference grid following the current gird
                    reference_column = column + columndelta;
                    if(board[reference_row][reference_column] == opponent) //if opponent counter found
                    {
                        for(;!valid;)
                        {
                            reference_row += rowdelta;          //checking along that direction
                            reference_column += columndelta;
                            //if along that direction is out of bound or found blank -> skip
                            if(reference_row<0||reference_row>=Board_size||reference_column<0||reference_column>=Board_size||(board[reference_row][reference_column]=='_'))
                            {
                                break;
                            }
                            if(board[reference_row][reference_column]==(opponent==comp_c?user_c:comp_c)) //if found our counter -> valid move
                            {
                                valid = true;
                                break;
                            }
                        }
                    }
                }
            }
            if(valid)
            {
                array_of_valid_moves[indexing] = calloc(input_size, sizeof(char));
                array_of_valid_moves[indexing][0] = (char)(row+'1');
                array_of_valid_moves[indexing][1] = (char)(column+'a');
                array_of_valid_moves[indexing][2] = '\0';
                valid = false;
                indexing++;
            }
        }
    }
    return array_of_valid_moves;
}

int **return_array_of_total_disc_eaten(char board[][Board_size], char **array_of_pointer_to_valid_moves, int number_of_valid_move, int turn)
{
    int reference_row = 0;
    int reference_column = 0;
    char opponent = (turn%2==1?user_c:comp_c);
    int **array_of_pointer_to_int = calloc(number_of_valid_move, sizeof(int**));
    //check if valid
    for(int i=0; i<number_of_valid_move; i++)
    {
        int disc_eaten = 0;
        int row = (int)(array_of_pointer_to_valid_moves[i][0]-'1');
        int column = (int)(array_of_pointer_to_valid_moves[i][1]-'a');
        for(int rowdelta = -1; rowdelta<=1; rowdelta++)
        {
            for(int columndelta = -1; columndelta<=1; columndelta++)
            {
                int temp_disc_eaten = 0;
                if(  (row+rowdelta)<0||(row+rowdelta)>=Board_size||
                        (column+columndelta)<0||(column+columndelta)>=Board_size||
                        (rowdelta == 0 && columndelta ==0) ) //check if reference grid out of bound
                        {
                        continue;
                        }
                reference_row = row + rowdelta;             //set the reference grid following the current gird in the delta direction
                reference_column = column + columndelta;
                if(board[reference_row][reference_column] == opponent) //if opponent counter found
                {
                    for(;;)
                    {
                        temp_disc_eaten++;
                        reference_row += rowdelta;          //checking along that direction
                        reference_column += columndelta;
                        //if along that direction is out of bound or found blank -> skip
                        if(reference_row<0||reference_row>=Board_size||reference_column<0||reference_column>=Board_size||(board[reference_row][reference_column]=='_'))
                        {
                            break;
                        }
                        if(board[reference_row][reference_column]==(opponent==comp_c?user_c:comp_c)) //if found our counter -> valid move
                        {
                            disc_eaten += temp_disc_eaten;
                            break;
                        }
                    }
                }
            }
        }
        array_of_pointer_to_int[i] = calloc(1, sizeof(int));
        *array_of_pointer_to_int[i] = disc_eaten;
    }
    return array_of_pointer_to_int;
}