/*
By Maria Vargas Caraballo 
/**/ 

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cmath> 
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;
void credits();
void resetGame(char myArray[]);
void switchPlayer();
void displayGrid (char myArray[]);
void playerMakeMove(char myArray[]);
string validatePlayersMove(string& userIput);
int checkPositionAvailability(int& userChoice, char myArray []);
bool checkWin(char myArray []);
bool checkTie(int numberOfPlays, char myArray[], bool Win);
void makeBestMove(char myArray []);
bool computerBlock(char myArray []);

int main ()
{
    credits(); 
    switchPlayer();
    return 0; 
    
}

void credits()
{
    cout << "***********************"<< endl;
    cout << "***********************"<< endl;
    cout << "***********************"<< endl;
    cout << "******           ******"<< endl;
    cout << "******TIC TAC TOE******"<< endl;
    cout << "******  ByMaria  ******"<< endl;
    cout << "******  Vargas   ******"<< endl;
    cout << "******           ******"<< endl;
    cout << "***********************"<< endl;
    cout << "***********************"<< endl;
    cout << "***********************"<< endl;
        
    char proceed = 'y';
    string userInput; 
        
    cout << "\ny/Y to continue, any other char to exit" << endl;
    getline(cin,userInput);
        
    if(userInput.length() == 0)
    {
        cout << "Goodbye" << endl;
        exit(0);
    }
        
    proceed = userInput[0];
        
    if (!(proceed == 'y' || proceed == 'Y'))
    {
        cout << "Goodbye" << endl;
        exit(0);
    }
}// end credits 

void resetGame(char myArray[])//resets the game when one concludes;this includes filling the array with values 0-8
{
       myArray[0]  = '0';
       myArray[1]  = '1';
       myArray[2]  = '2';
       myArray[3]  = '3';
       myArray[4]  = '4';
       myArray[5]  = '5';
       myArray[6]  = '6';
       myArray[7]  = '7';
       myArray[8]  = '8';
}//end resetGame
void displayGrid(char myArray[])//display the game after each player makes a move
{

    cout <<  "|" <<  myArray[0];
    cout <<  "|" <<  myArray[1];
    cout <<  "|" << myArray[2] << "|" << endl;
    cout <<  "|" <<  myArray[3];
    cout <<  "|" <<  myArray[4];
    cout <<  "|" <<  myArray[5] <<  "|" << endl;
    cout <<  "|" <<  myArray[6];
    cout <<  "|" <<  myArray[7];
    cout <<  "|" <<  myArray[8] <<  "|" << endl;
}//end displayGrid

void playerMakeMove(char myArray[])//prompts player to make a move, invokes validatePlayersMove, checkPositionAvailability
{
    string userInput;
    int userChoice;

    cout << "\nIt's your turn.\n";
    getline(cin,userInput);

    userInput = validatePlayersMove(userInput); //validate userInput
    userChoice = atoi(userInput.c_str());
    userChoice = checkPositionAvailability(userChoice, myArray);//check for availability
    myArray[userChoice] = 'H';//take spot
    checkWin(myArray);
}//end playerMakeMove

