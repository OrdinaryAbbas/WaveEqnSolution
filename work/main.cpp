#include<iostream>
#include "matrix.h"			//matrix class, inspired on c++ course
#include "Scheme.h"			//mother class
#include "ExplicitScheme.h" //inherited class
#include "ImplicitScheme.h" //inherited class

#include <chrono>

using namespace std;

int main()
{
	//Variables for SaveResultIntoFiles method
	//name of file - type of scheme
	string schemeName = " ";
	//name of file - deltaT
	double deltaT = 0.0;

	//objects ExplicitScheme, ImplicitScheme and Scheme classes
	ExplicitScheme eS, eS2;
	ImplicitScheme iS, iS2;
	Scheme s;
	
	int choice;
	// display menu and read user's choice
	cout << "Select a method: " << endl;
	cout << "1. Explicit FTBS" << endl;
	cout << "2. Lax-Wendroff" << endl;
	cout << "3. Implicit FTBS" << endl;
	cout << "4. Explicit FTCS" << endl;
	cout << "5. Analytical" << endl;
	cout << "Enter your choice (1-5): ";
	cin >> choice;

    // process user's choice
    	if(choice == 1) 
	{
		cout << "You selected Explicit FTBS" << endl;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		schemeName = eS.ExplicitUpWindFTBS();

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "\nTime = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;
			
		deltaT = eS.GetDeltaT();

		//Print results
		eS.PrintResult();
			
		//Norms
		s.AnalyticalSolution(deltaT);
		s.ComputeNorms(s.GetMatrix(), eS.GetMatrix());

		//Save results
		eS.SaveResultIntoFiles(deltaT, schemeName);

		//Destructors
		eS.~ExplicitScheme();
		s.~Scheme();
	}
	else if(choice == 2)
	{
            	cout << "You selected Lax-Wendroff" << endl;
	    	cout << "EXPLICIT SCHEME - LAX-WENDROFF \n";
	    	schemeName = eS2.ExplicitLaxWandroff();
	    	deltaT = eS2.GetDeltaT();
	    	//Print results
	    	eS2.PrintResult();
	    	//Norms
	    	s.AnalyticalSolution(deltaT);
	    	s.ComputeNorms(s.GetMatrix(), eS2.GetMatrix());
	    	//Save results
	    	eS2.SaveResultIntoFiles(deltaT, schemeName);
	    	//Destructors
	    	eS2.~ExplicitScheme();
		s.~Scheme();
	}
	else if(choice == 3)
	{
            	cout << "You selected Implicit FTBS" << endl;
            	cout << "IMPLICIT SCHEME - UP WIND, FTBS \n";
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		schemeName = iS.ImplicitUpWindFTBS();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "\nTime = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;


		deltaT = iS.GetDeltaT();

		//Print results
		iS.PrintResult();
		//Norms
		s.AnalyticalSolution(deltaT);
		s.ComputeNorms(s.GetMatrix(), iS.GetMatrix());

		//Save results
		iS.SaveResultIntoFiles(deltaT, schemeName);

		//Destructors
		iS.~ImplicitScheme();
		s.~Scheme();
        }
	else if(choice == 4)
	{
		cout << "You selected Explicit FTCS" << endl;
		cout << "IMPLICIT SCHEME - FTCS \n";
		schemeName = iS2.ImplicitFTCS();
		deltaT = iS2.GetDeltaT();
		//Print results
		iS2.PrintResult();

		//Norms
		s.AnalyticalSolution(deltaT);
		s.ComputeNorms(s.GetMatrix(), iS2.GetMatrix());
			
		//Save results
		iS2.SaveResultIntoFiles(deltaT, schemeName);
		//Destructors
		iS2.~ImplicitScheme();
		s.~Scheme();
	}
        else if(choice == 5)
	{
            	cout << "You selected Analytical" << endl;
            	cout << "ONLY ANALYTICAL SOLUTION \n";
		schemeName = s.AnalyticalSolution();
		deltaT = s.GetDeltaT();
		s.PrintResult();
		s.SaveResultIntoFiles(deltaT, schemeName);
		s.~Scheme();
	}
	else
	{
		cout << "Invalid Scheme" <<endl;
	}
	return 0;
}

