*/
    Name: Elliott Baker
    ID: ecb0105@auburn.edu
    File name: project4_Baker_ecb0105.cpp
    Compile using g++ -std=c++11 on Auburn server
    Sources: Dr. Li lecture's, Project_4 hints, Cpp documentation website
*/

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

/* Defines the TriviaNode data type */
struct TriviaNode

    string question;
    string answer;
    int points;
    TriviaNode *next;
};

/* Makes a pointer for TriviaNode */
typedef TriviaNode *ptrNode;

/* Initializes three default trivia questions */
void setDefault(ptrNode &);
void setDefaultTest(ptrNode &);

/* Prompts user for new trivia question, answer, point value and adds to linked structure */
void addNode(ptrNode &);
void addNodeTest(ptrNode &);

/* Starts the trivia game. Asks question*/
int askQuestion(ptrNode &, int);

/* Debugging version of the program
    Note: change comment on line 42 to enable product version
*/
void unitTest();

#define UNIT_TESTING
//#define triviaQuiz

// Total length of the linked structure
int length = 0;
// Total points scored by user
int totalPoints = 0;

// Prompts user for new question until quits
// Asks all questions or runs test driver
int main()
{
    ptrNode nodeList = new TriviaNode;
#ifdef triviaQuiz
    cout << "*** Welcome to Elliott's trivia quiz game ***\n";
    setDefault(nodeList);
    setDefaultTest(nodeList);
    string yesNo;
    do
    {
        addNode(nodeList);
        cout << "Continue? (Yes/No) ";
        getline(cin, yesNo);
        if (yesNo.compare("Yes") == 0 || yesNo.compare("yes") == 0)
        {
            continue;
        }
        else if (yesNo.compare("No") == 0 || yesNo.compare("no") == 0)
        {
            break;
        }
        else
        {
            cout << "*Invalid Response*\n";
            cout << "Assuming no.....\n\n";
            break;
        }
    } while (1 == 1);

    ptrNode node = nodeList;
    askQuestion(node, length);
    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
    return 0;
#endif

#ifdef UNIT_TESTING
    unitTest();
    return 0;
#endif
}

void setDefault(ptrNode &qList)
{
    ptrNode curPtr = new TriviaNode;
    ptrNode head = new TriviaNode;
    curPtr->question = "How long was the shortest war on record? (Hint: how many minutes)";
    curPtr->answer = "38";
    curPtr->points = 100;
    curPtr->next = new TriviaNode;

    head = curPtr;
    qList = curPtr;
    curPtr = head->next;

    curPtr->question = "What was the Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    curPtr->answer = "Bank of Italy";
    curPtr->points = 50;
    curPtr->next = new TriviaNode;

    head = curPtr;
    curPtr = head->next;

    curPtr->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
    curPtr->answer = "Wii Sports";
    curPtr->points = 20;
    length += 3;
}

void setDefaultTest(ptrNode &qList)
{
    ptrNode node = qList;
    assert(node->question.compare("How long was the shortest war on record? (Hint: how many minutes)") == 0);
    assert(node->answer.compare("38") == 0);
    assert(node->points == 100);
    node = node->next;

    assert(node->question.compare("What was the Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)") == 0);
    assert(node->answer.compare("Bank of Italy") == 0);
    assert(node->points == 50);
    node = node->next;

    assert(node->question.compare("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)") == 0);
    assert(node->answer.compare("Wii Sports") == 0);
    assert(node->points == 20);
}

void addNode(ptrNode &qList)
{
    ptrNode newNode = new TriviaNode;
    string pts;
    int myPoints;

    cout << "Enter a question: ";
    getline(cin, newNode->question);
    cout << "Enter an answer: ";
    getline(cin, newNode->answer);
    cout << "Enter award points: ";
    getline(cin, pts);
    myPoints = stoi(pts);
    newNode->points = myPoints;

    newNode->next = qList;
    qList = newNode;
    length++;
    addNodeTest(qList);
}

void addNodeTest(ptrNode &qList)
{
    assert(qList->question.compare("") != 0);
    assert(qList->answer.compare("") != 0);
    assert(qList->points >= 0);
}

int askQuestion(ptrNode &qList, int numAsk)
{
    string userAnswer;

    if (qList == NULL)
    {
        return 0;
    }
    else if (numAsk < 1)
    {
        cout << "Warning - the number of trivia to be asked must be equal to or be larger than 1";
        return 0;
    }
    else if (length < numAsk)
    {
        cout << "Warning - There are only " << length << " trivia in the list.";
        return 0;
    }
    else
    {
        for (int x = 0; x < numAsk; x++)
        {
            cout << "\nQuestion: " << qList->question << "\n";
            cout << "Answer: ";
            getline(cin, userAnswer);
            if (userAnswer.compare(qList->answer) == 0)
            {
                totalPoints += qList->points;
                cout << "Your answer is correct. You receive " << qList->points << " points.\n";
                cout << "Your total points: " << totalPoints << "\n";
            }
            else
            {
                cout << "Your answer is wrong. The correct answer is: " << qList->answer << "\n";
                cout << "Your total points: " << totalPoints << "\n";
            }
            qList = qList->next;
        }
    }
    return 1;
}

void unitTest()
{
    ptrNode node = new TriviaNode;
    ptrNode reset = new TriviaNode;
    setDefault(node);
    reset = node;
    cout << "*** This is a debugging version ***\n";
    cout << "Unit 1 Test Case 1: Ask no question. The program should give a warning message." << endl;
    askQuestion(node, 0);
    cout << "\nCase 1 Passed\n\n";

    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
    askQuestion(node, 1);
    cout << "\nCase 2.1 Passed\n\n";
    node = reset;
    totalPoints = 0;

    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
    askQuestion(node, 1);
    cout << "\nCase 2.2 Passed\n\n";
    node = reset;
    totalPoints = 0;

    cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
    askQuestion(node, 3);
    cout << "\nCase 3 Passed\n\n";
    node = reset;

    cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
    askQuestion(node, 5);
        cout << "\nCase 4 Passed\n\n";
        cout << "*** End of Debugging Version ***\n";
}