void switchPlayer()
{
     //most of the functions will be called here
    char  myArray[9]  = {'0','1','2','3','4','5','6','7','8'}; //make a class
    string userInput;
    char quitOrContinue = 'y';
    int userChoice;
    bool computerBlocked = false;
    bool Win = false;
    bool Tie = false;
       //Scanner keyboard = new Scanner(System.in);

    int numberOfPlays = 0;
    while(quitOrContinue == 'y')
    {
        while (numberOfPlays < 9)
        {
            displayGrid(myArray);

            if (numberOfPlays % 2 == 0)
            {
                playerMakeMove(myArray);
                Win = checkWin(myArray);
                Tie = checkTie(numberOfPlays, myArray, Win);
                if (Win == true)
		{
                    Tie = false;
                }
                if (Win == true || Tie == true)
		{
                    numberOfPlays = 12;
               	}
            }

            else
            {
                cout << "\nIt's the computer's turn\n";
                computerBlocked = computerBlock(myArray);
                if(computerBlocked == false)
                {
                    makeBestMove(myArray);
		}
                Win = checkWin(myArray);
                Tie = checkTie(numberOfPlays, myArray, Win);
                if (Win == true)
		{
                    Tie = false; 
                }
                if (Win == true || Tie == true)
		{
                    numberOfPlays = 12;
               	}
            }

            numberOfPlays++;
        }//end while loop
        
        cout << "Play again? Y/y\nAnything else will quit.\n";
	getline(cin,userInput);
	quitOrContinue = userInput[0];

	if(!(quitOrContinue == 'y' ||  quitOrContinue== 'Y'))
	{
            cout << "Goodbye!\n";
            exit(0);
	}
	else
	{
            resetGame(myArray);
            numberOfPlays = 0;
	}
    }//end outer while loop
}// end switchPlayer

string validatePlayersMove(string& userInput)
{
    
    int userInputLength = userInput.length();
    int counter = 0;
    
    while (userInputLength > 1 || userInputLength == 0)
        {
            cout << "That is an invalid entry.\n Try again.\n ";               
            getline(cin,userInput);
            userInputLength = userInput.length();            
        }
       
    while (counter < userInputLength || userInputLength > 1)
    {
        while (userInputLength > 1 || userInputLength == 0)
        {
            cout << "That is an invalid entry.\n Try again.\n ";               
            getline(cin,userInput);
            userInputLength = userInput.length();            
        }
        
        
        userInput = userInput[0];
        
        if (!isdigit(userInput[counter])) 
        {
            cout << "That is an invalid entry.\n Try again.\n ";               
            getline(cin,userInput);
            userInputLength = userInput.length();
            counter = 0;
            
            while (userInput != "0" && userInput !="1"
            && userInput !="2" && userInput !="3"
            && userInput !="4" && userInput !="5"
            && userInput !="6" && userInput !="7"
            && userInput !="8")
    
            {
                cout << "That is an invalid entry.\n Try again\n";
                userInput = userInput[0];
                getline(cin,userInput);
            }
        }
        else
            counter++;
    }
    return userInput;

}
int checkPositionAvailability(int& userChoice, char myArray [])//check that the position selected by the user is available
{
    string userAnswer;
    userAnswer = userAnswer[0];
    
    while (userChoice != myArray[userChoice] - '0')
    {
        cout << "That is an invalid entry.\n Try again\n";
        getline (cin, userAnswer);
        userAnswer = userAnswer[0];
        userAnswer = validatePlayersMove(userAnswer);
        userChoice = atoi(userAnswer.c_str());
    }
    return userChoice;
}//end checkPostionAvailability

