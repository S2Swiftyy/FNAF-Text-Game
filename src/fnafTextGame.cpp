#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace chrono;

enum location{LEFTDOOR, RIGHTDOOR, LEFT, RIGHT, KITCHEN, CLOSET, DINING, COVE, STAGE, SUPPLY};
enum foxyStuff{HIDING, PEEKING, REACHING, GONE};

string input;
int timer; //test value for now
int timerEnd; //test value for now, I want to make an actual timer at some point but for V1 I am going to make it turn based so it is a functional game
int nightUnlocked = 1;
string state;
bool dead;
int energy;
bool leftDoorOpen = true;
bool rightDoorOpen = true;
location freddyLoc;
location chicaLoc;
foxyStuff foxyLoc;
location bonnieLoc;
int nightSelected;
const int shortDelay = 2; //seconds
const int longDelay = 5; //seconds
int freddyDoorCount;
int bonnieDoorCount;
int chicaDoorCount;
int tempTimer;
const int flashDelay = 250; //miliseconds

int freddyMoveForwardValue;
int freddyMoveBackwardValue;
int bonnieMoveForwardValue;
int bonnieMoveBackwardValue;
int chicaMoveForwardValue;
int chicaMoveBackwardValue;
int foxyMoveForwardValue;


void startMenu();
void nightSelect(int);
void office();
void cams();
void clearInput();
void checkInput();
void checkLoc(location);
void clearScreen();
void doesFreddyMove();
void doesBonnieMove();
void doesChicaMove();
void doesFoxyMove();
void lightsOut();
void freddyDeath();
void bonnieDeath();
void chicaDeath();
void foxyDeath();
void playGame();
void checkFoxy();

void startMenu()
{
    clearScreen();
    cout<<"Five Nights at Freddy's\nbut in text format\n\nType \"Start\" to begin Night 1 or choose which Night to play by typing the number\nType \"Exit\" to quit\n";
    cout<<"Nights Unlocked - \n";
    switch (nightUnlocked)
    {
        case 1:
            cout<<"Night 1\n";
            break;
        case 2:
            cout<<"Night 1\n";
            cout<<"Night 2\n";
            break;
        case 3:
            cout<<"Night 1\n";
            cout<<"Night 2\n";
            cout<<"Night 3\n";
            break;
        case 4:
            cout<<"Night 1\n";
            cout<<"Night 2\n";
            cout<<"Night 3\n";
            cout<<"Night 4\n";
            break;
        case 5:
            cout<<"Night 1\n";
            cout<<"Night 2\n";
            cout<<"Night 3\n";
            cout<<"Night 4\n";
            cout<<"Night 5\n";
            break;
    }

    cin>>input;
    if((input == "Start") | (input == "start") | (input == "1"))
    {
        nightSelect(1);
    }
    else if((input == "2") && nightUnlocked >= 2)
    {
        nightSelect(2);
    }
    else if((input == "3") && nightUnlocked >= 3)
    {
        nightSelect(3);
    }
    else if((input == "4") && nightUnlocked >= 4)
    {
        nightSelect(4);
    }
    else if((input == "5") && nightUnlocked == 5)
    {
        nightSelect(5);
    }
    else if((input == "exit") | (input == "Exit"))
    {
        exit(0);
    }
    else
    {
        startMenu();
    }
}

void nightSelect(int i)
{
    clearScreen();

    switch(i)
    {
        case 1:
            nightSelected = 1;
            timerEnd = 300;
            freddyMoveBackwardValue = 35;
            freddyMoveForwardValue = 70;
            cout<<"NIGHT 1";
            this_thread::sleep_for(seconds(shortDelay));
            break;
        case 2:
            nightSelected = 2;
            timerEnd = 600;

            freddyMoveForwardValue = 60;
            freddyMoveBackwardValue = 30;
            
            bonnieMoveForwardValue = 60;
            bonnieMoveBackwardValue = 30;

            cout<<"NIGHT 2";
            this_thread::sleep_for(seconds(shortDelay));
            break;
        case 3:
            nightSelected = 3;
            timerEnd = 900;
            
            freddyMoveForwardValue = 55;
            freddyMoveBackwardValue = 25;
            
            bonnieMoveForwardValue = 55;
            bonnieMoveBackwardValue = 25;

            foxyMoveForwardValue = 75;

            cout<<"NIGHT 3";
            this_thread::sleep_for(seconds(shortDelay));
            break;
        case 4:
            nightSelected = 4;
            timerEnd = 1200;

            freddyMoveForwardValue = 50;
            freddyMoveBackwardValue = 20;

            bonnieMoveForwardValue = 50;
            bonnieMoveBackwardValue = 20;

            foxyMoveForwardValue = 65;

            chicaMoveForwardValue = 60;
            chicaMoveBackwardValue = 20;

            cout<<"NIGHT 4";
            this_thread::sleep_for(seconds(shortDelay));
            break;
        case 5:
            nightSelected = 5;
            timerEnd = 1500;

            freddyMoveForwardValue = 45;
            freddyMoveBackwardValue = 20;
            
            bonnieMoveForwardValue = 45;
            bonnieMoveBackwardValue = 20;

            foxyMoveForwardValue = 55;

            chicaMoveForwardValue = 50;
            chicaMoveBackwardValue = 20;

            cout<<"NIGHT 5";
            this_thread::sleep_for(seconds(shortDelay));
            break;
    }

    playGame();
}

