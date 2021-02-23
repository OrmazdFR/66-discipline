#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <C:\src\vcpkg\installed\x86-windows\include\json-c/json.h>

int hmMin(time_t timeToCheck)
{
    return timeToCheck / 60;
}

int hmHours(time_t timeToCheck)
{
    return timeToCheck / (60 * 60);
}

int hmDays(time_t timeToCheck)
{
    return timeToCheck / (60 * 60 * 24);
}

int hmWeeks(time_t timeToCheck)
{

    return timeToCheck / (60 * 60 * 24 * 7);
}

int todayHour(time_t currentTime)
{
    return ((currentTime - ((currentTime / 86400) * 86400)) / 3600) + 1;
}

time_t getNextCheckValue(time_t currentTime)
{
    int today;
    int hToday;
    time_t nextCheckValue;

    today = hmDays(currentTime);
    hToday = todayHour(currentTime);
    if (hToday <= 8)
    {
        return nextCheckValue = (today * 86400) + 25200;
    }
    else
    {
        return nextCheckValue = (today * 86400) + 111600;
    }
}

int main(int argc, char **argv)
{
    // unsigned short chosenUser = 65532;
    // short usersArray[10] = displayUsers(0);
    // int lostScore = 0;
    // time_t currentTimeT = time(NULL);

    // //Homepage displayed with icon
    // //If user.s are detected
    // if (usersArray[0] >= 0)
    // {
    //     do
    //     {
    //         displayUsers(1);
    //     } while (chosenUser == 65532);
    //     displayUser(chosenUser);
    // }

    //Create new user (button)
    // > createUser();
    return EXIT_SUCCESS;
}

json_object *weekPlanning()
{
    json_object *dayId;
    json_object *tajson;
    json_object *categories;
    json_object *category;
    json_object *categoryName;
    json_object *userTasks;
    json_object *tasks;
    json_object *task;
    json_object *taskObject;
    json_object *taskCy;
    json_object *taskCat;
    json_object *taskSub;
    json_object *taskPriority;
    json_object *taskDone;
    json_object *taskName;
    json_object *days;
    json_object *dayObject;
    int categoryAmount;
    int categoryChoice;
    int taskAmount;
    int taskChoice;
    int taskCyId;
    int priority;
    int day;
    int exitCode = -1;
    int i;

    days = json_object_new_array();

    //Open tasks.json
    tajson = json_object_from_file("tasks.json");
    json_object_object_get_ex(tajson, "categories", &categories);
    categoryAmount = json_object_array_length(categories);

    for (day = 0; day < 7; day++)
    {
        dayObject = json_object_new_object();
        userTasks = json_object_new_array();
        taskCyId = 0;

        do
        {
            taskObject = json_object_new_object();
            taskCyId++;
            //Display the day number
            printf("Day %d", day);

            //User can choose a category (Sports, Health, Finance... from in tasks.json)
            printf("\nChoose from one of these categories :");
            for (i = 0; i < categoryAmount; i++)
            {
                category = json_object_array_get_idx(categories, i);
                json_object_object_get_ex(category, "categoryName", &categoryName);
                printf("\n  %d. %s", i + 1, json_object_get_string(categoryName));
            }
            printf("\n999. Cancel.\n");
            scanf("%d", &categoryChoice);

            if (categoryChoice != 999)
            {
                //Then he chooses the task from the category (display from tasks.json)
                category = json_object_array_get_idx(categories, categoryChoice - 1);
                json_object_object_get_ex(category, "tasks", &tasks);
                taskAmount = json_object_array_length(tasks);
                printf("\nChoose from one of these tasks :");
                for (i = 0; i < taskAmount; i++)
                {
                    task = json_object_array_get_idx(tasks, i);
                    json_object_object_get_ex(task, "taskName", &taskName);
                    printf("\n%d. %s", i + 1, json_object_get_string(taskName));
                }
                printf("\n999. Cancel.\n");
                scanf("%d", &taskChoice);
            }

            if (categoryChoice != 999 || taskChoice != 999)
            {
                //And he chooses if it's Mandatory, Normal or Optional (see README.md). Explain what these things mean everytime
                printf("\nNow you have to choose is the task is :\n1. Mandatory : You win a lot of points if you do it, but lose a lot if you don't\n2. Normal : You win a basic amount of points if you do it, bot lose some if you don't\n3. Optional : You a few points if you do them, but don't lose points if you don't (bonus)");
                printf("\n999. Cancel and end the day.\n");
                scanf("%d", &priority);
            }
            if (categoryChoice != 999 || taskChoice != 999 || priority != 999)
            {
                taskCy = json_object_new_int64(taskCyId);
                json_object_object_add(taskObject, "taskCyId", taskCy);

                taskCat = json_object_new_int64(categoryChoice - 1);
                json_object_object_add(taskObject, "taskCat", taskCat);

                taskSub = json_object_new_int64(taskChoice - 1);
                json_object_object_add(taskObject, "taskSub", taskSub);

                taskPriority = json_object_new_int64(priority - 1);
                json_object_object_add(taskObject, "taskPriority", taskPriority);

                taskDone = json_object_new_int64(2);
                json_object_object_add(taskObject, "taskDone", taskDone);

                json_object_array_add(userTasks, taskObject);
            }
            printf("\n999. End day. Anything else will ask you to choose another category then task.");
            scanf("%d", &exitCode);
        } while (exitCode != 999);

        dayId = json_object_new_int64(day);
        json_object_object_add(dayObject, "dayId", dayId);

        json_object_object_add(dayObject, "tasks", userTasks);

        json_object_array_add(days, dayObject);
    }
    return days;
}

