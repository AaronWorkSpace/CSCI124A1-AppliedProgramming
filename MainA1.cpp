//Done by: Aaron Lim
//I did this alone without sharing my codes with others
//I am willing to accept whatever punishment

#include "Subject.h"
#include "Student.h"

int main()
{
	subject s;
	fstream file;

	int option1, option2, option3;

	srand(time(NULL));
	
	cout << fixed << showpoint << setprecision (1);

	mainMenu(option1);
	
	while (option1 != 9)
	{
		if (option1 == 1)
		{
			printFirstOption(option2);
			if (option2 == 1)
			{
				option2 = 0;
				sub1FirstOption (s, file,"Subject.dat");
			}
			else if(option2 == 2)
			{
				sub1SecondOption (file, s, "Subject.dat");
			}
			else if (option2 == 3)
			{
				sub1ThirdOption (file, s, "Subject.dat");
			}
			else if (option2 == 9)
			{
				mainMenu (option1);
			}
			else
			{
				cout << "You have entered a invalid value, please enter "
					 << "1 / 2 / 3 / 9"
					 << "\n--------------------------------------"
					 << endl;
				printFirstOption(option2);
			}
		}
		
		else if (option1 == 2)
		{
			printStudentOption (option3);
		
			if (option3 == 1)
				registration();
			else if (option3 == 2)
				processRecord ("student.dat");
			else if (option3 == 3)
				query ("student.dat");
			else if (option3 == 4)
				deleteStudent ("student.dat");
			else if (option3 == 9)
			{
				cout << "\n-----------------------------"
					 << endl;
				mainMenu(option1);
			}
			else
			{
				cout << "You entered a invalid value"
					 << ", please enter 1 / 2 / 3 /4 / 9"
					 << endl;
				printStudentOption(option3);
			}
		}
		
		else if (option1 == 9)
		{
		
		}
		
		else
		{
			cout << "You have entered a invalid value, please enter "
				 << "1 / 2 / 9"
				 << "\n--------------------------------------"
				 << endl;
			mainMenu (option1);
		}
	}
}

