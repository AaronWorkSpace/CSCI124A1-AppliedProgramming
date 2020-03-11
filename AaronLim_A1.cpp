//Done by: Aaron Lim
//I did this alone without sharing my codes with others
//I am willing to accept whatever punishment

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cctype>
#include <ctime>
#include <iomanip>

using namespace std;

const int MAX = 30;
const int MAXNO = 5;

enum Grade {HDist, Dist, Credit, Pass, Fail};

struct assessment
{
	//i.e. Assignment 1
	char title [MAX];
	//i.e. 30 -> 30%
	int weight;
	//i.e. Upon how much?
	int MarkUpon;
	//i.e. real number
	float mark;
	//i.e mark / upon * weight
	float obtain;
};

struct subject
{
	//i.e. CSCI124
	char code [MAX];
	//i.e. Applied Programming
	char sTitle [MAX];
	//number of tasks
	int tasks;
	assessment am[MAXNO];
	//sum of weight
	int overallWeight;
	//Overall mark for the subject
	int final;
	Grade grade;
};

struct studentInfo
{
	//name of the student
    char name[MAX];
	//student id for each student
    int studentID;
	//number of subject taken
    int subTaken;
	//subject
    subject sub[MAX];
};

//---------------------------------------
//----------------TASK 1-----------------
//---------------------------------------

//main menu
void mainMenu(int&);

//print 1st option
void printFirstOption (int&);
	
//print sub page of 1st option
//creation of binary file
void sub1FirstOption (subject, fstream&, const char []);

//create binary file
void createBinary (fstream&, const char [], subject);

//calculate the weight
int calculateWeight (subject, int, int);

//check if weight is over 100
void sumWeightValue (int);

//go in query option
void sub1ThirdOption (fstream&, subject , const char []);

//check grade
void findOutGrade (int, Grade&);

//print grade
void PrintOutGrade (Grade);

//compare code
bool compareCode(const char [],fstream&, const char []);

//print update option (2)
void sub1SecondOption (fstream&, subject, const char []);

//get the number of codes
int getTotalNoOfCode (fstream&, const char []);

//compare code
bool compareSubject(const char [], const char []);

//update the subject name
void updateSubName (subject);

//update task no, i.e. update task 3					
void updateTaskNo (subject);

//adding new task	 	 	 	 	 
void updateNewTask (subject);

//deleting task	   	   	   	   	   
void deleteATask (subject);
					
//print subject update option
void updateSubjectOption (subject);

//update binary file
void updateSubject (fstream&, const char [], subject);

//get a subject code
subject getACode (fstream&, const char [], int);

//---------------------------------------
//----------------TASK 2-----------------
//---------------------------------------

//print student option
void printStudentOption (int&);

//register a student
void registration();

//process all the student record
void processRecord (const char []);

//print out the score / taken subject
void query (const char []);

//compare student id
bool aStudentID(int, int);

//delete a student
void deleteStudent (const char []);

//get number of student
int getTotalNoOfStudent (fstream&, const char []);

//update the binary file for student
void updateStudBinary (fstream&, const char [], studentInfo, int);

//create binary file for student
void createStudBinary (fstream&, const char [], studentInfo);

//get a student info for processing
studentInfo aStudent (fstream&, const char [], int);

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

//main menu
void mainMenu(int& option1)
{
	option1 = 0;
	cout << "Welcome to ABC University\n\n"
		 << "Here are the options\n\n"
		 << "\t1. Subject Processing System\n"
		 << "\t2. Student SOLS System\n"
		 << "\t9. Quit\n\n"
		 << "\tYour option: ";
	cin >> option1;	 
	cout << "--------------------------------------" << endl;   
}
//print 1st option
void printFirstOption (int& i)
{
	i= 0;
	cout << "Welcome to ABC University\n"
		 << "(Subject Processing System)\n\n"
		 << "Here are the options\n"
		 << "\t1. Add a subject\n"
		 << "\t2. Update a subject\n"
		 << "\t3. Query a subject\n"
		 << "\t9. Quit\n"
		 << "\tYour option: ";
	cin >> i;	
	cout << "-------------------------------------" << endl;   
}

