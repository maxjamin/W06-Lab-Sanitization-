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

	std::cout << "Valid Input Test: \n\n";

	/*Test case 1  Example valid username and password*/
	username = "bill"; password="testpassword";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 1: " << sqlQuery << "\n";

	/*Test case 2  Example valid username and password*/
	username = "JAMES"; password="TESTPASSWORD";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 2: " << sqlQuery << "\n";

	/*Test case 3  Example valid username and password*/
	username = "james_Jones"; password="test_system";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 3: " << sqlQuery << "\n";

	/*Test case 4  Example valid username and password*/
	username = "568"; password="12784";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 4: " << sqlQuery << "\n";

	/*Test case 5  Example valid username and password*/
	username = "bill"; password="test3456";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 5: " << sqlQuery << "\n";

	/*Test case 6  Example valid username and password*/
	username = "bill_s"; password="test__3456";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 6: " << sqlQuery << "\n";

	/*Test case 7  Example valid username and password*/
	username = "SaM"; password="gHoStMaN";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 7: " << sqlQuery << "\n";

	/*Test case 8  Example valid username and password*/
	username = "JOHN-DOE"; password="TEST-PASSWORD";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 8: " << sqlQuery << "\n";

	/*Test case 9  Example valid username and password*/
	username = "John-doe"; password="test-password";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 9: " << sqlQuery << "\n";

	/*Test case 10  Example valid username and password*/
	username = "BILL4569"; password="TESTPASSWORD12345";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 10: " << sqlQuery << "\n";

	/*Test case 11  Example valid username and password*/
	username = "BILL.GHOST"; password="TEST.PASSWORD";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 11: " << sqlQuery << "\n";

	/*Test case 12  Example valid username and password*/
	username = "BILL_4569"; password="TESTPASSWORD_12345";
	queryGeneration(&sqlQuery, username, password);
	std::cout << "sql Query 12: " << sqlQuery << "\n\n";
	return 0;
}

/***********************************************************************
* Function:
* 	attackInputTest()
* Inputs: 
* Summary:
*************************************************************************/
int attackInputTest()
{
	std::string username;
	std::string password;
	std::string sqlQuery;

	std::cout << "Attack Input Test: \n\n";


	/*Tautology Attack*/
		/*Test case 1 Example valid username and password*/
		username = "BILL_4569"; password="password' OR 'x' = 'x";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 1: " << sqlQuery << "\n";
		/*Test case 2 Example valid username and password*/
		username = "BILL_4569"; password="password' OR '1' = '1";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 2: " << sqlQuery << "\n";

	/*Union Query Attack*/
		/*Test case 3 Example valid username and password*/
		username = "BILL_4569"; password="password' UNION SELECT authenticate FROM passwordList";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 3: " << sqlQuery << "\n";
		/*Test case 4 Example valid username and password*/
		username = "BILL_4569"; password="password' UNION SELECT name FROM passwordList";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 4: " << sqlQuery << "\n";

	/*Additional Statement Attack*/
		/*Test case 5 Example valid username and password*/
		username = "BILL_4569"; password="password' INSERT INTO users(name, id) VALUES 'sam', '0";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 5: " << sqlQuery << "\n";
		/*Test case 6 Example valid username and password*/
		username = "BILL_4569"; password="password' INSERT INTO product(name, id, price) VALUES 'intel Core i9', '345', '0.01";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 6: " << sqlQuery << "\n";
	/*Comment Attack*/
		/*Test case 7 Example valid username and password*/
		username = "BILL_4569'; --"; password="password";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 7: " << sqlQuery << "\n";
		/*Test case 8 Example valid username and password*/
		username = "freindsUserName'; --"; password="password";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 8: " << sqlQuery << "\n";

		return 0;
}
/***********************************************************************
* Function:
*    weakMitigationTest()
* Inputs: none
* Summary:
*    Driver function for the program.
 ************************************************************************/
int weakMitigationTest()
{
	std::cout << "\nWeak Mitigation Test: \n\n";
	return 0;
}
/***********************************************************************
* Function:
*    strongMitigationTest()
* Inputs: none
* Summary:
*    Driver function for the program.
 ************************************************************************/
int strongMitigationTest()
{
	std::cout << "\nStrong Mitigation Test: \n\n";

	return 0;
}
/***********************************************************************
* Function:
*    weakMitigationProtection()
* Inputs: none
* Summary:
*    Driver function for the program.
 ************************************************************************/
int weakMitigationProtection(std::string *input)
{
	return 0;
}

/***********************************************************************
* Function:
*    strongerMitigationProtection()
* Inputs: none
* Summary:
*    Driver function for the program.
 ************************************************************************/
int strongerMitigationProtection(std::string *input)
{
	return 0;
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
	attackInputTest();

	weakMitigationTest();
	strongMitigationTest();

}	