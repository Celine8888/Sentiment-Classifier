#include "DSString.h"

DSString::DSString()
{
    len = 1;
    data = new char[len]; // a one size array with \0
    data[len - 1] = '\0';
}
DSString::DSString(const char *newString)
{
    len = 0;
    while (newString[len] != '\0')
    {
        len++; // get the length of the pass in string
    }
    len++;
    data = new char[len];
    for (size_t i = 0; i < len; i++)
    {
        data[i] = newString[i]; // copy
    }
    data[len - 1] = '\0';
}
DSString::~DSString()
{
    delete[] data;
}
DSString::DSString(const DSString &oldString)
{
    data = new char[oldString.len];
    len = oldString.length();
    for (size_t i = 0; i < len; i++)
    {
        data[i] = oldString.data[i];
    }
}
DSString &DSString::operator=(const DSString &oldString)
{
    delete[] data;
    len = oldString.length();
    data = new char[len];
    for (size_t i = 0; i < len; i++)
    {
        data[i] = oldString.data[i];
    }

    return *this;
}
size_t DSString::length() const
{
    return len;
}
char &DSString::operator[](size_t i)
{
    if (i >= len)
    {
        cout << "Index out of bound, exiting"; // if take an inappropriate index, exit
        exit(1);
    }
    return *(data + i);
}
std::ostream &operator<<(std::ostream &theStream, const DSString &theString)
{
    cout << theString.data;
    return theStream;
}
std::istream &operator>>(std::istream &in, DSString &c)
{
    in >> c.data;
    return in;
}
DSString DSString::operator+(const DSString &addString) const
{
    // get the length of addString
    size_t addLen = addString.length();
    // create a new array
    size_t tempLen = len + addLen;
    DSString tempString;
    char *tempData = new char[tempLen];
    // copy myString
    size_t counter = 0;
    for (size_t i = 0; i < len - 1; i++)
    {
        tempData[i] = data[i];
        counter++;
    }
    // copy the addString
    for (size_t i = 0; i < addLen; i++)
    {
        tempData[counter] = addString.data[i];
        counter++;
    }
    delete[] tempString.data;
    tempString.data = tempData;
    tempString.len = tempLen;
    tempData = nullptr;
    return tempString;
}
bool DSString::operator==(const DSString &compString) const
{
    if (len == compString.len)
    { // compare each by each only if they have same length
        for (size_t i = 0; i < compString.len; i++)
        {
            if (data[i] != compString.data[i])
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false; // if not same length, not the same string
    }
}
bool DSString::operator<(const DSString &compString) const
{
    for (size_t i = 0; i < min(len, compString.len); i++)
    { // go through whichever shorter so as to not out of bound
        if (data[i] != compString.data[i])
        {                                          // whenever they are not equal
            return (data[i] < compString.data[i]); // lhs small then true, vice versa
        }
    }

    return len < compString.len; // it'll be false
}

DSString DSString::substring(const size_t start, const size_t numChars) const
{
    // create new object
    DSString tempString;
    // len = numChars
    tempString.len = numChars + 1;
    delete[] tempString.data;
    // create new array of size numChars
    tempString.data = new char[tempString.len];
    // counter for tempString data
    size_t counter = 0;
    // copy from  data[start] to data[start+numChars-1]
    for (size_t i = start; i < start + tempString.len - 1; i++)
    {
        tempString.data[counter] = data[i];
        counter++;
    }
    tempString[tempString.len - 1] = '\0';
    // return DSString
    return tempString;
}

DSString DSString::toLower() const
{
    DSString tempString;
    tempString.len = len;
    delete[] tempString.data;
    tempString.data = new char[tempString.len];
    for (size_t i = 0; i < len - 1; i++)
    {
        if (int(data[i]) >= 65 && int(data[i]) <= 90)
        {
            tempString.data[i] = char(int(data[i]) + 32); // only change to lower case if it's alphabet
        }
        else
        {
            tempString.data[i] = data[i]; // if it's anything other than alphabet, keep it
        }
    }
    tempString[len - 1] = '\0';
    return tempString;
}
char *DSString::c_str() const
{
    return data;
}
vector<DSString> DSString::tokenization()
{
    // create vector to store alphabet-nonalphabet transition points
    // the chars between certain sets of transition points would be a word or an alphabet
    vector<size_t> sigCharPos;
    // handle 1st char seperately because all other char we check before and after, but here there's no before
    if (((int(data[0]) >= 65 && int(data[0]) <= 90) || (int(data[0]) >= 97 && int(data[0]) <= 122)) && (int(data[1]) < 65 || (int(data[1]) > 90 && int(data[1]) < 97) || int(data[1]) > 122))
    { // if data[0] is an alphabet and data[1] is non-alphabet
        sigCharPos.push_back(0);
        sigCharPos.push_back(0); // push back index twice because when tolkenizing, the alphabet in between is a word
    }
    else if ((int(data[0]) >= 65 && int(data[0]) <= 90) || (int(data[0]) >= 97 && int(data[0]) <= 122))
    { // if it's just that data[0] is an alphabet, it'll be the start of a word
        sigCharPos.push_back(0);
    }

    for (size_t i = 1; i <= len - 2; i++) // go through the tweet and stop before before \0
    {
        if (((int(data[i]) >= 65 && int(data[i]) <= 90) || (int(data[i]) >= 97 && int(data[i]) <= 122)) && (int(data[i + 1]) < 65 || (int(data[i + 1]) > 90 && int(data[i + 1]) < 97) || int(data[i + 1]) > 122) && (int(data[i - 1]) < 65 || (int(data[i - 1]) > 90 && int(data[i - 1]) < 97) || int(data[i - 1]) > 122))
        { // if it is alphabet, before&after are non-alphabet
            // it is a word of single alphabet log twice to ensure tolkenization
            sigCharPos.push_back(i);
            sigCharPos.push_back(i);
        }
        else if (((int(data[i]) >= 65 && int(data[i]) <= 90) || (int(data[i]) >= 97 && int(data[i]) <= 122)) && ((int(data[i + 1]) < 65 || (int(data[i + 1]) > 90 && int(data[i + 1]) < 97) || int(data[i + 1]) > 122) || (int(data[i - 1]) < 65 || (int(data[i - 1]) > 90 && int(data[i - 1]) < 97) || int(data[i - 1]) > 122)))
        { // if it is an alphabet, before/after non-alphabet, log it as a transition point
            sigCharPos.push_back(i);
        }
    }
    vector<DSString> words;
    for (size_t i = 0; i < sigCharPos.size(); i = i + 2)
    { // if we have 1234 as transition points, then 1-2 is a word, 2-3 is not, 3-4 is a word
        // so we should add 2 to the counter
        DSString newWord;
        size_t char1Pos = sigCharPos[i];
        size_t char2Pos = sigCharPos[i + 1];   // get the two transition points
        newWord.len = char2Pos - char1Pos + 2; // get the length in between
        delete[] newWord.data;
        newWord.data = new char[newWord.len];
        for (size_t t = 0; t < newWord.len - 1; t++)
        {
            newWord.data[t] = data[char1Pos]; // copy the chars in between
            char1Pos++;
        }
        newWord.data[newWord.len - 1] = '\0'; // remember to add a \0 because we intercept a fragment from a sentence with no \0
        words.push_back(newWord);
    }
    return words;
}
