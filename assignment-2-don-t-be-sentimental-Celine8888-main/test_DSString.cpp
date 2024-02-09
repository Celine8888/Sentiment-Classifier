#include <iostream>
#include <vector>
#include <algorithm>

#include "DSString.h"
#include "SentimentClassifier.h"

using namespace std;

int main()
{
    DSString myString = "Hello, World!";
    cout << myString << endl;
    vector<DSString> words = myString.tokenization();
    // //my tests
    //   //testing indexing
    //     cout << myString[3];
    //     // myString[100];
    //   //testing copy assign oprt
    //     DSString newString;
    //     newString = myString;
    //     cout << newString;
    //   //testing << oprt
    //     DSString anotherString;
    //     cin >> anotherString;
    //     cout << anotherString;

    // this uses the one argument constructor in DSString and then the inherited operator=
    myString = "Good bye!";
    cout << myString << endl;
    cout << myString[9];

    // mytest
    DSString addString = "I'M BACK!";
    cout << addString.toLower() << '\n';
    DSString togString = myString + addString;
    cout << togString << '\n';
    cout << togString.c_str() << '\n';

    // mytest
    DSString test = myString.substring(5, 3);
    cout << "We are the champion" << test;

    cout << "substr: " << myString.substring(5, 3) << endl;

    DSString a = "test";
    DSString b = a;
    // mytest
    cout << b << '\n';

    cout << boolalpha;
    cout << (a == b) << endl;
    // mytest
    cout << (a < b) << '\n';

    // use initialization list (see DSVector.h)
    vector<DSString> strings = {
        DSString("bbb"),
        DSString("aaa"),
        DSString("ddd"),
        DSString("eee"),
        DSString("ccc")};

    // find strings
    for (const auto &s : strings)
        cout
            << s << "\n";

    cout << "found ddd: " << (find(strings.begin(), strings.end(), DSString("ddd")) != strings.end()) << endl;
    cout << "found zzz: " << (find(strings.begin(), strings.end(), DSString("zzz")) != strings.end()) << endl;

    // sorting
    sort(strings.begin(), strings.end());

    for (const auto &s : strings)
        cout
            << s << "\n";

    // now we can do more efficient search
    cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << endl;
    cout << "found zzz: " << binary_search(strings.begin(), strings.end(), DSString("zzz")) << endl;

    return 0;
}
