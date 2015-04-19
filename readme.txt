Year: 2015

Course: CS101

Group number: 181

Project Title: CHESS

Member1 Name: Hritik Singh 

Member1 Roll Number: 140010062

Member2 Name: Sushrut Phadke 

Member2 Roll Number: 140010002

Member3 Name: Ronit Saha
 
Member3 Roll Number: 140010039

Member4 Name: Adhish Tiwari
 
Member4 Roll Number: 140110022

YouTube Video Link: https://www.youtube.com/watch?v=UazfNUOwO_E 




INSTALLATION INSTRUCTIONS:


On Windows:

1. Install Code::Blocks : "http://www.codeblocks.org/downloads/binaries"
2. Download and extract the package using winrar or winzip.
   Copy folder named "dev_lib_SDL2.0.3" to any location in your hard drive but make sure to remember its path.

3. Create a new project of type "Console Application" in Code::Blocks. Make sure to remember its path directory.

4. Copy all source files from folder "source" and images in "data" to parent directory of your project.
   Make sure to replace default "main.cpp" with "main.cpp" taken from "code" folder. 
   Note: Do not copy the folders just copy the files.

5. Now open these files in Code::Blocks and add them to your active project created by you in step 3.

   To add them to the project, right click on each file and choose "Add file to active project".
   Make sure to mark both "Debug" and "Release" options in the dialog box that opens.

6. After adding all the files you have to include SDL library. 
   For that right click on your project in Management Tab on left and choose "Build options".

7. Make sure to mark option "Have g++ follow the C++11 ISO C++ language standard [-std=C++11]" under "Compiler settings".

8. Now go to "Search directories" and under "Compiler", add directory "SDL2" from folder saved by you in step 2.

   Path to this directory is : dev_lib_SDL2.0.3/include/SDL2 .

9. Now click on "Linker" and add directory "lib" from folder "dev_lib_SDL2.0.3".

10. Go to "Linker Settings"and type "-lmingw32-lSDL2main-lSDL2" under "Other linker options".

11. To make sure that Code::Blocks detect SDL: 
Copy file "SDL2.dll" to "windows32" folder of your window.
    You can get "SDL2.dll" file in "bin" folder of "dev_lib_SDL2.0.3".

12. Now you are ready to ues this software . Compile the project using Code::Blocks and run.


                      \\\\\\\\\\\\\\\\\\\\ " ENJOY  THE GAME  " /////////////////////// 




PLAYING INSTRUCTIONS:


Introduction :

We have built a two player Chess game. 
Chess is a two  player strategy board game played on a 8X8 grid.
Each player begins the game with 16 pieces: one king, one queen, two rooks, two knights, two bishops, and eight pawns. 
Each of the six piece have different type of moves. 
The objective of game is to 'checkmate' the opponent's king by placing it under an inescapable threat of capture.


Our chess displays the 8X8 grid on the screen with all the 16 pieces of both player1 and player2.

The pieces of white are displayed by capital letters and the blacks by small letters.


1. Movement of the pieces: It is done by entering the standard notations of initial and final positions for a piece.
   For example: Initial Position: e2
		Final Position: e4
   This is a common starting move. This moves white pawn in front of king two squares ahead.


2. Rules and Moves Of Pieces: http://en.wikipedia.org/wiki/Rules_of_chess


3. Pawn Promotion: During pawn promotion, you have to enter the standard notation of respective piece.
   For example: During promotion of a white pawn, enter 'Q' to promote to "queen" , 'R' for "rook" and similarly for other pieces.
		During promotion of a black pawn, enter 'q' to promote to "queen" , 'n' for "knight" and similarly for other pieces.
