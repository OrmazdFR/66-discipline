#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define clearCommand "clear"
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[37m"

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

int whourInDay(time_t timeToCheck)
{
    return ((timeToCheck - ((timeToCheck / 86400) * 86400)) / 3600) + 1;
}

time_t getNextCheckValue(time_t currentTime)
{
    int today;
    int hToday;
    time_t nextCheckValue;

    today = hmDays(currentTime);
    hToday = whourInDay(currentTime);
    if (hToday <= 8)
    {
        return nextCheckValue = (today * 86400) + 25200;
    }
    else
    {
        return nextCheckValue = (today * 86400) + 111600;
    }
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
            printf("Day %d", day + 1);

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

            if ((categoryChoice != 999))
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

            if ((categoryChoice != 999) && (taskChoice != 999))
            {
                //And he chooses if it's Mandatory, Normal or Optional (see README.md). Explain what these things mean everytime
                printf("\nNow you have to choose is the task is :\n1. Mandatory : You win a lot of points if you do it, but lose a lot if you don't\n2. Normal : You win a basic amount of points if you do it, bot lose some if you don't\n3. Optional : You a few points if you do them, but don't lose points if you don't (bonus)");
                printf("\n999. Cancel and end the day.\n");
                scanf("%d", &priority);
            }
            if ((categoryChoice != 999) && (taskChoice != 999) && (priority != 999))
            {
                taskCy = json_object_new_int(taskCyId);
                json_object_object_add(taskObject, "taskCyId", taskCy);

                taskCat = json_object_new_int(categoryChoice - 1);
                json_object_object_add(taskObject, "taskCat", taskCat);

                taskSub = json_object_new_int(taskChoice - 1);
                json_object_object_add(taskObject, "taskSub", taskSub);

                taskPriority = json_object_new_int(priority - 1);
                json_object_object_add(taskObject, "taskPriority", taskPriority);

                taskDone = json_object_new_int(2);
                json_object_object_add(taskObject, "taskDone", taskDone);

                json_object_array_add(userTasks, taskObject);
            }
            printf("\n999. End day. Anything else will ask you to choose another category then task.");
            scanf("%d", &exitCode);
        } while (exitCode != 999);

        dayId = json_object_new_int(day);
        json_object_object_add(dayObject, "dayId", dayId);

        json_object_object_add(dayObject, "tasks", userTasks);

        json_object_array_add(days, dayObject);
    }
    return days;
}

void createUser()
{
    json_object *usjson;
    json_object *usObject;
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
    usObject = json_object_new_object();
    json_object_object_get_ex(usjson, "users", &users);

    newUser = json_object_new_object();

    //Auto-increment userId.
    userAmount = json_object_array_length(users);
    userId = json_object_new_int(userAmount);
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
    printf("Lastname : ");
    scanf("%s", fsLastname);
    lastname = json_object_new_string(fsLastname);
    json_object_object_add(newUser, "lastname", lastname);

    //Set "score" to 100 (score)
    score = json_object_new_int64(100);
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
    printf("How many cycles ? (between 1 and 52) : ");
    scanf("%d", &fsCycleAmount);
    cycleAmount = json_object_new_int(fsCycleAmount);
    json_object_object_add(newUser, "cycleAmount", cycleAmount);

    //Create the cycles array
    cycles = json_object_new_array();
    json_object_object_add(newUser, "cycles", cycles);

    //Creates the object to put in cycles array
    cycleObject = json_object_new_object();

    //Defines the first cycleId
    cycleId = json_object_new_int(1);
    json_object_object_add(cycleObject, "cycleId", cycleId);

    //The user will then have to fill his first cycle (week) =>  ();
    days = json_object_new_array();
    days = weekPlanning();
    json_object_object_add(cycleObject, "days", days);

    //Adds the cycleObject to the cycles array
    json_object_array_add(cycles, cycleObject);

    // FINALLY appending newUser
    json_object_array_add(users, newUser);

    // Appending users to the global object
    json_object_object_add(usObject, "users", users);

    // Appending it to the file
    json_object_to_file("users.json", usObject);

    // Frees the users.json
    json_object_put(usjson);
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
                printf("%hu. %s %s - %lld\n", ++goodUsersAmount, json_object_get_string(firstname), json_object_get_string(lastname), (long long)json_object_get_int64(score));
            }
            json_object_array_add(userIds, json_object_new_int(i));
        }
    }
    return userIds;
}

