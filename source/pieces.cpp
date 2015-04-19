#include<iostream>
#include "pieces.h"
#include "input.h"
#include<string>
#include<stdlib.h>
#include<array>
using namespace std;

int * location = nullptr;
bool rookLeftMoved_White=false;
bool rookRightMoved_White=false;
bool rookLeftMoved_Black=false;
bool rookRightMoved_Black=false;
bool kingMoves_White=false;
bool kingMoves_Black=false;

//--------------------------------------------//
// a general function made to exchange the values of two pointers given any two pointers

void piece::exchange(int * t1 , int * t2)
{
    int temp;
    temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}


//--------------------------------------------//

// A general function which evaluates whether a move can be made or no, irrespective of the 'check' condition. Hence, this function does not take into consideration the legality of the move. Returns true, if by general rules of Chess the move can made, disregarding its legality. Else it returns false.
// The function takes two pointer arguments namely, the initial location and the final location
// Dereferencing the initial location, the 'type' of piece can be obtained. This function identifies the type of the piece and hence evaluates if a move to the specified final location can be made with the given type of piece.
/* Variables used:
    Arguments: int *location1 : corresponds to initial location
                int * location2 : corresponds to final location
    Defined in the function definition:
                bool move_valid: the main evaluating boolean variable. Takes either true or false in different move scenarios
                long variator1 : gives the index of the initial position in the two dimensional array
                long variator2 : gives the index of the final position in the two dimensional array
                long location_diff: gives the absolute value of the differences in the indices of the the initial and the final locations
                int i,j,k : iterators
 */

