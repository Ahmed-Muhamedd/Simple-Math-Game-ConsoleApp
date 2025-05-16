#include <iostream>
using namespace std;


enum enOperators { Add = 1, Sub = 2, Div = 3 , Multi = 4 , MixOp = 5 };
enum enLevels  {Easy = 1 , Mid = 2 , Hard = 3 , Mix = 4};

struct stQuestion {
	int Number;
	int Number2;
	enOperators OperationType;
	enLevels LevelType;
	int CorrectAnswer;
	int playerAnswer;
	bool AnswerResult;
};

struct stQuiz {
	stQuestion Questions[100];
	short NumberOfQuistions;
	enOperators Operator;
	enLevels Level;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool IsPass;
};

int RandomNumber(int From, int To) {
	int Number = rand() % (To - From + 1) + From; 
	return Number;
}

int ReadAnswer() {
	int Number = 0;
	cout << "Enter Your Answer? ";
	cin >> Number;
	return Number
		;
}

short ReadHowManyQuestion() {
	short Number = 0;

	do {
		cout << "Enter How Many Question ? ";
		cin >> Number;
	} while (Number < 1 || Number > 100);
	return Number;
}

enOperators ReadOperatortype() {
	short Number = 0;

	do {

		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?  ";
		cin >> Number;

	} while (Number < 1 || Number > 5);

	return (enOperators)Number;
}

enLevels ReadLevelType() {
	short Number = 0;

	do {

		cout << "Enter Level Type [1] Easy, [2] Mid, [3] Hard, [4] Mix  ";
		cin >> Number;

	} while (Number < 1 || Number > 4);

	return (enLevels)Number;
}

string OperatorString(enOperators OP) {
	string Op[5] = { "ADD" , "Sub" , "Div" , "Multi" , "MixOp" };
	return Op[OP - 1];
}

string OperatorSymbol(enOperators Sympol) {
	switch (Sympol) {
	case enOperators::Add:
		return "+";
	case enOperators::Sub:
		return "-";
	case enOperators::Multi:
		return "*";
	case enOperators::Div:
		return "/";

	}
}

int Calculator(enOperators Calc , int Number , int Number2) {
	switch (Calc) {
	case enOperators::Add:
		return Number + Number2;
	case enOperators::Sub:
		return Number - Number2;
	case enOperators::Div:
		return Number / Number2;
	case enOperators::Multi:
		return Number * Number2;
	}
}

string LevelString(enLevels Level) {
	string level[4] = { "Easy" , "Mid" , "Hard" , "Mix" };
	return level[Level - 1];
}

stQuestion GenerateQuestion(enOperators Operator , enLevels Level) {
	stQuestion Question;
	
	if (Level == enLevels::Mix)
		Level = (enLevels)RandomNumber(1, 3);

	if (Operator == enOperators::MixOp)
		Operator = (enOperators)RandomNumber(1, 4);

	Question.OperationType = Operator;

	switch (Level) {
	case enLevels::Easy:
		Question.Number = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = Calculator(Question.OperationType, Question.Number, Question.Number2);
		Question.LevelType = Level;
		return Question;
		
	case enLevels::Mid:
		Question.Number = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = Calculator(Question.OperationType, Question.Number, Question.Number2);
		Question.LevelType = Level;
		return Question;

	case enLevels::Hard:
		Question.Number = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = Calculator(Question.OperationType, Question.Number, Question.Number2);
		Question.LevelType = Level;
		return Question;
	}

	return Question;
}

void GenerateQuestions(stQuiz& Quiz) {
	for (int i = 0; i < Quiz.NumberOfQuistions; i++) {
		Quiz.Questions[i] = GenerateQuestion(Quiz.Operator, Quiz.Level);
	}
}

void PrintTheQuestion(stQuiz Quiz, int Quesiton) {
	cout << "\nQuestion [" << Quesiton + 1 << "/" << Quiz.NumberOfQuistions << "]" << endl;
	cout << Quiz.Questions[Quesiton].Number << endl;
	cout << OperatorSymbol(Quiz.Questions[Quesiton].OperationType) << endl;
	cout << Quiz.Questions[Quesiton].Number2 << endl;
	cout << "--------------------------------------\n\n";
}

void SetScreenColor(stQuiz Quiz , int Question) {
	if (Quiz.Questions[Question].AnswerResult)
		system("color 2F");
	else
		system("color 4F");
}

void CorrectAnswer(stQuiz& Quiz, int Question) {
	if (Quiz.Questions[Question].CorrectAnswer != Quiz.Questions[Question].playerAnswer) {
		Quiz.NumberOfWrongAnswer++;
		cout << "The Answer Is Wrong :(\n";
		cout << "The Right IS: " << Quiz.Questions[Question].CorrectAnswer << endl;
		Quiz.Questions[Question].AnswerResult = false;

	}
	else
	{
		Quiz.NumberOfRightAnswer++;
		Quiz.Questions[Question].AnswerResult = true;

		cout << "The Answer Is Right:)";

	}
	SetScreenColor(Quiz, Question);
}

void AskQuestionAndCorrect(stQuiz& Quiz) {
	for (int i = 0; i < Quiz.NumberOfQuistions; i++) {
		PrintTheQuestion(Quiz, i);
		Quiz.Questions[i].playerAnswer = ReadAnswer();
		CorrectAnswer(Quiz, i);
	}
	Quiz.IsPass = (Quiz.NumberOfRightAnswer >= Quiz.NumberOfWrongAnswer);
}

string PassOrNot(stQuiz Quiz) {
	if (Quiz.IsPass) {
		return "Pass :)";
	}
	else
	{
		return "Fail :(";
	}
}

void FinalColor(stQuiz Quiz) {
	if (Quiz.IsPass) {
		system("color 2F");
	}
	else
	{
		system("color 4f");
	}
}

void PrintQuizResult(stQuiz Quiz) {
	cout << "\n\n-----------------------------------------------------\n";
	cout << "The Result Is " << PassOrNot(Quiz) << endl << endl;;
	cout << "-----------------------------------------------------\n";
	cout << "The Number OF Questions : " << Quiz.NumberOfQuistions << endl;
	cout << "Question level    : " << LevelString(Quiz.Level) << endl;
	cout << "Operation Type    : " << OperatorString(Quiz.Operator) << endl;
	cout << "Number of Right Answers  : " << Quiz.NumberOfRightAnswer << endl;
	cout << "Number Of Wrong Answers  : " << Quiz.NumberOfWrongAnswer << endl;
	FinalColor(Quiz);
}

void resetScreen() {
	system("cls");
	system("color 0F");
}

void MathGame() {
	stQuiz Quiz;
	Quiz.NumberOfQuistions = ReadHowManyQuestion();
	Quiz.Level = ReadLevelType();
	Quiz.Operator = ReadOperatortype();

	GenerateQuestions(Quiz);
	AskQuestionAndCorrect(Quiz);
	PrintQuizResult(Quiz);


}

void StartGame() {
	char Start = 'Y';

	do {
		resetScreen();
		MathGame();
		cout << "Do You Wanna Play Again Y/N" << endl;
		cin >> Start;
	} while (Start == 'Y' || Start == 'y');
}


int main()
{
	srand((unsigned)time(NULL));
	StartGame();
		return 0;
}