bool checkWin(char myArray [])//check for a winning player
{
    bool Win = false;

        if (myArray [0] == myArray[1]
            && myArray [1] == myArray [2]
            && myArray [2] == 'C')//row 1
        {
            cout << "Computer Wins.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [0] == myArray[1]
            && myArray [1] == myArray [2]
            && myArray [2] == 'H')//row 1
        {
            cout << "You Win.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [3] == myArray[4]
            && myArray [4] == myArray [5]
            && myArray [5] == 'C')//row 2
        {
            cout << "Computer Wins.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [3] == myArray[4]
            && myArray [4] == myArray [5]
            && myArray [5] == 'H')//row 2
        {
            cout << "You Win.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [6] == myArray[7]
            && myArray [7] == myArray [8]
            && myArray [8] == 'C')//row 3
        {
            cout << "Computer Wins.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [6] == myArray[7]
            && myArray [7] == myArray [8]
            && myArray [8] == 'H')//row 3
        {
            cout << "You Win.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [0] == myArray[3]
            && myArray [3] == myArray [6]
            && myArray [6] == 'C')//coulmn 1
        {
            cout << "Computer Wins.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [0] == myArray[3]
            && myArray [3] == myArray [6]
            && myArray [6] == 'H')//coulmn 1
        {
            cout << "You Win.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [1] == myArray[4]
            && myArray [4] == myArray [7]
            && myArray [7] == 'C')//column 2
        {
            cout << "Computer Wins.\n" ;
            Win = true;
            displayGrid(myArray);
        }

         else if (myArray [1] == myArray[4]
            && myArray [4] == myArray [7]
            && myArray [7] == 'H')//column 2
        {
            cout << "You Win.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [2] == myArray[5]
            && myArray [5] == myArray [8]
            && myArray [8] == 'C')//column 3
        {
            cout << "Computer Wins.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [2] == myArray[5]
            && myArray [5] == myArray [8]
            && myArray [8] == 'H')//column 3
        {
            cout << "You Win.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [0] == myArray[4]
            && myArray [4] == myArray [8]
            && myArray [8] == 'C')//diagonal 1
        {
            cout << "Computer Wins.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [0] == myArray[4]
            && myArray [4] == myArray [8]
            && myArray [8] == 'H')//diagonal 1
        {
            cout << "You Win.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [2] == myArray[6]
            && myArray [6] == myArray [4]
            && myArray [4] == 'C')//diagonal 2
        {
            cout << "Computer Wins.\n" ;
            Win = true;
            displayGrid(myArray);
        }

        else if (myArray [2] == myArray[6]
            && myArray [6] == myArray [4]
            && myArray [4] == 'H')//diagonal 2
        {
            cout << "You Win.\n" ;
            Win = true;
            displayGrid(myArray);
        }
    
 

        return Win;

    }//end checkWin

bool checkTie(int numberOfPlays, char myArray [], bool Win)//check for a Tie
{
    Win = false;
    bool Tie = false;
    
    Win = checkWin(myArray);
    cout << "Number of plays = " << numberOfPlays << endl;
    if (numberOfPlays == 8 && Win == false)
    {
        cout << "It's a tie.\n";
        Tie = true; 
        displayGrid(myArray);
    }
    

    return Tie;
}// end checkTie 

void makeBestMove(char myArray [])//select best option
{
    srand(time(NULL)); 
    bool random = false;
    while (random == false)
    {
        int number = rand() % 8 + 1;
        cout << "Computer's choice: " << number << endl;//to know what number is picked by the Computer
        if (myArray [number] == 'C' || myArray [number] == 'H')
        {
            cout << "Taken. Computer will try again." << endl;
        }
        if (myArray [number] != 'C' && myArray [number] != 'H')//makes sure it's not taken
        {
            myArray[number] = 'C';
            random = true;
        }
    }

}//end makeBestMove

