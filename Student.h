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

