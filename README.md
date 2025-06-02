# FNAF-Text-Game
Text based rendition of Five Night's at Freddy's coded in C++.

As you progress to later nights, the animatronics will be more likely to move towards you and less likely to move away, nights last longer, energy will be more costly (so you need to use it wisely), and the animatronics will move more often.

-----------------
PATCH NOTES (ONLY UPDATED FROM V0.1.2 AND ON)
-----------------
V0.1.2

Tweaked the way movement works, added a system in which animatronics are more likely to move back to the dining room if they have tried to kill you so that they don't camp in the hallway

-----------------
V0.2.0

Added Night 2

Bonnie now gets active

Reworked Freddy movement to make Night 1 a bit easier now that difficulty scales with night

Updated map

Added new location on the map "SUPPLY" that Bonnie hide in 

Fixed a bug that caused a crash when user tried to select a night that was not unlocked 

-----------------
V0.2.1

Updated the Bonnie jump scare so now it has an "animation" when Bonnie kills you

Added "bonnie_scare.txt" to file list, this is just the text file containing the image of bonnie's jumpscare for the program to read from

-----------------
V0.2.2

ALL 5 NIGHTS ARE FUNCTIONAL (with only freddy and bonnie)

  Night dificulty scales accurately, possible to change if too easy/hard

Foxy is still a WIP which is why Night 3 is not finished 

-----------------
V0.3.0

Foxy is now active

Foxy becomes active on night 3, once Foxy is heard running through the halls, the player has 2 turns to close the door and stop the attack

Foxy includes 4 image files (so far) that display Pirate's Cove and show the different stages of Foxy's movement

Made changes on the backend to make the code run smoother when checking cams, no player impact

-----------------
V0.3.1

Fixed an issue where Foxy couldn't kill the player

Added Foxy jumpscare animation

Added "foxy_scare.txt" to file list, this is foxy jumpscare

-----------------
V0.4.0

ALL 5 NIGHTS ARE FULLY FINISHED

Chica is now working

Still turned based but that is being worked on and should soon be time based instead

-----------------
V1.0.0

GAME IS READY FOR TESTING

Game is now timer based rather than turn based, if you wish to play the turn based version it is still available

Regular, timer based version is simply fnaf.exe, turn based version is fnafTurnBased.exe

-----------------
V1.0.1

Updated the cameras to be able to move with numbers as well as the name of the location to reduce the amount of typing required

Added a load/save option on the title screen so that users are able to save their progress and continue where they left off rather than play all 5 nights at a time

gameSave.txt file contains the night that was saved, for now it can be manipulated to unlock further nights than played through by simply opening the text file and changing the number to what night you wish to unlock

-----------------
