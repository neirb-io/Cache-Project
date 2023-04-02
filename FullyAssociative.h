#ifndef FULLYASSOCIATIVE_H
#define FULLYASSOCIATIVE_H

#include <math.h>
#include <queue>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
struct FullyAssociative{
    int hits = 0;
    int accesses = 0;
    int offsetSize, tagSize, numLines;
    string name;
    double hitRatio;
    
    int cacheSize, bytesPerLine; //measured in bytes
    int addressSize; //bits in address, determined by file

    FullyAssociative(int cacheSize, int bytesPerLine, int addressSize):cacheSize(cacheSize),bytesPerLine(bytesPerLine),addressSize(addressSize)
    {
        numLines = cacheSize / bytesPerLine;
        offsetSize = log2(bytesPerLine);
        tagSize = addressSize - offsetSize;


    }

    void FIFORatio(vector<string> addresses){
        //cache is a tag queue
        this->name = "FIFO FULLY ASSOCIATIVE";
        deque<unsigned long long> cache;

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

            //hit?
            int numHitsStart = this->hits;

            for(auto iter = cache.cbegin(); iter != cache.cend(); iter++){
                if(tag_unsignedlonglong == *iter){
                    this->hits = 1 + this->hits;
                    break;
                }
            }
            this->accesses = 1 + this->accesses;

            //miss case
            if(numHitsStart == this->hits){
                
                //is queue full?
                if(cache.size() == this->numLines){
                    //queue is full, must replace
                    cache.pop_back();
                    cache.push_front(tag_unsignedlonglong);
                }
                else{
                    //not full, simply push front
                    cache.push_front(tag_unsignedlonglong);
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

        //cache is a map with a tag key and access value (least = least recently used)
        unordered_map<unsigned long long, int> cache;
        int access_counter = 0;

        this->name = "LRU FULLY ASSOCIATIVE";


        for(int i = 0; i < addresses.size(); i++){
            //first convert address to binary
            string s = addresses[i];
            stringstream ss;
            ss << hex << s;
            unsigned x;
            ss >> x;
            bitset<64> b(x);
            string b_string = b.to_string();

            //cout << "DEBUG FIFOFA BIT STRING: " << b_string << endl;

            
            string tag = b_string.substr(0, this->tagSize);
            unsigned long long tag_unsignedlonglong = stoull(tag, nullptr, 2);

            //hit?
            int numHitsStart = this->hits;

            for(auto iter = cache.begin(); iter != cache.end(); iter++){
                if(tag_unsignedlonglong == iter->first){
                    this->hits = 1 + this->hits;
                    iter->second = access_counter;
                    break;
                }
            }
            this->accesses = 1 + this->accesses;
            access_counter++;

            //miss case
            if(numHitsStart == this->hits){
                
                //is queue full?
                if(cache.size() == this->numLines){
                    //queue is full, must replace

                    //first remove element with least access time
                    auto it = cache.begin();
                    for(auto iter = cache.begin(); iter != cache.end(); iter++){
                        if(it->second > iter->second){
                            it = iter; 
                        }
                    }

                    cache.erase(it);
                    cache[tag_unsignedlonglong] = access_counter;
                }
                else{
                    //not full, simply push front
                    cache[tag_unsignedlonglong] = access_counter;
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