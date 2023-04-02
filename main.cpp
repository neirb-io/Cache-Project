#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "DirectMap.h"
#include "SetAssociative.h"
#include "FullyAssociative.h"

using namespace std;

//Load trace file into a vector of addresses, snipping off the unneccessary ends
void LoadTraceFile(string filename, vector<string>& addresses){
    ifstream myFile;
    string fullLine;

    myFile.open(filename);

    while(getline(myFile, fullLine)){
        fullLine = fullLine.substr(4);

        int pos = fullLine.find(' ');
        fullLine = fullLine.substr(0, pos);

        addresses.push_back(fullLine);
    }
    myFile.close();
}


int main(){


    vector<string> addresses;

    LoadTraceFile("gcc.trace", addresses);

    //generate csv file
    ofstream myFile;
    myFile.open("data.csv");

    // "Organization", "Hit Ratio" , "Bytes per Cache" , "Bytes per Line"





    cout << "FIFO FULLY ASSOCIATIVE CACHE, INCREASING CACHE SIZE: " << endl;
    for(int i = 1; i < 8; i++){

        FullyAssociative cache(pow(4,i), 4, 64);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << endl; 
        cache.FIFORatio(addresses);

        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";

        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "FIFO FULLY ASSOCIATIVE CACHE, INCREASING BYTES PER LINE (DECREASING NUMBER OF LINES): " << endl;

    for(int i = 3; i < 9; i++){

        FullyAssociative cache(8192, pow(2,i), 64);
        cout << "BYTES IN CACHE: 8192      BYTES PER LINE: " << pow(2,i) << endl;
        cache.FIFORatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout << endl;
    }

    cout << "LRU FULLY ASSOCIATIVE CACHE, INCREASING CACHE SIZE: " << endl;
    for(int i = 1; i < 8; i++){

        FullyAssociative cache(pow(4,i), 4, 64);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << endl;
        cache.LRURatio(addresses);

        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "LRU FULLY ASSOCIATIVE CACHE, INCREASING BYTES PER LINE (DECREASING NUMBER OF LINES): " << endl;

    for(int i = 3; i < 9; i++){

        FullyAssociative cache(8192, pow(2,i), 64);
        cout << "BYTES IN CACHE: 8192      BYTES PER LINE: " << pow(2,i) << endl;
        cache.LRURatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "DIRECT MAP CACHE, INCREASING CACHE SIZE: " << endl;

    for(int i = 2; i<8; i++){

        DirectMap cache(pow(4,i), 4, 64);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << endl;
        cache.HitRatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "DIRECT MAP CACHE, INCREASING BYTES PER LINE (DECREASING NUMBER OF LINES): " << endl;

    for(int i = 3; i<9; i++){
        DirectMap cache(8192, pow(2,i), 64);
        cout << "BYTES IN CACHE: 8192      BYTES PER LINE: " << pow(2,i) << endl;
        cache.HitRatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "FIFO 2-WAY ASSOCIATIVE CACHE, INCREASING CACHE SIZE: " << endl;
    for(int i = 2; i < 8; i++){
        SetAssociative cache(pow(4,i), 4, 64, 2);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << "     NUMBER OF SETS: " << (pow(4,i)/4)/2 << endl; 
        cache.FIFORatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }


    cout << endl;
    cout << endl;
    cout << "FIFO 4-WAY ASSOCIATIVE CACHE, INCREASING CACHE SIZE: " << endl;
    for(int i = 3; i < 8; i++){
        SetAssociative cache(pow(4,i), 4, 64, 4);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << "     NUMBER OF SETS: " << (pow(4,i)/4)/4 << endl; 
        cache.FIFORatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }

    cout << endl;
    cout << endl;
    cout << "FIFO 8-WAY ASSOCIATIVE CACHE, INCREASING CACHE SIZE: " << endl;
    for(int i = 3; i < 8; i++){
        SetAssociative cache(pow(4,i), 4, 64, 8);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << "     NUMBER OF SETS: " << (pow(4,i)/4)/8 <<endl; 
        cache.FIFORatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }



    cout << endl;
    cout << endl;
    cout << "FIFO 2-WAY ASSOCIATIVE CACHE, INCREASING BYTES PER LINE (DECREASING TOTAL LINES, INCREASING BYTES PER SET): " << endl;
    for(int i = 3; i < 9; i++){
        SetAssociative cache(8192, pow(2,i), 64, 2);
        cout << "BYTES IN CACHE: " << 8192 << "     BYTES PER LINE: " << pow(4,i) << "     NUMBER OF SETS: " << (8192/(pow(2,i)))/2 << endl; 
        cache.FIFORatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }

    cout << endl;
    cout << endl;
    cout << "FIFO 4-WAY ASSOCIATIVE CACHE, INCREASING BYTES PER LINE (DECREASING TOTAL LINES, INCREASING BYTES PER SET): " << endl;
    for(int i = 3; i < 9; i++){
        SetAssociative cache(8192, pow(2,i), 64, 4);
        cout << "BYTES IN CACHE: " << 8192 << "     BYTES PER LINE: " << pow(4,i) << "     NUMBER OF SETS: " << (8192/(pow(2,i)))/4 << endl; 
        cache.FIFORatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }

    cout << endl;
    cout << endl;
    cout << "FIFO 8-WAY ASSOCIATIVE CACHE, INCREASING BYTES PER LINE (DECREASING TOTAL LINES, INCREASING BYTES PER SET): " << endl;
    for(int i = 3; i < 9; i++){
        SetAssociative cache(8192, pow(2,i), 64, 8);
        cout << "BYTES IN CACHE: " << 8192 << "     BYTES PER LINE: " << pow(4,i) << "     NUMBER OF SETS: " << (8192/(pow(2,i)))/8 << endl; 
        cache.FIFORatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }






    cout << endl;
    cout << endl;
    cout << "LRU 2-WAY ASSOCIATIVE CACHE, INCREASING CACHE SIZE: " << endl;
    for(int i = 3; i < 8; i++){
        SetAssociative cache(pow(4,i), 4, 64, 2);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << "     NUMBER OF SETS: " << (pow(4,i)/4)/2 <<endl; 
        cache.LRURatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }
    
    cout << endl;
    cout << endl;
    cout << "LRU 4-WAY ASSOCIATIVE CACHE, INCREASING CACHE SIZE: " << endl;
    for(int i = 3; i < 8; i++){
        SetAssociative cache(pow(4,i), 4, 64, 4);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << "     NUMBER OF SETS: " << (pow(4,i)/4)/4 <<endl; 
        cache.LRURatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }


    cout << endl;
    cout << endl;
    cout << "LRU 8-WAY ASSOCIATIVE CACHE, INCREASING CACHE SIZE: " << endl;
    for(int i = 3; i < 8; i++){
        SetAssociative cache(pow(4,i), 4, 64, 8);
        cout << "BYTES IN CACHE: " << pow(4,i) << "     BYTES PER LINE: 4" << "     NUMBER OF SETS: " << (pow(4,i)/4)/8 <<endl; 
        cache.LRURatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }







    cout << endl;
    cout << endl;
    cout << "LRU 2-WAY ASSOCIATIVE CACHE, INCREASING BYTES PER LINE (DECREASING TOTAL LINES, INCREASING BYTES PER SET): " << endl;
    for(int i = 3; i < 9; i++){
        SetAssociative cache(8192, pow(2,i), 64, 2);
        cout << "BYTES IN CACHE: " << 8192 << "     BYTES PER LINE: " << pow(4,i) << "     NUMBER OF SETS: " << (8192/(pow(2,i)))/2 << endl; 
        cache.LRURatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }


    cout << endl;
    cout << endl;
    cout << "LRU 4-WAY ASSOCIATIVE CACHE, INCREASING BYTES PER LINE (DECREASING TOTAL LINES, INCREASING BYTES PER SET): " << endl;
    for(int i = 3; i < 9; i++){
        SetAssociative cache(8192, pow(2,i), 64, 4);
        cout << "BYTES IN CACHE: " << 8192 << "     BYTES PER LINE: " << pow(4,i) << "     NUMBER OF SETS: " << (8192/(pow(2,i)))/4 << endl; 
        cache.LRURatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }


    cout << endl;
    cout << endl;
    cout << "LRU 8-WAY ASSOCIATIVE CACHE, INCREASING BYTES PER LINE (DECREASING TOTAL LINES, INCREASING BYTES PER SET): " << endl;
    for(int i = 3; i < 9; i++){
        SetAssociative cache(8192, pow(2,i), 64, 8);
        cout << "BYTES IN CACHE: " << 8192 << "     BYTES PER LINE: " << pow(4,i) << "     NUMBER OF SETS: " << (8192/(pow(2,i)))/8 << endl; 
        cache.LRURatio(addresses);
        myFile << cache.name << "," << cache.hitRatio << "," << cache.cacheSize << "," << cache.bytesPerLine << "\n";
        cout<<endl;
    }



    myFile.close();


}