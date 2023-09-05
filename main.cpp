#include <iostream>
#include <string>
#include <vector>


// define a TrieNode class to represent nodes in the trie.
class TrieNode
{
public:
    TrieNode() : isEndOfWord(false)
    {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }

    bool isEndOfWord;
    TrieNode* children[26];
};


// define a Trie class to manage the trie structure.
class Trie
{
public:
    Trie()
    {
        root = new TrieNode();
    }

    // insert a word into the trie.
    void insert(const std::string& word)
    {
        TrieNode* current = root;

        for (char c : word) {
            // map the character to 
            // an index (0 to 25)
            int index = c - 'a'; 

            if (!current->children[index]) {
                // create a new node if it doesn't exist
                current->children[index] = new TrieNode();
            }

            // move to the next node
            current = current->children[index];
        }

        // mark the last node as the end of a word
        current->isEndOfWord = true;
    }

    // find all words in the trie that start with a given prefix
    std::vector<std::string> autoComplete(const std::string& prefix)
    {
        TrieNode* current = root;

        for (char c : prefix) {
            int index = c - 'a';

            if (!current->children[index]) {
                // no suggestions if the
                // prefix is not in the trie
                return {}; 
            }

            current = current->children[index];
        }

        std::vector<std::string> suggestions;
        findWordsWithPrefix(current, prefix, suggestions);

        return suggestions;
    }

private:
    TrieNode* root;

    // recursively find words with a given prefix
    void findWordsWithPrefix(TrieNode* node, const std::string& prefix, std::vector<std::string>& suggestions)
    {
        if (node->isEndOfWord) {
            suggestions.push_back(prefix);
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                char next_char = 'a' + i;

                findWordsWithPrefix(node->children[i], prefix + next_char, suggestions);
            }
        }
    }
};


int main() {
    Trie dictionary;

    // list of professions
    dictionary.insert("actor");
    dictionary.insert("actress");
    dictionary.insert("banker");
    dictionary.insert("barber");
    dictionary.insert("doctor");
    dictionary.insert("doorman");
    dictionary.insert("farmer");
    dictionary.insert("fireman");

    while (true) {
        std::cout << "Enter a partial word (or type \"exit\" to quit): ";
        std::string input;
        std::cin >> input;

        if (input == "exit") {
            // exit the program if
            // the user types 'exit'
            break; 
        }

        std::vector<std::string> suggestions = dictionary.autoComplete(input);

        if (suggestions.empty()) {
            std::cout << "No suggestions found." << std::endl;
        }
        else {
            std::cout << "Suggestions:" << std::endl;
            for (const std::string& word : suggestions) {
                // print the suggestions
                std::cout << word << std::endl;
            }
        }
    }

    return 0;
}
