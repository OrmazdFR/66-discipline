#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <json.h> (we'll have to install it)

int main(int argc, char **argv)
{
    //Homepage displayed with icon

    //If user.s are detected
    // > Displays user.s
    // > If a user is selected
    // __ > His planning is displayed
    // __ > Current date is being checked
    // __ > If current date is >= 1 to last daily check
    //////////////// TO CONTINUE

    //Create new user (button)
    // > Displays a new page to register the user
    // __ > Creating a new user in the file "users.json". Auto-increment userId.
    // __ > Ask for first name
    // __ > Ask for last name
    // __ > Ask for first name
    // __ > Ask for cycle day (today, monday = 1, tuesday = 2...)
    // __ > Ask for cycle amount (default = 10, can select between 1 and 52)
    //!!!!!!!!! ↓ THIS WILL HAVE TO BE A FUNCTION AS IT WILL BE REPEATED LATER v (week planning) ↓
    // __ > The user will then have to fill his first cycle (week)
    // *7___ > Display the Day name (Monday ? Tuesday ? ...)
    // *?___ > He can chose a category (Sports, Health, Finance... from in tasks.json) _/ Util the user enters an exit code
    // _____ > Then he choses the task from the category (display from tasks.json)
    // ___?* > And he choses if it's Mendatory, Normal or Optionnal (see README.md)
    // 7* >

    return EXIT_SUCCESS;
}

//