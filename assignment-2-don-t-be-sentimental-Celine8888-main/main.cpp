#include <iostream>
#include "SentimentClassifier.h"

#include <chrono>
using namespace std::chrono;

using namespace std;

int main(int argc, char **argv)
{
    SentimentClassifier myClassifier;

    cout << argc;

    myClassifier.train(argv[1]);

    myClassifier.predict(argv[2], argv[4]);

    myClassifier.evaluatePredictions(argv[3], argv[5]);

    return 0;
}