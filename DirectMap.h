#ifndef DIRECTMAP_H
#define DIRECTMAP_H

#include <math.h>
#include <queue>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;
struct DirectMap{
    int hits = 0;
    int accesses = 0;
    int offsetSize, tagSize, numLines;

    string name = "DIRECT MAP";
    double hitRatio;
    int lineWidth;
    int cacheSize, bytesPerLine; //measured in bytes
    int addressSize; //bits in address, determined by file

    DirectMap(int cacheSize, int bytesPerLine, int addressSize):cacheSize(cacheSize),bytesPerLine(bytesPerLine),addressSize(addressSize)
    {
        numLines = cacheSize / bytesPerLine;
        offsetSize = log2(bytesPerLine);
        lineWidth = log2(numLines);
        tagSize = addressSize - (offsetSize + lineWidth);

    }

    void HitRatio(vector<string> addresses){
        //cache will be vector
        //find line num by looking at subset of bit string
        //check if that line is full, deal with it as such



        vector<unsigned long long> cache(this->numLines, ULLONG_MAX);

        for(int i = 0; i < addresses.size(); i++){
            //first convert address to binary
            string s = addresses[i];
            stringstream ss;
            ss << hex << s;
            unsigned long long x;
            ss >> x;
            bitset<64> b(x);
            string b_string = b.to_string();

            string tag = b_string.substr(0, this->tagSize);
            string line_str = b_string.substr(this->tagSize, this->lineWidth);
            unsigned long long tag_unsignedlonglong = stoull(tag, nullptr, 2);
            int line = stoi(line_str, nullptr, 2);

            //hit?
            //check if cache[line] == tag_unsignedlonglong
            //if so, hit, otherwise miss
            //then, is it empty, or must it be replaced

            if(cache[line] == tag_unsignedlonglong){
                this->hits = 1 + this->hits;
            }
            else{
                cache[line] = tag_unsignedlonglong;
            }
            this->accesses = 1 + this->accesses;

        }

        double hitsDouble = (double)this->hits;
        double accessesDouble = (double)this->accesses;

        double hitRatio = ((double)((int)((hitsDouble*100.0)/accessesDouble)))/100.0;
        this->hitRatio = hitRatio;
        
        cout << "Hits : " << this->hits << endl;
        cout << "Accesses : " << this->accesses << endl;
        cout << "Hit Ratio : " << hitRatio << endl;
    }

};

#endif