void createUser()
{
    json_object *usjson;
    json_object *users;
    json_object *newUser;
    json_object *userId;
    json_object *enabled;
    json_object *firstname;
    char fsFirstname[25];
    json_object *lastname;
    char fsLastname[25];
    json_object *score;
    json_object *firstDay;
    json_object *lastCheck;
    json_object *nextCheck;
    json_object *cycleAmount;
    int fsCycleAmount;
    json_object *cycles;
    json_object *cycleId;
    json_object *cycleObject;
    json_object *days;
    int userAmount;
    time_t currentTime = time(NULL);
    time_t nextCheckValue;

    //Display a new page to register the user
    printf("\nCreate a new user");
    //Creating a new user in the file "users.json".
    usjson = json_object_from_file("users.json");
    json_object_object_get_ex(usjson, "users", &users);

    /**
     * This wall is basically 
     * a friendly reminder that
     * I need to append 
     * the following value
     * to the array users.
     * 
     * I will not take it off
     * until I finally append it
     */
    newUser = json_object_new_object();  // Yes, I'm talking about this value

    //Auto-increment userId.
    userAmount = json_object_array_length(users);
    userId = json_object_new_int64(userAmount);
    json_object_object_add(newUser, "userId", userId);

    //Set "enabled" to 'true' (enabled)
    enabled = json_object_new_boolean(1);
    json_object_object_add(newUser, "enabled", enabled);

    //Ask for first name (firstname)
    printf("\nFirstname : ");
    scanf("%s", fsFirstname);
    firstname = json_object_new_string(fsFirstname);
    json_object_object_add(newUser, "firstname", firstname);

    //Ask for last name (lastname)
    printf("\nLastname : ");
    scanf("%s", fsLastname);
    lastname = json_object_new_string(fsLastname);
    json_object_object_add(newUser, "lastname", lastname);

    //Set "score" to 100 (score)
    score = json_object_new_int(100);
    json_object_object_add(newUser, "score", score);

    //Set "firstDay" to current time :
    firstDay = json_object_new_int64(currentTime);
    json_object_object_add(newUser, "firstDay", firstDay);

    //Set "lastCheck" to current time :
    lastCheck = json_object_new_int64(currentTime);
    json_object_object_add(newUser, "lastCheck", lastCheck);

    //Set "nextCheck" to the right time :
    nextCheckValue = getNextCheckValue(currentTime);
    nextCheck = json_object_new_int64(nextCheckValue);
    json_object_object_add(newUser, "nextCheck", nextCheck);

    //Ask for cycle amount (default = 10, can select between 1 and 52) (cycleAmount)
    printf("\nHow many cycles ? (between 1 and 52) : ");
    scanf("%d", &fsCycleAmount);
    cycleAmount = json_object_new_int(fsCycleAmount);
    json_object_object_add(newUser, "cycleAmount", cycleAmount);

    //Create the cycles array
    cycles = json_object_new_array();
    json_object_object_add(newUser, "cycles", cycles);

    //Creates the object to put in cycles array
    cycleObject = json_object_new_object();

    //Defines the first cycleId
    cycleId = json_object_new_int64(1);
    json_object_object_add(cycleObject, "cycleId", cycleId);

    //The user will then have to fill his first cycle (week) => weekPlanning();
    days = json_object_new_array();
    days = weekPlanning();
    json_object_object_add(cycleObject, "days", days);

    //Adds the cycleObject to the cycles array
    json_object_array_add(cycles, days);

    
}

