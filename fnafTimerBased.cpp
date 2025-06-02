#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>
#include <fstream>
#include <thread>
#include <atomic>
using namespace std;
using namespace chrono;

enum location{LEFTDOOR, RIGHTDOOR, LEFT, RIGHT, KITCHEN, CLOSET, DINING, COVE, STAGE, SUPPLY};
enum foxyStuff{HIDING, PEEKING, REACHING, GONE};

string input;
atomic<int> timerValue(0);
atomic<bool> gameRunning(false);
int timerEnd;
int nightUnlocked = 1;
string state;
bool dead;
atomic<int> energy(100);
bool leftDoorOpen = true;
bool rightDoorOpen = true;
location freddyLoc;
location chicaLoc;
foxyStuff foxyLoc;
location bonnieLoc;
int nightSelected;
const int shortDelay = 2; //seconds
const int longDelay = 4; //seconds
int freddyDoorCount;
int bonnieDoorCount;
int chicaDoorCount;
int tempTimer;
const int flashDelay = 250; //miliseconds
atomic<int> lastFreddyMoveTime(0);
atomic<int> lastBonnieMoveTime(0);
atomic<int> lastFoxyMoveTime(0);
atomic<int> lastChicaMoveTime(0);
atomic<bool> gameOver(false);

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
void loadGame();
void saveGame();

void timer()
{
    while(gameRunning)
    {
        this_thread::sleep_for(seconds(1));
        ++timerValue;
    }
}

void energyCheck()
{
    while(gameRunning)
    {
        bool lostEnergy = false;
        
        switch(nightSelected)
        {
            case 1:
                if(leftDoorOpen == false)
                {
                    energy -= 1;
                    lostEnergy = true;
                }

                if(leftDoorOpen == false)
                {
                    energy -= 1;
                    lostEnergy = true;
                }

                break;
            case 2:
                if(leftDoorOpen == false)
                {
                    energy -= 2;
                    lostEnergy = true;
                }

                if(leftDoorOpen == false)
                {
                    energy -= 2;
                    lostEnergy = true;
                }

                break;
            case 3:
                if(leftDoorOpen == false)
                {
                    energy -= 3;
                    lostEnergy = true;
                }

                if(leftDoorOpen == false)
                {
                    energy -= 3;
                    lostEnergy = true;
                }

                break;
            case 4:
                if(leftDoorOpen == false)
                {
                    energy -= 4;
                    lostEnergy = true;
                }

                if(leftDoorOpen == false)
                {
                    energy -= 4;
                    lostEnergy = true;
                }

                break;
            case 5:
                if(leftDoorOpen == false)
                {
                    energy -= 5;
                    lostEnergy = true;
                }

                if(leftDoorOpen == false)
                {
                    energy -= 5;
                    lostEnergy = true;
                }

                break;
        }

        if(energy <= 0)
        {
            lightsOut();
        }

        if(lostEnergy == true)
        {
            this_thread::sleep_for(seconds(2));
        }
    }
}

void animatronicMoves()
{
    while(gameRunning)
    {
        switch(nightSelected)
        {
            case 1:
                doesFreddyMove();
                break;
            case 2:
                doesFreddyMove();
                doesBonnieMove();
                break;
            case 3:
                doesFreddyMove();
                doesBonnieMove();
                doesFoxyMove();
                break;
            case 4:
                doesFreddyMove();
                doesBonnieMove();
                doesFoxyMove();
                doesChicaMove();
                break;
            case 5:
                doesFreddyMove();
                doesBonnieMove();
                doesFoxyMove();
                doesChicaMove();
                break;
        }
    }
}

void winOrDie()
{
    while(gameRunning)
    {
        if(timerValue >= timerEnd)
        {
            gameRunning = false;
            gameOver = true;
            
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

            cout<<"\n\nPress Enter to Continue\n";
            
            return;
        }
        else if(dead == true)
        {
            gameRunning = false;
            gameOver = true;
            
            this_thread::sleep_for(seconds(longDelay));

            clearScreen();
            cout<<"You Died!\n";
            this_thread::sleep_for(seconds(longDelay));
            
            cout<<"\n\nPress Enter to Continue\n";

            return;
        }
    }
}

