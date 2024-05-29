/*
Made by: Mason Yuen (myuen1015@gmail.com)

Word Hunt by Game Pigeon: In this game, you play on a 4x4 grid board filled with letters. Your objective is to create as many words as possible. The larger the board, the more points you earn!

Usually, the more you play, the better you get, but who has time for that?

This algorithm allows you to find all the words that could be created. To use it, enter the board line by line, like this:

“Please enter 16 letters for the 4x4 board:”
m
e
a
f
g
a
s
n
i
g
r
w
s
a
g
l

In this algorithm, I’ve used a Trie data structure, DFS (Depth-First Search), Backtracking, and Sorting.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// Directions for DFS
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // directions it can move on the board. x-coordinates 
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // y-coordinates

struct TrieNode
{
    TrieNode* child[26]; // creats 26 children, one for each letter in the alphabet
    bool isEndOfWord; // is to represent the end of the word

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
    }
};

TrieNode* getNode()
{
    return new TrieNode(); // creats a returns new trie node
}

void insert(TrieNode* root, const string& key)  // this functiosn inserts a word into trie and traveres each character of the word. It creates nodes if they dont exsit it marks the end of the word. 
{
    TrieNode* pCrawl = root;
    for (char ch : key) {
        int index = ch - 'a';
        if (!pCrawl->child[index])
            pCrawl->child[index] = getNode();
        pCrawl = pCrawl->child[index];
    }
    pCrawl->isEndOfWord = true;
}

bool isSafe(int x, int y, vector<vector<bool>>& visited)  // checks the bounds of the boards
{
    return (x >= 0 && x < 4 && y >= 0 && y < 4 && !visited[x][y]);
}

void searchWord(vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j, string str, TrieNode* pNode, vector<string>& foundWords) //recursive function that adds the words to the results. then it explores the directionns. afterwards it backtracks by unmakring all cells as visited
{
    if (!isSafe(i, j, visited))
        return;

    visited[i][j] = true;
    str += board[i][j];

    int index = board[i][j] - 'a';
    if (!pNode->child[index]) {
        visited[i][j] = false;
        return;
    }

    pNode = pNode->child[index];

    if (str.length() > 3 && pNode->isEndOfWord) {
        foundWords.push_back(str);
    }

    for (int dir = 0; dir < 8; dir++) {
        int newX = i + dx[dir];
        int newY = j + dy[dir];
        searchWord(board, visited, newX, newY, str, pNode, foundWords);
    }

    visited[i][j] = false;
}

void printWords(vector<string>& foundWords) {
    sort(foundWords.begin(), foundWords.end(), [](const string& a, const string& b) {
        return a.size() < b.size();
        });

    for (const auto& word : foundWords)
        cout << word << endl;
}

void wordSearch(vector<vector<char>>& board, TrieNode* root) { // initiates the word search on the board by calling "searchword" 
    vector<vector<bool>> visited(4, vector<bool>(4, false));
    vector<string> foundWords;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            searchWord(board, visited, i, j, "", root, foundWords);
        }
    }

    printWords(foundWords);
}

int main() {
    TrieNode* root = getNode();
    ifstream dictionary("words_alpha.txt");
    string word;
    if (dictionary.is_open()) {
        while (dictionary >> word) {
            if (word.length() > 3)
                insert(root, word);
        }
        dictionary.close();
    }

    vector<vector<char>> board(4, vector<char>(4));

    cout << "Please enter 16 letters for the 4x4 board:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> board[i][j];
        }
    }

    wordSearch(board, root);

    return 0;
}
// This function sets up the Trie by inserting words from the dictionary file. It then reads a 4x4 board from user input and starts the word search. Finally, it prints the found words.



/*
The result of the testing output in the demonstrations.
meas
mean
rage
ragi
meas
mear
mesa
mesa
maes
mage
rase
magi
masa
maia
mags
magi
mags
maga
rasa
mars
rais
marg
raia
mara
rags
ragi
marg
nasa
marl
egma
egis
rags
raga
eggs
eggs
raia
rais
ears
earn
raga
earl
agag
asem
asea
ansa
rags
ragi
fans
rags
gean
gear
siam
saga
game
sags
gaea
gaes
sara
gaia
gags
gags
gaga
gars
aias
garn
garg
gara
garg
giga
agas
gigs
gigs
giga
agar
agra
ages
asem
asea
aias
agra
agar
arse
agas
agag
arse
arna
arna
asia
sean
agra
gram
gras
seam
sear
same
saan
sage
gras
gaia
gaga
gags
sags
saga
gags
gara
gars
garn
sara
naam
garg
game
gaea
gaes
gage
gaia
gars
garn
gara
garg
giga
gram
gras
gras
gaia
gara
gars
garn
garg
rame
means
igara
mages
magas
marse
marga
grame
maras
eggar
raiae
eggar
gigas
earns
aegis
ansae
ansar
ragas
gears
gesan
games
gasan
garse
gages
gigas
aegis
agars
argas
argas
segar
gigas
gasan
rages
saiga
saiga
sagra
sagai
sagas
ragis
sarna
sigma
garse
ragis
saiga
grame
sarsa
games
sagas
sagai
sagra
garse
sarsa
sarna
sagra
igara
marga
raias
agars
agsam
raias
arage
arase
ragis
igara
argas
garse
ragas
megara
marais
eggars
gemara
eggars
seggar
seggar
saggar
saggar
sigmas
saigas
saigas
garage
ramean
gamgia
saggar
garage
saigas
saggar
saggars
garages
saggars
garages
*/