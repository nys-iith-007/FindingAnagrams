#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

string signature(const string& input){
    string s;
    for(char c:input) if(isalpha(static_cast<unsigned char>(c))) s.push_back(tolower(static_cast<unsigned char>(c)));
    sort(s.begin(),s.end()); return s;
}
struct CustomHash{
    size_t operator()(const string& s) const{
        uint64_t h=1469598103934665603ULL;
        for(unsigned char c:s){h^=c;h*=1099511628211ULL;}
        return static_cast<size_t>(h);
    }
};
class AnagramIndex{
    unordered_map<string,vector<string>,CustomHash> table;
public:
    void load(const string& filename){
        ifstream in(filename); if(!in) throw runtime_error("Cannot open dictionary: "+filename);
        string word;
        while(in>>word) if(!word.empty()) table[signature(word)].push_back(word);
        for(auto& [key,words]:table){sort(words.begin(),words.end());words.erase(unique(words.begin(),words.end()),words.end());}
    }
    vector<string> find(const string& word) const{
        auto it=table.find(signature(word)); return it==table.end()?vector<string>{}:it->second;
    }
};
int main(int argc,char** argv){
    if(argc!=3){cerr<<"Usage: anagrams <dictionary-file> <word>\n";return 1;}
    try{
        AnagramIndex index; index.load(argv[1]);
        auto words=index.find(argv[2]);
        for(const auto& word:words) cout<<word<<"\n";
        if(words.empty()) cout<<"No anagrams found.\n";
    }catch(const exception& e){cerr<<e.what()<<"\n";return 2;}
}