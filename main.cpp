#include <iostream>
#include <cstring>
#include <fstream>
#include "DSVector.h"
using namespace std;

static char* readInAll(char *fileName);
void dumpFile(char*, char*);
void lsdRadixSort(DSVector<char*> &);

int main() {
    DSVector<char*> buckets[30];

    //Read in file into buffer
    char* buffer = readInAll("words_clean.txt");

    int count = 0,
        numWords = 0,
        numToSort = 0;

    //Parse buffer to extract words
    char* token = strtok(buffer, "\n");
    while(token != NULL) {
        if(count == 0) {
            numWords = atoi(token);
        } else if(count == 1) {
            numToSort = atoi(token);
        } else {
            int len = strlen(token);
            buckets[len - 1].push(token);
            token = strtok(NULL, "\n");
        }
        count++;
    }

    //Perform a radix sort on each bucket
    for(int i = 0; i < 30; i++) {
        if(buckets[i].getSize() != 0)
            lsdRadixSort(buckets[i]);
    }

    ofstream output("output.txt");
    //Dump sorted words to file
    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < buckets[i].getSize(); j++) {
            output << buckets[i][j] << endl;
        }
    }

    delete [] buffer;
}

static char* readInAll(char* fileName) {
    ifstream buffer(fileName, ios::binary | ios::ate);
    streamsize length = buffer.tellg();

    char* container = new char[length];
    buffer.seekg(0, ios::beg);
    buffer.read(container, length);

    return container;
}

void lsdRadixSort(DSVector<char *>& vec) {
   // Determine max length of string
    int len = strlen(vec[0]);
    char** temp = new char*[vec.getSize()];

    for(int i = len - 1; i >= 0; i--) {
        int counter[256] = {};

        for(int j = 0; j < vec.getSize(); j++) {
            counter[vec[j][i]]++;
        }

        for(int j = 1; j < 256; j++) {
            counter[j]+=counter[j-1];
        }

        for(int j = 0; j < vec.getSize(); j++) {
            temp[counter[vec[j][i] - 1]++] = vec[j];
        }

        for(int j = 0; j < vec.getSize(); j++) {
            vec[j] = temp[j];
        }
    }

    delete[] temp;
}
