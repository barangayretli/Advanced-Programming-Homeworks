#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

//Baran Gayretli

int direction[6][2] = {{1,0}, {-1,0}, {0,-1}, {0,1}, {-1,-1}, {1,1}};//this array is created in order to move 1 step to the direction wanted

bool checkJokerFirstLetter(vector<vector<char> > mat, char word[], int i, int j, int dir_index)
{
	//since we miss the first letter while we search according to the correctness of first letter, this function will check if the first letter wrong and the rest is true
	unsigned int k=1;//will start searching from the index 1 because we already know the index 0 was wrong.
	for( ; i<mat.size()  && j<mat[i].size()  && i>=0  && j >=0  && word[k] != '\0'; i = i+direction[dir_index][0],  j = j+direction[dir_index][1], k++)
		if((word[k]) != (mat[i][j]))
			return false;

	if (word[k] == '\0')//if function achieves to reach to the endpoint of string without returning false, function will return true
		return true;

	return false;  
}

bool checkJoker(vector<vector<char> > mat, char word[], int i, int j, int dir_index)
{
	int wrongCount=0;//to store the wrong letters in the word
	unsigned int k=0;
	for( ; i<mat.size()  && j<mat[i].size()  && i>=0  && j >=0  && word[k] != '\0'; i = i+direction[dir_index][0],  j = j+direction[dir_index][1], k++)
		if((word[k]) != (mat[i][j]))
		{
			wrongCount++;
			if(wrongCount>1)//if there is more than 1 wrong input, return false
				return false;
		}

		if (word[k] == '\0')//if function achieves to reach to the endpoint of string without returning false, function will return true
			return true;

		return false;  
}

int wordlength(char word[])//since strlen() function does not work on gradeChecker, this function will return the length
{
	int k=0;
	while(word[k]!='\0')
	{
		k++;
	}
	return k;
}

int wordPoint(char word[], int dir)//this function will calculate the point of a particular word
{
	int score;
	int wordLength=wordlength(word);
	if(dir>=4)// if the word is diagonal, score will be multiplied by 2
	{
		score=wordLength*2;
		if(wordLength>5)// if the word is longer than 5, 2 points will be added
		{
			score+=2;
		}
		return score;
	}
	else // if the word does not lay diagonally, will be taken as it is 
	{
		score=wordLength;
		if(wordLength>5)// if the length is more than 5, 2 points will be added
		{
			score+=2;
		}
		return score;
	}
}

bool match(vector<vector<char> > mat, char word[], int i, int j, int dir_index)
{
	// the function will check the presence of a particular word
	unsigned int k=0;
	for( ; i<mat.size()  && j<mat[i].size()  && i>=0  && j >=0  && word[k] != '\0'; i = i+direction[dir_index][0],  j = j+direction[dir_index][1], k++)
		if((word[k]) != (mat[i][j]))
			return false;

	if (word[k] == '\0')
		return true;

	return false;  
}

void presenceJoker(vector<vector<char> > mat, char word[], int & totalScore)
{
	for(unsigned int i=0; i<mat.size(); i++)
		for(unsigned int j=0; j<mat[i].size(); j++)
			if ((mat[i][j]) == (word[0]))//If the first index is true, check if the rest is true w/ joker
			{
				for (int k=4; k<6; k++)
					if (checkJoker(mat, word, i, j, k))
					{
						int tempScore=0;
						totalScore+=wordPoint(word, k)-2;
						tempScore=wordPoint(word, k)-2;
						cout << word << " is found in the diagonal level. One letter was replaced by joker. It contributes " << tempScore << " points."<< endl;
						cout << "---"<<endl;
						return;
					}
			}
			else if(mat[i][j]!=word[0])//if the first index does no match, check if the rest is true
			{
				for (int k=4; k<6; k++)
					if (checkJokerFirstLetter(mat, word, i, j, k))
					{
						int tempScore=0;
						totalScore+=wordPoint(word, k)-2;
						tempScore=wordPoint(word, k)-2;
						cout << word << " is found in the diagonal level. One letter was replaced by joker. It contributes " << tempScore << " points."<< endl;
						cout << "---"<<endl;
						return;
					}
			}
			//if the function reachs that point, word is not found and point will be deducted
			cout << word << " is not found in the matrix. 5 points are deducted." << endl;
			cout <<"---"<<endl;
			totalScore-=5;
}

