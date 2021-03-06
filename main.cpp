#include <iostream>
#include <cstring>
#include <fstream>
#include "DSVector.h"
using namespace std;

void parseBuffer(char*, DSVector<char*>*);
void sortBuckets(DSVector<char*>*);
void writeFile(const char*, DSVector<char*>*);

static char* readInAllFile(const char*);
void dumpFile(char*, char*);
void lsdRadixSort(DSVector<char*> &);

int main() {
    DSVector<char*> buckets[30](200000);

    char* buffer = readInAllFile("1.1million_word_list.txt");

    parseBuffer(buffer, buckets);
    sortBuckets(buckets);
    writeFile("output.txt", buckets);

    delete[] buffer;
}

void parseBuffer(char* buffer, DSVector<char*>* vec) {
    int count = 0,
        numWords = 0,
        numToSort = 0;

    //Parse buffer to extract words
    char* token = strtok(buffer, "\r\n");
    while(token != NULL) {
        if(count == 0) {
            numWords = atoi(token);
        } else if(count == 1) {
            numToSort = atoi(token);
        } else {
            int len = strlen(token);
            if(len < 31 && len > 0){
                vec[len - 1].push(token);
            }
            token = strtok(NULL, "\r\n");
        }
        count++;
    }
}


void sortBuckets(DSVector<char*>* vec) {
    //Perform a radix sort on each bucket
    for(int i = 0; i < 30; i++) {
        if(vec[i].getSize() != 0)
            lsdRadixSort(vec[i]);
    }
}

void writeFile(const char* file, DSVector<char*>* vec) {
    ofstream output(file);
    //Dump sorted words to file
    for(int i = 0; i < 30; i++) {
        int vecSize = vec[i].getSize();
        for(int j = 0; j < vecSize; j++) {
            output << vec[i][j] << '\n';
        }
    }
}

static char* readInAllFile(const char* fileName) {
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
    int vecSize = vec.getSize();
    char** arr = vec.getData();
    char** temp = new char*[vecSize];

    for(int i = len - 1; i >= 0; i--) {
        int counter[256] = {};

        for(int j = 0; j < vecSize; j++) {
            counter[arr[j][i]]++;
        }

        for(int j = 1; j < 256; j++) {
            counter[j]+=counter[j-1];
        }

        for(int j = 0; j < vecSize; j++) {
            temp[counter[arr[j][i] - 1]++] = arr[j];
        }

        // Direct copy over to arr
        memcpy(arr, temp, vecSize*sizeof(int));
    }

    delete[] temp;
}
