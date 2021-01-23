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
    //Display the Day name (Monday ? Tuesday ? ...)
    //Open users.json
    //Open tasks.json
    // *? > User can chose a category (Sports, Health, Finance... from in tasks.json) _/ Util the user enters an exit code
    // __ > Then he choses the task from the category (display from tasks.json)
    // ?* > And he choses if it's Mendatory, Normal or Optionnal (see README.md). Explain what these things mean everytime
}

void createUser() {
    //Display a new page to register the user
    //Creating a new user in the file "users.json". Auto-increment userId. (maybe detect last userId in the file, then add 1 ?)
    //Set "enabled" to 'true' (enabled)
    //Ask for first name (firstname)
    //Ask for last name (lastname)
    //Set "score" to 100 (score)
    //Set "firstDay" to current time : fileTime = TIME( NULL ); (firstDay)
    //Ask for cycle day (today, monday = 1, tuesday = 2...) (cycleDay)
    //Ask for cycle amount (default = 10, can select between 1 and 52) (cycleAmount)
    //The user will then have to fill his first cycle (week) => weekPlanning();
}

void deleteUser() {
    //Opens users.json 
    //Changes the value of "enabled" in the user profile to 'false'
    //Closes the file
}

int displayUsers() {
    //Open users.json
    //Retreive id of all users with "enabled" field set to 'true'
    //Display the firstname lastname and score
    //Clicking on the line leads returns the id of the user (then displayUser())
}

void displayUser(int userId)
{

}

void dailyCheck() {
    //Open users.json
    //Open tasks.json
    //Retreives the nextCheck and lastChecked field from the current user in users.json
    //if(currentTime > nextCheck){
    // > for each taskDone = 2 of the user{
    // > > check the taskCat (category) and taskCyId (taskId) in the tasks.json to retreive the taskScore
    // > > if(taskPriority == 1) {
    // > > > totalScore (from users.json) = -2 * taskScore
    // > > } else if (taskPriority == 2) {
    // > > > totalScore (from users.json) = -1 * taskScore
    // > > }
    // > > set taskDone (from users.json) to 0
    // > }
    // > set nextCheck to the next 8:00 am from current time
    // > find how long has the user been absent (absentDays = currentTime - lastCheck, but translate it in days)
    // > retreive the last dayId of the user
    // > if(lastDayId + absentDays >= 7) {
    // > > devs, be carefull when the user will register its next cycle, it will start late
    // > > so save the weeksLateAmount (absentDays/7) 
    // > > and daysInWeekLateAmount (absentDays%7)
    // > }

}