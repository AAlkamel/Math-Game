#include <iostream>
#include <string>
using namespace std;

enum enOperatersTypes
{
  Addition = 1,
  Subtraction = 2,
  Multiplication = 3,
  Division = 4,
  OpMix = 5
};

enum enDifficultyDegrees
{
  Easy = 1,
  Medium = 2,
  Hard = 3,
  Mix = 4
};

struct stMathQuestion
{
  int FirstNumber = 0;
  int SecondNumber = 0;
  enOperatersTypes Operator;
  enDifficultyDegrees DifficultyDegree;
  int CorrectAnswer;
  int PlayerAnswer;
  bool QuestionResult = false;
};

struct stMathQuiz
{
  stMathQuestion QuestionList[100];
  short NumberOfQuestions = 0;
  short NumberOfCorrectAnswer = 0;
  short NumberOfWrongAnswer = 0;
  enOperatersTypes Operator;
  enDifficultyDegrees DifficultyDegree;
  bool IsSuccess = false;
};

int ReadNumberBetween2Numbers(int from, int to, string message)
{
  int num = 0;
  do
  {
    cout << message << "\n"
         << "enter number between [ " << from << " : " << to << " ]\n";
    cin >> num;
  } while (num < from || num > to);
  return num;
}

char doYouPlayAgain()
{
  char again;
  cout << "\nIf you want to play again [y:n]?\n";
  cin >> again;
  return again;
}

int RandomNumber(int From, int To)
{
  int randNum = rand() % (To - From + 1) + From;
  return randNum;
}

void SetWinScreenColor()
{
  // switch (Winner)
  // {
  // case eGameWinner::Player:
  //   system("color 2F"); // turn screen to Green
  //   break;
  // case eGameWinner::Computer:
  //   system("color 4F"); // turn screen to Red
  //   cout << "\a";
  //   break;
  // default:
  //   system("color 6F");
  //   // turn screen to Yellow
  //   break;
  // }
}

void ResetScreen()
{
  system("cls");
  system("color 0F");
}
enDifficultyDegrees ReadDifficultyDegree()
{
  return (enDifficultyDegrees)ReadNumberBetween2Numbers(1, 4, "pleas enter Degree of game difficulty \nEasy:[1] Medium:[2] Hard[3] Mix[4]");
}
enOperatersTypes ReadOperatorType()
{
  return (enOperatersTypes)ReadNumberBetween2Numbers(1, 5, "pleas select Operation type \nAddition:[1] Subtraction:[2] Multiplication:[3] Division:[4] Mix:[5]");
}

int SimpleCalculator(int firstNum, int secondNum, enOperatersTypes Operater)
{
  switch (Operater)
  {
  case enOperatersTypes::Addition:
    return firstNum + secondNum;
    break;
  case enOperatersTypes::Subtraction:
    return firstNum - secondNum;
    break;
  case enOperatersTypes::Multiplication:
    return firstNum * secondNum;
    break;
  case enOperatersTypes::Division:
    return firstNum / secondNum;
    break;
  default:
    return firstNum + secondNum;
    break;
  }
}

stMathQuestion GenerateQuestion(enDifficultyDegrees DifficultyDegree, enOperatersTypes Operator)
{
  stMathQuestion Question;
  if (DifficultyDegree == enDifficultyDegrees::Mix)
  {
    DifficultyDegree = (enDifficultyDegrees)RandomNumber(1, 3);
  }
  if (Operator == enOperatersTypes::OpMix)
  {
    Operator = (enOperatersTypes)RandomNumber(1, 4);
  }

  Question.Operator = Operator;
  Question.DifficultyDegree = DifficultyDegree;

  switch (DifficultyDegree)
  {
  case enDifficultyDegrees::Easy:
    Question.FirstNumber = RandomNumber(1, 10);
    Question.SecondNumber = RandomNumber(1, 10);
    Question.CorrectAnswer = SimpleCalculator(Question.FirstNumber, Question.SecondNumber, Question.Operator);
    return Question;
    break;
  case enDifficultyDegrees::Medium:
    Question.FirstNumber = RandomNumber(10, 50);
    Question.SecondNumber = RandomNumber(10, 50);
    Question.CorrectAnswer = SimpleCalculator(Question.FirstNumber, Question.SecondNumber, Question.Operator);
    return Question;
    break;
  case enDifficultyDegrees::Hard:
    Question.FirstNumber = RandomNumber(50, 100);
    Question.SecondNumber = RandomNumber(50, 100);
    Question.CorrectAnswer = SimpleCalculator(Question.FirstNumber, Question.SecondNumber, Question.Operator);
    return Question;
    break;
  }
  return Question;
}