//print sub page of 1st option
//creation of binary file
void sub1FirstOption (subject s, fstream& file, const char fileName [])
{	 
	char code [MAX];
	bool check;
	cin.clear(); 
	cin.ignore(MAX, '\n');
	char c [MAX];
	 	
	cout << "Subject adding system\n"
	 	 << "---------------------\n"
		 << "Subject code: ";
	cin.getline(c, '\n');
		
	if (check = compareCode (fileName, file, c))
	{
		strcpy (s.code, c);
	    cout << "Subject Name: ";
		cin.getline(s.sTitle, MAX);
		
		cout << "No of assessment tasks: ";
		cin >> s.tasks;
		
		cin.clear();
		cin.ignore(MAX,'\n');	   
		
		s.overallWeight = 0;
		
		for (int i = 0; i < s.tasks;i++)
		{
			cout << "Task "
				 << i + 1
				 << " information\n"
				 << "\tTitle: ";
			cin.getline(s.am[i].title,MAX);	      
			
			cout << "\tWeight: ";
			cin >> s.am[i].weight;
			
			s.overallWeight = calculateWeight(s, s.overallWeight, i);	  
			
			cout << "\tUpon: ";
			cin >> s.am[i].MarkUpon;
			
			s.am[i].obtain = 0;
			s.am[i].mark = 0;
			
			cin.clear();
			cin.ignore(MAX,'\n');	  
		}
		
		s.final = 0;
		
		cout << "Total weight = "
			 << s.overallWeight
			 << endl;
			 
		cout << s.code << " have been added";	
			    		 
		sumWeightValue (s.overallWeight);
		
		createBinary(file, fileName, s);
	}
}

//create binary file
void createBinary (fstream& file, const char fileName [], subject s)
{
	file.open(fileName, ios::out | ios::app | ios::binary);
	
	if (!file)
	{
		file.close();
		exit(-1);
	}
	
	file.write(reinterpret_cast <const char *>(&s), sizeof(s));
	
	file.close(); 
}

//calculate the weight
int calculateWeight (subject s, int sum, int i)
{
	
	sum += s.am[i].weight;

	return sum;
}

//check if weight is over 100
void sumWeightValue (int sumWeight)
{
	if (sumWeight > 100)
	{
		cout << "\nNote that the total weight is not 100."
			 << "\nYou can update through the update system"
			 << "\n-----------------------------------------"
			 << endl;
	}
	
	else
	{
		cout << "\n-----------------------------------------" 
			 << endl;
	}
}

//go in query option
void sub1ThirdOption (fstream& file, subject s, const char fileName [])
{
	cin.ignore();  	
	file.open(fileName, ios::in | ios::binary);
	int option2;
	char code [MAX];
	
	if (!file)
	{
		file.close();
		cout << fileName << " is not created" 
			 << "\n-----------------------------" << endl;
	}
		 
	bool check = false;
	bool check1 = false;
	cout << "Select query system"
		 << "\n-------------------"
		 << "\nEnter Subject Code: "
		 << setfill(' ');
		 
	cin.getline(code, '\n');

	while(file.read (reinterpret_cast <char *>(&s), sizeof (s)))	 
	{	 	 	
		check = compareSubject (s.code, code); 	 	 
		if (check == 1)
		{	
			cout << "\nSubject Code: "
				 << s.code
				 << "\nSubject Name: "
				 << s.sTitle
				 << left << setw(8) << "\n\nTask"
				 << left << setw(16) << "Title"
				 << left << setw(8) << "Weight"
				 << left << setw(8) << "Upon"
				 << left << setw(8) << "Mark"
				 << left << setw(8) << "Obtained\n"
				 << endl;
			
			for (int b = 0; b < s.tasks; b++)
			{
				cout << left << setw(8) << b+1
					 << left << setw(16) << s.am[b].title
					 <<	left << setw(8) << s.am[b].weight
					 << left << setw(8) << s.am[b].MarkUpon
					 << left << setw(8) << s.am[b].mark
					 << left << setw(8) << s.am[b].obtain
					 << endl;
			}   

			
			cout << "\nTotal marks = "
				 << s.final;
			
			findOutGrade (s.final, s.grade);
			PrintOutGrade (s.grade);
			
			cout << "Total weight = "
			 	 << s.overallWeight;
			 
		sumWeightValue (s.overallWeight);
			
		check1 = true;	   	   
		//createBinary(file, fileName, s);  
		}	 
	}
	if (check1 != 1)
	{
		cout << "Subject code not found" 
			 << "\n--------------------------------"
			 << endl;	   
	}

	file.close(); 	   	    
}