void playGame()
{
    energy = 100;
    timer = 0;
    dead = false;
    
    clearInput(); 

    //set animatronics to starting locations
    freddyLoc = STAGE;
    chicaLoc = STAGE;
    foxyLoc = HIDING;
    bonnieLoc = STAGE;

    office(); //Always start the night in the office, sets state to office and prints the list of possible commands

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(dead == false && timer != timerEnd)
    {
        getline(cin, input);
        checkInput();
        clearInput();
        
        //AS THE NIGHTS PROGRESS IT GETS EASIER TO LOSE ENERGY AND MORE LIKELY FOR PPL TO MOVE TOWARDS YOU

        //In the OG game nobody is active on Night 1 but that is boring so Freddy is going to be active bc I can do what I want in my game
        if(nightSelected == 1)
        {
            doesFreddyMove();

            timer += 10;    //current iteration of the game is turn based and not time based so this increments the time

            //uses energy if doors are closed
            if(leftDoorOpen == false)
            {
                energy -= 2;
            }

            if(rightDoorOpen == false)
            {
                energy -= 2;
            }
        }
        else if(nightSelected == 2)
        {
            doesFreddyMove();
            doesBonnieMove();

            timer += 10;    //current iteration of the game is turn based and not time based so this increments the time

            //uses energy if doors are closed
            if(leftDoorOpen == false)
            {
                energy -= 4;
            }

            if(rightDoorOpen == false)
            {
                energy -= 4;
            }
        }
        else if(nightSelected == 3)
        {
            doesFreddyMove();
            doesBonnieMove();
            doesFoxyMove();

            timer += 10;

            //uses energy if doors are closed
            if(leftDoorOpen == false)
            {
                energy -= 5;
            }

            if(rightDoorOpen == false)
            {
                energy -= 5;
            }
        }
        else if(nightSelected == 4)
        {
            doesFreddyMove();
            doesBonnieMove();
            doesChicaMove();
            doesFoxyMove();

            //uses energy if doors are closed
            if(leftDoorOpen == false)
            {
                energy -= 6;
            }

            if(rightDoorOpen == false)
            {
                energy -= 6;
            }
        }
        else if(nightSelected == 5)
        {
            doesFreddyMove();
            doesBonnieMove();
            doesChicaMove();
            doesFoxyMove();

            //uses energy if doors are closed
            if(leftDoorOpen == false)
            {
                energy -= 7;
            }

            if(rightDoorOpen == false)
            {
                energy -= 7;
            }
        }

        if(energy <= 0)
        {
            lightsOut();
        }
    }

    if(timer == timerEnd)
    {
        clearScreen();
        cout<<"You Survived!\n";
        
        if(nightSelected == 1 && nightUnlocked < 2)
        {
            nightUnlocked = 2;
        }
        else if(nightSelected == 2 && nightUnlocked < 3)
        {
            nightUnlocked = 3;
        }
        else if(nightSelected == 3 && nightUnlocked < 4)
        {
            nightUnlocked = 4;
        }
        else if(nightSelected == 4 && nightUnlocked < 5)
        {
            nightUnlocked = 5;
        }

        if(nightSelected != 5)
        {
            cout<<"Night "<<nightUnlocked<<" now unlocked!";
        }
        else
        {
            cout<<"YOU WIN!";
        }

        this_thread::sleep_for(seconds(longDelay));
        clearScreen();
        startMenu();
    }
    else
    {
        clearScreen();
        cout<<"You Died!\n";
        this_thread::sleep_for(seconds(longDelay));
        clearScreen();
        startMenu();
    }
}

