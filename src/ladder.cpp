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
    set<string> mini_dict;
    mini_dict.insert("cat");
    mini_dict.insert("bat");
    mini_dict.insert("hat");
    mini_dict.insert("cot");
    mini_dict.insert("cog");
    mini_dict.insert("dog");

    mini_dict.insert("marty");
    mini_dict.insert("party");
    mini_dict.insert("parts");
    mini_dict.insert("carts");
    mini_dict.insert("cards");
    mini_dict.insert("curds");
    mini_dict.insert("curls");
    
    mini_dict.insert("code");
    mini_dict.insert("cade");
    mini_dict.insert("cate");
    mini_dict.insert("date");
    mini_dict.insert("data");
    
    mini_dict.insert("work");
    mini_dict.insert("fork");
    mini_dict.insert("form");
    mini_dict.insert("foam");
    mini_dict.insert("flam");
    mini_dict.insert("flay");
    mini_dict.insert("play");
    
    mini_dict.insert("sleep");
    mini_dict.insert("sheep");
    mini_dict.insert("sheer");
    mini_dict.insert("cheer");
    mini_dict.insert("clear");
    mini_dict.insert("cleat");
    mini_dict.insert("cleave");
    mini_dict.insert("aweave");
    mini_dict.insert("awake");
    
    mini_dict.insert("car");
    mini_dict.insert("cart");
    mini_dict.insert("chat");
    mini_dict.insert("cheat");
    
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

    my_assert(generate_word_ladder("cat", "dog", mini_dict).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", mini_dict).size() == 6);
    my_assert(generate_word_ladder("code", "data", mini_dict).size() == 5);
    my_assert(generate_word_ladder("work", "play", mini_dict).size() == 7);
    my_assert(generate_word_ladder("sleep", "awake", mini_dict).size() == 9);
    my_assert(generate_word_ladder("car", "cheat", mini_dict).size() == 4);
}