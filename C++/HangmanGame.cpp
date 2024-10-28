#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.size(); i++) {
        if (guessed[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool checkWin(const vector<bool>& guessed) {
    return all_of(guessed.begin(), guessed.end(), [](bool g) { return g; });
}

int main() {
    vector<string> wordList = {"apple", "banana", "grapes", "orange", "melon"};
    srand(static_cast<unsigned>(time(0)));  
    string word = wordList[rand() % wordList.size()];  

    vector<bool> guessed(word.size(), false); 
    vector<char> incorrectGuesses;
    int maxAttempts = 6;

    cout << "Welcome to Hangman!\nGuess the word letter by letter." << endl;

    while (incorrectGuesses.size() < maxAttempts) {
        displayWord(word, guessed);
        cout << "\nIncorrect guesses: ";
        for (char c : incorrectGuesses) cout << c << " ";
        cout << "\nAttempts left: " << maxAttempts - incorrectGuesses.size() << endl;

        cout << "Enter a letter: ";
        char guess;
        cin >> guess;

        if (find(incorrectGuesses.begin(), incorrectGuesses.end(), guess) != incorrectGuesses.end() || 
            find_if(guessed.begin(), guessed.end(), [&](bool g) { return word[&g - &guessed[0]] == guess && g; }) != guessed.end()) {
            cout << "You already guessed that letter!" << endl;
            continue;
        }

        bool found = false;
        for (size_t i = 0; i < word.size(); i++) {
            if (word[i] == guess) {
                guessed[i] = true;
                found = true;
            }
        }

        if (!found) {
            incorrectGuesses.push_back(guess);
        }

        if (checkWin(guessed)) {
            cout << "Congratulations! You guessed the word: " << word << endl;
            break;
        }
    }

    if (incorrectGuesses.size() >= maxAttempts) {
        cout << "Sorry, you've been hanged! The word was: " << word << endl;
    }

    return 0;
}
