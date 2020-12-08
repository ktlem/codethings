/* 'Path-game'
 *
 * Description:
 * This program generates a Path puzzle. The board is ROWS x COLUMNS (5x4),
 * and every round the player chooses a source point and a target point
 * (totally four numbers), making the given button to be moved to the target
 * position (if possible). The game checks if the user-given move can be made.
 *
 * At the start of the game,  all green buttons are on the top row, and all red buttons are on
 * the bottom row. Game will end when all green buttons have been moved to the
 * bottom row, and all red buttons to the top row. It is not allowed to move a
 * button over another button.
 *
 * When printing the game board, green button is represented by 'G', red
 * button by 'R', empty hole by 'o', and unused position by empty space.
 *
 * Program author
 * Name: Kristian Lempinen
 * Student number: H296236
 * UserID: sbkrle
 * E-Mail: kristian.lempinen@tuni.fi
 * Feedback language (fi/en): fi
 *
 * Notes about the program and it's implementation:
 * -
 * */

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

enum Slot_type {RED, GREEN, EMPTY, UNUSED};
const unsigned int ROWS = 5;
const unsigned int COLUMS = 4;

const string INPUT_TEXT = "Enter start point (x, y) and destination point (x, y), or q to quit: ";
const string INVALID_POINT = "Invalid start/destination point.";
const string CANNOT_MOVE = "There is no path between start point and destination point.";
const string GAME_OVER = "Game over. Congratulations!";
const string MOVES_MADE = " move(s) made.";

using Board_type = vector<vector<Slot_type>>;

// ---------------------------------

// Prints the current game board state.
void print(const vector < vector < Slot_type > >& g)
{
    cout << "===============" << endl;
    cout << "|   | 1 2 3 4 |" << endl;
    cout << "---------------" << endl;
    for(unsigned int i = 0; i < ROWS; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < COLUMS; ++j)
        {
            switch(g.at(i).at(j))
            {
            case GREEN: cout << "G "; break;
            case RED: cout << "R "; break;
            case EMPTY: cout << "o "; break;
            case UNUSED: cout << "  "; break;
            }
        }
        cout << "|" << endl;
    }
    cout << "===============" << endl;
}

// ---------------------------------

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}


// ---------------------------------

// Checks whether the game is won after each turn.
bool win_condition_met(Board_type gameBoard)

{
    if ( equal( gameBoard[0].begin() + 1, gameBoard[0].end(), gameBoard[0].begin() ) )
    {
        if ( equal( gameBoard[4].begin() + 1, gameBoard[4].end(), gameBoard[4].begin() ) )
            return true;
        else
            return false;
    }
    else
        return false;
}

// ---------------------------------


// Reads the user's input and converts it into a vector of integers.
// If any given token returns 0, the function returns a vector of insufficient size.
// Insufficient vector size is checked in the main function.
void read_coordinate_input(string inputCoordinates, vector<int>& coordinateVector)
{
    string delimiter = " ";

    size_t pos = 0;
    string token;

    while (( pos = inputCoordinates.find(delimiter)) != string::npos)
    {
        token = inputCoordinates.substr(0, pos);
        if ( stoi_with_check(token) == 0)
        {
            break;
        }
        else
        {
        coordinateVector.push_back(stoi_with_check(token));
        inputCoordinates.erase(0, pos + delimiter.length());
        }

    }
    coordinateVector.push_back(stoi_with_check(inputCoordinates));
}


// Checks whether movement on the y-axis is possible in either direction.
// Used as a support function within the primary movement functions.
bool y_check(Board_type gameBoard, int y_point, int target_value)

{
    y_point += 1;
    if ( y_point < target_value)
    {
        for ( int i = y_point; i < target_value; ++i)
        {
            if ( gameBoard[i][1] != EMPTY )
                return false;
            else
                return true;
        }
    }

    else if ( y_point > target_value)
    {
        y_point -= 2;
        for ( int i = y_point; i > target_value; --i)
        {
            if ( gameBoard[i][1] != EMPTY )
                return false;
        }
        return true;
    }
    else
    {
    return true;
    }

return false;
}


// Checks whether movement from start to the middle of the board is possible.
bool move_to_middle(Board_type gameBoard, vector<int> coordinateVector)

