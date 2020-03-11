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


