#include<iostream>
#include<string>
#include<cstdlib>
#include<array>
#include"pieces.h"
#include "input.h"
#include <SDL.h>
#include <stdio.h>

using namespace std;

// width and height of SDL window
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// this is window that will pop-up during play
SDL_Window* gWindow = NULL;
//this is surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//These are image surfaces that will load and show picture on the screen
SDL_Surface* chess = NULL;
SDL_Surface* chess_piece = NULL;

bool init()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )//initializing SDL
	{
		printf( "SDL could not initialize! SDL_Error:\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "CHESS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error:\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool init_piece()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )//initializing SDL
	{
		printf( "SDL could not initialize! SDL_Error:\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "PIECE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 175, 300, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error:\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}
bool load()
{
	bool success = true;

	chess = SDL_LoadBMP( "chess.bmp" );//to load image
	if( chess == NULL )
	{
		printf( "Unable to load image. SDL Error:\n", "chess.bmp", SDL_GetError() );
		success = false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface( chess );
	chess = NULL;
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	// to quit SDL
	SDL_Quit();
}

int variator = 0;

// A function to DISPLAY THE CHESSBOARD and Killed Pieces
/*  Chessboard is considered as an 8x8 array of numbers representing pieces and
    vacant places.
    Function is called whenever chessboard is required to display usually after each change in position of pieces
 */
/*  Variables Used:
        Arguments: piece_name : Stores name of a piece as corresponding letter
 */
void displayChessboard()
{
    cout<<"\n\t\tBLACKS\n\n";
    char piece_name=' ';

   // variable to count number of each of pieces
    int white_pawn_count=0;
    int white_bishop_count=0;
    int white_rook_count=0;
    int white_knight_count=0;
    int white_queen_count=0;
    int black_pawn_count=0;
    int black_bishop_count=0;
    int black_rook_count=0;
    int black_knight_count=0;
    int black_queen_count=0;

    for(int i=7; i>=0 ; i--)
    {
        cout << "  |---|---|---|---|---|---|---|---|\n"<<i+1<<" | "; // draws board and also prints ranks

        for(int j=0; j<8 ; j++)
        {
            variator=8*i + j;

            /*identification of each piece and its naming according to standard rules of chess
             Capital letters represent whites while small letters represent blacks */

            if(*(location+variator)==1)
               {
                    white_pawn_count++;
                    piece_name='P';
               }
            else if(*(location+variator)==2)
                {
                    white_rook_count++;
                    piece_name='R';
                }
            else  if(*(location+variator)==3)
                {
                    white_knight_count++;
                    piece_name='N';
                }
            else  if(*(location+variator)==4)
                {
                    white_bishop_count++;
                    piece_name='B';
                }
            else  if(*(location+variator)==99)
                piece_name='K';
            else if(*(location+variator)==10)
                {
                    white_queen_count++;
                    piece_name='Q';
                }
            else if(*(location+variator)==-1)
               {
               black_pawn_count++;
               piece_name='p';
               }
            else if(*(location+variator)==-2)
                {
                    black_rook_count++;
                    piece_name='r';
                }
            else  if(*(location+variator)==-3)
                {
                    black_knight_count++;
                    piece_name='n';
                }
            else  if(*(location+variator)==-4)
                {
                    black_bishop_count++;
                    piece_name='b';
                }
            else  if(*(location+variator)==-99)
                piece_name='k';
            else if(*(location+variator)==-10)
                {
                    black_queen_count++;
                    piece_name='q';
                }
            else piece_name=' ';
            cout<<piece_name<<" | ";
        }
      cout<<endl;
    }

    cout << "  |---|---|---|---|---|---|---|---|\n";
    cout << "    a   b   c   d   e   f   g   h\n"; // prints file notations
    cout << "\n\t\tWHITES\n";

    // display KILLED pieces
     if(white_pawn_count<total_white_pawns)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("white_pawn.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );

        // this updates the surface with image
         SDL_UpdateWindowSurface( gWindow );

        //Wait two seconds after displaying pic
         SDL_Delay( 2000 );
         close();

         killed_pieces[killed_piece_count]='P';
         killed_piece_count++;
         total_white_pawns--;
     }

     if(black_pawn_count<total_black_pawns)
     {
         // display image when a pawn is killed
         init_piece();

         chess_piece=SDL_LoadBMP("black_pawn.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();

         killed_pieces[killed_piece_count]='p';
         killed_piece_count++;
         total_black_pawns--; // decrease number of pawns whenever it gets killed
     }
     if(white_rook_count<total_white_rooks)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("white_rook.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();

         killed_pieces[killed_piece_count]='R';
         killed_piece_count++;
         total_white_rooks--;
     }

     if(black_rook_count<total_black_rooks)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("black_rook.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();
         killed_pieces[killed_piece_count]='r';
         killed_piece_count++;
         total_black_rooks--;
     }
      if(white_bishop_count<total_white_bishops)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("white_bishop.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();
         killed_pieces[killed_piece_count]='B';
         killed_piece_count++;
         total_white_bishops--;
     }
     if(black_bishop_count<total_black_bishops)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("black_bishop.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();
         killed_pieces[killed_piece_count]='b';
         killed_piece_count++;
         total_black_bishops--;
     }
      if(white_knight_count<total_white_knights)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("white_knight.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();
         killed_pieces[killed_piece_count]='N';
         killed_piece_count++;
         total_white_knights--;
     }
     if(black_knight_count<total_black_knights)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("black_knight.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();
         killed_pieces[killed_piece_count]='n';
         killed_piece_count++;
         total_black_knights--;
     }
     if(white_queen_count<white_queen)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("white_queen.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();
         killed_pieces[killed_piece_count]='Q';
         killed_piece_count++;
         white_queen--;
     }
      if(black_queen_count<black_queen)
     {
         init_piece();

         chess_piece=SDL_LoadBMP("black_queen.bmp");
         SDL_BlitSurface(chess_piece, NULL, gScreenSurface, NULL );
         SDL_UpdateWindowSurface( gWindow );
         SDL_Delay( 2000 );

         close();

         killed_pieces[killed_piece_count]='q';
         killed_piece_count++;
         black_queen--;
     }
     if(!checkmate_pointer)
     {
        cout <<"\nKilled pieces:";

        for(int i=0;killed_pieces[i]!='\0';i++)
        {
            cout << killed_pieces[i]<<",";
        }
     }
     cout <<"\n\n";
}


// MAIN FUNCTION OF PROGRAM

int main( int argc, char* args[] )
{

    //REQUIRED VARIABLES AND POINTERS
    string player1,player2;
    int * initial_location_white;
    int * initial_location_black;
    int * final_location_white;
    int * final_location_black;
    int position_saver=0;           //saves the value of a position
    int ** store_white;
    int ** store_black;
    int size_white , size_black;
    int numOfMoves_White=0 , numOfMoves_Black=0;
    bool moveValid;
    bool checkmate=false;
    bool no_check;
    int numOfChecks_White=0;
    int numOfChecks_Black=0;
    int * locationWhiteKing=nullptr;
    int * locationBlackKing=nullptr;
    rookLeftMoved_White=false;
    rookRightMoved_White=false;
    rookLeftMoved_Black=false;
    rookRightMoved_Black=false;
    kingMoves_White=false;
    kingMoves_Black=false;


    //--------------------------

    //REQUIRED OBJECTS

    piece pie;
    input_translate in;
    colour player_white , player_black;
    int chessboard[8][8];

    for(int i=0; i<8 ; i++)
    {
        for(int j=0; j<8; j++)
        {
            chessboard[i][j]=0;
        }
    }
    location = new int;

    location = &chessboard[0][0];


/* Display of Cover picture */
    init();
    load();
    // to apply the image
    SDL_BlitSurface( chess, NULL, gScreenSurface, NULL );

    // this updates the surface
    SDL_UpdateWindowSurface( gWindow );

    //Wait two seconds
    SDL_Delay( 5000 );
	close();

 /*Introduction and Reading names of users*/
    cout << "Welcome to 2-player Chess\n\n";
    cout << "Enter Player Names:\nWhites: ";
    getline(cin, player1);
    cout << "Blacks: ";
    getline(cin, player2);

    /*assigning values to pieces
     - positive values to whites
     - negative values to blacks
     */

    for(int i=0; i<8 ; i++)
    {
        player_white.pawn[i]= 1;
    }
    for(int i=0; i<8 ; i++)
    {
        player_black.pawn[i]= -1;
    }
    player_white.rook_1=2; player_white.rook_2=2;
    player_black.rook_1=-2; player_black.rook_2=-2;

    player_white.knight_1=3; player_white.knight_2=3;
    player_black.knight_1=-3; player_black.knight_2=-3;

    player_white.bishop_1=4; player_white.bishop_2=4;
    player_black.bishop_1=-4; player_black.bishop_2=-4;

    player_white.queen=10;
    player_black.queen=-10;

    player_white.king=99;
    player_black.king=-99;

    /*assigning positions to pieces on chessboard*/
    //for whites

    *location = player_white.rook_1;
    *(location+7) = player_white.rook_1;
    *(location+1)= player_white.knight_1;
    *(location+6) = player_white.knight_1;
    *(location+2) = player_white.bishop_1;
    *(location+5) = player_white.bishop_1;
    *(location+3) = player_white.queen;
    *(location+4) = player_white.king;

    for(int k =0; k<8 ; k++)
    {
        *(location+8+k)=player_white.pawn[k];
    }

    //for blacks

    *(location+63) = player_black.rook_1;
    *(location+63-7) = player_black.rook_1;
    *(location+63-1)= player_black.knight_1;
    *(location+63-6) = player_black.knight_1;
    *(location+63-2) = player_black.bishop_1;
    *(location+63-5) = player_black.bishop_1;
    *(location+63-4) = player_black.queen;
    *(location+63-3) = player_black.king;
    for(int k =0; k<8 ; k++)
    {
        *(location+63-8-k)=player_black.pawn[k];
    }

    //initializing the location of kings(to later keep track of king)
    locationWhiteKing=location+4;
    locationBlackKing=location+63-4;

    // to display initial chessboard

    displayChessboard();

    while (!checkmate)
    {
    white_plays:
        size_white=pie.numPiecesWhite();            //saves number of all white pieces
        store_white=pie.storeWhitePointer();        //saves positions of all white pieces


        size_black=pie.numPiecesBlack();            //saves number of all black pieces
        store_black=pie.storeBlackPointer();        //saves positions of all black pieces

        if(pie.checkmate(store_white, size_white, store_black, size_black)) // checking for STALEMATE
        {
            init();

            chess=SDL_LoadBMP("stalemate.bmp");
            SDL_BlitSurface(chess, NULL, gScreenSurface, NULL );
            SDL_UpdateWindowSurface( gWindow );
            SDL_Delay( 3000 );

            close();

            cout<<"STALEMATE. Game Draw."<<endl<<endl;
            delete [] store_black; // delete pointer array to prevent dangling references
            delete [] store_white;
            displayChessboard();
            return 0;
        }


        //Player White input
        cout<<player1<<"(White) plays:"<<endl;
        cout<<"Enter:-\nInitial Position: ";
        for(int i=0;i<2; i++)
        {
            cin>>player_white.initial_position[i];
        }

        cout<<"Final Position: ";
        for(int i=0;i<2; i++)
        {
            cin>>player_white.final_position[i];
        }

        initial_location_white = location + in.translate(player_white.initial_position);
        //location1


        if(*initial_location_white <= 0)
        {
            cout<<"INVALID MOVE(A White Piece is not at this position)"<<endl;

            delete [] store_black;
            delete [] store_white;
            displayChessboard();
            goto white_plays;
        }

        final_location_white = location + in.translate(player_white.final_position);    //location2


        moveValid= pie.move(initial_location_white, final_location_white);

        if(moveValid==false)
        {
            cout<<"INVALID MOVE."<<endl;

            displayChessboard();
            delete [] store_black;
            delete [] store_white;
            goto white_plays;
        }

        position_saver = *initial_location_white;
        // saves position of white piece

        no_check=pie.check_escape(initial_location_white, final_location_white, store_black, size_black);
        //to check if the move made is legal


        if(player_white.check)          //for a check to white
        {
            player_white.check=!no_check;

            if (player_white.check) // works when player tries to move King to a position where it is getting a check
            {
                cout<<"This is a CHECK. Enter a valid move:"<<endl;
                displayChessboard();
                delete [] store_black;
                delete [] store_white;
                goto white_plays;
            }

        }

        if(no_check)
        {
            //make a move
            pie.make_move(initial_location_white, final_location_white);

            //update the position of the king
            locationWhiteKing=location + pie.searchWhiteKing();
            locationBlackKing=location + pie.searchBlackKing();

            numOfMoves_White = numOfMoves_White+1;

            pie.pawn_promotion(final_location_white);

            delete [] store_white;
            size_white=pie.numPiecesWhite();
            store_white=pie.storeWhitePointer();

            delete[] store_black;
            store_black=pie.storeBlackPointer();
            size_black=pie.numPiecesBlack();

            player_black.check=pie.check_present(locationBlackKing , store_white, size_white);

            if(player_black.check)
            {
                numOfChecks_Black = numOfChecks_Black+1;
                //checking for checkmate

                checkmate=pie.checkmate(store_white ,size_white, store_black ,size_black);

                if(checkmate) // works if player black has no valid move left
                {
                    init();

                    chess=SDL_LoadBMP("checkmate.bmp");
                    SDL_BlitSurface(chess, NULL, gScreenSurface, NULL );
                    SDL_UpdateWindowSurface( gWindow );
                    SDL_Delay( 3000 );

                    close();

                    displayChessboard();
                    cout<<"CHECKMATE"<<endl;
                    cout<<player1<<"(WHITE) WINS THE GAME.\n";
                    delete [] store_black;
                    delete [] store_white;
                    return 0;
                }
                else
                {
                    init();

                    chess=SDL_LoadBMP("check.bmp");
                    SDL_BlitSurface(chess, NULL, gScreenSurface, NULL );
                    SDL_UpdateWindowSurface( gWindow );
                    SDL_Delay( 2000 );

                    close();
                    cout<<player2<<"(BLACK), YOU HAVE A CHECK."<<endl;
                }

            }

        }

        //for invalid move
        else
        {
            cout<<"ILLEGAL MOVE. Enter a legal move."<<endl;
            displayChessboard();
            delete [] store_black;
            delete [] store_white;
            goto white_plays;
        }

        displayChessboard();

        if (position_saver==*initial_location_white)      //piece hasnt moved
        {
            cout<<"INVALID MOVE(Piece cannot move there)"<<endl;

            delete [] store_black;
            delete [] store_white;
            goto white_plays;
        }
        delete [] store_black;
        delete [] store_white;


    black_plays:

        size_white=pie.numPiecesWhite();            //saves number of all white pieces
        store_white=pie.storeWhitePointer();        //saves positons of all white pieces

        size_black=pie.numPiecesBlack();            //saves number of all black pieces
        store_black=pie.storeBlackPointer();        //saves postions of all black pieces


        if(pie.checkmate(store_black, size_black, store_white, size_white))//works if only kings are left
        {
            init();

            chess=SDL_LoadBMP("stalemate.bmp");
            SDL_BlitSurface(chess, NULL, gScreenSurface, NULL );
            SDL_UpdateWindowSurface( gWindow );
            SDL_Delay( 3000 );

            close();
            cout<<"STALEMATE. Game Draw."<<endl<<endl;
            delete [] store_black;
            delete [] store_white;
            displayChessboard();
            return 0;
        }


        //Player black input
        cout<<player2<<"(Black) plays:"<<endl;
        cout<<"Enter:-\nInitial Position: ";
        for(int i=0;i<2; i++)
        {
            cin>>player_black.initial_position[i];
        }

        cout<<"Final Position: ";
        for(int i=0;i<2; i++)
        {
            cin>>player_black.final_position[i];
        }

        initial_location_black = location + in.translate(player_black.initial_position);        //location1

        if(*initial_location_black >= 0)
        {
            cout<<"INVALID MOVE(A Black Piece is not at this position)"<<endl;
            displayChessboard();
            delete [] store_white;
            delete [] store_black;
            goto black_plays;
        }

        final_location_black = location + in.translate(player_black.final_position);       //location2

        moveValid=pie.move(initial_location_black, final_location_black);
        if(moveValid==false)
        {
            cout<<"INVALID MOVE."<<endl;
            delete [] store_black;
            delete [] store_white;
            displayChessboard();
            goto black_plays;
        }


        position_saver = *initial_location_black;

        no_check=pie.check_escape(initial_location_black, final_location_black, store_white, size_white);
        //to check if the move made is legal

        if(player_black.check)          //for a check to white
        {
            player_black.check=!no_check;

            if (player_black.check)
            {
                cout<<"This is a CHECK. Enter a valid move:"<<endl;
                displayChessboard();
                delete [] store_black;
                delete [] store_white;
                goto black_plays;
            }

        }


        if(no_check)
        {
            //make a move
            pie.make_move(initial_location_black,final_location_black);

            //updating the positon of the kings
            locationWhiteKing=location + pie.searchWhiteKing();
            locationBlackKing=location + pie.searchBlackKing();

            numOfMoves_Black = numOfMoves_Black + 1;

            pie.pawn_promotion(final_location_black);

            delete [] store_black;
            size_black=pie.numPiecesBlack();
            store_black=pie.storeBlackPointer();

            delete [] store_white;
            size_white=pie.numPiecesWhite();
            store_white = pie.storeWhitePointer();

            player_white.check=pie.check_present(locationWhiteKing , store_black, size_black);

            if(player_white.check)
            {
                numOfChecks_White = numOfChecks_White + 1;
                //check for checkmate

                checkmate=pie.checkmate(store_black ,size_black, store_white ,size_white);

                if(checkmate)
                {
                    init();

                    chess=SDL_LoadBMP("checkmate.bmp");
                    SDL_BlitSurface(chess, NULL, gScreenSurface, NULL );
                    SDL_UpdateWindowSurface( gWindow );
                    SDL_Delay( 3000 );

                    close();

                    displayChessboard();
                    cout<<"CHECKMATE"<<endl;
                    cout<<player2<<"(BLACK) WINS THE GAME.\n";
                    delete [] store_black;
                    delete [] store_white;
                    return 0;
                }
                else
                {
                    init();

                    chess=SDL_LoadBMP("check.bmp");
                    SDL_BlitSurface(chess, NULL, gScreenSurface, NULL );
                    SDL_UpdateWindowSurface( gWindow );
                    SDL_Delay( 3000 );

                    close();
                    cout<<player1<<"(WHITE), YOU HAVE A CHECK."<<endl;
                }

            }

        }

        //for invalid move
        else
        {
            cout<<"ILLEGAL MOVE. Enter a correct move."<<endl;
            displayChessboard();
            delete [] store_black;
            delete [] store_white;
            goto black_plays;
        }

        displayChessboard();

        if (position_saver==*initial_location_black)      //piece hasnt moved
        {
            cout<<"INVALID MOVE(Piece cannot move there)."<<endl;
            delete [] store_black;
            delete [] store_white;
            goto black_plays;
        }
        delete [] store_black;
        delete [] store_white;

    } // end of while loop

    delete location;

    return 0;

} // end of main function




