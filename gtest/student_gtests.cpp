#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <algorithm>
#include "dijkstras.h"
#include "ladder.h"

Graph create_test_graph() {
    Graph G;
    G.numVertices = 4;
    G.resize(G.numVertices);
    
    G[0].push_back(Edge(0, 1, 3));
    G[0].push_back(Edge(0, 3, 1));
    G[1].push_back(Edge(1, 2, 3));
    G[3].push_back(Edge(3, 1, 2));
    G[3].push_back(Edge(3, 2, 5));
    
    return G;
}

TEST(LadderTest, IsAdjacent) {
    EXPECT_TRUE(is_adjacent("cat", "bat"));
    EXPECT_TRUE(is_adjacent("dog", "bog"));

    EXPECT_TRUE(is_adjacent("cat", "cats"));
    EXPECT_TRUE(is_adjacent("dog", "dogs"));
  
    EXPECT_FALSE(is_adjacent("cat", "dog"));
    EXPECT_FALSE(is_adjacent("hello", "world"));
    
    EXPECT_FALSE(is_adjacent("cat", "cathy"));
}

TEST(LadderTest, GenerateWordLadder) {
    set<string> word_list = {"cat", "bat", "hat", "hot", "dot", "dog"};
    
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    EXPECT_EQ(ladder.size(), 4);
    
    if (ladder.size() == 4) {
        EXPECT_EQ(ladder[0], "cat");
        EXPECT_EQ(ladder[3], "dog");
    }
    
    ladder = generate_word_ladder("rat", "dog", word_list);
    if (!ladder.empty()) {
        EXPECT_EQ(ladder[0], "rat");
        EXPECT_EQ(ladder.back(), "dog");
    }
    
    word_list.erase("hot");
    word_list.erase("dot");
    ladder = generate_word_ladder("cat", "dog", word_list);
    EXPECT_TRUE(ladder.empty());
}


TEST(DijkstraTest, ShortestPath) {
    Graph G = create_test_graph();
    vector<int> previous;
    
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    EXPECT_EQ(distances[0], 0);  
    EXPECT_EQ(distances[1], 3);  
    EXPECT_EQ(distances[2], 6);  
    EXPECT_EQ(distances[3], 1);  
    
    EXPECT_EQ(previous[0], -1);
    EXPECT_EQ(previous[1], 0);   
    EXPECT_EQ(previous[2], 1);   
    EXPECT_EQ(previous[3], 0);   
}

TEST(DijkstraTest, ExtractPath) {
    Graph G = create_test_graph();
    vector<int> previous;
    
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    vector<int> path = extract_shortest_path(distances, previous, 2);
    
    EXPECT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 2);
    
    path = extract_shortest_path(distances, previous, 1);
    
    EXPECT_EQ(path.size(), 2);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
}

TEST(DijkstraTest, ReadFromFile) {
    ofstream test_file("test_graph.txt");
    test_file << "4" << endl;
    test_file << "0 1 3" << endl;
    test_file << "0 3 1" << endl;
    test_file << "1 2 3" << endl;
    test_file << "3 1 2" << endl;
    test_file << "3 2 5" << endl;
    test_file.close();
    
    Graph G;
    file_to_graph("test_graph.txt", G);
    
    EXPECT_EQ(G.numVertices, 4);
    EXPECT_EQ(G[0].size(), 2);
    EXPECT_EQ(G[1].size(), 1);
    EXPECT_EQ(G[2].size(), 0);
    EXPECT_EQ(G[3].size(), 2);
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 3);
    EXPECT_EQ(distances[2], 6);
    EXPECT_EQ(distances[3], 1);
    
    remove("test_graph.txt");
}

TEST(LadderTest, RealWordlist) {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    if (word_list.empty()) {
        GTEST_SKIP() << "Skipping test because words.txt file is not available";
    }
    
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    EXPECT_EQ(ladder.size(), 4);
    
    ladder = generate_word_ladder("code", "data", word_list);
    EXPECT_EQ(ladder.size(), 6);
    
    ladder = generate_word_ladder("car", "cheat", word_list);
    EXPECT_EQ(ladder.size(), 4);
}