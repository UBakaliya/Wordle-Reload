/* main.cpp
    Wordle Reload is a game that allows you to guess either a 3 letter word or 5 letter word.
    You have a set amount of time to guess a word.  At the conlusion of game play
    you will be provided stats on your overall game play.
*/
#include <iostream> // For Input and Output
#include <fstream>  // For file input and output
#include <vector>   // Input file is stored in a vector
#include <cassert>  // For the assert statement used to validate file open
#include <cctype>   // Allows using the tolower() function
#include <ctime>    // Allows to use srand()

using namespace std; // use it so we don't have to say std:: overtime

//--------------------------------------------------------------------------------
// Display welcome message, introducing the user to the program and
// describing the instructions for the game
void gameDisplayInstructions()
{
    cout << "Program 3: Wordle Reload \n"
         << " \n"
         << "The objective of this game is to guess the randomly selected \n"
         << "word within a given number of attempts. You can select either \n"
         << "a three or five word board. \n"
         << "At the conlusion of the game, stats will be displayed.  \n"
         << "Indicators will be given if characters of the user entered \n"
         << "word are reflected in the guessed word. \n"
         << "  - If the character is in the correct position, the character \n"
         << "    will display as an uppercase value.\n"
         << "  - If the character is within the random word, the character \n"
         << "    will display as a lowercase value.\n"
         << "  - If you enter a character that is not in the word, an asterisk '*' \n"
         << "    will display."
         << " \n"
         << endl;
} // End displayWelcomeMessage()

// Opening the file and reading from it
// gamePlay is for us to spilit the 3 letter's words and 5 letter words
void readWordsIntoDictionary(vector<string> &dictionary, int gamePlay)
{
    // Read in dictionary into dictionary vector
    ifstream inStream;                // Declare an input stream for reading
    inStream.open("wordlewords.txt"); // Open dictionary file
    assert(inStream.fail() == false); // Ensure file open worked
    dictionary.clear();

    // Keep repeating while input from the file yields a word
    string newWord; // Store a single input word
    while (inStream >> newWord)
    { // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        if (gamePlay == 3)
        { // if the user chose game Play 1 then all three letter word
            if (newWord.length() == 3)
            { // push back all the three letter words
                dictionary.push_back(newWord);
            }
        }
        else if (gamePlay == 5)
        { // if the user chose game Play 2 then all five letter word
            if (newWord.length() == 5)
            { // push back all the five letter words
                dictionary.push_back(newWord);
            }
        }
    }

    inStream.close(); // close the file after it gets all the words
} // End of readWordsIntoDictionary()

// Binary Search to see if the word user enters is in the wordlewords.txt
// searchPlace is where do you want to search, searchStr is what STRING you want to search, index what INDEX you want to search at
// if the result returns -1 then it didn't' find the word in the searchPlace
int binarySearch(vector<string> searchPlace, string searchStr, int index)
{
    int lower = 0;
    int upper = index - 1; // go to last index of the search Place
    while (lower <= upper)
    {
        int mid = lower + (upper - lower) / 2; // devid the half search Place and start from the middle of the vector
        int res;
        if (searchStr == (searchPlace[mid])) // check in the middle
            res = 0;
        if (res == 0)
            return mid;                     // found in mid
        if (searchStr > (searchPlace[mid])) // if the string we looking for is length is more then the search Place then lower will become mid + 1
            lower = mid + 1;
        else
            upper = mid - 1; // if not the true then
    }
    return -1; // not found the word
} // End of binarySearch()

