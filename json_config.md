# How to fill the user JSON ? (what data must be put in it)

field       | example    | comment
:---------- | ---------: | :------- 
userid      | 1          | Here, it would be the first user
enabled     | true       | 
firstname   | John       |
lastname    | DOE        |
score       | 5700       | The score of the user
firstDay    | 1611360005 | Beginning of the disciplining in a 'seconds since 1970-01-01' format
lastCheck   | 1611400465 | Last time user has been checked (5:00 am, the day after the last check)
nextCheck   | 1611460800 | Next check (5:00 am, the day after the last check)
cycleDay    | 3          | 1 = Monday, 2 = Tuesday, etc
cycleAmount | 10         | 10*7 = 77 days. 3 would have been 21 days
cycles      |            | Contains the infos of each cycle
cycleId     | 3          | Defines that we're talking about the 3rd cycle
days        |            | Contains the infos about each day (of the 3rd cycle)
dayId       | 4          | Defines that we're talking about the 4th day after the beginning of the cycle. Here, saturday (as cycleDay = 3 (= wednesday))
tasks       |            | Contains the infos about the tasks of the 4th day of the 3rd cycle
taskCyId    | 1          | Defines that we are talking about the first task of the 4th day of the 3rd **cy**cle
taskCat     | 2          | The 2nd type in the **cat**egories json (sports, for example)
taskSub     | 5          | The 5th **sub**category of the type (30 pushups, for example)
taskPriority| 1          | 1 = Mandatory, 2 = Normal, 3 = Optionnal (changes the reward/loss value)
taskDone    | 2          | 0 = Failed, 1 = Done, 2 = Pending (not checked yet)