void checkInput()
{
    if(state == "office")
    {
        if((input == "Left door") | (input == "left door"))
        {
            if(leftDoorOpen == true)
            {
                leftDoorOpen = false;
                cout<<"Left door is now closed\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
            else
            {
                leftDoorOpen = true;
                cout<<"Left door is now open\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
        }
        else if((input == "Right door") | (input == "right door"))
        {
            if(rightDoorOpen == true)
            {
                rightDoorOpen = false;
                cout<<"Right door is now closed\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
            else
            {
                rightDoorOpen = true;
                cout<<"Right door is now open\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
        }
        else if((input == "Cam") | (input == "cam"))
        {
            cams();
        }
        else if((input == "Left light") | (input == "left light"))
        {
            energy--;

            //Tells player if any animatronics are present at the left door
            //Except for Foxy bc foxy does not wait at the door to attack
            if(freddyLoc == LEFTDOOR)
            {
                cout<<"Freddy is here!\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
            else if(bonnieLoc == LEFTDOOR)
            {
                cout<<"Bonnie is here!\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
            else if(chicaLoc == LEFTDOOR)
            {
                cout<<"Chica is here!\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
            else
            {
                cout<<"Coast is clear\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
        }
        else if((input == "Right light") | (input == "right light"))
        {
            energy--;

            //Tells player if any animatronics are present at the right door
            //Except for Foxy bc foxy does not attack the right door
            if(freddyLoc == RIGHTDOOR)
            {
                cout<<"Freddy is here!\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
            else if(bonnieLoc == RIGHTDOOR)
            {
                cout<<"Bonnie is here!\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
            else if(chicaLoc == RIGHTDOOR)
            {
                cout<<"Chica is here!\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
            else
            {
                cout<<"Coast is clear\n";
                this_thread::sleep_for(seconds(shortDelay));
                office();
            }
        }
        else if((input == "Wait") | (input == "wait"))
        {
            cout<<"Passing the time\n";
            this_thread::sleep_for(seconds(shortDelay));
            office();
        }
        else
        {
            cout<<"Bad Input - Try Again\n";
            this_thread::sleep_for(seconds(shortDelay));
            office();
        }
    }
    else if(state == "cams")
    {
        if((input == "Exit") | (input == "exit"))
        {
            office();
        }
        else if((input == "STAGE") | (input == "stage"))
        {
            checkLoc(STAGE);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "CLOSET") | (input == "closet"))
        {
            checkLoc(CLOSET);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "DINING") | (input == "dining"))
        {
            checkLoc(DINING);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "COVE") | (input == "cove"))
        {
            checkFoxy();
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "KITCHEN") | (input == "kitchen"))
        {
            checkLoc(KITCHEN);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "LEFT") | (input == "left"))
        {
            checkLoc(LEFT);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "RIGHT") | (input == "right"))
        {
            checkLoc(RIGHT);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "SUPPLY") | (input == "supply"))
        {
            checkLoc(SUPPLY);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else
        {
            cout<<"Bad Input - Try Again";
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
    }
}

void checkLoc(location lookingAt)
{
    bool seenSomeone = false;
    
    if(freddyLoc == lookingAt)
    {
        cout<<"Freddy is here!\n";
        seenSomeone = true;
    }

    if(chicaLoc == lookingAt)
    {
        cout<<"Chica is here!\n";
        seenSomeone = true;
    }

    if(bonnieLoc == lookingAt)
    {
        cout<<"Bonnie is here!\n";
        seenSomeone = true;
    }

    if(seenSomeone == false)
    {
        cout<<"Nobody here";
    }
}

void clearInput()
{
    input = "";
}

void office()
{
    state = "office";
    
    clearScreen();
    cout<<"You are in the office\n";
    cout<<"Time - " << timer << "\n";
    cout<<"Energy - " << energy << "%\n";

    if(leftDoorOpen == true)
    {
        cout<<"Left Door - Open\n";
    }
    else
    {
        cout<<"Left Door - Closed\n";
    }

    if(rightDoorOpen == true)
    {
        cout<<"Right Door - Open\n";
    }
    else
    {
        cout<<"Right Door - Closed\n\n";
    }

    cout<<"Type the following promts to take action\n\n";

    cout<<"\"Left door\" - Closes\\Opens the left door\n";
    cout<<"\"Right door\" - Closes\\Opens the right door\n";
    cout<<"\"Cam\" - Opens the cameras\n";
    cout<<"\"Left light\" - Tells you if an animatronic is at the left door\n";
    cout<<"\"Right light\" - Tells you if an animatronic is at the right door\n";
    cout<<"\"Wait\" - Passes the time\n";
}

void cams()
{
    state = "cams";
    
    clearScreen();
    cout<<"               _________\n";
    cout<<"              |         |\n";
    cout<<"              |  STAGE  |\n";
    cout<<"              |_________|\n";
    cout<<"                   |\n";
    cout<<" __________        |\n";
    cout<<"|          |     _________________________\n";
    cout<<"|  CLOSET  |----|                         |\n";
    cout<<"|__________|    |                         |\n";
    cout<<"                |                         |\n";
    cout<<"                |                         |\n";
    cout<<"     ________   |       DINING ROOM       |\n";
    cout<<"    |        |  |                         |\n";
    cout<<"    |  COVE  |--|                         |\n";
    cout<<"    |________|  |                         |\n";
    cout<<"                |_________________________|\n";
    cout<<"                    |              |     |\n";
    cout<<"                    |              |     |_________\n";
    cout<<"                    |              |     |         |\n";
    cout<<"                    |              |     | KITCHEN |\n";
    cout<<"   ________      ______         _______  |_________|\n";
    cout<<"  |        |    |      |       |       |\n";
    cout<<"  | SUPPLY |----| LEFT |       | RIGHT |\n";
    cout<<"  |________|    | HALL |       | HALL  |\n";
    cout<<"                |______|       |_______|\n";
    cout<<"                    |             |    \n";
    cout<<"                    |_____YOU_____|    \n";
    cout<<"                                       \n";

    cout<<"To check the location of the animatronics, type\n";
    cout<<"\"STAGE\" - to check the stage\n";
    cout<<"\"CLOSET\" - to check the close\n";
    cout<<"\"DINING\" - to check the dining room\n";
    cout<<"\"COVE\" - to check the cove\n";
    cout<<"\"KITCHEN\" - to check the kitchen\n";
    cout<<"\"SUPPLY\" - to check the supply closet\n";
    cout<<"\"LEFT\" - to check the left hallway\n";
    cout<<"\"RIGHT\" - to check the right hallway\n";
    cout<<"\"EXIT\" - to exit the cameras\n";
}

void clearScreen()
{
    for(int i = 0; i < 100; i++)
    {
        cout<<"\n";
    }
}

void doesFreddyMove()
{
	int rng = rand() % 101; //random number between 0 - 100
	
	bool moves = false;
	
	switch(nightSelected)
	{
		case 1:
			if(timer >= 40 && timer % 30 == 0) //Freddy moves if 4 moves have passed and every third move
			{
				moves = true;
			}
			break;
		case 2:
            if(timer >= 40 && timer % 30 == 0) //Freddy moves if 4 moves have passed and every third move
            {
                moves = true;
            }
			break;
		case 3:
            if(timer >= 40 && timer % 30 == 0) //Freddy moves if 4 moves have passed and every third move
            {
                moves = true;
            }
			break;
		case 4:
            if(timer >= 30 && timer % 30 == 0) //Freddy moves if 4 moves have passed and every third move
            {
                moves = true;
            }
			break;
		case 5:
            if(timer >= 10 && timer % 30 == 0) //Freddy moves if 4 moves have passed and every third move
            {
                moves = true;
            }
			break;
	}
	
	if(moves == true)
	{
		if(freddyLoc == STAGE)
        {
            if(rng >= 30)
            {
                freddyLoc = DINING;
            }
        }
        else if(freddyLoc == DINING)
        {
            int leftOrRight = 0;

            if(nightSelected > 3)
            {
                leftOrRight = rand() % 101;
            }
            
            if(rng >= (freddyMoveForwardValue - 30) && rng <= freddyMoveForwardValue)
            {
                freddyLoc = CLOSET;
            }
            else if(rng > freddyMoveForwardValue && leftOrRight >= 50) //unless it is night 4 or 5, leftOrRight is always 0, if it is N4/N5 then it is a 50/50 chance to go left or right
            {
                freddyLoc = RIGHT;
            }
            else if(rng > freddyMoveForwardValue && leftOrRight < 50)
            {
                freddyLoc = LEFT;
            }
        }
        else if(freddyLoc == CLOSET)
        {
            if(rng >= (freddyMoveForwardValue - 20))
            {
                freddyLoc = DINING;
            }
        }
        else if(freddyLoc == RIGHT)
        {
            if(rng >= freddyMoveForwardValue && chicaLoc != RIGHTDOOR && bonnieLoc != RIGHTDOOR)
            {
                freddyLoc = RIGHTDOOR;
                freddyDoorCount = 0; //the count of how long freddy has been at the door
            }
            else if(rng <= freddyMoveBackwardValue)
            {
                freddyLoc = DINING;
                        
				switch(nightSelected)
				{
					case 1:
						freddyMoveForwardValue = 70;
                        freddyMoveBackwardValue = 35;
						break;
					case 2:
                        freddyMoveForwardValue = 60;
                        freddyMoveBackwardValue = 30;
						break;
					case 3:
						freddyMoveForwardValue = 55;
                        freddyMoveBackwardValue = 25;
						break;
					case 4:
						freddyMoveForwardValue = 50;
                        freddyMoveBackwardValue = 20;
						break;
					case 5:
                        freddyMoveForwardValue = 45;
                        freddyMoveBackwardValue = 20;
						break;
				}
            }
        }
        else if(freddyLoc == LEFT)
        {
            if(rng >= freddyMoveForwardValue && chicaLoc != LEFTDOOR && bonnieLoc != LEFTDOOR)
            {
                freddyLoc = LEFTDOOR;
                freddyDoorCount = 0; //the count of how long freddy has been at the door
            }
            else if(rng <= freddyMoveBackwardValue)
            {
                freddyLoc = DINING;
                        
				switch(nightSelected)
				{
					case 1:
						freddyMoveForwardValue = 70;
                        freddyMoveBackwardValue = 35;
						break;
					case 2:
                        freddyMoveForwardValue = 60;
                        freddyMoveBackwardValue = 30;
						break;
					case 3:
						freddyMoveForwardValue = 55;
                        freddyMoveBackwardValue = 25;
						break;
					case 4:
						freddyMoveForwardValue = 50;
                        freddyMoveBackwardValue = 20;
						break;
					case 5:
                        freddyMoveForwardValue = 45;
                        freddyMoveBackwardValue = 20;
						break;
				}
            }
        }
        else if(freddyLoc == LEFTDOOR)
        {
            freddyDoorCount++;  //every move that he is there increments the count
                    
            //freddy can only kill you if he is allowed to move forward by the rng (75% chance) and the door is open
            if(rng >= 25 && leftDoorOpen == true)
            {
                freddyDeath();
            }
            else if(rng < 25)
            {
                freddyLoc = LEFT;

                //these values stay constant throughout nights bc freddy needs to back the fuck up, this makes it more likely that he retreats to the dining room
                freddyMoveForwardValue = 80; //changes the value required for freddy to move forward bc we want him to back away
                freddyMoveBackwardValue = 70; //changes the value required for freddy to move backwards bc we want him to back away
            }

            //if freddy has been camping the door too long without killing you then he must move back
            if(freddyDoorCount > 2)
            {
                freddyLoc = LEFT;
						
				//these values stay constant throughout nights bc freddy needs to back the fuck up
                freddyMoveForwardValue = 80;
                freddyMoveBackwardValue = 70;
            }
        }
        else if(freddyLoc == RIGHTDOOR)
        {
            freddyDoorCount++;  //every move that he is there increments the count
                    
            //freddy can only kill you if he is allowed to move forward by the rng (75% chance) and the door is open
            if(rng >= 25 && rightDoorOpen == true)
            {
                freddyDeath();
            }
            else if(rng < 25)
            {
                freddyLoc = RIGHT;

                //these values stay constant throughout nights bc freddy needs to back the fuck up, this makes it more likely that he retreats to the dining room
                freddyMoveForwardValue = 80; //changes the value required for freddy to move forward bc we want him to back away
                freddyMoveBackwardValue = 70; //changes the value required for freddy to move backwards bc we want him to back away
            }

            //if freddy has been camping the door too long without killing you then he must move back
            if(freddyDoorCount > 2)
            {
                freddyLoc = RIGHT;
						
				//these values stay constant throughout nights bc freddy needs to back the fuck up
                freddyMoveForwardValue = 80;
                freddyMoveBackwardValue = 70;
            }
        }
	}
}

void doesBonnieMove()
{
    int rng = rand() % 101; //random number between 0 - 100
    bool moves = false;

    switch(nightSelected)
    {
        case 2:
            if(timer >= 80 && timer % 30 == 0) //Bonnie moves every third move after 8 moves
            {
                moves = true;
            }
            break;
        case 3:
            if(timer >= 60 && timer % 30 == 0) //Bonnie moves if 6 moves have passed and every third move
            {
                moves = true;
            }
            break;
        case 4:
            if(timer >= 50 && timer % 30 == 0) //Bonnie moves if 5 moves have passed and every third move
            {
                moves = true;
            }
            break;
        case 5:
            if(timer >= 30 && timer % 30 == 0) //Bonnie moves if 3 moves have passed and every third move
            {
                moves = true;
            }
            break;
    }

    if(moves == true)
    {
        if(bonnieLoc == STAGE)
        {
            if(rng >= 40)
            {
                bonnieLoc = DINING;
            }
        }
        else if(bonnieLoc == DINING)
        {
            int leftOrRight = 0;

            if(nightSelected > 3)
            {
                leftOrRight = rand() % 101;
            }
            
            if(rng >= bonnieMoveForwardValue && leftOrRight >= 50)
            {
                bonnieLoc = RIGHT;
            }
            else if(rng >= bonnieMoveForwardValue)
            {
                bonnieLoc = LEFT;
            }
        }
        else if(bonnieLoc == RIGHT)
        {
            if(rng >= bonnieMoveForwardValue && freddyLoc != RIGHTDOOR && chicaLoc != RIGHTDOOR)
            {
                bonnieLoc = RIGHTDOOR;
                bonnieDoorCount = 0;
            }
            else if(rng <= bonnieMoveBackwardValue)
            {
                bonnieLoc = DINING;

                switch(nightSelected)
                {
                    case 2:
                        bonnieMoveForwardValue = 60;
                        bonnieMoveBackwardValue = 30;
                        break;
                    case 3:
                        bonnieMoveForwardValue = 55;
                        bonnieMoveBackwardValue = 25;
                        break;
                    case 4:
                        bonnieMoveForwardValue = 50;
                        bonnieMoveBackwardValue = 20;
                        break;
                    case 5:
                        bonnieMoveForwardValue = 45;
                        bonnieMoveBackwardValue = 20;
                        break;
                }
            }
        }
        else if(bonnieLoc == LEFT)
        {
            if(rng >= bonnieMoveForwardValue && freddyLoc != LEFTDOOR && chicaLoc != LEFTDOOR)
            {
                bonnieLoc = LEFTDOOR;
                bonnieDoorCount = 0;
            }
            else if(rng <= bonnieMoveBackwardValue)
            {
                bonnieLoc = DINING;

                switch(nightSelected)
                {
                    case 2:
                        bonnieMoveForwardValue = 60;
                        bonnieMoveBackwardValue = 30;
                        break;
                    case 3:
                        bonnieMoveForwardValue = 55;
                        bonnieMoveBackwardValue = 25;
                        break;
                    case 4:
                        bonnieMoveForwardValue = 50;
                        bonnieMoveBackwardValue = 20;
                        break;
                    case 5:
                        bonnieMoveForwardValue = 45;
                        bonnieMoveBackwardValue = 20;
                        break;
                }
            }
            else if(rng >= bonnieMoveForwardValue - 20 && rng < bonnieMoveForwardValue)
            {
                bonnieLoc = SUPPLY;
            }
        }
        else if(bonnieLoc == SUPPLY)
        {
            if(rng >= bonnieMoveForwardValue)
            {
                bonnieLoc = LEFT;
            }
        }
        else if(bonnieLoc == LEFTDOOR)
        {
            bonnieDoorCount++;
            
            if(rng >= 25 && leftDoorOpen == true)
            {
                bonnieDeath();
            }
            else if(rng < 25)
            {
                bonnieLoc = LEFT;

                //bonnie has already been to the door so he needs to back the fuck up
                bonnieMoveForwardValue = 80;
                bonnieMoveBackwardValue = 70;
            }

            if(bonnieDoorCount > 2)
            {
                bonnieLoc = LEFT;

                bonnieMoveForwardValue = 80;
                bonnieMoveBackwardValue = 70;
            }
        }
        else if(bonnieLoc == RIGHTDOOR)
        {
            bonnieDoorCount++;
            
            if(rng >= 25 && rightDoorOpen == true)
            {
                bonnieDeath();
            }
            else if(rng < 25)
            {
                bonnieLoc = RIGHT;

                //bonnie has already been to the door so he needs to back the fuck up
                bonnieMoveForwardValue = 80;
                bonnieMoveBackwardValue = 70;
            }

            if(bonnieDoorCount > 2)
            {
                bonnieLoc = RIGHT;

                bonnieMoveForwardValue = 80;
                bonnieMoveBackwardValue = 70;
            }
        }
    }
}

void lightsOut()
{
    cout<<"NO MORE POWER\n";
    this_thread::sleep_for(seconds(shortDelay));

    if(leftDoorOpen == false)
    {
        leftDoorOpen = true;
        cout<<"Left door opened!\n";
    }

    if(rightDoorOpen == false)
    {
        rightDoorOpen = true;
        cout<<"Right door opened!\n";
    }

    freddyDeath();
}

void doesFoxyMove()
{
    int rng = rand() % 101;
    bool moves = false;

    if(nightSelected == 3)
    {
        if(timer > 100 && timer % 20 == 0)
        {
            moves = true;
        }
    }
    else if(nightSelected == 4)
    {
        if(timer > 80 && timer % 20 == 0)
        {
            moves = true;
        }
    }
    else if(nightSelected == 5)
    {
        if(timer > 60 && timer % 20 == 0)
        {
            moves = true;
        }
    }

    if(moves == true)
    {
        switch(foxyLoc)
        {
            case HIDING:
                if(rng >= foxyMoveForwardValue)
                {
                    foxyLoc = PEEKING;
                }
                break;
            case PEEKING:
                if(rng >= foxyMoveForwardValue)
                {
                    foxyLoc = REACHING;
                }
                break;
            case REACHING:
                if(rng >= foxyMoveForwardValue)
                {
                    foxyLoc = GONE;
                    tempTimer = timer + 20; //You get 2 moves to react
                    cout<<"\nYou hear running!\n";
                }
                break;
            case GONE:
                if(timer == tempTimer)
                {
                    if(leftDoorOpen == true)
                    {
                        foxyDeath();
                    }
                    else
                    {
                        cout<<"\nTHUD!\n";
                        foxyLoc = HIDING;
                    }
                }
                break;
        }
    }
}

void doesChicaMove()
{
    int rng = rand() % 101;
    bool moves = false;

    if(nightSelected == 4)
    {
        if(timer > 110 && timer % 20 == 0)
        {
            moves = true;
        }
    }
    else if(nightSelected == 5)
    {
        if(timer > 90 && timer % 20 == 0)
        {
            moves = true;
        }
    }

    if(moves == true)
    {
    
        if(chicaLoc == STAGE)
        {
            if(rng >= chicaMoveForwardValue)
            {
                chicaLoc = DINING;
            }
        }
        else if(chicaLoc == DINING)
        {
            int leftOrRight = rand() % 101;

            if(rng >= chicaMoveForwardValue && leftOrRight < 50)
            {
                chicaLoc = LEFT;
            }
            else if(rng >= chicaMoveForwardValue - 20 && rng < chicaMoveForwardValue)
            {
                chicaLoc = KITCHEN;
            }
            else if(rng >= chicaMoveForwardValue && leftOrRight >= 50)
            {
                chicaLoc = RIGHT;
            }
        }
        else if(chicaLoc == KITCHEN)
        {
            if(rng >= chicaMoveForwardValue)
            {
                chicaLoc = DINING;
            }
        }
        else if(chicaLoc == LEFT)
        {
            if(rng >= chicaMoveForwardValue && freddyLoc != LEFTDOOR && bonnieLoc != LEFTDOOR)
            {
                chicaLoc = LEFTDOOR;
                chicaDoorCount = 0; //the count of how long Chcia has been at the door
            }
            else if(rng <= chicaMoveBackwardValue)
            {
                chicaLoc = DINING;
                      
    		    switch(nightSelected)
    		    {
				    case 4:
					    chicaMoveForwardValue = 60;
                        chicaMoveBackwardValue = 20;
    				    break;
    				case 5:
                        chicaMoveForwardValue = 50;
                        chicaMoveBackwardValue = 20;
    		    		break;
			    }
            }
        }
        else if(chicaLoc == RIGHT)
        {
            if(rng >= chicaMoveForwardValue && freddyLoc != RIGHTDOOR && bonnieLoc != RIGHTDOOR)
            {
                chicaLoc = RIGHTDOOR;
                chicaDoorCount = 0; //the count of how long Chcia has been at the door
            }
            else if(rng <= chicaMoveBackwardValue)
            {
                chicaLoc = DINING;
                      
    		    switch(nightSelected)
    		    {
				    case 4:
					    chicaMoveForwardValue = 60;
                        chicaMoveBackwardValue = 20;
    				    break;
    				case 5:
                        chicaMoveForwardValue = 50;
                        chicaMoveBackwardValue = 20;
    		    		break;
			    }
            }
        }
        else if(chicaLoc == LEFTDOOR)
        {
            chicaDoorCount++;
            
            if(rng >= 25 && leftDoorOpen == true)
            {
                chicaDeath();
            }
            else if(rng < 25)
            {
                chicaLoc = LEFT;

                //Chica has already been to the door so she needs to back the fuck up
                chicaMoveForwardValue = 80;
                chicaMoveBackwardValue = 70;
            }

            if(chicaDoorCount > 2)
            {
                chicaLoc = LEFT;

                chicaMoveForwardValue = 80;
                chicaMoveBackwardValue = 70;
            }
        }
        else if(chicaLoc == RIGHTDOOR)
        {
            chicaDoorCount++;
            
            if(rng >= 25 && rightDoorOpen == true)
            {
                chicaDeath();
            }
            else if(rng < 25)
            {
                chicaLoc = RIGHT;

                //Chica has already been to the door so she needs to back the fuck up
                chicaMoveForwardValue = 80;
                chicaMoveBackwardValue = 70;
            }

            if(chicaDoorCount > 2)
            {
                chicaLoc = RIGHT;

                chicaMoveForwardValue = 80;
                chicaMoveBackwardValue = 70;
            }
        }
    }   
}

void freddyDeath()
{
    for(int i = 0; i < 10; i++)
    {
        if( i % 2 == 0)
        {
            clearScreen();
            this_thread::sleep_for(milliseconds(flashDelay));
        }
        else
        {
            cout<<"                             %%%           %%####****#####%%       %*******%                        \n                                      %########      %###*###****+******##%   ###%%%%%%##%                      \n                                    %*#%%%%%%%%#%  %%#######*##*******######  *%#####%% ##                      \n                                    #*  %#######% %%%       %###**%        ## %###*###%%*#                      \n                                    %*% %####### %%     %%%##*##***##%%#%%%### %#%##%%#**%                      \n                                     #*#%%%%###  %% %%%%%  %%##****%    %#*#### %#%##**#                        \n                                      %####%%#% %%%%#%       %#***%       %*###%   %%%                          \n                                                %%%##          %%          *###%                                \n                                                 %%##            %#%      %**##%                                \n                                                %%%%##%#####%%%%%%%#####****####%                               \n                                              %%%%%###****+++++++**++++++++****###%                             \n                                              %%%%%##****++++++++**+++++++++++####%                             \n                                              % %%%#*******++++++***++++++++*****#%                             \n                                                %%####*********+***************##%                              \n                                                  %%%%########***####***########%                               \n                                                          %%%%%%#%%%%%%%%%%%  %                                 \n                                     %%                                      %#                                 \n                               %%######%                                   ###*##%  %%                         %\n            ####%%%%%%    %%%####***###%                                   #*#*#*##%#*##%%                   %%#\n            ##**##%###%%%%####********%                                    #***#**##+****##%                  %#\n            *****############******+**                                     %#**####*******###%          %%      \n            +*********#####***+******#            %###                     %#**#######******###%  %%##%         \n            ******##**######**####**##            %%###%                  ##**#%%%%####*****###%%####%          \n            *****#########%%##########              #****#%%#%%%###%%####*****%    %%###########%####%          \n            #**#####%%%#%%  %%%%%%%%%%               %##**##***+**###*****##%%       %%%%%#####%%####%          \n            #######%%%%%                                %%%#%####%%%%%#%%%%%%          %%%%%%##%%######%%%%%%   \n            %%%%%%%%                                                     %%%%%              %%%%%%##%%%%%%##%   \n                                                                         %%%%%                      %%%%%%      \n                                                                         %%%%                                   \n                                                                        %*#%%                                   \n";
            this_thread::sleep_for(milliseconds(flashDelay));
        }

        dead = true;
    }
}

void bonnieDeath()
{
    for(int i = 0; i < 10; i++)
    {
        if(i % 2 == 0)
        {
            clearScreen();
            this_thread::sleep_for(milliseconds(flashDelay));
        }
        else
        {
            
            ifstream file("bonnie_scare.txt");

            string line;

            if(!file.is_open())
            {
                cout<<"ERROR\n";
            }

            while(getline(file, line))
            {
                cout<<line<<"\n";
            }

            file.close();

            this_thread::sleep_for(milliseconds(flashDelay));
        }

        dead = true;
    }
}

void foxyDeath()
{
    for(int i = 0; i < 10; i++)
    {
        if(i % 2 == 0)
        {
            clearScreen();
            this_thread::sleep_for(milliseconds(flashDelay));
        }
        else
        {
            
            ifstream file("foxy_scare.txt");

            string line;

            if(!file.is_open())
            {
                cout<<"ERROR\n";
            }

            while(getline(file, line))
            {
                cout<<line<<"\n";
            }

            file.close();

            this_thread::sleep_for(milliseconds(flashDelay));
        }

        dead = true;
    }
}

void chicaDeath()
{
    for(int i = 0; i < 10; i++)
    {
        if(i % 2 == 0)
        {
            clearScreen();
            this_thread::sleep_for(milliseconds(flashDelay));
        }
        else
        {
            
            ifstream file("chica_scare.txt");

            string line;

            if(!file.is_open())
            {
                cout<<"ERROR\n";
            }

            while(getline(file, line))
            {
                cout<<line<<"\n";
            }

            file.close();

            this_thread::sleep_for(milliseconds(flashDelay));
        }

        dead = true;
    }
}

void checkFoxy()
{
    if(foxyLoc == HIDING)
    {
        ifstream file("stage_1.txt");
        
        string line;

        while(getline(file, line))
        {
            cout<<line<<"\n";
        }
    }
    else if(foxyLoc == PEEKING)
    {
        ifstream file("stage_2.txt");
        
        string line;

        while(getline(file, line))
        {
            cout<<line<<"\n";
        }
    }
    else if(foxyLoc == REACHING)
    {
        ifstream file("stage_3.txt");
        
        string line;

        while(getline(file, line))
        {
            cout<<line<<"\n";
        }
    }
    else if(foxyLoc == GONE)
    {
        ifstream file("stage_4.txt");

        string line;

        while(getline(file, line))
        {
            cout<<line<<"\n";
        }
    }
}

int main()
{
    startMenu();
    
    return 0;
}
