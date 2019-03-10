#include "DSString.h"

DSString::DSString(){
    len = 0;
  //One space for null char
    stringStart = new char[1];
  //store null char in string
    stringStart[0] = 0;
}

//Pass pointer to constructor
DSString::DSString(const char* rhs){
    len = ::strlen(rhs);
    stringStart = new char[len+1];
    ::strcpy(stringStart, rhs);
    stringStart[len] = 0;
}

DSString::DSString(const DSString& rhs){
    len = rhs.len;
    stringStart = new char[len+1];
    ::strcpy(this->stringStart, rhs.stringStart);
    stringStart[len] = 0;
}

DSString& DSString::operator= (const char* rhs){
    if(rhs != stringStart){
        len = ::strlen(rhs);
        delete[] stringStart;
        stringStart = new char[len + 1];
        ::strcpy(stringStart, rhs);
        stringStart[len] = 0;
        return *this;
    }
}

DSString& DSString::operator= (const DSString& rhs){
    if(&rhs != this){
        len = rhs.len;
      //Deallocate memory from previous string
        delete[] stringStart;
      //Allocate new memory in the heap
        stringStart = new char[len + 1];
        ::strcpy(this->stringStart, rhs.stringStart);
        stringStart[len] = 0;
        return *this;
    }
}

DSString DSString::operator+ (const DSString& rhs){
    int newLength = len + rhs.len;
    char *newString = new char[newLength + 1];

    for(int i = 0; i < len; i++){
        newString[i] = stringStart[i];
    }
    for( int i = 0; i < rhs.len; i++){
        newString[len + i] = rhs.stringStart[i];
    }

    newString[newLength] = 0;
    DSString appendedString(newString);
    delete[] newString;
    return appendedString;
}


bool DSString::operator== (const char* rhs){
   return strcmp(stringStart, rhs) == 0;
}


bool DSString::operator== (const DSString& rhs) const{
   return strcmp(stringStart, rhs.stringStart) == 0;
}


bool DSString::operator> (const DSString& rhs) const{
   int tmp = strcmp(stringStart, rhs.stringStart);
   return strcmp(stringStart, rhs.stringStart) > 0;
}

char& DSString::operator[] (const int rhs){
    if(len == 0) {
        return *(stringStart);
    } else if(rhs >= 0 && rhs < len){
        return *(stringStart + rhs);
    } else if(rhs < 0 && (-1 * rhs) < len ) {
        return *(stringStart + (len + rhs));
    }
}

int DSString::size(){
    return len;
}
DSString DSString::substring(int indexToStartAt, int numOfChars){
    DSString newSubstring;

    if(indexToStartAt >= 0) {//+
        if(numOfChars > 0) {//+
            char temp[numOfChars + 1];
            for (int i = 0, j = indexToStartAt; i < numOfChars; i++, j++) {
                temp[i] = stringStart[j];
            }
            temp[numOfChars] = 0;
            newSubstring = temp;
            return newSubstring;
        } else {//-
            int endIndex = (this->len + numOfChars) + 1;
            int newNumOfChars = endIndex - indexToStartAt;
            char temp[newNumOfChars + 1];
            for (int i = 0, j = indexToStartAt; i < newNumOfChars; i++, j++) {
                temp[i] = stringStart[j];
            }
            temp[newNumOfChars] = 0;
            newSubstring = temp;
            return newSubstring;
        }
    } else {//-
        if(numOfChars > 0) {//+
            char temp[numOfChars + 1];
            for (int i = 0, j = (this->len + indexToStartAt); i < numOfChars; i++, j++) {
                temp[i] = stringStart[j];
            }
            temp[numOfChars] = 0;
            newSubstring = temp;
            return newSubstring;
        } else {//-
            char temp[((this->len + numOfChars) + indexToStartAt) + 1];
            for (int i = 0, j = (this->len + indexToStartAt) + 1; i < (this->len + numOfChars); i++, j++) {
                temp[i] = stringStart[j];
            }
            temp[numOfChars] = 0;
            newSubstring = temp;
            return newSubstring;
        }
    }
}

char* DSString::c_str(){
    return stringStart;
}


std::ostream& operator<< (std::ostream& stream, const DSString& rhs){
  //Prints up until null char
    for(int i = 0; i < rhs.len; i++) {
        stream << (rhs.stringStart)[i];
    }
    return stream;
}


DSString::~DSString(){
    delete[] stringStart;
}