bool piece::move(int * location1 , int * location2)       //a function taking initial and final
// locations of piece and input command
{
    bool move_valid=false;                  //bool variable checking if move is valid
    long variator1 = location1-location;
    long variator2 = location2-location;
    long location_diff = abs(location1 - location2);

    if(*location1 == 0)     // if no piece on the initial location(while running checkmate)
    {
        move_valid = false;
    }

    else if((*location1>0 && *location2>0) || (*location1<0 && *location2<0) )     //checking if final position doesnt have a piece of the same colour
    {
        move_valid = false;
    }

    else if(location1==location2)
    {
        move_valid=false;
    }
    else
    {
        // for rook

        if(abs(*location1)==2)        //checking for same row or column
        {
            if((location_diff)%8 == 0)
            {
                if((location_diff)==8)
                {
                    move_valid=true;
                }
                else if(location1>location2)
                {
                    int k=1;
                    do
                    {
                        if((*(location1-8*k))==0)//all places in between the inital and
                            //final
                        {
                            move_valid = true;
                        }

                        else move_valid= false;
                        ++k;

                    }while(move_valid && k<(location_diff/8));
                }

                else
                {
                    int k=1;
                    do
                    {
                        if((*(location1+8*k))==0)//all places in between the initial and final position
                        {
                            move_valid = true;
                        }

                        else move_valid= false;
                        ++k;

                    }while(move_valid && k<(location_diff/8));
                }
            }
            else if(location_diff/8==0 && (variator1)/8 == (variator2)/8)  //checking column
            {
                if((location_diff)==1) move_valid=true;

                else if(location1 > location2){
                    int k=1;
                    do{
                        if((*(location1-k))==0) //all places in between the initial and final
                        {
                            move_valid = true;
                        }

                        else move_valid = false;
                        ++k;
                    }while(move_valid && k<(location_diff));
                }

                else{
                    int k=1;
                    do{
                        if((*(location1+k))==0) //all places in between the initial and final
                        {
                            move_valid = true;
                        }

                        else move_valid = false;
                        ++k;
                    }while(move_valid && k<(location_diff));

                }
            }
        }

        //for bishop

        if(abs(*location1)==4)              // checking 4 conditions : 4 directions in 2D

        {
            if((abs(location1-location2))==9 || (abs(location2-location1))==7) move_valid=true;

            else if(location_diff%9==0 && (location1) < location2 && (variator2 - (location_diff/9))==variator1+(location_diff/9)*8)     //-45 deg to x axis

            {
                int k =1;
                do{
                    if((*(location1 + 9*k))==0)
                    {
                        move_valid=true;
                    }
                    else move_valid=false;

                    ++k;

                }while(move_valid && k<abs(location1-location2)/9);

            }

            else if(location_diff % 9==0 && (location1) > location2  && (variator2 + (abs(location1-location2)/9))==variator1-(location_diff/9)*8)    //180-45 deg

            {
                int k =1;
                do{
                    if((*(location1 - 9*k))==0)
                    {
                        move_valid=true;
                    }
                    else move_valid=false;

                    ++k;

                }while(move_valid && k<location_diff/9);

            }



            else if(location_diff%7==0 && (location1) < location2  && (variator2 + (location_diff/7)) ==variator1+(location_diff/7)*8)     // 180+45 deg

            {
                int k =1;
                do{
                    if((*(location1 + 7*k))==0)
                    {
                        move_valid=true;
                    }
                    else move_valid=false;

                    ++k;

                }while(move_valid && k<location_diff/7);
            }


            else if(location_diff%7==0 && location1 > location2  && (variator2 - (location_diff/7))==variator1-(location_diff/7)*8)    //45 deg

            {
                int k =1;
                do{
                    if((*(location1 - 7*k))==0)
                    {
                        move_valid=true;
                    }
                    else move_valid=false;

                    ++k;

                }while(move_valid && k<(location_diff)/7);
            }
        }

 // Queen's moves : Combination of Rook and Bishop
        if(abs(*location1)==10)

        {
            //testing for rook

            if((location_diff)%8 == 0)   //checking for same row or column
            {
                if((location_diff)==8)
                {
                    move_valid=true;
                }
                else if(location1>location2){
                    int k=1;
                    do
                    {
                        if((*(location1-8*k))==0)//all places in between the inital and
                            //final
                        {
                            move_valid = true;
                        }

                        else move_valid= false;
                        ++k;

                    }while(move_valid && k<(location_diff/8));
                }

                else
                {
                    int k=1;
                    do
                    {
                        if((*(location1+8*k))==0)//all places in between the inital and
                            //final
                        {
                            move_valid = true;
                        }

                        else move_valid= false;
                        ++k;

                    }while(move_valid && k<(location_diff/8));
                }
            }
            else if(location_diff/8==0 && (variator1)/8 == (variator2)/8)  //checking column
            {
                if((location_diff)==1) move_valid=true;

                else if(location1 > location2){
                    int k=1;
                    do{
                        if((*(location1-k))==0) //all places in between the initial and final
                        {
                            move_valid = true;
                        }

                        else move_valid = false;
                        ++k;
                    }while(move_valid && k<(location_diff));
                }

                else{
                    int k=1;
                    do{
                        if((*(location1+k))==0) //all places in between the initial and final
                        {
                            move_valid = true;
                        }

                        else move_valid = false;
                        ++k;
                    }while(move_valid && k<(location_diff));

                }
            }


            // testing for bishop

            // checking 4 conditions : 4 directions in 2D

            if((abs(location1-location2))==9 || (abs(location2-location1))==7) move_valid=true;

            else if(location_diff%9==0 && (location1) < location2 && (variator2 - (location_diff/9))==variator1+(location_diff/9)*8)     //-45 deg to x axis

            {
                int k =1;
                do{
                    if((*(location1 + 9*k))==0)
                    {
                        move_valid=true;
                    }
                    else move_valid=false;

                    ++k;

                }while(move_valid && k<abs(location1-location2)/9);

            }

            else if(location_diff % 9==0 && (location1) > location2  && (variator2 + (abs(location1-location2)/9))==variator1-(location_diff/9)*8)    //180-45 deg

            {
                int k =1;
                do{
                    if((*(location1 - 9*k))==0)
                    {
                        move_valid=true;
                    }
                    else move_valid=false;

                    ++k;

                }while(move_valid && k<location_diff/9);

            }



            else if(location_diff%7==0 && (location1) < location2  && (variator2 + (location_diff/7)) ==variator1+(location_diff/7)*8)     // 180+45 deg

            {
                int k =1;
                do{
                    if((*(location1 + 7*k))==0)
                    {
                        move_valid=true;
                    }
                    else move_valid=false;

                    ++k;

                }while(move_valid && k<location_diff/7);
            }


            else if(location_diff%7==0 && location1 > location2  && (variator2 - (location_diff/7))==variator1-(location_diff/7)*8)    //45 deg

            {
                int k =1;
                do{
                    if((*(location1 - 7*k))==0)
                    {
                        move_valid=true;
                    }
                    else move_valid=false;

                    ++k;

                }while(move_valid && k<(location_diff)/7);
            }



        }

        if(*(location1)==1)     // for white pawns
        {
            if(location2==location1+8 && (*(location2))==0) move_valid=true;

            else if(location2 == location1+16 && *(location2)==0 && *(location1+8)==0 && ((location1 == location+8) || location1 == location+9 || location1 == location + 10 || location1 == location + 11 || location1 == location+ 12 || location1 == location+13 || location1 == location+14 || location1 == location+15))
            {
                move_valid=true;
            }

            else if(*location2<0 && (location2 ==location1 + 7 || location2 == location1 + 9))
            {
                if ((variator1)%8 == 7 && location_diff == 9) {
                    move_valid = false;
                }
                else    move_valid=true;
            }
        }

        if(*(location1)==-1)        //for black pawns
        {
            if(location2==location1-8 && (*(location2))==0) move_valid=true;

            else if(location2 == location1-16 && (*(location2))==0 && (*(location1-8))==0 && ((location1 == location+63-8) || location1 == location+63-9 || location1 == location+63-10 || location1 == location+63-11 || location1 == location+63-12 || location1 == location+63-13 || location1 == location+63-14 || location1 == location+63-15))
            {
                move_valid=true;
            }

            else if((*location2)>0 && (location2 ==location1-7 || location2 == location1-9))
            {
                if ((variator1)%8 == 0 && location_diff == 9)
                {
                    move_valid = false;
                }

                else   move_valid=true;
            }

            else move_valid=false;
        }

    }

    if((abs(*location1))==99)     //for king
    {
        if(castle(location1, location2))
        {
            return true;
        }

        else if((abs(location1 - location2))==1 || (abs(location1 - location2)) == 8 || (abs(location1 - location2))==7 || (abs(location1 - location2))==9)
        {

            if((*location2 < 0 && * location1 > 0) || (*location2 > 0 && *location1 < 0))
            {
                //kill is true and lets assume move is true
                int temp = *location2;
                change(location1, location2, true, true);

                //after moving the king , looking at all 6 squares around and checking for the presence of king of the opposite colour. If other king is present, returns false and resets positions. Else returns true and resets positions

                if(abs(*(location2+1))!=99 && abs(*(location2-1))!=99 && abs(*(location2+8))!=99 && abs(*(location2-8))!=99 && abs(*(location2+7))!=99 && abs(*(location2-7))!=99 && abs(*(location2+9))!=99 && abs(*(location2-9))!=99 )
                {
                    move_valid=true;
                    exchange(location1, location2);
                    *location2 = temp;
                }

                else
                {
                    move_valid=false;
                    exchange(location1, location2);
                    *location2 = temp;
                }

            }

            else if(*location2 == 0)
            {
                change(location1, location2, false, true);
                if(abs(*(location2+1))!=99 && abs(*(location2-1))!=99 && abs(*(location2+8))!=99 && abs(*(location2-8))!=99 && abs(*(location2+7))!=99 && abs(*(location2-7))!=99 && abs(*(location2+9))!=99 && abs(*(location2-9))!=99)
                {
                    move_valid=true;
                    exchange(location1, location2);
                }

                else
                {
                    move_valid=false;
                    exchange(location1, location2);

                }

            }
        }
        else move_valid = false;
    }

    if((abs(*location1))==3)               // for knight
    {
        if((abs(location2-location1))==6)
        {
            move_valid=true;
        }

        else if((abs(location2-location1))==10)
        {
            move_valid=true;
        }

        else if((abs(location2-location1))==15)
        {
            move_valid=true;
        }
        else if((abs(location2-location1))==17)
        {
            move_valid=true;
        }
    }

    return move_valid;
}