//compare code
bool compareSubject(const char sub [], const char code [])
{
	if (strcmp(sub, code) == 0)
		return true;
	else
		return false;
}

//check grade
void findOutGrade (int i, Grade& j)
{
	if (i < 50)
		j = Fail;
	else if (i < 65 && i >= 50)
		j = Pass;
	else if (i < 75 && i >= 65)
		j = Credit;
	else if (i < 85 && i >= 75)
		j = Dist;
	else if (i > 84)
		j = HDist; 
}

//print grade
void PrintOutGrade (Grade j)
{
	switch (j)
	{
		case 0:	cout << "\nGrade: HDist" 
					 << endl;
				break;
		case 1:	cout << "\nGrade: Dist"
					 << endl;
				break;
		case 2: cout << "\nGrade: Credit"
					 << endl;
				break;
		case 3: cout << "\nGrade: Pass"
					 << endl;
				break;
		case 4: cout << "\nGrade: Fail"
					 << endl;
				break;
	}
}

//compare code if 
bool compareCode(const char fileName[], fstream& file, const char userCode [])
{
	subject s;
	
	file.open (fileName, ios::in | ios::binary);
	
	if (!file)
	{
		file.close();
	}
	
	while (file)
	{
		file.read (reinterpret_cast <char *>(&s), sizeof (s));
		//for (int i = 0; i <= size; i++)
		//{
			if (strcmp(userCode, s.code) == 0)
			{
				cout << "Subject code " << userCode 
					 << " has been used"
					 << "\nExit add a subject system"
					 << "\n-------------------------"
					 << endl;
					file.close();	
					return false;
			}
	}
	file.close();
	return true;
}

//compare code if 
bool compareCode2(const char fileName[], fstream& file, const char userCode [])
{
	subject s;
	
	file.open (fileName, ios::in | ios::binary);
	
	if (!file)
	{
		file.close();
	}
	
	while (file)
	{
		file.read (reinterpret_cast <char *>(&s), sizeof (s));
		//for (int i = 0; i <= size; i++)
		//{
			if (strcmp (s.code, userCode) == 0)
			{
				cout << "Subject code " << userCode 
					 << " has not been included"
					 << "\nExit add a subject system"
					 << "\n-------------------------"
					 << endl;
					file.close();	
					return true;
			}
	}
	file.close();
	return false;
}

//print update option (2)
void sub1SecondOption (fstream& file, subject s, const char fileName [])
{
	cin.ignore();  	
	file.open (fileName, ios::in | ios:: out | ios::binary);
	
	if(!file)
	{
		cout << fileName << " not created"
			 << "\n--------------------------"
			 << endl;
	}
	
	char code [MAX];
	bool check;
	bool check1 = false;
	
	cout << "Subject updating system"
		 << "\n-----------------------"
		 << "\n\nEnter subject code: "
		 << setfill (' ');
	cin >> code;
	
	while (file.read(reinterpret_cast <char *>(&s), sizeof (s)))
	{
		check = compareSubject (s.code, code);
		if (check == 1)
		{
			updateSubjectOption (s);
			check1 = true;
		}
	}
	if (file.eof () && check1 == false)
	{
		cout << "Subject not added"
			 << "\n----------------"
			 << endl;
	}
	
	file.close();
}

