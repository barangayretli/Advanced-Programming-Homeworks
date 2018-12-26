#ifndef _matrixclass
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#define _matrixclass

//BARAN GAYRETLI CS204 HW4-SUMMER 2018

template <class type>
class Matrix2D {
	friend Matrix2D<type>operator +<type>( Matrix2D<type> & lhs,  Matrix2D<type> & rhs);//+ operator prototype
	friend istream& operator>> <type>(istream&in, Matrix2D<type>& rhs);//>> operator prototype
	friend ostream& operator<< <type>(ostream&os, Matrix2D<type>& rhs);//<< operator prototype
private: 
	int rows, cols;
	type ** data;
public:
	Matrix2D<type>();//deafult constructor
	Matrix2D<type>(int r, int c);
	Matrix2D<type>(Matrix2D<type>&a);//deep copy constructor
	~Matrix2D<type>();//destructor
	int GetIndex(int i, int j);
	void SetIndex(int i, int j, type val);
	Matrix2D<type>& Matrix2D<type>::operator  += ( Matrix2D<type> & rhs);//+= operator
	Matrix2D<type>& Matrix2D<type>::operator = (Matrix2D<type>&rhs);//assignment operator
};

template <class type>
Matrix2D<type>::Matrix2D()// default constructor
{
	rows=0;
	cols=0;
	data = NULL;
}

template <class type>
Matrix2D<type>::Matrix2D(int r, int c)
{
	rows=r;
	cols=c;
	data = new type* [r]; 

	for(int i = 0; i<r; i++) 
		data[i] = new type[c];
}

template <class type>
Matrix2D<type>::Matrix2D(Matrix2D<type>&a)// deep copy constructor
{
	rows=a.rows;
	cols=a.cols;

	data = new type* [rows]; // memory allocatiion of deep copy

	for(int i = 0; i<rows; i++) 
		data[i] = new type[cols];

	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
		{
			data[i][j]=a.data[i][j];//assigning parameter to the copy
		}


}

template <class type>
Matrix2D<type>::~Matrix2D()// destructor to avoid memory leak
{
	int r=rows;

	{
		for (int i = 0; i < r; i++)
			delete[] data[i];
		delete[] data;
	}
	data = NULL;
}

template <class type>
int Matrix2D<type>::GetIndex(int i, int j)
{
	return data[i][j];
}

template <class type>
void Matrix2D<type>::SetIndex(int i, int j, type value)
{
	data[i][j] = value;
}

template <class type>
Matrix2D<type> & Matrix2D<type>::operator  += ( Matrix2D<type> & rhs)
{


	for (int i=0; i < rows  ; i++) 
	{
		for (int j=0; j < cols; j++) 
		{
			this->data[i][j]+=rhs.data[i][j];
		}

	}
	return *this;

}

template <class type>
Matrix2D<type> operator  + (   Matrix2D<type>  & lhs, Matrix2D<type> & rhs)
{
	
	Matrix2D<type> temp(rhs.rows,rhs.cols);// deep copy constructor called

	for (int i=0; i < rhs.rows ; ++i) 
	{
		for (int j=0; j < rhs.cols; ++j) 
		{
			temp.data[i][j]=lhs.data[i][j]+rhs.data[i][j];
		}

	}
	return temp;
}

template <class type>
istream&operator  >>(istream&in, Matrix2D<type>&x)//istream operator
{
	bool alfa=true;
	string line;
	type a;
	int row=0;
	int col=0;
	while(getline(in,line))// take the lines until there is no line
	{
		stringstream ss(line);
		while(ss>>a)
		{
			if(alfa)//in order to avoid multiple incrementation
				col++;// col count
		}
		alfa=false;
		row++;// row count
	}
	x.rows=row;
	x.cols=col;
	x.data = new( type* [x.rows]); //memory allocation

	for(int i = 0; i<x.rows; i++) 
		x.data[i] = new type[x.cols];
	in.clear();
	in.seekg(0);// going back to the beginning of the file

	row=0;
	col=0;

	while(getline(in,line))// reading the file and assigning the variable to the matrix
	{
		stringstream ss(line);
		while(ss>>a)
		{
			x.data[row][col]=a;
			col++;
		}
		col=0;
		row++;

	}
	return in;
}

template <class type>
ostream &operator  << (ostream &os, Matrix2D<type> &alfa) //ostream operator
{
	for (int i=0; i < alfa.rows; i++) 
	{
		for (int j=0; j < alfa.cols; j++) 
		{
			os << setw(5) <<alfa.data[i][j]; // leaving 5 spaces empty
		}
		os << '\n';
	}
	return os;
}

template <class type>
Matrix2D<type> & Matrix2D<type>::operator  = ( Matrix2D<type> & rhs)// assignment operator
{
	this->~Matrix2D<type>();//destructor called

	this->data = new( type* [rhs.rows]); // memory allocation is done

	for(int i = 0; i<rhs.rows; i++) 
		this->data[i] = new type[rhs.cols];

	for (int i=0; i < rows  ; i++) 
	{
		for (int j=0; j <cols; j++) 
		{
			this->data[i][j]=rhs.data[i][j];// assigning the data
		}
	}
	return *this;
}

#endif