void startMenu()
{
    clearScreen();
    cout<<"Five Nights at Freddy's\nbut in text format\n\nType \"Start\" to begin Night 1 or choose which Night to play by typing the number\nType \"Load\" to load a save\nType \"Save\" to save game\nType \"Exit\" to quit\n";
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
    else if((input == "Load") | (input == "load") | (input == "l"))
    {
        loadGame();
    }
    else if((input == "Save") | (input == "save") | (input == "s"))
    {
        saveGame();
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
            timerEnd = 180;
            freddyMoveBackwardValue = 35;
            freddyMoveForwardValue = 70;
            cout<<"NIGHT 1";
            this_thread::sleep_for(seconds(shortDelay));
            break;
        case 2:
            nightSelected = 2;
            timerEnd = 300;

            freddyMoveForwardValue = 60;
            freddyMoveBackwardValue = 30;
            
            bonnieMoveForwardValue = 60;
            bonnieMoveBackwardValue = 30;

            cout<<"NIGHT 2";
            this_thread::sleep_for(seconds(shortDelay));
            break;
        case 3:
            nightSelected = 3;
            timerEnd = 360;
            
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
            timerEnd = 420;

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
            timerEnd = 480;

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
    timerValue = 0;
    dead = false;
    leftDoorOpen = true;
    rightDoorOpen = true;

    gameRunning = true;

    //constantly counts up while the game is running
    thread t(timer);
    t.detach();

    //constantly uses energy if the doors are in use
    thread e(energyCheck);
    e.detach();

    //constantly moves animatronics
    thread a(animatronicMoves);
    a.detach();

    //constantly checks if you have died or survived
    thread w(winOrDie);
    w.detach();
    
    clearInput(); 

    //set animatronics to starting locations
    freddyLoc = STAGE;
    chicaLoc = STAGE;
    foxyLoc = HIDING;
    bonnieLoc = STAGE;

    office(); //Always start the night in the office, sets state to office and prints the list of possible commands

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(gameRunning && !dead && timerValue < timerEnd)
    {
        getline(cin, input);
        
        if(gameRunning == true)
        {
            checkInput();
            clearInput();
        }
    }

    cin.clear();

    startMenu();

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
        if((input == "Exit") | (input == "exit") | (input == "e"))
        {
            office();
        }
        else if((input == "STAGE") | (input == "stage") | (input == "1"))
        {
            checkLoc(STAGE);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "CLOSET") | (input == "closet") | (input == "2"))
        {
            checkLoc(CLOSET);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "DINING") | (input == "dining") | (input == "4"))
        {
            checkLoc(DINING);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "COVE") | (input == "cove") | (input == "3"))
        {
            checkFoxy();
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "KITCHEN") | (input == "kitchen") | (input == "8"))
        {
            checkLoc(KITCHEN);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "LEFT") | (input == "left") | (input == "6"))
        {
            checkLoc(LEFT);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "RIGHT") | (input == "right") | (input == "7"))
        {
            checkLoc(RIGHT);
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "SUPPLY") | (input == "supply") | (input == "5"))
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
    cout<<"Time - " << timerValue << "\n";
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
    cout<<"\"Wait\" - Passes the time / Update displayed time\n";
}