void autoCheck(unsigned short userId)
{
    //__ users
    json_object *usjson;
    json_object *users;
    json_object *userContent;
    json_object *usScore;
    int userScore = 0;
    json_object *usCycles;
    json_object *usCycle;
    int usCycleIndex = 0;
    json_object *usDays;
    json_object *usDay;
    int usDayIndex = 0;
    json_object *usTasks;
    json_object *usTask;
    json_object *usTaskCat;
    json_object *usTaskSub;
    json_object *usTaskPriority;
    json_object *usTaskDone;
    int taskPriority;
    int usTaskAmount;
    int usTaskIndex = 0;
    //__ time
    json_object *usFirstDay;
    int64_t firstDay;
    int firstDayDay;
    json_object *usLastCheck;
    int64_t lastCheck;
    int lastCheckDay;
    json_object *usNextCheck;
    int64_t nextCheck;
    int currentlyCheckingDay;
    time_t currentTime = time(NULL);
    int today;
    //__ tasks
    json_object *tajson;
    json_object *taCategories;
    json_object *taCategory;
    int taCategoryIndex = 0;
    json_object *taTasks;
    json_object *taTask;
    int taTaskIndex = 0;
    json_object *taTaskScore;
    int taskScore;
    //__ other vars
    int lostScore = 0;

    // Users declarations
    usjson = json_object_from_file("users.json");
    json_object_object_get_ex(usjson, "users", &users);
    userContent = json_object_array_get_idx(users, userId);
    json_object_object_get_ex(userContent, "score", &usScore);
    json_object_object_get_ex(userContent, "cycles", &usCycles);

    json_object_object_get_ex(userContent, "firstDay", &usFirstDay);
    firstDay = json_object_get_int64(usFirstDay);
    firstDayDay = whourInDay(firstDay) <= 8 ? hmDays(firstDay) - 1 : hmDays(firstDay);

    json_object_object_get_ex(userContent, "lastCheck", &usLastCheck);
    lastCheck = json_object_get_int64(usLastCheck);
    lastCheckDay = whourInDay(lastCheck) <= 8 ? hmDays(lastCheck) - 1 : hmDays(lastCheck);

    json_object_object_get_ex(userContent, "nextCheck", &usNextCheck);
    nextCheck = json_object_get_int64(usNextCheck);

    today = whourInDay(currentTime) <= 8 ? hmDays(currentTime) - 1 : hmDays(currentTime);

    // Tasks declarations
    tajson = json_object_from_file("tasks.json");
    json_object_object_get_ex(tajson, "categories", &taCategories);

    if (currentTime > nextCheck)
    {
        for (currentlyCheckingDay = lastCheckDay; currentlyCheckingDay < today; currentlyCheckingDay++)
        {
            usCycleIndex = (currentlyCheckingDay - firstDayDay) / 7;
            usDayIndex = (currentlyCheckingDay - firstDayDay) % 7;

            //Get into the good cycle
            usCycle = json_object_array_get_idx(usCycles, usCycleIndex);

            //Check the good day
            json_object_object_get_ex(usCycle, "days", &usDays);
            usDay = json_object_array_get_idx(usDays, usDayIndex);

            //Get to the tasks
            json_object_object_get_ex(usDay, "tasks", &usTasks);
            usTaskAmount = json_object_array_length(usTasks);

            //Check every task
            for (usTaskIndex = 0; usTaskIndex < usTaskAmount; usTaskIndex++)
            {
                usTask = json_object_array_get_idx(usTasks, usTaskIndex);
                json_object_object_get_ex(usTask, "taskCat", &usTaskCat);
                taCategoryIndex = json_object_get_int(usTaskCat);
                json_object_object_get_ex(usTask, "taskSub", &usTaskSub);
                taTaskIndex = json_object_get_int(usTaskSub);
                json_object_object_get_ex(usTask, "taskPriority", &usTaskPriority);
                taskPriority = json_object_get_int(usTaskPriority);

                //  check the taskCat (category) and taskCyId (taskId) in the tasks.json to retreive the taskScore
                taCategory = json_object_array_get_idx(taCategories, taCategoryIndex);
                json_object_object_get_ex(taCategory, "tasks", &taTasks);
                taTask = json_object_array_get_idx(taTasks, taTaskIndex);
                json_object_object_get_ex(taTask, "taskScore", &taTaskScore);
                taskScore = json_object_get_int(taTaskScore);

                if (taskPriority == 1)
                {
                    lostScore += 2 * taskScore;
                }
                else if (taskPriority == 2)
                {
                    lostScore += taskScore;
                }
                json_object_object_get_ex(usTask, "taskDone", &usTaskDone);
                json_object_set_int(usTaskDone, 0);
            }
        }
        //   display a message saying that the user lost lostScore by not validating his discipline in the app, and that he's absentDays late in his discipline
        userScore = json_object_get_int(usScore);
        userScore = (userScore - lostScore < 0) ? 0 : userScore - lostScore;
        printf("\nOh no! You were absent for %d days, and you lost %d points... Be careful next time :)\nYour current score is : %d.\n", lastCheckDay - today, lostScore, userScore);
    }
    //   set nextCheck to the next 8:00 am from current time
    getNextCheckValue(currentTime);
    nextCheck = getNextCheckValue(currentTime);
    json_object_set_int64(usNextCheck, nextCheck);
    json_object_to_file_ext("users.json", usjson, JSON_C_TO_STRING_PRETTY);
}

