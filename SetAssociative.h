#ifndef SETASSOCIATIVE_H
#define SETASSOCIATIVE_H

#include <math.h>
#include <queue>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;
struct SetAssociative{
    int hits = 0;
    int accesses = 0;
    int offsetSize, tagSize, numLines;
    string name;
    double hitRatio;

    int setWidth, linesPerSet, numSets;
    int cacheSize, bytesPerLine; //measured in bytes
    int addressSize; //bits in address, determined by file

    SetAssociative(int cacheSize, int bytesPerLine, int addressSize, int linesPerSet):cacheSize(cacheSize),bytesPerLine(bytesPerLine),addressSize(addressSize),linesPerSet(linesPerSet)
    {
        numSets = (cacheSize / bytesPerLine) / linesPerSet;
        offsetSize = log2(bytesPerLine);
        setWidth = log2(numSets);
        tagSize = addressSize - (offsetSize + setWidth);
    }

    void FIFORatio(vector<string> addresses){
        //vector of queues of tags

        vector< deque<unsigned long long> > cache(this->numSets);

        this->name = "FIFO " + to_string(this->linesPerSet) + "-WAY SET ASSOCIATIVE";


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
            unsigned long long tag_unsignedlonglong = stoull(tag, nullptr, 2);

            string set = b_string.substr(this->tagSize, this->setWidth);
            unsigned long long set_unsignedlonglong = stoull(set, nullptr, 2);


            //hit?
            int numHitsStart = this->hits;

            for(auto iter = cache[set_unsignedlonglong].cbegin(); iter !=cache[set_unsignedlonglong].cend(); iter++){
                if(tag_unsignedlonglong == *iter){
                    this->hits = 1 + this->hits;
                    break;
                }
            }
            this->accesses = 1 + this->accesses;

            //miss case
            if(numHitsStart == this->hits){

                //is set full?
                if(cache[set_unsignedlonglong].size() == this->linesPerSet){
                    //set is full, replacement needed
                    cache[set_unsignedlonglong].pop_back();
                    cache[set_unsignedlonglong].push_front(tag_unsignedlonglong);
                }
                else{
                    //not full, push into set
                    cache[set_unsignedlonglong].push_front(tag_unsignedlonglong);
                }
            }

        }

        double hitsDouble = (double)this->hits;
        double accessesDouble = (double)this->accesses;

        double hitRatio = ((double)((int)((hitsDouble*100.0)/accessesDouble)))/100.0;
        this->hitRatio = hitRatio;

        cout << "Hits : " << this->hits << endl;
        cout << "Accesses : " << this->accesses << endl;
        cout << "Hit Ratio : " << hitRatio << endl;
        
    }

    void LRURatio(vector<string> addresses){
        //vector of maps, key is tag, value is access counter
        vector< unordered_map<unsigned long long, int>> cache(this->numSets);
        int accessCounter = 0;

        this->name = "LRU " + to_string(this->linesPerSet) + "-WAY SET ASSOCIATIVE";


        for(int i = 0; i < addresses.size(); i++){
            //first convert address to binary
            string s = addresses[i];
            stringstream ss;
            ss << hex << s;
            unsigned x;
            ss >> x;
            bitset<64> b(x);
            string b_string = b.to_string();

            string tag = b_string.substr(0, this->tagSize);
            unsigned long long tag_unsignedlonglong = stoull(tag, nullptr, 2);
            string set = b_string.substr(this->tagSize, this->setWidth);
            unsigned long long set_unsignedlonglong = stoull(set, nullptr, 2);

            //hit?
            int numHitsStart = this->hits;
            
            for(auto iter = cache[set_unsignedlonglong].begin(); iter != cache[set_unsignedlonglong].end(); iter++){
                if(tag_unsignedlonglong == iter->first){
                    this->hits = 1 + this->hits;
                    iter->second = accessCounter;
                    break;
                }
            }
            this->accesses = 1+ this->accesses;
            accessCounter++;
            
            //miss case
            if(numHitsStart == this->hits){

                //is map full?
                if(cache[set_unsignedlonglong].size() == this->linesPerSet){
                    //map full, replacement needed.
                    auto it = cache[set_unsignedlonglong].begin();
                    for(auto iter = cache[set_unsignedlonglong].begin(); iter != cache[set_unsignedlonglong].end(); iter++){
                        if(it->second > iter->second){
                            it = iter;
                        }
                    }

                    cache[set_unsignedlonglong].erase(it);
                    cache[set_unsignedlonglong][tag_unsignedlonglong] = accessCounter;
                }
                else{
                    cache[set_unsignedlonglong][tag_unsignedlonglong] = accessCounter;
                }
            }
            
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