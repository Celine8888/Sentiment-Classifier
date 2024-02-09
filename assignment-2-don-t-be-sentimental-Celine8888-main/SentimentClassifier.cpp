#include "SentimentClassifier.h"

void SentimentClassifier::train(char *trainFile)
{
        maxlen = 1000;
        stream = fopen(trainFile, "r");
        if (stream == NULL)
        {
                std::cerr << "Opening the file failed!" << std::endl;
        }
        // get rid of the first line containing titles
        getline(&b, &maxlen, stream);
        // keep reading till end of file
        while ((nread = getline(&b, &maxlen, stream)) != -1)
        {
                getTrainData(buffer);
                std::cout << std::endl;
        }
        fclose(stream);
}

void SentimentClassifier::getTrainData(const char *buffer)
{
        // get tweet sentiment value as char
        char charSenti = *buffer;
        // translate the value into int
        int senti = int(charSenti) - 48;
        // get the rest of the information in the same line
        DSString wholeText = buffer;
        // break it into a temporary word pile to be sorted and added to the word bank
        // this vector can be destroyed after logging each line of tweet to save memory so I initialize it here
        vector<DSString> brokenText = wholeText.tokenization();
        // when adding the first word to word bank
        if (wordBank.empty() == true)
        {
                // push whatever the first word, first 5 words are not part of the tweet but other info, so start with index 5
                wordBank.push_back(brokenText[5]);
                // decide and push the word value
                if (senti == 4)
                {
                        wordValue.push_back(1);
                }
                else
                {
                        wordValue.push_back(-1);
                }
                // initialize the signal to use later as indication if the new words is found in the word bank
                int foundSignal = 0;
                // continue to decide the rest of the first tweet
                for (size_t i = 6; i < brokenText.size(); i++)
                {
                        // compare each word bank word with the new word
                        for (size_t j = 0; j < wordBank.size(); j++)
                        {
                                // if it's in the bank already, just modify the value
                                if (wordBank[j] == brokenText[i])
                                {
                                        if (senti == 4)
                                        {
                                                wordValue[j]++;
                                        }
                                        else
                                        {
                                                wordValue[j]--;
                                        }
                                        // change the sigal to the word being found so not to enter the not found path
                                        foundSignal = 1;
                                }
                        }
                        // if the word is not found in the bank, we need to add it and the value
                        if (foundSignal == 0)
                        {
                                wordBank.push_back(brokenText[i]);
                                if (senti == 4)
                                {
                                        wordValue.push_back(1);
                                }
                                else
                                {
                                        wordValue.push_back(-1);
                                }
                        }
                }
        }
        // if it is not the first word of the bank
        else
        {
                int foundSignal = 0;
                // compare with bank starting from the first valid word in the tweet
                for (size_t i = 5; i < brokenText.size(); i++)
                {
                        for (size_t j = 0; j < wordBank.size(); j++)
                        {
                                if (wordBank[j] == brokenText[i])
                                {
                                        if (senti == 4)
                                        {
                                                wordValue[j]++;
                                        }
                                        else
                                        {
                                                wordValue[j]--;
                                        }
                                        foundSignal = 1;
                                }
                        }
                        if (foundSignal == 0)
                        {
                                DSString newWord = brokenText[i];
                                wordBank.push_back(newWord);
                                if (senti == 4)
                                {
                                        wordValue.push_back(1);
                                }
                                else
                                {
                                        wordValue.push_back(-1);
                                }
                        }
                }
        }
}

void SentimentClassifier::predict(char *predictFile, char *resultFile)
{
        maxlen = 1000;
        stream = fopen(predictFile, "r");
        if (stream == NULL)
        {
                std::cerr << "Opening the file failed!" << std::endl;
        }
        // get rid of the title line
        getline(&b, &maxlen, stream);
        while ((nread = getline(&b, &maxlen, stream)) != -1)
        {
                getPredictData(buffer);
                std::cout << std::endl;
        }
        writePredictResults(resultFile);
        fclose(stream);
}
void SentimentClassifier::writePredictResults(char *resultFile)
{
        myFile.open(resultFile);
        for (size_t i = 0; i < predictSenti.size(); i++)
        {
                myFile << predictSenti[i] << ", "
                       << ids[i] << "\n";
        }
        myFile.close();
}

void SentimentClassifier::getPredictData(const char *buffer)
{
        // get id from chars to a string
        string stringId = "";
        for (size_t i = 0; i <= 9; i++)
        {
                stringId += buffer[i];
        }
        // translate id from string to long long
        long long id = stoll(stringId);
        ids.push_back(id);
        // get text
        DSString wholeText = buffer;
        // break text into words
        vector<DSString> brokenText = wholeText.tokenization();
        int textValue = 0;
        // go through the words
        for (size_t i = 6; i < brokenText.size(); i++)
        {
                // compare the word to each word in the wordBank
                for (size_t j = 0; j < wordBank.size(); j++)
                {
                        // if found
                        if (wordBank[j] == brokenText[i])
                        {
                                // if the word is positive add 1 to the tweet value vice versa
                                if (wordValue[j] > 0)
                                {
                                        textValue++;
                                }
                                else
                                {
                                        textValue--;
                                }
                        }
                }
        }
        // decide the tweet sentiment from its value
        if (textValue >= 0)
        {
                predictSenti.push_back(4);
        }
        else
        {
                predictSenti.push_back(0);
        }
}

void SentimentClassifier::evaluatePredictions(char *groundTruthFile, char *evaluationFile)
{
        maxlen = 1000;
        stream = fopen(groundTruthFile, "r");
        if (stream == NULL)
        {
                std::cerr << "Opening the file failed!" << std::endl;
        }
        // get rid of the title line
        getline(&b, &maxlen, stream);
        int counter = 0;
        // keep reading till the end
        while ((nread = getline(&b, &maxlen, stream)) != -1)
        {
                // get the sentiment value as a char
                char charSenti = *buffer;
                // translate the value into an int
                int senti = int(charSenti) - 48;
                // if the ground truth is not the same as my prediction
                if (senti != predictSenti[counter])
                {
                        // document how many I got wrong and the wrong index, and store the ground truth
                        wrongNum++;
                        wrongIndexes.push_back(counter);
                        groundTruth.push_back(senti);
                }
                // make sure I am comparing the ground truth with the corresponding prediction
                counter++;
        }
        fclose(stream);
        myFile.open(evaluationFile);
        // calculate accuracy
        accuracy = (1 - wrongNum / static_cast<int>(predictSenti.size()));
        myFile << fixed;
        myFile << setprecision(3);
        myFile << accuracy << "\n";
        for (size_t i = 0; i < wrongIndexes.size(); i++)
        {
                myFile << predictSenti[wrongIndexes[i]] << ", "
                       << groundTruth[i] << ", "
                       << ids[wrongIndexes[i]] << "\n";
        }
        myFile.close();
}