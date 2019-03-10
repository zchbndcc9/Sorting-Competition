#include <iostream>
#include <cstring>
#include <fstream>
#include "DSVector.h"
using namespace std;

static char* readInAll(char *fileName);
void dumpFile(char*, char*);
void mergeSort(DSVector<char*>);

int main() {
    DSVector<char*> buckets[30];

    //Read in file into buffer
    char* buffer = readInAll("test.txt");

    //Parse buffer to extract words
    char* token = strtok(buffer, "\n");
    while(token != NULL) {
        int len = strlen(token);
        buckets[len - 1].push(token);
        token = strtok(NULL, "\n");
    }

    //Merge sort each bucket
    //Dump sorted words to file
    delete buffer;
}

static char* readInAll(char* fileName) {
    ifstream buffer(fileName, ios::binary | ios::ate);
    streamsize length = buffer.tellg();

    char* container = new char[length];
    buffer.seekg(0, ios::beg);
    buffer.read(container, length);

    return container;
}