// function will run will when the user enters 1 (For 3 Letter Words Game Play )
bool threeLetterWord()
{
    vector<string> dictionaryStoreThreeLetter, previousInputsThreeLetter; // Store all the 3 letter words in vector,  and another vector for to print out the Previous entries
    // game play 3 give all the 3 letters words and do the Binary Search on the user entires, and keep track of the Attemps
    int gamePlay = 3, wordIndexThreeLat, resultFromBinarySearchThreeLat, attempsCountThreeLetters = 0, elapsedSecThreeLetterWord = 0; // elapsedSecThreeLetterWord will store the time
    readWordsIntoDictionary(dictionaryStoreThreeLetter, gamePlay);                                                                    // Generate 3 letter words
    string randWordGenreFromDict, userThreeLetterGuess, storeGuessEntires;                                                            // store the Guess Entires  in userThreeLetterGuess, store the previous storeGuessEntires
    wordIndexThreeLat = rand() % dictionaryStoreThreeLetter.size();                                                                   // Generate a Random Index from the file Indexes
    randWordGenreFromDict = dictionaryStoreThreeLetter.at(wordIndexThreeLat);                                                         // Use the Random Index to get a Word from the file

    while (userThreeLetterGuess != randWordGenreFromDict && attempsCountThreeLetters < 4 && elapsedSecThreeLetterWord <= 20)
    {                                         // Run till the user doesn't guess the right word with out reaching the Max Attemps
        time_t startTimeInGuess = time(NULL); // time start when the user gets starts entering the words
        cout << "\nPlease enter word --> ";
        cin >> userThreeLetterGuess;
        cout << endl; // Guess entry

        for (unsigned convertLow = 0; convertLow < userThreeLetterGuess.length(); convertLow++)
        { // convert in to a lower case if the user entry is upper case
            userThreeLetterGuess[convertLow] = tolower(userThreeLetterGuess[convertLow]);
        }
        // look the word entered by the user is in the file (doing the Binary Search with the user of  binarySearch() function )
        for (unsigned searchIndexBinaryThreeLetter = 0; searchIndexBinaryThreeLetter < dictionaryStoreThreeLetter.size(); searchIndexBinaryThreeLetter++)
        { // search the word that entred is in the three lettter word vector
            resultFromBinarySearchThreeLat = binarySearch(dictionaryStoreThreeLetter, userThreeLetterGuess, searchIndexBinaryThreeLetter);
        }
        if (userThreeLetterGuess.length() > 3 || userThreeLetterGuess.length() < 3)
        { // check the word guess word is within the length of 3
            cout << "Invalid word entry - please enter a word that is 3 characters long.\n"
                 << endl;
            continue;
        }
        else if (resultFromBinarySearchThreeLat == -1 && userThreeLetterGuess != randWordGenreFromDict)
        { // if the guess entry is not in the file
            cout << "\nNot a playable word, please select another word." << endl;
            continue;
        }
        else
        { // if the word the word is in the length, and in the file
            for (unsigned previousGuessThreeLetter = 0; previousGuessThreeLetter < previousInputsThreeLetter.size(); previousGuessThreeLetter++)
            { // print out the PREVIOUS Guesses, print the previous words on the new line after vector get filled with 3 characters
                cout << "[ " << previousInputsThreeLetter[previousGuessThreeLetter] << " ]";
                if ((previousGuessThreeLetter + 1) % 3 == 0)
                {
                    cout << endl;
                } // new line after is get 3 char
            }
            for (int rowThreeLetter = 0; rowThreeLetter < 3; rowThreeLetter++)
            { // out the word and split the Characters in with the [ ] 3 times valid and non valid or the whole valid word
                if (userThreeLetterGuess[rowThreeLetter] == randWordGenreFromDict[rowThreeLetter])
                { // check Guess entry is on the same postion as the Random Word
                    storeGuessEntires = toupper(userThreeLetterGuess[rowThreeLetter]);
                    cout << "[ " << storeGuessEntires << " ]";
                    previousInputsThreeLetter.push_back(storeGuessEntires); // push back tha character and we can print out the PREVIOUS  entry
                }
                // checks that character is entered is in the word but not in the same postion as random word
                else if (userThreeLetterGuess[rowThreeLetter] == randWordGenreFromDict[0] || userThreeLetterGuess[rowThreeLetter] == randWordGenreFromDict[1] || userThreeLetterGuess[rowThreeLetter] == randWordGenreFromDict[2])
                {
                    storeGuessEntires = userThreeLetterGuess[rowThreeLetter];
                    cout << "[ " << storeGuessEntires << " ]";
                    previousInputsThreeLetter.push_back(storeGuessEntires); // push back the previous entry
                }
                // check valid or not
                else if (userThreeLetterGuess[rowThreeLetter] != randWordGenreFromDict[rowThreeLetter])
                { // check the word entry is valid. If not then print [ * ] and push back *
                    cout << "[ * ]";
                    previousInputsThreeLetter.push_back("*");
                }
                elapsedSecThreeLetterWord = difftime(time(NULL), startTimeInGuess); // time count will run till the user stop guessing the words
            }
        } // end of else means that either the user guessed the word correctly or maximum number of the attemps reached if not that then use is still playing so the attemps will increment
        cout << endl;
        attempsCountThreeLetters++;
        if (attempsCountThreeLetters == 4 && userThreeLetterGuess != randWordGenreFromDict && elapsedSecThreeLetterWord <= 20)
        { // max attemps will display the message and it will break out of the look
            cout << "Maximum amount of attempts have been reached. Try again.\n"
                 << endl;
        }
        else if (userThreeLetterGuess == randWordGenreFromDict && elapsedSecThreeLetterWord <= 20)
        { // if the guess entry is right then display the message
            cout << "\nNice Work!  You guessed the correct word\n   - You completed the board in: " << elapsedSecThreeLetterWord << " seconds.\n"
                 << "   - It took you " << attempsCountThreeLetters << "/4 attempts.\n"
                 << endl;
            return true; // to keep track of the streak's and the guess when the user press 3 for the menuOptions
        }
        else if (elapsedSecThreeLetterWord > 20)
        { // time is more then 20 seconds then it will not pass the any inputs and will display the message
            cout << "\nYour time has expired.  Try again. \n"
                 << "  - You are " << elapsedSecThreeLetterWord - 20 << " seconds over the 20 second time limit.\n"
                 << endl;
            break; // time went to 20 seconds
        }
    } // end of While Loop
    return false;
} // End of threeLetterWord()

