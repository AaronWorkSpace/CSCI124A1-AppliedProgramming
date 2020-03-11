//Done by: Aaron Lim
//I did this alone without sharing my codes with others
//I am willing to accept whatever punishment

#include "Subject.h"
#include "Student.h"


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