//--------------------------------------------//

// A general function to see if a kill can be made or no. Similar to the move_valid function, the kill function takes in two pointer arguements and also one move_valid argument. The pointer arguements have the same use.
// The move_valid arguement is not exactly necessary. It can be computed inside the function definition as well. However, in the main function , the computation of move_valid is essential. Hence, in order to reduce function calls , the same computed boolean value is used as an arguement in the kill function
/*
    Variables used:
            Arguments:  int * location1 : initial position of the piece
                        int * location2 : final position of the piece
                        bool move_valid : gives if the move can be made or no disregarding the legality of the move. Computed inside the main function using the above move function.
 */


bool piece::kill(bool move_valid ,int * location1, int * location2)
{
    if(move_valid==false)
    {
        return false;
    }

    else
    {
        if((*location1>0 && *location2<0)||(*location1<0 && *location2>0))
        {
            return true;
        }

        else
        {
            return false;
        }
    }
}

//--------------------------------------------//

// A general location to change positions. This function is different from exchange as it takes into account killing of pieces. In order to carry the functionality, this function calls the exchange function
// It takes four arguments. The two pointer arguments namely , location1 and location2 have same uses. It also takes into consideration if a kill can be made or no. If a kill is made, it makes appropriate changes in the chessboard. move_valid has to be true in order for any changes to happen on the board. If move_valid is false, this function makes no change on the board.
/*
    Variables used:
            Arguments:  int * location1 : initial position of the piece
                        int * location2 : final position of the piece
                        bool kill_piece : indicates if a kill can be made or no
                        bool move_valid : indicates if a move can be made or no
*/