//print subject update option
void updateSubjectOption (subject s)
{
	fstream file;
	
	int option3, option2;
	cout << "\nSubject Code: "
		 << s.code
		 << "\nSubject Name: "
		 << s.sTitle
		 << left << setw(8) << "\n\nTask"
		 << left << setw(16) << "Title"
		 << left << setw(8) << "Weight"
		 << left << setw(8) << "Upon"
		 << left << setw(8) << "Mark"
		 << left << setw(8) << "Obtained\n"
		 << endl;
		
		for (int b = 0; b < s.tasks; b++)
		{
			cout << left << setw(8) << b+1
				 << left << setw(16) << s.am[b].title
				 <<	left << setw(8) << s.am[b].weight
				 << left << setw(8) << s.am[b].MarkUpon
				 << left << setw(8) << s.am[b].mark
				 << left << setw(8) << s.am[b].obtain
				 << endl;
		}     
		
		cout << "\nTotal marks = "
			 << s.final;

		findOutGrade (s.final, s.grade);
		
		PrintOutGrade (s.grade);
		
		cout << "Total weight = "
		 	 << s.overallWeight;
	
		sumWeightValue (s.overallWeight);
		
		cout << "\n1. Update subject name"
			 << "\n2. Update task no"
			 << "\n3. Add a new task"
			 << "\n4. Delete a task"
			 << "\n9. Quit"
			 << "\n\nYour option: ";
		cin >> option3;
		
		cin.clear();
		cin.ignore(MAX, '\n');
	
		switch(option3)
		{
			case 1: cout << "-----------------------" << endl;
					updateSubName (s);
					break;
			case 2: cout << "-----------------------" << endl;
					updateTaskNo (s);
					break;
			case 3: cout << "-----------------------" << endl;
					updateNewTask (s);
					break;
			case 4: cout << "-----------------------" << endl;
					deleteATask (s);
					break;
			case 9: cout << "-----------------------" << endl;
					updateSubject (file, "subject.dat", s);
					break;
			
			default: cout << "You have enter a invalid value, please enter 1 / 2 / 3 / 4 / 9.\n "
						  << "Please re-enter the subject code\n"
						  << "-------------------------------------------------------"
						  << endl;
					 sub1SecondOption (file, s, "subject.dat");
		}
}
//get the number of codes
int getTotalNoOfCode (fstream& file, const char fileName[])
{
	file.open(fileName, ios::in | ios::binary);
	
	if(!file)
	{
		file.close();
		return 0;
	}
	
	file.seekg (0, ios::end);
	
	int totalBytes = file.tellg ();
	
	int noOfCodes = totalBytes / sizeof (subject);
	
	file.close();
	
	return noOfCodes;
}

//update the subject name
void updateSubName (subject s)
{
	cout << "Enter updated subject name: ";
	cin.getline (s.sTitle, sizeof (s.sTitle));
	
	cout << "\nSummary after updates"
		 << "\n---------------------"
		 << endl;
		 
	updateSubjectOption (s);
}

//update task no, i.e. update task 3					
void updateTaskNo (subject s)
{
	int task = 0;
	
	cout << "Enter update task no: ";
	cin >> task;
	cin.clear();
	cin.ignore(MAX,'\n');

	s.overallWeight -= s.am[task - 1].weight;		
	
	if (task - 1 < s.tasks)
	{
		cout << "Enter updated task title: ";
		cin.getline (s.am[task-1].title, MAX);
		
		cout << "Enter task weight: ";
		cin >> s.am[task-1].weight;
		
		s.overallWeight += s.am[task - 1].weight;		
		
		cout << "Enter task mark upon: ";
		cin >> s.am[task-1].MarkUpon;
		
		cout << "\nSummary after updates"
			 << "\n---------------------"
			 << endl;
	}
	else
	{
		cout << "You entered a invalid value"
			 << "\n-------------------------";
	}
	updateSubjectOption (s);
}

//adding new task	 	 	 	 	 
void updateNewTask (subject s)
{
	s.tasks += 1;
	cout << "Enter new task title: ";
	cin.getline (s.am[s.tasks - 1].title, MAX);
	
	cout << "Enter new task weight: ";
	cin >> s.am[s.tasks - 1].weight;

	s.overallWeight += s.am[s.tasks - 1].weight;
	
	cout << "Enter new task mark upon: ";
	cin >> s.am[s.tasks - 1].MarkUpon;
	
	cout << "\nSummary after updates"
		 << "\n---------------------"
		 << endl;
	
	updateSubjectOption (s);	   
}

//deleting task	   	   	   	   	   
void deleteATask (subject s)
{
	int i = 0;
	
	cout << "Enter delete a task: ";
	cin >> i;
	
	s.overallWeight -= s.am [i - 1].weight;
	
	for (i; i < s.tasks; i++)
	{
		strcpy (s.am[i - 1].title, s.am[i].title);
		s.am[i - 1].weight = s.am[i].weight;
		s.am[i - 1].MarkUpon = s.am[i - 1].MarkUpon;
	}
	
	s.tasks -= 1;
	
	cout << "\nSummary after updates"
		 << "\n---------------------"
		 << endl;
	
	updateSubjectOption (s);	  	   
}

