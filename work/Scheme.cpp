#include "Scheme.h"

using namespace std;

//Default, empty constructor
Scheme::Scheme() {}

//Print 10 rows from entire matrix to screen
// From 0.0 to 0.5 with step 0.1
void Scheme::PrintResult()
{
	//equation computing step for each size matrix 
	int step = (this->sizeT - 1)*0.1;

	cout << "Steps [from 0.0 sec to 0.5 sec] \n";
	for (int i = 0; i < this->sizeT; i = i + step)
	{
		cout << "\n";
		cout << "[" << i * this->deltaT << "]";
		for (int j = 0; j < this->sizeX; j++)
		{
			cout << " " << this->matrix[i][j];
		}
		
		//delay for slower displaying rows in the console
		cout << "\n";
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	cout << "\n";
}

//Compute initial condition
void Scheme::InitialCondition()
{

	for (int x = 0; x < this->sizeX; x++)
	{
		if (x >= 0 && x <= 10)
		{
			this->matrix[0][x] = 0;
		}
		if (x >= 10 && x <= 22)
		{
			this->matrix[0][x] = 100 * (sin((this->PI)*((((double)x * 5) - 50) / 60)));
		}
		if (x >= 22 && x < this->sizeX)
		{
			this->matrix[0][x] = 0;
		}
	}
}

//Compute boundry condition
void Scheme::BoundryCondition()
{
	for (int t = 0; t < this->sizeT; t++)
	{
		this->matrix[t][0] = 0;
		this->matrix[t][this->sizeX-1] = 0;
	}
}

//Compute analytical solution 
string Scheme::AnalyticalSolution(double defaultDeltaT)
{
	if (defaultDeltaT == 0)
	{
		InsertDeltaT();
	}
	else
	{
		this->deltaT = defaultDeltaT;
	}
	ComputeSizeOfMatrix(0);
	InitialCondition();
	BoundryCondition();

	double T;
	for (int i = 0; i < this->sizeT; i++)
	{
		T = i * deltaT;
		for (int x = 0; x < this->sizeX; x++)
		{
			double Y = 5 * x;
			if (Y <= 110 + (250 * T) && Y >= 50 + 250 * T)
			{
				this->matrix[i][x] = 100 * (sin((this->PI)*
					((Y - 50 - (250 * T)) / 60)));
			}
		}
	}
	//------------------------------------------------------//

	return __func__; //useful for method SaveResultIntoFiles
}

//Compute three different norms, which have been implemented in Matrix class
void Scheme::ComputeNorms(Matrix m1, Matrix m2)
{
	Matrix result = Matrix(m1.getNrows(), m2.getNcols());
	result = m1 - m2;
	double size = m2.getNcols()*m2.getNrows();
	
	cout << "--NORMS--";
	cout<<"\n One norm: "<<result.one_norm()/size;
	cout<<"\n Second norm: "<<result.two_norm()/size;
	cout<<"\n Uniform norm: "<<result.uniform_norm()/size;
	cout << "\n";
}

//Friend method used in InsertDeltaT method
bool IsDouble(string input)
{
	//Loop of the size of the input
	if (input[0] == '0' && input[1] == '.')
	{
		for (int i = 0; i < input.size(); i++)
		{
			if (!isdigit(input[i]) && input[i] != '.')
				return 0;
		}
	}
	else
		return 0;

	return 1;
}

//Prompt user to input deltaT
void Scheme::InsertDeltaT()
{
	string tmpDeltaT;
	cout << "Insert preffered time step: ";
	getline(cin, tmpDeltaT);
	while (!IsDouble(tmpDeltaT) || tmpDeltaT == "")
	{
		getline(cin, tmpDeltaT);
	}
	this->deltaT = stod(tmpDeltaT);
}

//Compute size of matrix
void Scheme::ComputeSizeOfMatrix(bool ifPrinted)
{
	//Values from excercise
	this->deltaX = 5.0;		//5 meters 
	const double x = 400;	//Domain is xE[0;400] meters
	const double t = 0.5;	//t goes from 0.0 to 0.5sec

	//compute sizeX (columns) and sizeT (rows), this is size of matrix
	this->sizeX = (x / deltaX) + 1;
	this->sizeT = (t / deltaT) + 1;

	//Create&return Matrix with proper size filled by zeros
	Matrix m(this->sizeT, this->sizeX);
	this->matrix = m;

	//Print information about size of creted matrix
	if (ifPrinted == 1)
	{
		cout << "Size of matrix: \n" << " -columns: " << this->matrix.getNcols() << "\n -rows: " << this->matrix.getNrows() << endl;
	}

	//delay in console
	this_thread::sleep_for(chrono::milliseconds(1000));
}

//Save results into file with different name depends on parameters.
void Scheme::SaveResultIntoFiles(double deltaT, string schemeName)
{
	try
	{
		//name of file is created from name of executed scheme and value of deltaT
		string fileName = schemeName + "_" + to_string(deltaT);

		ofstream f;
		f.open(fileName + ".xlsx");
		for (int t = 0; t < this->sizeT; t++)
		{
			for (int x = 0; x < this->sizeX; x++)
			{
				f << fixed << setprecision(5) << this->matrix[t][x] << " ";
			}
			f << endl;
		}
		cout <<"\n"<< schemeName << " - results have been saved as: " << fileName << " in project folder.\n\n";
	}
	catch (const exception& e)
	{
		cerr << "std::exception caught" << endl;
		cerr << "Type: " << typeid(e).name() << endl;
		cerr << "What: " << e.what() << endl;
	}

}

//Accessors---------------------//
//Get Matrix matrix.
Matrix Scheme::GetMatrix()
{
	return this->matrix;
}

//Get value of deltaT.
double Scheme::GetDeltaT()
{
	return this->deltaT;
}
//------------------------------//