void displayWeek(unsigned short userId)
{
    time_t currentTime = time(NULL);
    json_object *usjson;
    json_object *users;
    json_object *userContent;
    json_object *usCycles;
    json_object *usCycle;
    json_object *usDays;
    json_object *usDay;
    json_object *usTasks;
    json_object *usTask;
    json_object *usTaskCat;
    json_object *usTaskSub;
    json_object *usFirstDay;
    int usCycleIndex = 0;
    int usTaskAmount;
    int usTaskIndex = 0;
    int firstDay;
    int firstDayDay;

    json_object *tajson;
    json_object *taCategories;
    json_object *taCategory;
    json_object *taTasks;
    json_object *taTask;
    json_object *taTaskName;
    int taCategoryIndex = 0;
    int taTaskIndex = 0;

    int day;
    int today;

    // Users declarations
    usjson = json_object_from_file("users.json");
    json_object_object_get_ex(usjson, "users", &users);
    userContent = json_object_array_get_idx(users, userId);
    json_object_object_get_ex(userContent, "cycles", &usCycles);

    json_object_object_get_ex(userContent, "firstDay", &usFirstDay);
    firstDay = json_object_get_int64(usFirstDay);
    firstDayDay = whourInDay(firstDay) <= 8 ? hmDays(firstDay) - 1 : hmDays(firstDay);

    today = whourInDay(currentTime) <= 8 ? hmDays(currentTime) - 1 : hmDays(currentTime);

    // Tasks declarations
    tajson = json_object_from_file("tasks.json");
    json_object_object_get_ex(tajson, "categories", &taCategories);

    usCycleIndex = (today - firstDayDay) / 7;

    for (day = 0; day < 7; day++)
    {

        //Get into the good cycle
        usCycle = json_object_array_get_idx(usCycles, usCycleIndex);

        //Check the good day
        json_object_object_get_ex(usCycle, "days", &usDays);
        usDay = json_object_array_get_idx(usDays, day);

        //Get to the tasks
        json_object_object_get_ex(usDay, "tasks", &usTasks);
        usTaskAmount = json_object_array_length(usTasks);

        printf("Day %d.", day);

        //Check every task
        for (usTaskIndex = 0; usTaskIndex < usTaskAmount; usTaskIndex++)
        {
            usTask = json_object_array_get_idx(usTasks, usTaskIndex);
            json_object_object_get_ex(usTask, "taskCat", &usTaskCat);
            taCategoryIndex = json_object_get_int(usTaskCat);
            json_object_object_get_ex(usTask, "taskSub", &usTaskSub);
            taTaskIndex = json_object_get_int(usTaskSub);

            //  check the taskCat (category) and taskCyId (taskId) in the tasks.json to retreive the taskScore
            taCategory = json_object_array_get_idx(taCategories, taCategoryIndex);
            json_object_object_get_ex(taCategory, "tasks", &taTasks);
            taTask = json_object_array_get_idx(taTasks, taTaskIndex);
            json_object_object_get_ex(taTask, "taskName", &taTaskName);
            printf("\n%s", json_object_get_string(taTaskName));
        }
        printf("\n__________\n");
    }
}

