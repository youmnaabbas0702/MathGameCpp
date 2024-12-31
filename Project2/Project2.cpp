#include <iostream>
using namespace std;

enum enQuizLevel{ Easy = 1, Mid, Hard, Mix};
enum enOpType{ Add = 1, Sub, Mul, Div, MixOp};

struct stQuestion
{
    int operand1;
    int operand2;
    char operation;
    int UserAnswer;
    int answer;
};

struct stGameInfo
{
    int NumberOfQuestions;
    enQuizLevel Level;
    enOpType OperationType;
    int CorrectAnswers = 0;
};

int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

int ReadNumberOfQuestions()
{
    int N = 0;
    do
    {
        cout << "How many questions do you want?: ";
        cin >> N;

    } while (N <= 0);

    return N;
}

enQuizLevel ReadQuizLevel()
{
    int choice = 0;

    do
    {
        cout << "Choose questions level: [1]Easy. [2]Mid. [3]Hard. [4]Mix. : ";
        cin >> choice;

    } while (choice < 1 || choice > 4);

    return (enQuizLevel)choice;
}

enOpType ReadOperationType()
{
    int choice = 0;

    do
    {
        cout << "Choose operation type: [1]Addition. [2]Subtraction. [3]Multiplication. [4]Division. [5]Mix. : ";
        cin >> choice;

    } while (choice < 1 || choice > 5);

    return (enOpType)choice;
}

int GenerateRandomOperand(enQuizLevel level)
{
    switch (level)
    {
    case Easy:
        return RandomNumber(1, 10);
    case Mid:
        return RandomNumber(10, 50);
    case Hard:
        return RandomNumber(50, 100);
    }
}

void GenerateOperands(enQuizLevel level, int& operand1, int& operand2)
{
    switch (level)
    {
    case Easy:
    case Mid:
    case Hard:
        operand1 = GenerateRandomOperand(level);
        operand2 = GenerateRandomOperand(level);
        break;
    case Mix:
        operand1 = GenerateRandomOperand(enQuizLevel(RandomNumber(1, 3)));
        operand2 = GenerateRandomOperand(enQuizLevel(RandomNumber(1, 3)));
        break;
    }
}

char GetOperationSymbol(enOpType optype)
{
    switch (optype)
    {
    case Add:
        return '+';
    case Sub:
        return '-';
    case Mul:
        return '*';
    case Div:
        return '/';
    }
}

void GenerateOperation(enOpType optype, char &operation)
{
    switch (optype)
    {
    case Add:
    case Sub:
    case Mul:
    case Div:
        operation = GetOperationSymbol(optype);
        break;
    case MixOp:
        operation = GetOperationSymbol(enOpType(RandomNumber(1,4)));
        break;
    }
}

int ComputeAnswer(int operand1, int operand2, char operation)
{
    switch (operation)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    }
}

stQuestion GenerateQuestion(enQuizLevel level, enOpType optype)
{
    stQuestion Question;

    GenerateOperation(optype, Question.operation);

    GenerateOperands(level, Question.operand1, Question.operand2);

    Question.answer = ComputeAnswer(Question.operand1, Question.operand2, Question.operation);

    return Question;
}

void PrintQuestion(stQuestion &Question)
{
    cout << Question.operand1 << endl;
    cout << Question.operand2 << " " << Question.operation << endl;
    cout << "-------------" << endl;
    cin >> Question.UserAnswer;
}

bool CheckPass(int UserAnswer, int Answer)
{
    return UserAnswer == Answer;
}

void StartRound(enQuizLevel level, enOpType optype, int& PassCounter)
{
    stQuestion Question;

    Question = GenerateQuestion(level, optype);

    PrintQuestion(Question);

    if (CheckPass(Question.UserAnswer, Question.answer))
    {
        system("Color 2F");
        cout << "Correct answer ;)" << endl;
        PassCounter++;
    }
    else
    {
        system("Color 4F");
        cout << "\aWrong answer :(" << endl;
        cout << "Correct answer is: " << Question.answer << endl;
    }
}

string LevelName(enQuizLevel level)
{
    switch (level)
    {
    case Easy:
        return "Easy";
    case Mid:
        return "Middle";
    case Hard:
        return "Hard";
    case Mix:
        return "Mix";
    }
}

string OperationName(enOpType optype)
{
    switch (optype)
    {
    case Add:
        return "Addition";
    case Sub:
        return "Subtraction";
    case Mul:
        return "Multiplication";
    case Div:
        return "Division";
    case MixOp:
        return "Mix";
    }
}

void PrintFinalResult(stGameInfo GameInfo)
{
    cout << "\n-----------------------------------------------------\n";
    if (GameInfo.CorrectAnswers > GameInfo.NumberOfQuestions / 2)
    {
        system("Color 2F");
        cout << "\t\t\t\tP A S S :) \n";
    }
    else
    {
        system("Color 4F");
        cout << "\a\t\t\t\tF A I L :( \n";
    }
    cout << "\n-----------------------------------------------------\n";
    cout << "Number of Questions: " << GameInfo.NumberOfQuestions << endl;
    cout << "Game level: " << LevelName(GameInfo.Level) << endl;
    cout << "Operation type: " << OperationName(GameInfo.OperationType) << endl;
    cout << "Number of correct answers: " << GameInfo.CorrectAnswers << endl;
    cout << "Number of wrong answers: " << GameInfo.NumberOfQuestions - GameInfo.CorrectAnswers << endl;
    cout << "\n-----------------------------------------------------\n";
}

void StartQuiz()
{
    char PlayAgain = 'Y';

    do
    {
        stGameInfo GameInfo;

        GameInfo.NumberOfQuestions = ReadNumberOfQuestions();
        GameInfo.Level = ReadQuizLevel();
        GameInfo.OperationType = ReadOperationType();


        for (int i = 1; i <= GameInfo.NumberOfQuestions; i++)
        {
            cout << "Question [" << i << " / " << GameInfo.NumberOfQuestions << "] : " << endl;
            StartRound(GameInfo.Level, GameInfo.OperationType, GameInfo.CorrectAnswers);
        }

        PrintFinalResult(GameInfo);

        cout << "do you want to play again? Y/N :";
        cin >> PlayAgain;
        
        if (PlayAgain == 'Y' || PlayAgain == 'y')
        {
            system("cls");
            system("Color 0F");
        }
            

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartQuiz();
}