void piece::change(int * location1 , int * location2 , bool kill_piece , bool move_valid)
//different modifications when kill and when no kill
{
    if(move_valid == true)
    {
        if(!kill_piece)
        {
            exchange(location1 , location2);
        }

        else
        {
            exchange(location1 , location2);
            *location1 = 0;
        }
    }

}

//--------------------------------------------//

// A general function checking the legality of a move. Can be regarded as the most important function of the game. Takes two pointer arguements namely location1 and location2 having the same uses. Another arguement is a pointer to a pointer. Basically gives an array of pointers. This array stores the locations of all pieces of the opposite colour. Length gives the length of this array
/*
    Variables used:
            Arguments:  int * location1 : initial position of the piece.
                        int * location2 : final position of the piece.
                        int ** store_pointer_other : positions of all pieces of the opposite colour.
                        int length : number of opponent pieces.
            Defined inside the function definition:
                        bool move_initial : uses the move function defined above. Disregarding the legality , determines if the move can be made.
                        bool kill_initial : uses the kill function defined above. Disregarding the legality, determines if a kill or capture can be made or no.
                        bool castle_check : uses the castle function defined further below. Determines if castling is performed or no.
                        int killed_piece : if a kill is made , identifies the 'type' of the piece that is killed . Is used in further resetting the board.
                        bool no_check : Uses the check_present function defined further below. Determines if after making the moves , a 'check' condition is incurred or no.
                        int * locationKing : Used to find out the position of the king in order to evaluate the 'check' conditon.

 */


bool piece::check_escape(int * location1, int * location2, int * store_pointer_other[], int length)
{
    // store_pointer_other stores the locations of all pieces of the opponent

    bool no_check=true , kill_initial , move_initial, castle_check;

    // move initial checks if the move from location1 to location2 can be made
    //kill initial checks if moveinitial==true, then if a kill can be made or no

    int killed_piece = 0;

    int * locationKing=nullptr;

    move_initial=move(location1, location2);
    if (castle(location1, location2))
    {
        castle_check=true;
    }

    else
    {
        castle_check = false;
    }

    if(move_initial)
    {
        kill_initial = kill(move_initial, location1, location2);
        if(kill_initial)
        {
            killed_piece = *location2;              // the piece that gets killed (located at location2)
        }
        make_move(location1, location2);       //moves the piece from location1 to location2

        if(*location2 > 0)  locationKing = location + searchWhiteKing();
        else locationKing = location + searchBlackKing();

        no_check = !(check_present(locationKing , store_pointer_other, length));  //verifies that in the new positon if there is a check or no

        //resets to the original position
        if(!castle_check)
        {
            if(!kill_initial)
            {
                exchange(location1, location2);
            }

            else if(kill_initial)
            {
                exchange(location1, location2);
                *location2=killed_piece;
            }
        }

        else
        {
            if (location2 == location + 6)
            {
                exchange(location1, location2);
                exchange(location2 + 1, location2 - 1);
                rookRightMoved_White=false;
                kingMoves_White=false;
            }

            else if (location2 == location + 2)
            {
                exchange(location1, location2);
                exchange(location2 - 2, location2 + 1);
                rookLeftMoved_White=false;
                kingMoves_White=false;
            }

            else if (location2 == location + 62)
            {
                exchange(location1, location2);
                exchange(location2 + 1, location2 - 1);
                rookRightMoved_Black=false;
                kingMoves_Black=false;
            }

            else if (location2 == location + 58)
            {
                exchange(location1, location2);
                exchange(location2 - 2, location2 + 1);
                rookLeftMoved_Black=false;
                kingMoves_Black=false;
            }

        }


            return no_check;            //if no_check=true , the move from location1 to location2 is legal
        // else the move is illegal

    }

    else
    {
        if ((*location1) == 99)
                cout<<"Zero";
        return 0;
    }

    //the move is determined as illegal if move is invalid in the first place
}

