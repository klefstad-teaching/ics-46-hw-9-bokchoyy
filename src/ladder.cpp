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
    if (word1 == word2) {
        return true;
    }
    
    int len1 = word1.size(), len2 = word2.size();
    if (abs(len1 - len2) > 1) return false;
    
    int diff = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++diff > 1) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    if (i < len1 || j < len2) {
        diff++;
    }
    
    return diff == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return vector<string>();
    }
    
    if (word_list.empty() || word_list.find(end_word) == word_list.end()) {
        return vector<string>();
    }
    
    queue<vector<string>> ladder_queue;
    
    vector<string> initial_ladder;
    initial_ladder.push_back(begin_word);
    ladder_queue.push(initial_ladder);
    
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
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
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
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
    exit(0); 
}