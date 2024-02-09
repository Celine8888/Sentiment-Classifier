# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name:Celine Zhang

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## UML Diagram

Add your UML class diagram here.

Replace the following image with your diagram. You can draw it by hand and take a photo.
![UML Class Diagram](UML_class.png)

## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

    > Training: I find all the words in all the tweets and add them to a vector. In another vector, I store all their values. If the word appears in a positive tweet, I +1 to its value, if in a negative tweet, I -1 to its value. I end up with a vector of words, and another vector with their corresponding values of positive/negative numbers or 0s.
    
    Testing: I take in a tweet and break it into words. I check all its words' values. If it has a word with positive value, I +1 to the value of the tweet, vice versa. If the tweet ends up with a total value that is a positive number, then it has a sentiment value of 4. If the value is a negative number, the sentiment value would be 0.  

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > 15453984 microseconds O(N^3) I need to go through each tweet(N), go through each word in the tweet(N), and go through each word in the word bank(N) to see if the word is added to the bank and then modify its value. I read the file line by line and used linear search loop in loop.

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > 12285413 microseconds O(N^3) I need to go through each tweet(N), go through each word in the tweet(N), and go through each word in the word bank(N) to see if the words' values and modify the tweet value and finally get the sentiment value. I read the file line by line and used linear search loop in loop.

4. How do you know that you use proper memory management? I.e., how do you know that you do not have
   a memory leak?

   > I used valgrind on a small data set. Although the set is small, it still tests all the memory allocation, so I know if a small set has no leak, neither will a big set.

5. What was the most challenging part of the assignment?

   > Correcting the impression that the knowledge and skills we learned in class are for made-up assignments and not for real-life and useful tools