void GenerateQuizQuestions(stMathQuiz &Quiz)
{
  for (short i = 0; i < Quiz.NumberOfQuestions; i++)
  {
    Quiz.QuestionList[i] = GenerateQuestion(Quiz.DifficultyDegree, Quiz.Operator);
  }
}

int ReadPlayerAnswer()
{
  int Answer = 0;
  cin >> Answer;
  return Answer;
}

string GetOperationSymbol(enOperatersTypes Operator)
{
  string Operators[5] = {"+", "-", "*", "/", "Mix"};
  return Operators[Operator - 1];
}
string GetDifficultyDegreeText(enDifficultyDegrees DifficultyDegree)
{
  string Operators[4] = {"Easy", "Medium", "Hard", "Mix"};
  return Operators[DifficultyDegree - 1];
}

void PrintQuestion(stMathQuestion Question, short QuestionIndex, short NumberOfQuestions)
{
  cout << "\n";
  cout << "Question [" << QuestionIndex + 1 << "/" << NumberOfQuestions << "] \n\n";
  cout << Question.FirstNumber << endl;
  cout << Question.SecondNumber << " ";
  cout << GetOperationSymbol(Question.Operator);
  cout << "\n_________" << endl;
}

void SetScreenColor(bool Right)
{
  if (Right)
    system("color 2F"); // turn screen to Green
  else
  {
    system("color 4F"); // turn screen to Red
    cout << "\a";
  }
}

void ShowQuestionResult(bool result, int CorrectAnswer)
{
  if (!result)
  {
    cout << "Wrong Answer :-( \n";
    cout << "The right answer is: ";
    cout << CorrectAnswer;
    cout << "\n";
  }
  else
  {
    cout << "Right Answer :-) \n";
  }
  cout << endl;
  SetScreenColor(result);
}

void AskAndCorrectQuizQuestionsAnswers(stMathQuiz &Quiz)
{
  for (short i = 0; i < Quiz.NumberOfQuestions; i++)
  {
    PrintQuestion(Quiz.QuestionList[i], i, Quiz.NumberOfQuestions);
    Quiz.QuestionList[i].PlayerAnswer = ReadPlayerAnswer();
    Quiz.QuestionList[i].QuestionResult = Quiz.QuestionList[i].CorrectAnswer == Quiz.QuestionList[i].PlayerAnswer;
    if (Quiz.QuestionList[i].QuestionResult)
    {
      Quiz.NumberOfCorrectAnswer++;
    }
    else
    {
      Quiz.NumberOfWrongAnswer++;
    }
    ShowQuestionResult(Quiz.QuestionList[i].QuestionResult, Quiz.QuestionList[i].CorrectAnswer);
  }
  Quiz.IsSuccess = (Quiz.NumberOfCorrectAnswer >= Quiz.NumberOfWrongAnswer);
}

void PrintQuizResult(stMathQuiz Quiz)
{

  cout << "\n______________________________\n\n";
  cout << " Final Results is " << Quiz.IsSuccess ? "PASS :-)" : "Fail :-(";
  cout << "\n______________________________\n\n";
  cout << "Number of Questions: " << Quiz.NumberOfQuestions << endl;
  cout << "Questions Level    : " << GetDifficultyDegreeText(Quiz.DifficultyDegree) << endl;
  cout << "OpType             : " << GetOperationSymbol(Quiz.Operator) << endl;
  cout << "Number of Right Answers: " << Quiz.NumberOfCorrectAnswer << endl;
  cout << "Number of Wrong Answers: " << Quiz.NumberOfWrongAnswer << endl;
  cout << "______________________________\n";
  SetScreenColor(Quiz.IsSuccess);
}

void PlayQuiz()
{
  stMathQuiz Quiz;
  Quiz.NumberOfQuestions = ReadNumberBetween2Numbers(1, 100, "How many rounds the game will be?");
  Quiz.DifficultyDegree = ReadDifficultyDegree();
  Quiz.Operator = ReadOperatorType();

  GenerateQuizQuestions(Quiz);
  AskAndCorrectQuizQuestionsAnswers(Quiz);
  PrintQuizResult(Quiz);
}

void StartGame()
{
  char again = 'n';
  do
  {
    ResetScreen();
    PlayQuiz();
    again = doYouPlayAgain();
  } while (again == 'y' || again == 'Y');
}
int main()
{
  srand((unsigned)time(NULL));
  StartGame();
  return 0;
}