//update binary file
void updateSubject (fstream& file, const char fileName [], subject s)
{
	int size = getTotalNoOfCode (file, "subject.dat");

	file.open (fileName, ios::in | ios::out | ios::binary);
	
	if(!file)
	{
		cout << "Updating of " << fileName << " failed"
			 << endl;
		file.close();
	}
	
	subject d;
	
	file.seekg ((size - 1) * sizeof(subject), ios::beg);
	file.read (reinterpret_cast <char *>(&d), sizeof (d));
	
	file.seekp ((size - 1) * sizeof (subject), ios::beg);
	file.write (reinterpret_cast <const char *> (&s), sizeof (s));
	
	file.close();
	
	cout << "Binary " << fileName << " updated"
		 << "\n-----------------------"
		 << endl;
}

//get a record
subject getACode (fstream& file, const char fileName [], int size)
{
	subject s;
	file.open(fileName, ios::in | ios::binary);
	
	if(!file)
	{
		cout << fileName << " does not exist"
			 << ", proceeding to add subject page"
			 << endl;
		sub1FirstOption (s, file, "subject.dat");	
	}
	
	file.seekg ((size - 1) * sizeof (subject), ios::beg);
	
	file.read (reinterpret_cast <char *>(&s), sizeof (subject));
	
	file.close();
	
	return s;
}

//---------------------------------------
//----------------TASK 2-----------------
//---------------------------------------

//print student option
void printStudentOption (int& i)
{
	int option = 0;
	cout << "Welcome to ABC University"
		 << "\n(Student SOL System)"
		 << "\n\nHere are the options"
		 << "\n\t1. Registration"
		 << "\n\t2. Process Student System"
		 << "\n\t3. Query Student"
		 << "\n\t4. Delete Student Record"
		 
		 << "\n\t9. Quit"
		 << "\n\n\tYour option: ";
	cin >> i;
	
	/*do
	{
		switch(i)
		{
			case 1: registration(i);
					break;
			
			case 2: processRecord ("student.dat");
					break;
			
			case 3: query ("student.dat");
					break;
			
			case 4: deleteStudent ("student.dat");
					break;
		}
	}while (i != 9);*/
	
	cout << "----------------------------" << endl;
}

//register a student
void registration()
{
	fstream file;
	subject aCode;
	studentInfo stud;
	char name [MAX];
	bool check = false;
	char fileName [MAX] = "subject.dat";
	int n;
	
	cout << "\nOnline Registration system"
		 << "\n--------------------------"
		 << "\n\nEnter your name: ";
		 
	cin.clear();
	cin.ignore(MAX,'\n');
	
	cin.getline(stud.name, MAX);
	
	if (!fileName)
	{
		file.close();
		printStudentOption(n);
	}
	
	cout << "\nStudent id allocated: ";
	
	stud.studentID = 888000 + (getTotalNoOfStudent (file, "student.dat")) + 1;
	
	int appliedStud = getTotalNoOfStudent (file, "student.dat");
	
	cout << stud.studentID
		 << "\n\nSubjects available for this term"
	 	 << endl;
	
	int i = 0;
	
	cout << "\t";
	
	while(i < getTotalNoOfCode(file, "subject.dat"))
	{
		aCode = getACode (file, "subject.dat", i + 1);
		
		cout << i + 1 << " - " << aCode.code << " ";
		i++;
	}
	int choice = 0;
	
	do
	{
		cout << "\nNo of subjects registered (maximum 2 subjects): ";
		cin >> choice;
		
		if (choice < 1 || choice > 2)
		{
			cout << "Invalid no" << endl;
		}
		
	}while(choice < 1 || choice > 2);
	
	stud.subTaken = choice;
	int studChoice = 0;
	int applied = 0;
	char empty [MAX];
	int f = 0;
	
	do
	{
		strcpy (stud.sub[f].code, empty);	
		cout << "\nEnter subject no: ";
		cin >> studChoice;
		
		if (studChoice < getTotalNoOfCode(file, "subject.dat") + 1)
		{
			aCode = getACode (file, "subject.dat", studChoice);
			
			if (strcmp(stud.sub[f].code, aCode.code) == 0)
			{
				cout << "Subject already registered" << endl;
			}
			
			else
			{
				aCode = getACode (file, "subject.dat", studChoice);
				strcpy (stud.sub[f].code, aCode.code);
				strcpy (stud.sub[f].sTitle, aCode.sTitle);
				stud.sub[f].tasks = aCode.tasks;
				cout << "Registered - " 
					 << stud.sub[f].code
					 << endl;
				
				stud.sub[f].overallWeight = 0;
				
				for (int j = 0; j < aCode.tasks; j++)
				{
					strcpy(stud.sub[applied].am[j].title, aCode.am[j].title);
					stud.sub[applied].am[j].weight = aCode.am[j].weight;
					stud.sub[applied].am[j].MarkUpon = aCode.am[j].MarkUpon;
					stud.sub[applied].am[j].mark = 0;
					stud.sub[applied].am[j].obtain = 0;
					stud.sub[applied].overallWeight += stud.sub[i].am[j].weight;
				}
				stud.sub[applied].final = 0;
				findOutGrade (stud.sub[applied].final, stud.sub[applied].grade);
				applied++;
				f++;			
			}
		}
		
		else
		{
			cout << "Entered a invalid value"
				 << endl;
		}
	}while(applied < choice);
	
	cout << "Student "
		 << stud.name
		 << " registered"
		 << endl;	 
	createStudBinary (file, "student.dat", stud);
	cout << "-------------------------------------" << endl;
}