bool computerBlock(char myArray [])//used to make the move, in other words populate the array
    {
        bool computerBlocked = false;

        //row 1 (--0--1--2--)

        if (myArray[1] == myArray[2]
            && myArray[1] == 'H' && myArray[0] == '0')
        {
          myArray[0] = 'C';
          computerBlocked = true;
        }

        else if (myArray[0] == myArray[2]
            && myArray[0] == 'H' && myArray[1] == '1')
        {
          myArray[1] = 'C';
          computerBlocked = true;
        }

        else if (myArray[0] == myArray[1]
            && myArray[1] == 'H' && myArray[2] == '2')
        {
          myArray[2] = 'C';
          computerBlocked = true;
        }
        //end row 1

        //row 2  (--3--4--5--)
       else if (myArray[3] == myArray[4]
            && myArray[3] == 'H' && myArray[5] == '5')
        {
          myArray[5] = 'C';
          computerBlocked = true;
        }

       else if (myArray[3] == myArray[5]
            && myArray[3] == 'H' && myArray[4] == '4')
        {
          myArray[4] = 'C';
          computerBlocked = true;
        }

      else  if (myArray[4] == myArray[5]
            && myArray[4] == 'H' && myArray[3] == '3')
        {
          myArray[3] = 'C';
          computerBlocked = true;
        }
        //end row 1

        //row 3 (--6--7--8--)
      else  if (myArray[6] == myArray[7]
            && myArray[6] == 'H' && myArray[8] == '8')
        {
          myArray[8] = 'C';
          computerBlocked = true;
        }

     else if (myArray[6] == myArray[8]
            && myArray[6] == 'H' && myArray[7] == '7')
        {
          myArray[7] = 'C';
          computerBlocked = true;
        }

      else if (myArray[7] == myArray[8]
            && myArray[7] == 'H' && myArray[6] == '6')
        {
          myArray[6] = 'C';
          computerBlocked = true;
        }
        //end row 3

        //column 1 (--0--3--6--)
      else if (myArray[0] == myArray[3]
            && myArray[0] == 'H' && myArray[6] == '6')
        {
          myArray[6] = 'C';
          computerBlocked = true;
        }

      else if (myArray[0] == myArray[6]
            && myArray[6] == 'H' && myArray[3] == '3')
        {
          myArray[3] = 'C';
          computerBlocked = true;
        }

      else if (myArray[3] == myArray[6]
            && myArray[3] == 'H' && myArray[0] == '0')
        {
          myArray[0] = 'C';
          computerBlocked = true;
        }
        //column 1

        //column 2 (--1--4--7--)
       else if (myArray[1] == myArray[4]
            && myArray[1] == 'H' && myArray[7] == '7')
        {
          myArray[7] = 'C';
          computerBlocked = true;
        }

       else if (myArray[1] == myArray[7]
            && myArray[1] == 'H' && myArray[4] == '4')
        {
          myArray[4] = 'C';
          computerBlocked = true;
        }

       else if (myArray[4] == myArray[7]
            && myArray[4] == 'H' && myArray[1] == '1')
        {
          myArray[1] = 'C';
          computerBlocked = true;
        }
        //column 2

        //column 3 (--2--5--8--)
       else if (myArray[2] == myArray[5]
            && myArray[2] == 'H' && myArray[8] == '8')
        {
          myArray[8] = 'C';
          computerBlocked = true;
        }

       else if (myArray[2] == myArray[8]
            && myArray[2] == 'H' && myArray[5] == '5')
        {
          myArray[5] = 'C';
          computerBlocked = true;
        }

       else if (myArray[5] == myArray[8]
            && myArray[5] == 'H' && myArray[2] == '2')
        {
          myArray[2] = 'C';
          computerBlocked = true;
        }
        //column 3

        //diagonal 1 (--0--4--8--)
       else if (myArray[0] == myArray[4]
            && myArray[4] == 'H' && myArray[8] == '8')
        {
          myArray[8] = 'C';
          computerBlocked = true;
        }

       else if (myArray[0] == myArray[8]
            && myArray[8] == 'H' && myArray[4] == '4')
        {
          myArray[4] = 'C';
          computerBlocked = true;
        }

       else if (myArray[8] == myArray[4]
            && myArray[4] == 'H' && myArray[0] == '0')
        {
          myArray[0] = 'C';
          computerBlocked = true;
        }
        //diagonal 1

        //diagonal 2 (--2--4--6--)
       else if (myArray[2] == myArray[4]
            && myArray[4] == 'H' && myArray[6] == '6')
        {
          myArray[6] = 'C';
          computerBlocked = true;
        }

      	else if (myArray[2] == myArray[6]
            && myArray[6] == 'H' && myArray[4] == '4')
        {
          myArray[4] = 'C';
          computerBlocked = true;
        }

        else if (myArray[4] == myArray[6]
            && myArray[6] == 'H' && myArray[2] == '2')
        {
          myArray[2] = 'C';
          computerBlocked = true;
        }
        //diagonal 2

	return computerBlocked;
    }//end computerMakeMove



