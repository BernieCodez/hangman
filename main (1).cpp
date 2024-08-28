#include <bits/stdc++.h>
using namespace std;

string guess, selectedWord;
set<char> guessedChars;
int triesLeft = 7;
bool correctGuess, hint=false;

void printHangman(int attempts = 7) {
    cout << "\033[H\033[2J\033[3J" ;//clears screen
    
    if (attempts == 7) {
        cout << "   |--|" << endl;
        cout << "   |  " << endl;
        cout << "   |  " << endl;
        cout << "   |  " << endl;
        cout << "--------" << endl;
    } else if (attempts == 6) {
        cout << "   |--|" << endl;
        cout << "   |  O" << endl;
        cout << "   |  " << endl;
        cout << "   |  " << endl;
        cout << "--------" << endl;
    } else if (attempts == 5) {
        cout << "   |--|" << endl;
        cout << "   |  O" << endl;
        cout << "   |  |" << endl;
        cout << "   |  " << endl;
        cout << "--------" << endl;
    } else if (attempts == 4) {
        cout << "   |--|" << endl;
        cout << "   |  O" << endl;
        cout << "   | /|" << endl;
        cout << "   |  " << endl;
        cout << "--------" << endl;
    } else if (attempts == 3) {
        cout << "   |--|" << endl;
        cout << "   |  O" << endl;
        cout << "   | /|\\" << endl;
        cout << "   |  " << endl;
        cout << "--------" << endl;
    } else if (attempts == 2) {
        cout << "   |--|" << endl;
        cout << "   |  O" << endl;
        cout << "   | /|\\" << endl;
        cout << "   | /" << endl;
        cout << "--------" << endl;
    } else if (attempts == 1) {
        cout << "   |--|" << endl;
        cout << "   |  O" << endl;
        cout << "   | /|\\" << endl;
        cout << "   | / \\" << endl;
        cout << "--------" << endl;
    } else if (attempts == 0) {
        cout << "Game Over!" << endl;
    }
}

void start() {
    string words[50] = {
        "export", "linear", "mosaic", "hesitate", "conservative", "understanding", "rear",
        "related", "far", "engagement", "thinker", "angle", "beneficiary", "behead",
        "ghostwriter", "chip", "marsh", "trouser", "joystick", "birthday", "praise",
        "hill", "multiply", "extension", "exile", "bean", "staff", "funeral", "grace",
        "lake", "complex", "fool", "prescription", "economy", "presidency", "campaign",
        "twin", "coffin", "advertising", "flush", "artificial", "correction", "judgment",
        "work", "comfortable", "emergency", "jet", "soul", "trustee", "acquit"
    };
    srand((unsigned)time(0));
    int random = rand() % 50;
    selectedWord = words[random];
}

void printBlanks() {
    //cout<<selectedWord<<endl;
    cout << "Tries left: " << triesLeft << endl;
    for (char c : selectedWord) {
        if (guessedChars.count(toupper(c))) {
            cout << c << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << "(" << selectedWord.size() << " letters)" << endl;
    
}

void containsLetter(const string& word, const string& letter) {
    if (letter.empty() || letter.size() != 1) {
        correctGuess = false;
        return;
    }
    char letterChar = toupper(letter[0]);
    correctGuess = false;
    //cout << "Checking for letter: " << letterChar << " in word: " << word << endl;
    for (char ch : word) {
        if (toupper(ch) == letterChar) {
            correctGuess = true;
            break;
        }
    }
    //cout << "Letter found: " << correctGuess << endl;
}

void checkAnswer() {
    containsLetter(selectedWord, guess);
    if (correctGuess) {
        //cout << "Well done!" << endl;
        guessedChars.insert(toupper(guess[0]));
    } else {
        triesLeft--;
        //cout << "Failure!" << endl;
    }
}

int main() {
    start();
    cout << "Welcome to Hangman v1.0." << endl;
    cout << "Do you know how to play? (yes or no)" << endl;
    string input;
    cin >> input;
    hint = false;

    if (input == "yes") {
        while (triesLeft > 0) {
            printHangman(triesLeft);
            printBlanks();
            
            if(hint==true){
                cout<<"Your guess should be "<<selectedWord<<":";
            }else{
                cout << "Your guess: ";

            }
            cin >> guess;
            guess[0] = toupper(guess[0]);

            if (guess.size() == 1) {
                if (guessedChars.count(toupper(guess[0]))) {
                    cout << "You've already guessed that letter!" << endl;
                } else {
                    checkAnswer();
                }
            } else if(guess == "hint plz"){
                hint = true;
            }else{
                cout << "Your guess is not accepted. Please use one character only." << endl;
            }

            if (all_of(selectedWord.begin(), selectedWord.end(), [&](char c) { return guessedChars.count(toupper(c)); })) {
                cout << "Congratulations, you've won!" << endl;
                break;
            }
        }
        if (triesLeft == 0) {
            cout << "Game Over! The word was " << selectedWord << endl;
        }
    }else{
        cout << "You should know how to play." << endl;
        this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"Exiting..."<<endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        cout << "\033[H\033[2J\033[3J" ;//clears screen

    }
    return 0;
}
