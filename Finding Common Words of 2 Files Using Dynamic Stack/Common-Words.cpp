#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include "DynIntStack.h"

using namespace std;

DynIntStack s1;
DynIntStack s2;

bool doesExist(DynIntStack & alfa, string wordName)//this function will return true if the word does exist in the stack
{
	DynIntStack temp;

	bool exist=false;//initialized to false in the beginning

	string beta;

	while(!alfa.isEmpty())
	{
		alfa.pop(beta);
		if(wordName==beta)
			exist= true;
		temp.push(beta);
	}
	while(!temp.isEmpty())
	{
		temp.pop(beta);
		alfa.push(beta);
	}

	return exist;
}


void copy(DynIntStack & alfa, DynIntStack & beta,  DynIntStack & other)//this function will copy the original stacks
{
	DynIntStack temp, sweeper;
	string word;
	while(!alfa.isEmpty())
	{
		alfa.pop(word);
		sweeper.push(word);
	}
	while(!sweeper.isEmpty())
	{
		sweeper.pop(word);

		if(doesExist(other, word))//if the word exist in the other file, push it to the copy stack
		{
			beta.push(word);
		}
		temp.push(word);
	}
	while(!temp.isEmpty())
	{
		temp.pop(word);
		alfa.push(word);
	}

}


int wordCount(DynIntStack & alfa, string wordName)
{
	DynIntStack temp;
	int count=0;

	while(!alfa.isEmpty())
	{
		string beta;
		alfa.pop(beta);

		temp.push(beta);
	}
	while(!temp.isEmpty())
	{
		string beta;
		temp.pop(beta);
		if(beta==wordName)//if the word is equal to the name in the node, increase the count
		{
			count++;
		}	
		alfa.push(beta);
	}
	return count;
}


void firstFileReading(ifstream & input1)//reading the first file and pushing it to the stack
{
	string line, word;
	while(getline(input1, line))
	{
		stringstream ss(line);
		while(ss>>word)
		{
			s1.push(word); 	
		}
	}

}

void secondFileReading(ifstream & input2)//reading the second file and pushing it to the stack
{
	string line, word;
	while(getline(input2, line))
	{
		stringstream ss(line);
		while(ss>>word)
		{

			s2.push(word); 
		}
	}
}

int main(){

	cout <<"This program finds the common words of two files using stacks." <<endl;
	cout << "---" << endl;
	string filename1, filename2;
	string choice;
	cout << "Enter the first file name: ";
	cin >> filename1;
	// will ask the user a filename to open
	ifstream input1, input2;
	input1.open(filename1.c_str());

	while(input1.fail())//if the filename is not valid, ask again until user enters a valid filename
	{	
		input1.close();
		cin.ignore();
		cout <<"Enter the first file name: ";
		cin >>filename1;
		input1.open(filename1.c_str());
	}	
	cout << "Enter the second file name: ";
	cin >> filename2;
	// will ask the user a filename to open
	input2.open(filename2.c_str());

	while(input2.fail())//if the filename is not valid, ask again until user enters a valid filename
	{	
		input2.close();
		cin.ignore();
		cout <<"Enter the second file name: ";
		cin >>filename2;
		input2.open(filename2.c_str());
	}

	cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file): ";
	cin >> choice;
	cout <<"---"<<endl;

	while((choice!="1")&&(choice!="2"))
	{
		cin.ignore();
		cout << "Invalid choice" << endl;
		cout << "---"<<endl;
		cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file): ";
		cin >> choice;
		cout << "---"<<endl;
	}
	firstFileReading(input1);
	secondFileReading(input2);

	string word;

	DynIntStack temp1,temp2,copy1,copy2;
	copy(s1,copy1,s2);
	copy(s2,copy2,s1);

	if(choice=="1")
	{
		int firstCount,secondCount;

		while(!copy1.isEmpty())//reverse the copy stack
		{
			copy1.pop(word);
			temp1.push(word);	
		}
		while(!temp1.isEmpty())
		{				
			temp1.pop(word);
			if(doesExist(s2, word)&&(!doesExist(copy1, word)))// if it does exist in the other file, print to the screen
			{
				int count=0;
				firstCount=(wordCount(s1,word));
				secondCount=(wordCount(s2,word));
				if(firstCount>secondCount)
					count=secondCount;
				else
					count=firstCount;
				cout << "The word \""<< word << "\" occurred at least " << count<<  " time(s) in both files." <<endl;
			}		
			copy1.push(word);		
		}

	}
	else if(choice=="2")
	{
		int firstCount,secondCount;

		while(!copy2.isEmpty())//reverse the copy stack
		{
			copy2.pop(word);
			temp2.push(word);	
		}
		while(!temp2.isEmpty())
		{		
			temp2.pop(word);
			if(doesExist(s1,word)&&(!doesExist(copy2, word)))// if it does exist in the other file, print to the screen
			{
				int count=0;
				firstCount=(wordCount(s1,word));
				secondCount=(wordCount(s2,word));
				if(firstCount>secondCount)
					count=secondCount;
				else
					count=firstCount;

				cout << "The word \""<< word<< "\" occurred at least " << count  <<  " time(s) in both files." <<endl;
			}	
			copy2.push(word);		
		}
	}	
	return 0;
}