//process all the studen record
void processRecord (const char fileName[])
{
	fstream file;
	studentInfo stud;
	cout << "-----------------------------------------"
		 << "\nProcess Student Records"
		 << "\n-----------------------"
		 << "\n\nBegin processing of updates"
		 << endl;	
		    
	int totalStud = getTotalNoOfStudent (file, fileName);
	
	for (int h = 0;h < totalStud; h++)	  
	{
		stud = aStudent (file, fileName, h);
		
		for (int i = 0;i < stud.subTaken;i++)	
		{	
			float finalScore = 0;
			int countWeight = 0;
			
			for (int j = 0; j < stud.sub[i].tasks; j++)
			{	 	 	 	 
				stud.sub[i].am[j].mark = 1.0 * (rand() % stud.sub[i].am[j].MarkUpon) + 0.1 * (rand() % 10);
				stud.sub[i].am[j].obtain = ((stud.sub[i].am[j].mark / stud.sub[i].am[j].MarkUpon) 
											* stud.sub[i].am[j].weight);
				
				finalScore += stud.sub[i].am[j].obtain;
			} 
			
			stud.sub[i].final = finalScore;	   
			findOutGrade (stud.sub[i].final, stud.sub[i].grade);
			
			updateStudBinary (file, "student.dat", stud, h); 
		}
		
		if (stud.studentID == 0)
		{
		
		}
		else
		{
			cout << "Updated student id " << stud.studentID << endl;		
		}
	}
	
	cout << "All records processed\n\n"
		 << "---------------------------------------"
		 << endl;
}

//print out the score / taken subject
void query (const char fileName [])
{
	fstream file;
	studentInfo stud;
	int studentID;
	bool check;
	bool check1 = false;
	int o;
	
	cout << "\nSelect Query system"
		 << "\n-------------------"
		 << "\n\nEnter your id: ";
	cin >> studentID;
	
	file.open(fileName, ios::in | ios::binary);
	
	if(!file)
	{
		cout << fileName << " not created"
			 << endl;
		registration ();
	}
	
	while (file.read(reinterpret_cast <char *>(&stud), sizeof (stud)))
	{
		check = aStudentID(stud.studentID, studentID);
		if (check == 1)	   
		{
			check1 = true;
			cout << "\n\nName: "
				 << stud.name
				 << "\nStudent id: "
				 << stud.studentID
				 << "\n\nYour term assessment"
				 << endl;
			
			for (int i = 0; i < stud.subTaken; i++)	
			{	 
				cout << "\nSubject Code: "
					 << stud.sub[i].code
					 << "\nSubject Name: "
					 << stud.sub[i].sTitle
					 << left << setw(8) << "\n\nTask"
					 << left << setw(16) << "Title"
					 << left << setw(8) << "Weight"
					 << left << setw(8) << "Upon"
					 << left << setw(8) << "Mark"
					 << left << setw(8) << "Obtained\n"
					 << endl;
				
				for (int j = 0; j < stud.sub[i].tasks; j++)
				{
					cout << left << setw(8) << j + 1
						 << left << setw(16) << stud.sub[i].am[j].title
						 <<	left << setw(8) << stud.sub[i].am[j].weight
						 << left << setw(8) << stud.sub[i].am[j].MarkUpon
						 << left << setw(8) << stud.sub[i].am[j].mark
						 << left << setw(8) << stud.sub[i].am[j].obtain
						 << endl;
				}  
				
				cout << "\nTotal marks = "
					 << stud.sub[i].final;
					 
				//PrintOutGrade (stud.sub[i].grade);
				
				cout << "\n---------------------------------"
					 << endl;	
			}	     
		} 
	}
	if (check1 != 1)
	{
		cout << "Student ID " << studentID 
		 << " does not exist"
		 << "\nExiting query option"
		 << "\n-------------------------"
		 << endl;
	}
	
	file.close();
}