//--------------------------------------------//

// A general function used to determine for the ultimate 'Checkmate' or 'Stalemate' condition. Named as checkmate as 'checkmate' is a frequently occured condition. Uses four arguements.
// When already under 'check' and checkmate gives true, then the condition is 'checkmate' and game is over. The colour under 'check' loses. When NOT under 'check' and checkmate gives true, then the condition is 'stalemate' and the game is draw.
// This function is based on the concept that no legal moves are available for a player.
/*
    Variables Used:
            Arguments:  int ** store_pointer_sameColour :  stores the locations of all the playing        pieces of the same colour(i.e. the colour of the player who is playing).
                        int length_sameColour: number of pieces available(same colour).
                        int ** store_pointer_otherColour : stores the locations of all the playing pieces of the other colour(i.e. the pieces of the opponent).
                        int length_otherColour : number of pieces available(other colour).
            Defined inside the function definition :
                        int * any_location : a kind of iterator used to obtain all locations on the chessboard one by one.
                        bool no_check : determines whether a 'check' is present or no after making the move
 */


bool piece::checkmate(int * store_pointer_sameColour[], int length_sameColour, int * store_pointer_otherColour[] , int length_otherColour)
{
    //suppose white is playing(sameColour)
    //white gives a check to black(otherColour)
    //now i check if no move of black is legal

    int * any_location=nullptr;             //gives the locations of all pieces on the chessboard
    bool no_check;

    // for any move of opposite colour, confirm that the 'check' condition is retained ie. no legal moves are possible

    for(int j=0;j<length_otherColour;j++)
    {
        for(int k=0;k<64;k++)
        {
            any_location=location+k;            //any postion on the chessboard
            no_check = check_escape(store_pointer_otherColour[j], any_location, store_pointer_sameColour, length_sameColour);
            if(no_check)            // if no_check==true, the move is legal and hence no checkmate
            {
                return false;
            }

        }
    }

    return true;

}

//--------------------------------------------//



// A function used to determine if a 'check' is present in that board condition.
// Basically checks in the king is under threat by any opponent piece, i.e. if the king can be killed by any opponent piece
/*
    Variables Used:
            Arguements : int * locationOfKingSameColour : a pointer variable giving the position of the king of the player for whom we are checking for a 'check'
                        int ** store_pointer_otherColour : a pointer to an array that stores the positions of all available pieces of the opponent.
                        int length : gives the number of available pieces of the opponent
 */

bool piece::check_present(int * locationOfKingSameColour , int * store_pointer_otherColour[],int length)
{

    for(int k=0; k<length ; k++)
    {
        bool move_valid = move(store_pointer_otherColour[k], locationOfKingSameColour);
        if(move_valid==false)
        {
            continue;
        }
        else
        {
            if(kill(move_valid, store_pointer_otherColour[k], locationOfKingSameColour))
            {
                return true;
            }
            else continue;
        }
    }

    return false;
}


//--------------------------------------------//

