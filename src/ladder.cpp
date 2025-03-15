
#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << endl;
    cerr << "Word 1: " << word1 << endl;
    cerr << "Word 2: " << word2 << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs(static_cast<int>(str1.length()) - static_cast<int>(str2.length())) > d) {
        return false;
    }
        if (str1.length() == str2.length()) {
        int diff = 0;
        for (size_t i = 0; i < str1.length(); i++) {
            if (str1[i] != str2[i]) {
                diff++;
                if (diff > d) return false;
            }
        }
        return true;
    } 
    else if (str1.length() == str2.length() + 1) {
        for (size_t i = 0; i < str1.length(); i++) {
            string temp = str1;
            temp.erase(i, 1);
            if (temp == str2) return true;
        }
        return false;
    } 
    else if (str1.length() + 1 == str2.length()) {
        for (size_t i = 0; i < str2.length(); i++) {
            string temp = str2;
            temp.erase(i, 1);
            if (temp == str1) return true;
        }
        return false;
    }
    
    return false;
}
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.empty()) {
        return vector<string>();
    }
        if (word_list.find(end_word) == word_list.end()) {
        return vector<string>();
    }
        if (begin_word == end_word) {
        // Change from returning a vector with one element to an empty vector
        return vector<string>();
    }
    queue<vector<string>> ladder_queue;
    
    vector<string> initial_ladder;
    initial_ladder.push_back(begin_word);
    ladder_queue.push(initial_ladder);
    set<string> visited;
    visited.insert(begin_word);
    
    const size_t MAX_ITERATIONS = 100000;
    size_t iterations = 0;
    
    while (!ladder_queue.empty() && iterations < MAX_ITERATIONS) {
        iterations++;
        
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
    
        string last_word = current_ladder.back();
        for (const string& word : word_list) {
            if (visited.find(word) != visited.end()) {
                continue;
            }
            if (is_adjacent(last_word, word)) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                visited.insert(word);
                
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return vector<string>();
}

void load_words(set<string>& word_list, const string& file_name) {
    word_list.clear();
    
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }
        if (file.peek() == ifstream::traits_type::eof()) {
        cerr << "Error: File " << file_name << " is empty" << endl;
        file.close();
        return;
    }
    string word;
    while (file >> word) {
        if (word.empty()) {
            continue;
        }
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    
    if (word_list.empty()) {
        cerr << "Warning: No valid words found in " << file_name << endl;
    }
    
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << " " << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    cout << "Testing word ladders..." << endl;
    
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}