#include <iostream>
#include <string>
/***********************************************************************
* Program:
*    Lab 06, Sanitization
*    Brother Helfrich, CS 370
* Author:
*    John Miller
*    Bretton Steiner
*	 Ben Smith
*    Tyler Starr
*
* Summary:
*    Enter a brief description of your program here!
 ************************************************************************/

/***********************************************************************
* Function:
* 	queryGeneration()
* Inputs: 
* Summary:
*************************************************************************/
int queryGeneration(std::string *output, std::string username, std::string password)
{
	if(username == "" || password == "")
		return 1;

	*output = "SELECT authenticate FROM passwordList WHERE name='" + 
	username  + "' and passwd='" + password + "';";
	return 0;
}

/***********************************************************************
* Function:
*    main()
* Inputs: string pointer input, string prompt
* Summary:
*    ask for the user input
 ************************************************************************/
 void getUserInput(std::string *input, std::string promptString)
 {
 	printf(" %s",promptString.c_str());
 	getline(std::cin, *input);
 }

/***********************************************************************
* Function:
* 	validInputTest()
* Inputs: 
* Summary:
*************************************************************************/
int validInputTest()
{
	std::string username;
	std::string password;
	std::string sqlQuery;

	/*Test case 1  Example valid username and password*/
	username = "bill"; password="test123";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query " << sqlQuery << "\n";
}

/***********************************************************************
* Function:
*    main()
* Inputs: none
* Summary:
*    Driver function for the program.
 ************************************************************************/
int main()
{
	validInputTest();


}	