void deleteUser(unsigned short userId)
{
    json_object *usjson;
    json_object *users;
    json_object *userContent;
    json_object *enabledField;

    //Opens users.json
    usjson = json_object_from_file("users.json");

    //Selects the good user
    json_object_object_get_ex(usjson, "users", &users);
    userContent = json_object_array_get_idx(users, userId);

    //Changes the value of "enabled" in the user profile to 'false'
    json_object_object_get_ex(userContent, "enabled", &enabledField);
    json_object_set_boolean(enabledField, 0);
}

json_object *displayUsers(unsigned char doOutput)
{
    unsigned short goodUsersAmount = 0;
    unsigned short i;
    unsigned short usersAmount;
    json_object *usjson;
    json_object *users;
    json_object *userIds;
    json_object *userContent;
    json_object *enabledField;
    json_object *firstname;
    json_object *lastname;
    json_object *score;

    //Open users.json
    usjson = json_object_from_file("users.json");

    userIds = json_object_new_array();

    //Retreive id of all users with "enabled" field set to 'true'
    json_object_object_get_ex(usjson, "users", &users);
    usersAmount = json_object_array_length(users);
    for (i = 0; i < usersAmount; i++)
    {
        userContent = json_object_array_get_idx(users, i);
        json_object_object_get_ex(userContent, "enabled", &enabledField);
        if (json_object_get_boolean(enabledField) == 1)
        {
            json_object_object_get_ex(userContent, "firstname", &firstname);
            json_object_object_get_ex(userContent, "lastname", &lastname);
            json_object_object_get_ex(userContent, "score", &score);
            //Display the number, firstname, lastname and score IF output != 0
            if (doOutput > 0)
            {
                printf("%hu. %s %s - %d\n", goodUsersAmount, json_object_get_string(firstname), json_object_get_string(lastname), json_object_get_int(score));
            }
            json_object_array_add(userIds,json_object_new_int(i));
            goodUsersAmount++;
        }
    }
    return userIds;
}

void autoCheck(unsigned short userId)
{
    time_t currentTime = time(NULL);
    json_object *usjson;
    json_object *tajson;
    json_object *users;
    json_object *userContent;
    json_object *nextCheck;
    int64_t nextCheckValue;
    json_object *lastCheck;
    int64_t lastCheckValue;
    json_object *firstDay;
    int64_t firstDayValue;

    //Open users.json
    usjson = json_object_from_file("users.json");

    //Open tasks.json
    tajson = json_object_from_file("tasks.json");

    //Selects the good user
    json_object_object_get_ex(usjson, "users", &users);
    userContent = json_object_array_get_idx(users, userId);

    //Retreives the nextCheck, lastChecked and firstDay field from the current user in users.json
    json_object_object_get_ex(userContent, "nextCheck", &nextCheck);
    nextCheckValue = json_object_get_int64(nextCheck);

    json_object_object_get_ex(userContent, "lastCheck", &lastCheck);
    lastCheckValue = json_object_get_int64(lastCheck);

    json_object_object_get_ex(userContent, "lastCheck", &lastCheck);
    lastCheckValue = json_object_get_int64(lastCheck);

    if (currentTime > nextCheckValue)
    {
        //   for each taskDone = 2 of the user from before this day {
        //     check the taskCat (category) and taskCyId (taskId) in the tasks.json to retreive the taskScore
        //     if(taskPriority == 1) {
        //       totalScore (from users.json) -= lostScore = 2 * taskScore;
        //     } else if (taskPriority == 2) {
        //       totalScore (from users.json) -= lostScore = 1 * taskScore;
        //     }
        //     set taskDone (from users.json) to 0
        //   }
        //   set nextCheck to the next 8:00 am from current time
        //   find how long has the user been absent (absentDays = currentTime - lastCheck, but translate it in days)
        //   retreive the last dayId of the user
        //   if(lastDayId + absentDays >= 7) {
        //     devs, be carefull when the user will register its next cycle, it will start late
        //     so save the weeksLateAmount (absentDays/7)
        //     and daysInWeekLateAmount (absentDays%7)
        //   }
        //   if scoreLost
        //   display a message saying that the user lost lostScore by not validating his discipline in the app, and that he's absentDays late in his discipline
    }
}
