#ifndef __CHESS__input_h
#define __CHESS__input_h

#include <stdio.h>
#include<cstdlib>
#include<string>

using namespace std;

// DECLARATION OF GLOBAL VARIABLES
extern char killed_pieces[32];
extern int killed_piece_count;
extern int call_counter;
extern int checkmate_pointer;
extern int check_pointer;

// variables representing initial number of pieces like 8 white and black pawns
extern int total_white_pawns;
extern int total_white_rooks;
extern int total_white_knights;
extern int total_white_bishops;
extern int total_black_pawns;
extern int total_black_rooks;
extern int total_black_knights;
extern int total_black_bishops;
extern int white_queen,black_queen;

class input_translate{
public:
    int translate(char position[]);
    string retranslate(int variator);
};


#endif
