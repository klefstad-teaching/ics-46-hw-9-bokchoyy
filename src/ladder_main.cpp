#include "ladder.h"

int main() {
    try {
        set<string> word_list;
        load_words(word_list, "words.txt");
        
        if (word_list.empty()) {
            cerr << "Error: Dictionary is empty or failed to load." << endl;
            return 1;
        }
        string start_word, end_word;
        cout << "Enter start word: ";
        if (!(cin >> start_word)) {
            cerr << "Error: Failed to read start word." << endl;
            return 1;
        }
        transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
        
        cout << "Enter end word: ";
        if (!(cin >> end_word)) {
            cerr << "Error: Failed to read end word." << endl;
            return 1;
        }
        transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);
        
        if (start_word.empty() || end_word.empty()) {
            error(start_word, end_word, "Start or end word is empty.");
            return 1;
        }
        if (start_word == end_word) {
            error(start_word, end_word, "Start and end words are the same. This is not allowed.");
            return 1;
        }
        if (word_list.find(end_word) == word_list.end()) {
            error(start_word, end_word, "End word is not in the dictionary.");
            return 1;
        }
        vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
        
        if (ladder.empty()) {
            cout << "No word ladder found." << endl;
        } else {
            print_word_ladder(ladder);
        }
        
        return 0;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Unknown error occurred." << endl;
        return 1;
    }
}