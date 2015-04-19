#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<string>
#include "input.h"

using namespace std;

// REQUIRED GLOBAL VARIABLES
int killed_piece_count=0;
char killed_pieces[32];
int call_counter=0; // to count number of calls made to piece_change function
int checkmate_pointer=0;
int check_pointer=0;
int total_white_pawns=8;
int total_white_rooks=2;
int total_white_knights=2;
int total_white_bishops=2;
int white_queen=1;
int total_black_pawns=8;
int total_black_rooks=2;
int total_black_knights=2;
int total_black_bishops=2;
int black_queen=1;

int input_translate::translate(char position[])
//converting the required input to function acceptable form
{
    return (position[0] - 'a') + 8*(position[1] - '1');
}
/* Above function will change the input char array to required char array

   Using the above array, all move and kill operations can be performed
*/
string input_translate::retranslate(int variator)
{
    string finalString;
    finalString.resize(2);
    char letter , number;
    letter = (char)(variator%8) + 'a';
    number = (char)(variator/8) + '1';
    finalString[0] = letter;
    finalString[1] = number;
    return finalString;
}