void cams()
{
    state = "cams";
    
    clearScreen();
    cout<<"               _________\n";
    cout<<"              |         |\n";
    cout<<"              | 1-STAGE |\n";
    cout<<"              |_________|\n";
    cout<<"                   |\n";
    cout<<" __________        |\n";
    cout<<"|          |     _________________________\n";
    cout<<"| 2-CLOSET |----|                         |\n";
    cout<<"|__________|    |                         |\n";
    cout<<"                |                         |\n";
    cout<<"                |                         |\n";
    cout<<"     ________   |      4-DINING ROOM      |\n";
    cout<<"    |        |  |                         |\n";
    cout<<"    | 3-COVE |--|                         |\n";
    cout<<"    |________|  |                         |\n";
    cout<<"                |_________________________|\n";
    cout<<"                    |              |     |\n";
    cout<<"                    |              |     |_________\n";
    cout<<"                    |              |     |    8-   |\n";
    cout<<"                    |              |     | KITCHEN |\n";
    cout<<"   ________      ______         _______  |_________|\n";
    cout<<"  |        |    |  6-  |       |   7-  |\n";
    cout<<"  |5-SUPPLY|----| LEFT |       | RIGHT |\n";
    cout<<"  |________|    | HALL |       | HALL  |\n";
    cout<<"                |______|       |_______|\n";
    cout<<"                    |             |    \n";
    cout<<"                    |_____YOU_____|    \n";
    cout<<"                                       \n";

    cout<<"To check the location of the animatronics, type the corresponding number or \n";
    cout<<"\"1\" or \"STAGE\" - to check the stage\n";
    cout<<"\"2\" or \"CLOSET\" - to check the close\n";
    cout<<"\"3\" or \"COVE\" - to check the cove\n";
    cout<<"\"4\" or \"DINING\" - to check the dining room\n";
    cout<<"\"5\" or \"SUPPLY\" - to check the supply closet\n";
    cout<<"\"6\" or \"LEFT\" - to check the left hallway\n";
    cout<<"\"7\" or \"RIGHT\" - to check the right hallway\n";
    cout<<"\"8\" or \"KITCHEN\" - to check the kitchen\n";
    cout<<"\"e\" or \"EXIT\" - to exit the cameras\n";
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
	
    if(timerValue.load() != lastFreddyMoveTime.load())
    {
        switch(nightSelected)
        {
            case 1:
                if(timerValue >= 30 && timerValue % 15 == 0) //Freddy moves if 30 seconds have passed and moves every 15 seconds
                {
                    moves = true;
                    lastFreddyMoveTime.store(timerValue);
                }
                break;
            case 2:
                if(timerValue >= 20 && timerValue % 15 == 0) //Freddy moves every 15 seconds after 20 seconds
                {
                    moves = true;
                    lastFreddyMoveTime.store(timerValue);
                }
                break;
            case 3:
                if(timerValue % 15 == 0) //Freddy moves every 15 seconds
                {
                    moves = true;
                    lastFreddyMoveTime.store(timerValue);
                }
                break;
            case 4:
                if(timerValue % 15 == 0) //Freddy moves every 15 seconds
                {
                    moves = true;
                    lastFreddyMoveTime.store(timerValue);
                }
                break;
            case 5:
                if(timerValue % 12 == 0) //Freddy moves every 10 seconds
                {
                    moves = true;
                    lastFreddyMoveTime.store(timerValue);
                }
                break;
        }

        if((freddyLoc == LEFTDOOR || freddyLoc == RIGHTDOOR) && timerValue >= (freddyDoorCount - 10))
        {
            moves = true;
            lastFreddyMoveTime.store(timerValue);
        }
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
                freddyDoorCount = timerValue + 15;
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
                freddyDoorCount = timerValue + 15;
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
            if(freddyDoorCount == timerValue)
            {
                freddyLoc = LEFT;
						
				//these values stay constant throughout nights bc freddy needs to back the fuck up
                freddyMoveForwardValue = 80;
                freddyMoveBackwardValue = 70;
            }
        }
        else if(freddyLoc == RIGHTDOOR)
        {
                    
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
            if(freddyDoorCount == timerValue)
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

    if(timerValue.load() != lastBonnieMoveTime.load())
    {
        switch(nightSelected)
        {
            case 2:
                if(timerValue >= 40 && timerValue % 20 == 0) //Bonnie moves every 20 seconds move after 40 seconds
                {
                    moves = true;
                    lastBonnieMoveTime.store(timerValue);
                }
                break;
            case 3:
                if(timerValue >= 30 && timerValue % 20 == 0)
                {
                    moves = true;
                    lastBonnieMoveTime.store(timerValue);
                }
                break;
            case 4:
                if(timerValue % 20 == 0)
                {
                    moves = true;
                    lastBonnieMoveTime.store(timerValue);
                }
                break;
            case 5:
                if(timerValue % 15 == 0)
                {
                    moves = true;
                    lastBonnieMoveTime.store(timerValue);
                }
                break;
        }

        if((bonnieLoc == LEFTDOOR || bonnieLoc == RIGHTDOOR) && timerValue >= (bonnieDoorCount - 10))
        {
            moves = true;
            lastBonnieMoveTime.store(timerValue);
        }
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
                bonnieDoorCount = timerValue + 15;
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
                bonnieDoorCount = timerValue + 15;
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

            if(bonnieDoorCount == timerValue)
            {
                bonnieLoc = LEFT;

                bonnieMoveForwardValue = 80;
                bonnieMoveBackwardValue = 70;
            }
        }
        else if(bonnieLoc == RIGHTDOOR)
        {
            
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

            if(bonnieDoorCount == timerValue)
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

    gameRunning = false;
    freddyDeath();
}

void doesFoxyMove()
{
    int rng = rand() % 101;
    bool moves = false;

    if(timerValue.load() != lastFoxyMoveTime.load())
    {
        if(nightSelected == 3)
        {
            if(timerValue > 60 && timerValue % 20 == 0)
            {
                moves = true;
                lastFoxyMoveTime.store(timerValue);
            }
        }
        else if(nightSelected == 4)
        {
            if(timerValue > 45 && timerValue % 20 == 0)
            {
                moves = true;
                lastFoxyMoveTime.store(timerValue);
            }
        }
        else if(nightSelected == 5)
        {
            if(timerValue > 30 && timerValue % 20 == 0)
            {
                moves = true;
                lastFoxyMoveTime.store(timerValue);
            }
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
                    tempTimer = timerValue + 10; //You get 10 seconds to react
                    cout<<"\nYou hear running!\n";
                }
                break;
            case GONE:
                if(timerValue == tempTimer)
                {
                    if(leftDoorOpen == true)
                    {
                        foxyDeath();
                    }
                    else
                    {
                        cout<<"\nBNAG!!\n";
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

    if(timerValue.load() != lastChicaMoveTime.load())
    {
        if(nightSelected == 4)
        {
            if(timerValue >= 60 && timerValue % 20 == 0)
            {
                moves = true;
                lastChicaMoveTime.store(timerValue);
            }
        }
        else if(nightSelected == 5)
        {
            if(timerValue >= 40 && timerValue % 20 == 0)
            {
                moves = true;
                lastChicaMoveTime.store(timerValue);
            }
        }

        if((chicaLoc == LEFTDOOR || chicaLoc == RIGHTDOOR) && timerValue >= (chicaDoorCount - 10))
        {
            moves = true;
            lastChicaMoveTime.store(timerValue);
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
                chicaDoorCount = timerValue + 15;
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
                chicaDoorCount = timerValue + 15;
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

            if(chicaDoorCount == timerValue)
            {
                chicaLoc = LEFT;

                chicaMoveForwardValue = 80;
                chicaMoveBackwardValue = 70;
            }
        }
        else if(chicaLoc == RIGHTDOOR)
        {
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

            if(chicaDoorCount == timerValue)
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

void loadGame()
{
    ifstream saveFile("gameSave.txt");
    
    int savedNight;

    saveFile >> savedNight;

    if(savedNight <= 5 && savedNight >= 1)
    {
        nightUnlocked = savedNight;
    }
    else
    {
        cout<<"Corrupted saved file!";
        this_thread::sleep_for(seconds(shortDelay));
    }

    clearScreen();
    startMenu();
}

void saveGame()
{
    ofstream saveFile("gameSave.txt", ios::trunc);

    if(saveFile.is_open())
    {
        saveFile << nightUnlocked;
        saveFile.close();
        cout<<"Game Saved!";
        this_thread::sleep_for(seconds(shortDelay));
    }
    else
    {
        cout<<"Error: Game Not Saved";
        this_thread::sleep_for(seconds(shortDelay));
    }
    

    clearScreen();
    startMenu();
}

int main()
{
    startMenu();

    return 0;
}