void userCheck(unsigned short userId)
{
    time_t currentTime = time(NULL);
    json_object *usjson;
    json_object *users;
    json_object *userContent;
    json_object *usLastCheck;
    json_object *usNextCheck;
    json_object *usCycles;
    json_object *usCycle;
    json_object *usDays;
    json_object *usDay;
    json_object *usTasks;
    json_object *usTask;
    json_object *usTaskCat;
    json_object *usTaskSub;
    json_object *usTaskPriority;
    json_object *usFirstDay;
    json_object *usScore;
    int usCycleIndex;
    int usTaskAmount;
    int usTaskIndex;
    int taskPriority;
    int64_t score;
    int scoreModif = 0;
    int firstDay;
    int firstDayDay;
    json_object *tajson;
    json_object *taCategories;
    json_object *taCategory;
    json_object *taTasks;
    json_object *taTask;
    json_object *taTaskName;
    json_object *taTaskScore;
    int taCategoryIndex;
    int taTaskIndex;
    int taskScore;
    int today;
    int day;
    json_object *usTaskDone;
    int taskDone;
    int taskChoice;
    int statusChoice;
    int exitCode;

    // Users declarations
    usjson = json_object_from_file("users.json");
    json_object_object_get_ex(usjson, "users", &users);
    userContent = json_object_array_get_idx(users, userId);
    json_object_object_get_ex(userContent, "cycles", &usCycles);
    json_object_object_get_ex(userContent, "firstDay", &usFirstDay);
    firstDay = json_object_get_int64(usFirstDay);
    firstDayDay = whourInDay(firstDay) <= 8 ? hmDays(firstDay) - 1 : hmDays(firstDay);
    today = whourInDay(currentTime) <= 8 ? hmDays(currentTime) - 1 : hmDays(currentTime);

    // Tasks declarations
    tajson = json_object_from_file("tasks.json");
    json_object_object_get_ex(tajson, "categories", &taCategories);
    usCycleIndex = (today - firstDayDay) / 7;
    //Get into the good cycle
    usCycle = json_object_array_get_idx(usCycles, usCycleIndex);

    //Check the good day
    day = (today - firstDayDay) % 7;
    json_object_object_get_ex(usCycle, "days", &usDays);
    usDay = json_object_array_get_idx(usDays, day);

    //Get to the tasks
    json_object_object_get_ex(usDay, "tasks", &usTasks);
    usTaskAmount = json_object_array_length(usTasks);
    do
    {
        printf("What have you finished today ?\n");
        //Return every task
        for (usTaskIndex = 0; usTaskIndex < usTaskAmount; usTaskIndex++)
        {
            usTask = json_object_array_get_idx(usTasks, usTaskIndex);
            json_object_object_get_ex(usTask, "taskCat", &usTaskCat);
            taCategoryIndex = json_object_get_int(usTaskCat);
            json_object_object_get_ex(usTask, "taskSub", &usTaskSub);
            json_object_object_get_ex(usTask, "taskDone", &usTaskDone);
            json_object_object_get_ex(usTask, "taskPriority", &usTaskPriority);
            taskDone = json_object_get_int(usTaskDone);
            taTaskIndex = json_object_get_int(usTaskSub);
            taskPriority = json_object_get_int(usTaskPriority);
            json_object_object_get_ex(userContent, "score", &usScore);
            score = json_object_get_int64(usScore);

            //check the taskCat (category) and taskCyId (taskId) in the tasks.json to retreive the taskScore
            taCategory = json_object_array_get_idx(taCategories, taCategoryIndex);
            json_object_object_get_ex(taCategory, "tasks", &taTasks);
            taTask = json_object_array_get_idx(taTasks, taTaskIndex);
            json_object_object_get_ex(taTask, "taskName", &taTaskName);
            json_object_object_get_ex(taTask, "taskScore", &taTaskScore);
            taskScore = json_object_get_int(taTaskScore);

            if (taskPriority == 1)
            {
                scoreModif = 2 * taskScore;
            }
            else
            {
                scoreModif = taskScore;
            }

            //Prints the task
            if (taskDone == 0)
                printf(RED "%d. %s\n" RESET, usTaskIndex + 1, json_object_get_string(taTaskName));
            if (taskDone == 1)
                printf(GREEN "%d. %s\n" RESET, usTaskIndex + 1, json_object_get_string(taTaskName));
            if (taskDone == 2)
                printf("%d. %s\n" RESET, usTaskIndex + 1, json_object_get_string(taTaskName));
        }
        printf("999. Cancel\n");
        scanf("%d", &taskChoice);
        if (taskChoice != 999)
        {
            printf("\nWhat value ?\n1. " GREEN "Done" RESET "\n2. " RED "Failed" RESET "\n3. Cancel\n");
            scanf("%d", &statusChoice);
            if (statusChoice < 3)
            {
                statusChoice = (statusChoice == 1) ? 1 : 0;
                if (statusChoice != taskDone)
                {
                    if (statusChoice == 0)
                    {
                        if (taskPriority != 3)
                        {
                            if (score - scoreModif < 0)
                            {
                                score = 0;
                            }
                            else
                            {
                                score = score - scoreModif;
                            }
                            printf("Oh... You lost " RED "%d" RESET " points...\nYour new score is " RED "%ld" RESET "\n", scoreModif, score);
                        }
                    }
                    else
                    {
                        score += scoreModif;
                        printf("Congratulations! You won " GREEN "%d" RESET " points !\nYour new score is " GREEN "%ld" RESET "\n", scoreModif, score);
                    }

                    usTask = json_object_array_get_idx(usTasks, taskChoice - 1);
                    json_object_object_get_ex(usTask, "taskDone", &usTaskDone);
                    json_object_set_int(usTaskDone, statusChoice);
                    json_object_set_int64(usScore, score);
                } else {
                    printf(RED "You can't set the same status.\n" RESET);
                }
            }
        }
        printf("\nStop choosing tasks ?\n999. Stop\nAnything else to continue");
        scanf("%d", &exitCode);
        system(clearCommand);
    } while (exitCode != 999);
    json_object_object_get_ex(userContent, "lastCheck", &usLastCheck);
    json_object_set_int64(usLastCheck, currentTime);
    json_object_object_get_ex(userContent, "nextCheck", &usNextCheck);
    json_object_set_int64(usNextCheck, getNextCheckValue(currentTime));
    json_object_to_file_ext("users.json", usjson, JSON_C_TO_STRING_PRETTY);
}

int main(int argc, char **argv)
{
    unsigned short chosenUser = 1;
    // json_object *arrayUser;

    system(clearCommand);
    //     short usersArray[10] = displayUsers(0);
    //     int lostScore = 0;
    //     time_t currentTimeT = time(NULL);

    //     //Homepage displayed with icon
    //     //If user.s are detected
    //     if (usersArray[0] >= 0)
    //     {
    //         do
    //         {
    //             displayUsers(1);
    //         } while (chosenUser == 65532);
    //         displayUser(chosenUser);
    //     }
    // arrayUser = displayUsers(1);
    // printf("\n");
    // json_object_to_json_string_ext(arrayUser, JSON_C_TO_STRING_PRETTY);
    userCheck(chosenUser);
    // printf("hi")
    // createUser();
    return EXIT_SUCCESS;
}