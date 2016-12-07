//Angelo Zamudio CS381 Summer 16'

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class InvertedIndex {
private:
    map<string, pair<int, vector<int>>> wordIndex;
public:
    InvertedIndex() { };

    ~InvertedIndex(){};

    bool alreadyIndexed(string x, int line_num, int line_pos) {
        map<std::string, std::pair<int, vector<int>>>::iterator i = wordIndex.find(x);
        if (i != wordIndex.end()) {
            i->second.first += 1;
            i->second.second.push_back(line_num);
            i->second.second.push_back(line_pos);
            return true;
        }//if
        return false;
    }//alreadyIndexed

    void addToindex(string x, int line_num, int line_pos) {
        if (alreadyIndexed(x, line_num, line_pos)) {
            return;
        } else {
            wordIndex[x] = {1, {line_num, line_pos}};
            return;
        }//else
    }//addToIndex

    void printIndex() {
        int count = 0;
        for (auto i: wordIndex) {
            cout << i.first << " " << i.second.first<<" [ ";

            for (auto j:i.second.second) {
                if (count % 2 == 0) {
                    cout << "(" << j << ",";
                    count++;
                } else if (count % 2 == 1) {
                    cout << j << ") ";
                    count++;
                }//if
            }//forj
            cout << "]\n\n";
            count = 0;
        }//for i
        return;
    }//printIndex
};

int main(int argc, char *argv[]) {
    InvertedIndex a;
    int count = 1;
    size_t line_pos;
    string word;
    ifstream in(argv[1]);
    string line;
    if (in) {
        while (getline(in, line)) {
            stringstream ss(line);
            while (ss >> word) {
                line_pos = line.find(word);
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] == ',' || word[i] == '.') {
                        word.erase(word.begin() + i);
                    }//if
                }//for
                a.addToindex(word, count, int(line_pos));
            }//while word
            count += 1;
        }//while line
    }//open
    in.close();
    a.printIndex();
    return 0;
};