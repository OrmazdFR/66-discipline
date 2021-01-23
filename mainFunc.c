#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h> // (we'll have to install it)
#include <json-c/json.h> // (we'll have to install it)

int main(int argc, char **argv)
{
    time_t currentTime = time( NULL );
    int chosenUser;
    time_t debugTime; //we should be able to change date to debug

    //Homepage displayed with icon

    //If user.s are detected
    chosenUser = displayUsers();
    displayUser(chosenUser);
    //Create new user (button)
    // > createUser();
    return EXIT_SUCCESS;
}

void weekPlanning() {
    //Displays the Day name (Monday ? Tuesday ? ...)
    //Opens tasks.json
    // *? > User can chose a category (Sports, Health, Finance... from in tasks.json) _/ Util the user enters an exit code
    // __ > Then he choses the task from the category (display from tasks.json)
    // ?* > And he choses if it's Mendatory, Normal or Optionnal (see README.md), and tell it to the user
}

void createUser() {
    //Displays a new page to register the user
    //Creating a new user in the file "users.json". Auto-increment userId. (maybe detect last userId in the file, then add 1 ?)
    //Sets "enabled" to 'true' (enabled)
    //Asks for first name (firstname)
    //Asks for last name (lastname)
    //Sets "score" to 100 (score)
    //Sets "firstDay" to current time : fileTime = TIME( NULL ); (firstDay)
    //Asks for cycle day (today, monday = 1, tuesday = 2...) (cycleDay)
    //Asks for cycle amount (default = 10, can select between 1 and 52) (cycleAmount)
    //The user will then have to fill his first cycle (week) => weekPlanning();
}

void deleteUser() {
    //Opens users.json 
    //Changes the value of "enabled" in the user profile to 'false'
    //Closes the file
}

int displayUsers() {
    //Opens users.json
    //Retreives id of all users with "enabled" field set to 'true'
    //Displays the firstname lastname and score
    //Clicking on the line leads returns the id of the user (then displayUser())
}

void displayUser(int userId)
{

}

void checkTasks() {
    
}