{
    int x_start = coordinateVector.at(0) - 1;
    int y_start = coordinateVector.at(1) - 1;

    if ( y_start == 2)
    {
        return true;
    }
    else if ( x_start > 1)
    {
        x_start -= 1;
        for ( int i = x_start; i > 1; --i)
        {
            if ( gameBoard[y_start][i] != EMPTY )
               return false;
        }
        if ( y_check( gameBoard, y_start, 2 ) )
            return true;
        else
            return false;
    }

    else if ( x_start < 1  )
    {
        x_start += 1;
        for ( int i = x_start; i < 1; ++i)
        {
            if ( gameBoard[y_start][i] != EMPTY )
               return false;
        }
        if ( y_check( gameBoard, y_start, 2 ) )
            return true;
        else
            return false;
    }
    else
    {
        if ( y_check( gameBoard, y_start, 2 ) )
            return true;
        else
            return false;
    }

}



// Checks whether movement from the middle of the board to the destination is possible.
bool move_from_middle_to_destination(Board_type gameBoard, vector<int> coordinateVector)

{
    int x_final = coordinateVector.at(2) - 1;
    int y_final = coordinateVector.at(3) - 1;

    if ( y_check( gameBoard, 2, y_final ) )
    {
        if ( x_final > 1)
        {
            for ( int i = x_final; i > 1; ++i)
            {
                if ( gameBoard[y_final][i] != EMPTY )
                   return false;
                else
                    return true;
            }
        }
        else if ( x_final < 1)
        {
            // x_final += 1;
            for ( int i = x_final; i < 1; --i)
            {
                if ( gameBoard[y_final][i] != EMPTY )
                   return false;
                else
                    return true;
            }
        }
        else
            return true;

    }
    else
        return false;

return false;
}


// ---------------------------------


int main()

{

Board_type gameBoard;
gameBoard = {{GREEN, GREEN, GREEN, GREEN}, {UNUSED, EMPTY, UNUSED, UNUSED},
             {UNUSED, EMPTY, EMPTY, UNUSED}, {UNUSED, EMPTY, UNUSED, UNUSED,},
             {RED, RED, RED, RED}};

bool is_game_over = false;
int move_count = 0;

print(gameBoard);

while ( is_game_over == false )
    {

    string inputCoordinates = "";
    cout << INPUT_TEXT;
    getline(cin, inputCoordinates);

    if ( inputCoordinates == "q" )
    {
        cout << move_count << " move(s) made." << endl;
        return EXIT_SUCCESS;
    }

    else
    {
        vector<int> coordinateVector;
        vector<int>::size_type length;

        read_coordinate_input(inputCoordinates, coordinateVector);
        length = coordinateVector.size();

        // Check for non-viable movement vector.
        if ( length != 4 )
        {
            cout << INVALID_POINT << endl;
        }
        else
        {

            int x_start = coordinateVector.at(0) - 1;
            int y_start = coordinateVector.at(1) - 1;

            int x_final = coordinateVector.at(2) - 1;
            int y_final = coordinateVector.at(3) - 1;

            Slot_type starting_point = gameBoard[ y_start ][ x_start ];
            Slot_type destination_point = gameBoard[ y_final ][ x_final ];

            // Check for non-viable coordinates.
             if ( starting_point == UNUSED or starting_point == EMPTY)
             {
                 cout << INVALID_POINT << endl;
             }

             else if ( destination_point == UNUSED or destination_point == GREEN or destination_point == RED )
             {
                 cout << INVALID_POINT << endl;
             }

             else
             {

                 // Check for non-viable moves.
                 if ( move_to_middle( gameBoard, coordinateVector ) )
                 {
                     if ( move_from_middle_to_destination( gameBoard, coordinateVector ) )
                     {
                         // Updating board status after a successful move.
                         gameBoard[ y_start ][ x_start ] = destination_point;
                         gameBoard[ y_final ][ x_final ] = starting_point;

                         ++move_count;
                         coordinateVector.clear();

                         // Check win condition.
                         is_game_over = win_condition_met(gameBoard);
                         print(gameBoard);
                     }

                     else
                         cout << CANNOT_MOVE<< endl;
                 }
                 else
                     cout << CANNOT_MOVE << endl;


             }
    }
    }
    }

    cout << GAME_OVER << endl;
    cout << move_count << MOVES_MADE << endl;
    return EXIT_SUCCESS;




    return 0;
}
