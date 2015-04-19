#ifndef castle_pieces_h
#define castle_pieces_h
#include<string>
#include<stdlib.h>
#include<array>
using namespace std;

// global variables
extern int * location ;
extern bool rookLeftMoved_White;
extern bool rookRightMoved_White;
extern bool rookLeftMoved_Black;
extern bool rookRightMoved_Black;
extern bool kingMoves_White;
extern bool kingMoves_Black;

// to initialize pop-up window
bool init();

//to load pictures
bool load();

//to close SDL window
void close();
// to initialize piece killed window
bool init_piece();

struct colour
{
    int pawn[8];
    int rook_1 , rook_2;
    int knight_1, knight_2 ;
    int bishop_1 , bishop_2;
    int queen ;
    int king ;
    char initial_position[2];
    char final_position[2];
    bool check=false;
    int no_of_remaining_pieces=0;
};


class piece{
public:
    void exchange(int * t1 , int * t2);

    bool move(int * location1 , int * location2);


    bool kill(bool move_valid ,int * location1, int * location2);
    void change(int * location1 , int * location2 , bool kill_piece , bool move_valid);

    bool check(int * location1, int * location2 );

    bool check_escape (int * location1 , int * location2 ,int * store_pointer_other[],int length);

    bool checkmate(int * store_pointer_same_postcheck[] , int length_postcheck, int * store_pointer_other_precheck[] , int length_precheck);

    bool check_present(int * locationOfKingSameColour, int * store_pointer_other_player[],int length);

    void make_move(int * location1 , int * location2);

    void pawn_promotion(int * location2);

    bool castle(int * location1 , int * location2);

    int numPiecesWhite();
    int numPiecesBlack();
    int ** storeWhitePointer();
    int ** storeBlackPointer();

    int searchWhiteKing();
    int searchBlackKing();
};


#endif
