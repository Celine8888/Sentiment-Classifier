#ifndef SentimentClassifier_H
#define SentimentClassifier_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>  // C++ version of C's stdio.h
#include <cstdlib> // C++ version of C's stdlib.h
#include <vector>
#include <cstring>
#include "DSString.h"

using namespace std;

class SentimentClassifier
{
private:
    FILE *stream;
    char buffer[1001]; // add extra space for null terminator, etc.
    char *b = buffer;  // we need a pointer to the buffer
    size_t maxlen;
    int nread;
    // training
    vector<int> wordValue;     // wide range of values of the words from word bank(not only 0/4)
    vector<DSString> wordBank; // words appeared in the tweets
    // predict
    vector<long long> ids;    // all the ids from the test set
    vector<int> predictSenti; // my prediction of the sentiments of the tweets(0/4)
    vector<int> groundTruth;  // ground truth of the tweets(0/4)
    // evaluate
    vector<int> wrongIndexes; // the index of the ones I predict wrong
    double wrongNum;          // the number of my wrong predictions
    double accuracy;

    ofstream myFile;

    void getTrainData(const char *);
    void getPredictData(const char *);
    void writePredictResults(char *);

public:
    void train(char *);
    void predict(char *, char *);
    void evaluatePredictions(char *, char *);
};

#endif