// A general function that actually makes the move from one position to the other after considerationf of all factors
/*
    Variables used :
            Arguements : int * location1 : initial position of the piece.
                         int * location2 : final position of the piece.
            Defined inside the function definition:
                        bool move_valid : Same use as all above move_valid.
                        bool kill_piece : Same use as all above kill_piece.
*/


void piece::make_move(int * location1  , int * location2)
{

    bool move_valid= move(location1, location2);
    bool kill_piece = kill(move_valid,location1, location2);
    if (castle(location1, location2))
    {
        if (location2 == location + 6)
        {
            exchange(location1, location2);
            exchange(location2 + 1, location2 - 1);
            rookRightMoved_White=true;
            kingMoves_White=true;
        }

        else if (location2 == location + 2)
        {
            change(location1, location2, false, true);
            change(location2 - 2, location2+1, false, true);
            rookLeftMoved_White=true;
            kingMoves_White=true;
        }

        else if (location2 == location + 62)
        {
            change(location1, location2, false, true);
            change(location2 + 1, location2 - 1, false, true);
            rookRightMoved_Black=true;
            kingMoves_Black=true;
        }

        else if (location2 == location + 58)
        {
            change(location1, location2, false, true);
            change(location2 - 2, location2 + 1, false, true);
            rookLeftMoved_Black=true;
            kingMoves_Black=true;
        }

    }
    else
    {
        change(location1, location2, kill_piece, move_valid);
    }

    //CHANGES AFTER CHANGING ORIENTATION OF CHESSBOARD
    if(rookLeftMoved_White==false && location1==location)
    {
        rookLeftMoved_White = true;
    }
    else if(rookRightMoved_White==false && location1==location + 7)
    {
        rookRightMoved_White = true;
    }
    else if(rookLeftMoved_Black==false && location1==location + 56)
    {
        rookLeftMoved_Black = true;
    }
    else if(rookRightMoved_Black==false && location1==location + 63)
    {
        rookRightMoved_Black = true;
    }

    if (kingMoves_White == false && location1 == location + 4)
    {
        kingMoves_White = true;
    }
    else if (kingMoves_Black == false && location1 == location + 60)
    {
        kingMoves_Black = true;
    }
}

//--------------------------------------------//

// Function carrying out the phenomenon of the pawn promotion in chess.
// Basically, when pawn of a colour reaches the furthermost row without being killed , it can be promoted to any piece except king.
// Variables used: Arguements: location2 : final location of the pawn


void piece::pawn_promotion(int * location2)
{
    if(*location2 == 1)             //player playing is white
    {
        if(location2==location+63 || location2==location+62 || location2==location+61 || location2==location+60 || location2==location+59 || location2==location+58 || location2==location+57 || location2==location+56)
        {
            total_white_pawns--;
            cout<<"You can now promote your pawn to any desirable piece."<<endl;
            cout<<"Enter the notation of the desired piece."<<endl;
        pawnPromotionWhite:
            char new_piece;
            cin>>new_piece;
            if(new_piece == 'R')
            {
                cout<<"You just promoted your pawn to a rook"<<endl;
                *location2 = 2;
                total_white_rooks++;
            }

            else if(new_piece == 'N')
            {
                cout<<"You just promoted your pawn to a knight"<<endl;
                *location2 = 3;
                total_white_knights++;
            }

            else if(new_piece == 'B')
            {
                cout<<"You just promoted your pawn to a bishop"<<endl;
                *location2 = 4;
                total_white_bishops++;
            }

            else if(new_piece == 'Q')
            {
                cout<<"You just promoted your pawn to a queen"<<endl;
                *location2 = 10;
                white_queen++;
            }
            else
            {
                cout<<"Enter a correct notation."<<endl;
                goto pawnPromotionWhite;
            }


        }
    }

    else if(*location2 == -1)             //player playing is black
    {
        if(location2==location || location2==location+1 || location2==location+2 || location2==location2+3 || location2==location+4 || location2==location+5 || location2==location+6|| location2==location+7 || location2==location+8)
        {
            total_black_pawns--;
            cout<<"You can now promote your pawn to any desirable piece."<<endl;
            cout<<"Enter notation of the desired piece."<<endl;
        pawnPromotionBlack:
            char new_piece;
            cin>>new_piece;
            if(new_piece == 'r')
            {
                cout<<"You just promoted your pawn to a rook"<<endl;
                *location2 = -2;
                total_black_rooks++;

            }

            else if(new_piece == 'n')
            {
                cout<<"You just promoted your pawn to a knight"<<endl;
                *location2 = -3;
                total_black_knights++;
            }

            else if(new_piece == 'b')
            {
                cout<<"You just promoted your pawn to a bishop"<<endl;
                *location2 = -4;
                total_black_bishops++;
            }

            else if(new_piece == 'q')
            {
                cout<<"You just promoted your pawn to a queen"<<endl;
                *location2 = -10;
                black_queen++;
            }

            else
            {
                cout<<"Enter a correct notation."<<endl;
                goto pawnPromotionBlack;
            }

        }
    }

}