// menu option is 2 then run the fiveLetterWord() it will be checking the five letters word valid and all entires
bool fiveLetterWord()
{
    vector<string> dictionaryStoreFiveLetter, previousInputsFivesLetter; // Store all the 5 letter words in vector,  and another vector for to print out the Previous entries
    // game play 5 give all the 5 letters words and do the Binary Search on the user entires, and keep track of the Attemps
    int gamePlayFiveLetter = 5, wordIndexFiveLetter, attempsCoutFiveLetter = 0, elapsedSecondsForFiveWordGuess = 0, resultFromBinarySearchFiveLat;
    readWordsIntoDictionary(dictionaryStoreFiveLetter, gamePlayFiveLetter); // Generate 5 letter words
    string fiveLetterRandWord, userGuessFiveLetter, userFiveLetterGuess;    // store the Guess Entires  in userThreeLetterGuess, store the previous storeGuessEntires
    wordIndexFiveLetter = rand() % dictionaryStoreFiveLetter.size();        // Generate a Random Index from the file Indexes
    fiveLetterRandWord = dictionaryStoreFiveLetter.at(wordIndexFiveLetter); // Use the Random Index to get a Word from the file

    while (userGuessFiveLetter != fiveLetterRandWord && attempsCoutFiveLetter < 6 && elapsedSecondsForFiveWordGuess <= 40)
    {                                         // Run till the user doesn't guess the right word with out reaching the Max Attemps
        time_t startTimeInGuess = time(NULL); // time start when the user gets starts entering the words
        cout << "\nPlease enter word --> ";
        cin >> userGuessFiveLetter;
        cout << endl; // User input

        for (unsigned convertLowFiveLetter = 0; convertLowFiveLetter < userGuessFiveLetter.length(); convertLowFiveLetter++)
        {                                                                                                   //  convert in to lower case if the entry upper case
            userGuessFiveLetter[convertLowFiveLetter] = tolower(userGuessFiveLetter[convertLowFiveLetter]); // tolower the user input
        }
        for (unsigned searchIndexBinaryFiveLett = 0; searchIndexBinaryFiveLett < dictionaryStoreFiveLetter.size(); searchIndexBinaryFiveLett++)
        {                                                                                                                            // look the word entered by the user is in the file (doing the Binary Search with the user of  binarySearch() function )
            resultFromBinarySearchFiveLat = binarySearch(dictionaryStoreFiveLetter, userGuessFiveLetter, searchIndexBinaryFiveLett); // search in binarySearch()
        }
        if (userGuessFiveLetter.length() > 5 || userGuessFiveLetter.length() < 5)
        { // check the word guess word is within the length of 5
            cout << "Invalid word entry - please enter a word that is 5 characters long.\n"
                 << endl;
            continue;
        }
        else if (resultFromBinarySearchFiveLat == -1 && userGuessFiveLetter != fiveLetterRandWord)
        { // if the guess entry is no in the file
            cout << "\nNot a playable word, please select another word." << endl;
            continue;
        }
        else
        { // if the word the word is in the length, and in the file
            for (unsigned previousGuessFiveLetter = 0; previousGuessFiveLetter < previousInputsFivesLetter.size(); previousGuessFiveLetter++)
            { // print out the PREVIOUS Guesses
                cout << "[ " << previousInputsFivesLetter[previousGuessFiveLetter] << " ]";
                if ((previousGuessFiveLetter + 1) % 5 == 0)
                { // print the previous words on the new line after vector get filled with 5 characters
                    cout << endl;
                }
            }
            for (int rowFiveLetter = 0; rowFiveLetter < 5; rowFiveLetter++)
            { // out the word and split the Characters in with the [ ] 5 times
                // checks the user enter word mathes with the random word position
                if (userGuessFiveLetter[rowFiveLetter] == fiveLetterRandWord[rowFiveLetter])
                { // check Guess entry is in the same postion as the Random Word, if yes then print and push back to previous entry vector
                    userFiveLetterGuess = toupper(userGuessFiveLetter[rowFiveLetter]);
                    cout << "[ " << userFiveLetterGuess << " ]";
                    previousInputsFivesLetter.push_back(userFiveLetterGuess);
                }
                // checks that character is entered is in the word  of the randoms word if it is then print the word at the user entered postion
                else if (userGuessFiveLetter[rowFiveLetter] == fiveLetterRandWord[0] || userGuessFiveLetter[rowFiveLetter] == fiveLetterRandWord[1] || userGuessFiveLetter[rowFiveLetter] == fiveLetterRandWord[2] || userGuessFiveLetter[rowFiveLetter] == fiveLetterRandWord[3] || userGuessFiveLetter[rowFiveLetter] == fiveLetterRandWord[4])
                {
                    userFiveLetterGuess = userGuessFiveLetter[rowFiveLetter];
                    cout << "[ " << userFiveLetterGuess << " ]";
                    previousInputsFivesLetter.push_back(userFiveLetterGuess);
                }
                // check the word in valid
                else if (userGuessFiveLetter[rowFiveLetter] != fiveLetterRandWord[rowFiveLetter])
                {                    // the character entered is not the character of the random word we are looking for
                    cout << "[ * ]"; // not valid
                    previousInputsFivesLetter.push_back("*");
                }
                elapsedSecondsForFiveWordGuess = difftime(time(NULL), startTimeInGuess); // stores the time it took
            }
            cout << endl;
            attempsCoutFiveLetter++; // increment the attemps after circling the loop valid & invalid entries
            if (attempsCoutFiveLetter > 5 && userGuessFiveLetter != fiveLetterRandWord && elapsedSecondsForFiveWordGuess <= 40)
            { // reaching the max attemps will display the message and it will break out of the look
                cout << "Maximum amount of attempts have been reached. Try again.\n"
                     << endl;
            }
            else if (fiveLetterRandWord == userGuessFiveLetter && elapsedSecondsForFiveWordGuess <= 40)
            { // if the guess entry is right then display the message
                cout << "\nNice Work!  You guessed the correct word\n   - You completed the board in: " << elapsedSecondsForFiveWordGuess << " seconds.\n"
                     << "   - It took you " << attempsCoutFiveLetter << "/6 attempts.\n\n"
                     << endl;
                return true; // so we can keep track of the streak's
            }
            else if (elapsedSecondsForFiveWordGuess > 40)
            { // time is more then 40 seconds then it will not pass the any inputs and will display the message
                cout << "\nYour time has expired.  Try again. \n"
                     << "  - You are " << elapsedSecondsForFiveWordGuess - 40 << " seconds over the 40 second time limit.\n"
                     << endl;
                break; // time went to 40 seconds
            }
        } // end of else

    } // End of the While loop
    return false;
} // End of fiveLetterWord()

