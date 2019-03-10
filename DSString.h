#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <cstring>

class DSString {

    public:

        DSString();
        DSString(const char*);
        DSString(const DSString&); //Copy constructor

        DSString& operator= (const char*);
        DSString& operator= (const DSString&);
        DSString operator+ (const DSString&);
        bool operator== (const char*);
        bool operator== (const DSString&) const;
        bool operator> (const DSString&) const;
        char& operator[] (const int);

        int size();
        DSString substring(int, int);
        bool stringCompareAlpabetical(const DSString&) const;
        char* c_str();

        friend std::ostream& operator<< (std::ostream&, const DSString&);

        ~DSString();

    private:

        int len;
        char* stringStart;
};

#endif // DSSTRING_H