//--------------------------------------------//

// A function used to check if the phenomenon of castling can be carried out. This function disregard the legality of the move.
// Takes into consideration all required conditions.
//This function is called by move function and hence location1 and location2 are written generally.
/*
    Variables used:
            Arguements: location1 : initial position of the king
                        location2 : final position of the king
 */



bool piece::castle(int * location1 , int * location2 )
{


        if (kingMoves_White == false && *location1 == 99)           //white king
        {
            if (rookRightMoved_White==false && location2 + 1 == location + 7 && *(location+6)==0 && *(location+5)==0)       //right rook
            {
                return true;
            }

            else if (rookLeftMoved_White==false && location2 - 1 == location+1 && *(location+2)==0 && *(location+3)==0)          //left rook
            {
                return true;
            }

        }

        else if (kingMoves_Black == false && *location1 == -99)           //black king
        {
            if (rookRightMoved_Black==false && location2 + 1 == location + 63 && *(location+62)==0 && *(location+61)==0)          //right rook
            {
                return true;
            }

            else if (rookLeftMoved_Black==false && location2 - 1 == location + 57 && *(location+58)==0 && *(location+59)==0)          //left rook
            {
                return true;
            }

        }
        return false;
}

//--------------------------------------------//


//A function returning index of the position of white king

int piece::searchWhiteKing()
{
    int variator;
    for(int i=0;i<64;i++)
    {
        if((*(location+i))==99)
        {
            variator=i;
            break;
        }
    }
    return variator;
}

//--------------------------------------------//

//The function returnign the index of the position of the black king

int piece::searchBlackKing()
{
    int variator;
    for(int i=0;i<64;i++)
    {
        if((*(location + i))==-99)
        {
            variator=i;
            break;
        }
    }
    return variator;
}

//--------------------------------------------//

// The function returns the number of available white pieces

int piece::numPiecesWhite()
{
    int numRemainingPieces=0;
    for(int i=0 ; i<64 ; i++)
    {
        if(*(location+i)>0)
        {
            numRemainingPieces=numRemainingPieces+1;
        }
    }

    return numRemainingPieces;

}

//--------------------------------------------//

// The function returns a pointer to the array storing the locations of all the available white pieces

int ** piece::storeWhitePointer()
{
    int length;
    length= numPiecesWhite();
    int ** store_pointer_white;
    store_pointer_white = new int *[length];
    int k=0;
    for(int i=0 ; i<64 ; i++)
    {
        if(*(location+i)>0)
        {
            store_pointer_white[k]=location+i;
            ++k;
        }
    }

    return store_pointer_white;
}

//--------------------------------------------//

// The function returns the number of available black pieces

int piece::numPiecesBlack() // calculates the number of black pieces remaining
{
    int numRemainingPieces=0;
    for(int i=0 ; i<64 ; i++)
    {
        if(*(location+i)<0)
        {
            numRemainingPieces=numRemainingPieces+1;
        }
    }

    return numRemainingPieces;

}

//--------------------------------------------//

// The function returns a pointer to the array storing the locations of all the available black pieces


int ** piece::storeBlackPointer()
{
    int length;
    length= numPiecesBlack();
    int ** store_pointer_black;
    store_pointer_black = new int *[length];
    int k=0;
    for(int i=0 ; i<64 ; i++)
    {
        if(*(location+i)<0)
        {
            store_pointer_black[k]=location+i;
            ++k;
        }
    }

    return store_pointer_black;
}