//a student id
bool aStudentID(int b, int i)
{
	if (b == i)
	{
		return true;
	}	
	else
		return false;
}
//delete a student
void deleteStudent (const char fileName [])
{
	cout << "\nDelete student record"
		 << "\n---------------------"
		 << endl;
	
	fstream file;
	int studentID;
	int foundStudent = 0;
	studentInfo stud;
	int size;
	int m;
	
	cout << "Enter student id: ";
	cin >> studentID;
	
	size = getTotalNoOfStudent (file, "student.dat");
		
	while (size > 0 && foundStudent == 0)
	{
		stud = aStudent (file, "student.dat", size);
		
		if (studentID == stud.studentID)
		{
			foundStudent++;
		}
		size--;
	}
	
	if (foundStudent != 0)
	{
		cout << "Record of the student id not found"
			 << ", please try again later"
			 << "\n----------------------------------"
			 << endl;
		printStudentOption (m);
	}
	
	cout << "Record found"
		 << "\n\tStudent id = "
		 << stud.studentID
		 << "\n\tStudent name = "
		 << stud.name
		 << "\nDeleted"
		 << endl;
	
	stud = aStudent (file, "student.dat", size);
	//stud = aStudent (file, "student.dat", size);
	stud.studentID = 0;
	updateStudBinary (file, "student.dat", stud, size);
	
	printStudentOption (m);
}

//get number of student
int getTotalNoOfStudent (fstream& sfile, const char fileName[])
{
	studentInfo stud;
	
    sfile.open (fileName, ios::in | ios::binary);
    
    if (!sfile)
    {
        sfile.close ();
        return 0;
    }
    
    sfile.seekg (0, ios::end);
	
    int totalBytes = sfile.tellg ();
	
    int noOfRecords =  totalBytes / sizeof(studentInfo);
    
    sfile.close ();
    
    return noOfRecords;
}

//update the binary file for student
void updateStudBinary (fstream& file, const char fileName [], studentInfo stud,int i)
{
	file.open (fileName, ios::in | ios::out | ios::binary);
    
    if (!file)
	{
		cout << "Failed to update " << fileName
			 << " because it does not exist"
			 << "\n----------------------------------"
			 << endl;
		file.close(); 
		printStudentOption(i);
	}
	
	studentInfo update;
	
    file.seekg ((i) * sizeof (studentInfo), ios::beg);
    file.read (reinterpret_cast <char *>(&update), sizeof (update));
    
    file.seekp ((i) * sizeof (stud), ios::beg);
    file.write (reinterpret_cast <const char *>(&stud), sizeof (stud));
    
    file.close ();	  
}

//create binary file for student
void createStudBinary (fstream& file, const char fileName [], studentInfo stud)
{
	file.open(fileName, ios::out | ios:: app | ios::binary);
	int i;
	
	if(!file)
	{
		cout << "Binary file " << fileName 
			 << " opened for creation failed"
			 << endl;
		file.close();
		printStudentOption(i);
	}	 
	
	file.write (reinterpret_cast <const char *> (&stud), sizeof (stud));
	file.close();
}

//get a student info for processing
studentInfo aStudent (fstream& file, const char fileName [], int h)
{
	file.open (fileName, ios::in | ios::binary);
	int i;
	
	if (!file)
	{
		cout << "Failed to update " << fileName
			 << " because it does not exist"
			 << "\n----------------------------------"
			 << endl;
		file.close(); 
		printStudentOption(i);	  
	}
	
	file.seekg ((h) * sizeof (studentInfo), ios::beg);
	
	studentInfo stud;
	
	file.read(reinterpret_cast <char *>(&stud), sizeof (stud));
	
	file.close();
	return stud;
}

