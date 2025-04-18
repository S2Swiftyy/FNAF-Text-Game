#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>
using namespace std;
using namespace chrono;

enum location{LEFTDOOR, RIGHTDOOR, LEFT, RIGHT, KITCHEN, CLOSET, DINING, COVE, STAGE};

string input;
int timer = 0; //test value for now
const int timerEnd = 300; //test value for now, I want to make an actual timer at some point but for V1 I am going to make it turn based so it is a functional game
int nightUnlocked = 1;
string state;
bool dead = false;
int energy = 100;
bool leftDoorOpen = true;
bool rightDoorOpen = true;
location freddyLoc;
location chicaLoc;
location foxyLoc;
location bonnieLoc;
location lookingAt;
int nightSelected;
const int shortDelay = 2; //seconds
const int longDelay = 5; //seconds
int freddyDoorCount;
const int flashDelay = 250; //miliseconds

void startMenu();
void night1();
void night2();
void night3();
void night4();
void night5();
void office();
void cams();
void clearInput();
void checkInput();
void checkLoc();
void clearScreen();
void doesFreddyMove();
void lightsOut();
void freddyDeath();

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
        night1();
    }
    else if((input == "2"))
    {
        //night2();
    }
    else if((input == "3"))
    {
        //night3();
    }
    else if((input == "4"))
    {
        //night4();
    }
    else if((input == "5"))
    {
        //night5();
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

void night1()
{
    energy = 100;
    timer = 0;
    dead = false;
    
    clearScreen();
    cout<<"NIGHT 1";
    this_thread::sleep_for(seconds(shortDelay));
    
    clearInput(); 
    nightSelected = 1;

    //set animatronics to starting locations
    //Freddy is the only one active on Night 1 so we only need to deal with him for now
    //In the OG game nobody is active on Night 1 but that is boring so Freddy is going to be active bc I can do what I want in my game
    freddyLoc = STAGE;
    chicaLoc = STAGE;
    foxyLoc = COVE;
    bonnieLoc = STAGE;

    office(); //Always start the night in the office, sets state to office and prints the list of possible commands

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(dead == false && timer != timerEnd)
    {
        getline(cin, input);
        checkInput();
        clearInput();
        
        //Freddy is active on Night 1 after 3 actions
        if(timer >= 30 && timer % 20 == 0)
        {
            doesFreddyMove();
        }
        
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

        if(energy <= 0)
        {
            lightsOut();
        }
    }

    if(timer == timerEnd)
    {
        clearScreen();
        cout<<"You Survived!\nNight 2 now unlocked";
        nightUnlocked = 2;
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
            lookingAt = STAGE;
            checkLoc();
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "CLOSET") | (input == "closet"))
        {
            lookingAt = CLOSET;
            checkLoc();
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "DINING") | (input == "dining"))
        {
            lookingAt = DINING;
            checkLoc();
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "COVE") | (input == "cove"))
        {
            lookingAt = COVE;
            checkLoc();
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "KITCHEN") | (input == "kitchen"))
        {
            lookingAt = KITCHEN;
            checkLoc();
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "LEFT") | (input == "left"))
        {
            lookingAt = LEFT;
            checkLoc();
            this_thread::sleep_for(seconds(shortDelay));
            cams();
        }
        else if((input == "RIGHT") | (input == "right"))
        {
            lookingAt = RIGHT;
            checkLoc();
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

void checkLoc()
{
    bool seenSomeone = false;
    
    if(freddyLoc == lookingAt)
    {
        cout<<"Freddy is here!\n";
        seenSomeone = true;
    }

    if(foxyLoc == lookingAt)
    {
        cout<<"Foxy is here!\n";
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
    cout<<"                 ______         _______  |_________|\n";
    cout<<"                |      |       |       |\n";
    cout<<"                | LEFT |       | RIGHT |\n";
    cout<<"                | HALL |       | HALL  |\n";
    cout<<"                |______|       |_______|\n\n";

    cout<<"To check the location of the animatronics, type\n";
    cout<<"\"STAGE\" - to check the stage\n";
    cout<<"\"CLOSET\" - to check the close\n";
    cout<<"\"DINING\" - to check the dining room\n";
    cout<<"\"COVE\" - to check the cove\n";
    cout<<"\"KITCHEN\" - to check the kitchen\n";
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
    
    //Further along in the game, it is more likely that Freddy moves towards the player and less likely he moves away
    //Lower value location type means closer to player
    switch (nightSelected)
    {
        case 1: //Currently on Night 1
            
            if(freddyLoc == STAGE)
            {
                if(rng >= 50)
                {
                    freddyLoc = DINING;
                }
            }
            else if(freddyLoc == DINING)
            {
                if(rng >= 50 && rng <= 70)
                {
                    freddyLoc = CLOSET;
                }
                else if(rng > 70)
                {
                    freddyLoc = LEFT;
                }
            }
            else if(freddyLoc == CLOSET)
            {
                if(rng >= 55)
                {
                    freddyLoc = DINING;
                }
            }
            else if(freddyLoc == LEFT)
            {
                if(rng >= 70)
                {
                    freddyLoc = LEFTDOOR;
                    freddyDoorCount = 0; //the count of how long freddy has been at the door
                }
                else if(rng <= 35)
                {
                    freddyLoc = DINING;
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
                }

                //if freddy has been camping the door too long without killing you then he must move back
                if(freddyDoorCount > 1)
                {
                    freddyLoc = LEFT;
                }
            }

            break;
        case 2: //Currently on Night 2
            //stuff
            break;
        case 3: //Currently on Night 3
            //stuff
            break;
        case 4: //Currently on Night 4
            //stuff
            break;
        case 5: //Currently on Night 5
            //stuff
            break;
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

int main()
{
    startMenu();
    

    return 0;
}
