//Done by: Aaron Lim
//I did this alone without sharing my codes with others
//I am willing to accept whatever punishment

#include "Subject.h"
#include "Student.h"

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