void presence(vector<vector<char> > mat, char word[], int & totalScore)
{
	for(unsigned int i=0; i<mat.size(); i++)
		for(unsigned int j=0; j<mat[i].size(); j++)
			if ((mat[i][j]) == (word[0]))
				for (int k=0; k<6; k++)//will check through all 6 directions
					if (match(mat, word, i, j, k))// check if the word matches with the matrix without using joker
					{	
						int tempScore=0;
						totalScore+=wordPoint(word, k);
						tempScore=wordPoint(word, k);
						if(k>=4)//diagonal
						{
							cout<< word <<" is found in the diagonal level. It contributes " << tempScore << " points." << endl;
							cout<< "---" << endl;
						}
						else if(k<=1)//column level
						{
							cout<< word <<" is found in the column level. It contributes " << tempScore << " points." << endl;
							cout<< "---" << endl;
						}
						else
						{
							cout<< word <<" is found in the row level. It contributes " << tempScore << " points." << endl;
							cout<< "---" << endl;
						}
						return;
					}

					for(unsigned int i=0; i<mat.size(); i++)
						for(unsigned int j=0; j<mat[i].size(); j++)
							if ((mat[i][j]) == (word[0]))
							{
								for (int k=4; k<6; k++)//will check diagonally if the word is present with joker
								{
									//k will be 4 and 5 which correspods to the indexes of diagonal incrementation
									presenceJoker(mat, word, totalScore);
									return;
								}
							}
							else if((mat[i][j]!=word[0]))
							{

							}
							cout << word << " is not found in the matrix. 5 points are deducted." << endl;
							cout <<"---"<<endl;
							totalScore-=5;

}

int main()
{
	string fileName;

	int countCol=0,totalScore=0;

	vector<vector<char> > mat;
	cout << "This program allows you to play a Sunday morning puzzle on your computer."<<endl;
	cout << "---" <<endl;
	cout << "Enter the matrix file name: ";
	cin >> fileName;
	// will ask the user a filename to open
	ifstream input;
	input.open(fileName.c_str());

	while(input.fail())//if the filename is not valid, ask again until user enters a valid filename
	{
		cout << "Invalid file name!"<< endl;
		cout << "---" <<endl;
		input.close();
		cout <<"Enter the matrix file name: ";
		cin >>fileName;
		input.open(fileName.c_str());
	}

	string line;
	while(getline(input, line))
	{
		stringstream ss(line);

		char ch;
		vector<char> temp;

		while(ss >> ch)//will get the line character by character
		{
			temp.push_back(ch);//character will be pushed back until there is none
		}
		mat.push_back(temp);//temporary matrix will be pushed back to the original vector we have created

	}
	for(unsigned int i=0; i<mat.size()-1; i++)
	{
		if(i==0)
		{
			countCol=mat[i].size();
		}
		if(mat[i].size()!=mat.size())
		{
			//if any of the columns does not match with the first one, program will be terminated
			cout << "The matrix does not have row equality, terminating..."<< endl;
			return 0;
		}
	}
	
	char word[100];//words are going to be stored in a char array
	
	cout <<"---"<<endl;
	cout << "Enter a word: ";
	cin >> word;

	int wordLength=wordlength(word);
	
	if(wordLength>=3)//call the function for the first time use
	{
		presence(mat, word, totalScore);
	}
	else if(wordLength<3)
	{
		cout << "---"<<endl;
		cout << "Game has ended." << endl;
		cout << "Total score of the words: " << totalScore << endl;
		return 0;
	}

	while(wordLength>=3)
	{
		// will ask the user to enter a word until the user enters a word that has length of 2 or less.
		cout << "Enter a word: ";
		cin >> word;
		int lengthofWord=wordlength(word);
		if(lengthofWord>=3)
		{
			presence(mat, word, totalScore);
		}
		else if(lengthofWord<3)
		{
			cout << "---"<<endl;
			cout << "Game has ended." << endl;
			cout << "Total score of the words: " << totalScore << endl;//totalscore will be shown and the game will be terminated
			return 0;
		}
	}
}