int main()
{
    srand(1); // srand for to generate the rand word in same sequence

    // Display game instructions
    gameDisplayInstructions();
    int menuOption;         // menu Option user can chose from
    int guessCount = 0;     // to keep track how many words user guessed
    int elapsedSeconds = 0; // time it took to get a right word
    int longestStreak = 0;  //  to keep track of the Longest Streak
    int currentStreak = 0;  // to keep track of the cCurrent Streak

    // Keep looping until user selects the option to exit
    while (menuOption != 3)
    {
        // deplay the message to user chose from
        cout << "Select a menu option:\n"
             << "    1. To play Wordle Reload 3 letter play\n"
             << "    2. To play Wordle Reload 5 letter play\n"
             << "    3. Exit the program"
             << endl;
        // cin Menu Option
        cout << "Your choice --> ";
        cin >> menuOption;

        // user chose 1 then began the game with the 3 letter words
        if (menuOption == 1)
        {
            // deplay the instruction for the 3 letter words
            cout << "\nTo get started, enter your first 3 letter word.\n"
                 << "You have 4 attempts to guess the random word.\n"
                 << "The timer will start after your first word entry.\n"
                 << "Try to guess the word within 20 seconds.\n"
                 << endl;

            if (threeLetterWord() == true)
            {                                                            // for 3 letter words if the user guess matches with the random word
                time_t startTimeInGuess = time(NULL);                    // start the time after right guess
                guessCount++;                                            // increment the correct word guess for 3 letter words
                currentStreak++;                                         // increment the current Streak for 3 letter words
                elapsedSeconds = difftime(time(NULL), startTimeInGuess); // stop the timer
            }
            else
            {                      // if the guess was not right and got to the maximum number of the tries for 3 letter words
                currentStreak = 0; // current streak rest to 0 for 3 letter words
            }

            // deplay the longest Streak for 3 letter words
            if (currentStreak >= longestStreak)
            {
                longestStreak = currentStreak;
            }

        } // End of the Menu Option 1

        // user chose 2 then began the game with the 5 letter words
        else if (menuOption == 2)
        {
            // deplay the instruction for the 5 letter words
            cout << "\nTo get started, enter your first 5 letter word.\n"
                 << "You have 6 attempts to guess the random word.\n"
                 << "The timer will start after your first word entry.\n"
                 << "Try to guess the word within 40 seconds.\n"
                 << endl;

            if (fiveLetterWord() == true)
            {                                                            //  for 5 letter words if the user guess matches with the random word
                time_t startTimeInGuess = time(NULL);                    // start the time after right guess
                currentStreak++;                                         // increment the correct word guess for 5 letter words
                guessCount++;                                            // increment the current Streak 5 letter words
                elapsedSeconds = difftime(time(NULL), startTimeInGuess); // time will not go further because we want to get a average time it took use to guess the word
            }
            else
            {                      // if the guess was not right and reached to the maximum number of the tries for 5 letter words
                currentStreak = 0; // current streak rest to for 5 letter word to 0
            }
            // deplay the longest Streak for the 5 letter words
            if (currentStreak >= longestStreak)
            {
                longestStreak = currentStreak;
            }
        } // End of the Menu Option 2

        // menuOption is 3 then deplay the Overall Stats with the Time, Longest Streak and Guesses
        else if (menuOption == 3)
        {
            // if the user chose 3 before the game starts or the user didn't get any words right and enters 3
            if (longestStreak == 0 && guessCount == 0)
            {
                cout << "Overall Stats:\n"
                     << "   - You guessed: " << guessCount << "\n"
                     << "   - Your longest streak is: " << longestStreak << "\n"
                     << "   - Average word completion time: N/A\n"
                     << "Exiting program\n"
                     << endl;
            }
            else
            { // if the words were right and show the Guesses, Longest Streak and Time
                cout << "Overall Stats:\n"
                     << "   - You guessed: " << guessCount << "\n"
                     << "   - Your longest streak is: " << longestStreak << "\n"
                     << "   - Average word completion time: " << guessCount / elapsedSeconds << "\n"
                     << "Exiting program\n"
                     << endl;
            }
        } // End of the Menu Option 3

    } // End of the loop

} // End of Main