#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    
    transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
    
    cout << "Enter end word: ";
    cin >> end_word;
    
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);
    
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
        cout << "No word ladder found from '" << start_word << "' to '" << end_word << "'." << endl;
    } else {
        cout << "Word ladder from '" << start_word << "' to '" << end_word << "':" << endl;
        print_word_ladder(ladder);
    }
    
    return 0;
}