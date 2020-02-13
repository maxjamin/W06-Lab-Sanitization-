#include <iostream>
#include <string>
#include <locale> 
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
* Inputs: output string, username string, password string
* Summary:
*	Creates an SQL query with the provided username and password
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
* 	removeSubstring()
* Inputs: Main string and a substring
* Summary: 
*	Removes every instance of a substring from the main string
*   String Erase from http://www.cplusplus.com/reference/string/string/erase/
*   String Find from http://www.cplusplus.com/reference/string/string/find/
*************************************************************************/
std::string removeSubstring(std::string main, std::string substring)
{
	std::string::size_type found = main.find(substring);
	if (found != std::string::npos)
	{
		// Remove this instance
		main.erase(found, substring.length());

		// Remove other instances
		main = removeSubstring(main, substring);
	}

	return main;
}

/***********************************************************************
* Function:
*   weakTautologyMitigation()
* Inputs: output string, username string, password string
* Summary:
*   Creates an SQL query with the provided username and password
*	using a weak mitigation strategy to Tautology attacks
 ************************************************************************/
int weakTautologyMitigation(std::string *output, std::string username, std::string password)
{
	if(username == "" || password == "")
		return 1;
	
	// Check for and remove keyword 'OR'
	// Username check
	username = removeSubstring(username, "OR");
	username = removeSubstring(username, "or");

	// Password check
	password = removeSubstring(password, "OR");
	password = removeSubstring(password, "or");

	*output = "SELECT authenticate FROM passwordList WHERE name='" + 
	username  + "' and passwd='" + password + "';";
	return 0;
}

/***********************************************************************
* Function:
*    weakUnionMitigation()
* Inputs: output string, username string, password string
* Summary:
*   Creates an SQL query with the provided username and password
*	using a weak mitigation strategy to Union attacks
 ************************************************************************/
int weakUnionMitigation(std::string *output, std::string username, std::string password)
{
	if(username == "" || password == "")
		return 1;

	// Check for and remove keyword 'UNION'
	// Username check
	username = removeSubstring(username, "UNION");
	username = removeSubstring(username, "union");

	// Password check
	password = removeSubstring(password, "UNION");
	password = removeSubstring(password, "union");

	*output = "SELECT authenticate FROM passwordList WHERE name='" + 
	username  + "' and passwd='" + password + "';";
	return 0;
}

/***********************************************************************
* Function:
*    weakAdditionalStatementMitigation()
* Inputs: output string, username string, password string
* Summary:
*   Creates an SQL query with the provided username and password
*	using a weak mitigation strategy to Additional Statement attacks
 ************************************************************************/
int weakAdditionalStatementMitigation(std::string *output, std::string username, std::string password)
{
	if(username == "" || password == "")
		return 1;

	// Check for and remove ';'
	// Username check
	username = removeSubstring(username, ";");

	// Password check
	password = removeSubstring(password, ";");

	*output = "SELECT authenticate FROM passwordList WHERE name='" + 
	username  + "' and passwd='" + password + "';";
	return 0;
}

/***********************************************************************
* Function:
*    weakCommentMitigation()
* Inputs: output string, username string, password string
* Summary:
*   Creates an SQL query with the provided username and password
*	using a weak mitigation strategy to Comment attacks
 ************************************************************************/
int weakCommentMitigation(std::string *output, std::string username, std::string password)
{
	if(username == "" || password == "")
		return 1;

	// Check for and remove '--'
	// Username check
	username = removeSubstring(username, "--");

	// Password check
	password = removeSubstring(password, "--");

	*output = "SELECT authenticate FROM passwordList WHERE name='" + 
	username  + "' and passwd='" + password + "';";
	return 0;
}

/***********************************************************************
* Function:
* 	whitelist()
* Inputs: String to parse
* Summary:
*	Removes all characters that are not part of our whitelist
* 	isalnum from http://www.cplusplus.com/reference/locale/isalnum/
*************************************************************************/
std::string whitelist(std::string string)
{
	for (int i = 0; i < string.length(); i++)
	{
		if (!std::isalnum(string[i]))
		{
			if (string[i] != '_' && string[i] != '.')
			{
				string.erase(i,1);
				i--;
			}
		}
	}

	return string;
}

/***********************************************************************
* Function:
*    strongMitigation()
* Inputs: output string, username string, password string
* Summary:
*   Creates an SQL query with the provided username and password
*	using a whitelist, a strong mitigation strategy
 ************************************************************************/
int strongMitigation(std::string *output, std::string username, std::string password)
{
	if(username == "" || password == "")
		return 1;

	// Put strings through our whitelist
	// Alphanumeric characters only (but '_' and '.' are allowed)
	username = whitelist(username);
	password = whitelist(password);

	*output = "SELECT authenticate FROM passwordList WHERE name='" + 
	username  + "' and passwd='" + password + "';";
	return 0;
}

/***********************************************************************
* Function:
* 	validInputTest()
* Inputs: 
* Summary:
*************************************************************************/
int validInputTest(int queryGeneration(std::string *input, std::string username, std::string password))
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
int attackInputTest(int queryGeneration(std::string *input, std::string username, std::string password))
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
		username = "BILL_4569"; password="password'; INSERT INTO users(name, id) VALUES 'sam', '0";
		queryGeneration(&sqlQuery, username, password);
		std::cout << "sql Query 5: " << sqlQuery << "\n";
		/*Test case 6 Example valid username and password*/
		username = "BILL_4569"; password="password'; INSERT INTO product(name, id, price) VALUES 'intel Core i9', '345', '0.01";
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

	std::cout << "Weak Tautology Mitigation:\n";
	validInputTest(weakTautologyMitigation);
	attackInputTest(weakTautologyMitigation);

	std::cout << "\nWeak Union Mitigation:\n";
	validInputTest(weakUnionMitigation);
	attackInputTest(weakUnionMitigation);

	std::cout << "\nWeak Additional Statement Mitigation:\n";
	validInputTest(weakAdditionalStatementMitigation);
	attackInputTest(weakAdditionalStatementMitigation);

	std::cout << "\nWeak Comment Mitigation:\n";
	validInputTest(weakCommentMitigation);
	attackInputTest(weakCommentMitigation);

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

	validInputTest(strongMitigation);
	attackInputTest(strongMitigation);

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
	validInputTest(queryGeneration);
	attackInputTest(queryGeneration);

	weakMitigationTest();
	strongMitigationTest();
}	