/*

Project 5 by Noah Blount



*/

#include <iostream>
#include <iomanip>
#include <string> //including stuff to use
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

//-----------------------------------------------------------------------

class line
{
private:
	int accNum;
	int accDeb; //initializing vars with class
	int accCred;
	//-----------------------------------------------------------------------
public:

	line(int num, int deb, int cred)
	{
		accNum = num;
		accDeb = deb; //constructorzzzzzzzzz
		accCred = cred;
	}
	//-----------------------------------------------------------------------
	int getAccNum()
	{
		return accNum; //accessor
	}
	//-----------------------------------------------------------------------
	int getAccDeb()
	{
		return accDeb; //accessor
	}
	//-----------------------------------------------------------------------
	int getAccCred()
	{
		return accCred; //accessor
	}
	//-----------------------------------------------------------------------
};

//-----------------------------------------------------------------------

class header
{
private:

	string journDate;
	string journID;
	string journMemo; //more high-clas vars
	vector <line> journLines;
	bool journValid;
	//-----------------------------------------------------------------------
public:

	header(string date, string memo, string id)
	{
		journDate = date;
		journMemo = memo; //more constructorzzzzzz
		journID = id;
	}
	//-----------------------------------------------------------------------
	void setNextLine(int account, int deb, int cred)
	{
		journLines.push_back(line(account, deb, cred)); //a mutator (wow!)
	}
	//-----------------------------------------------------------------------
	vector<line> getLine()
	{
		return journLines; //another one of those accessors
	}
	//-----------------------------------------------------------------------
	int getAccNum(int index)
	{
		return journLines[index].getAccNum(); //and another one of those accessors
	}
	//-----------------------------------------------------------------------
	int getAccDeb(int index)
	{
		return journLines[index].getAccDeb(); //and another another one of those accessors
	}
	//-----------------------------------------------------------------------
	int getAccCred(int index)
	{
		return journLines[index].getAccCred(); //one more
	}
	//-----------------------------------------------------------------------
	string getDate()
	{
		return journDate; //just kidding theres more than one more
	}

	void setDate(string date)
	{
		journDate = date; //but thre are also more muuutators yay
	}
	//-----------------------------------------------------------------------
	string getID()
	{
		return journID; //guess what this is?
	}

	void setID(string id)
	{
		journID = id; //this right here is a wild mutator, in its natural habitat
	}
	//-----------------------------------------------------------------------
	string getMemo()
	{
		return journMemo; //accessors: say it five times fast cause they keep on comin
	}

	void setMemo(string memo)
	{
		journMemo = memo; //look! A mutator-tot, freshly cooked
	}
	//-----------------------------------------------------------------------
	bool getValid()
	{
		return journValid; //this is the last one in this class
	}

	void setValid(bool valid)
	{
		journValid = valid; //final mutator
	}
	//-----------------------------------------------------------------------
};

//-----------------------------------------------------------------------

class entry
{
private:

	int accNum;
	string accName; //variables, but classier
	string accType;
	int accBal;
	//-----------------------------------------------------------------------
public:

	entry()
	{
		accNum = 9999;
		accName = "NULL";
		accType = "NULL"; //oooh a default constructor, havent seen one of these yet
		accBal = 0;
	}

	entry(int num, string name, string type)
	{
		accNum = num;
		accName = name;
		accType = type; //plus a non-default one too for good measure
		accBal = 0;
	}
	//-----------------------------------------------------------------------
	int getAccNum()
	{
		return accNum; //say it with me now: accessor
	}
	//-----------------------------------------------------------------------
	string getAccName()
	{
		return accName; //and another one
	}
	//-----------------------------------------------------------------------
	string getAccType()
	{
		return accType; //and another one
	}
	//-----------------------------------------------------------------------
	int getAccBal()
	{
		return accBal; //and another one
	}

	void changeAccBal(int num)
	{
		accBal += num; //with a plus one mutator
	}
	//-----------------------------------------------------------------------
};

//-----------------------------------------------------------------------

void initializeAccounts(entry dataMatrix[])
{
	dataMatrix[0] = entry(1000, "Sales", "Revenue");
	dataMatrix[1] = entry(1010, "Services", "Revenue");
	dataMatrix[2] = entry(1020, "Warranties", "Revenue"); //setting stuff up
	dataMatrix[3] = entry(1030, "Refunds", "Revenue");
	dataMatrix[4] = entry(1040, "Shipping", "Revenue");
	//-----------------------------------------------------------------------
	dataMatrix[5] = entry(6000, "Travel", "Expense");
	dataMatrix[6] = entry(6005, "Meals", "Expense");
	dataMatrix[7] = entry(6010, "Salaries", "Expense");
	dataMatrix[8] = entry(6020, "Supplies", "Expense"); //setting more stuff up
	dataMatrix[9] = entry(6050, "Rent", "Expense");
	dataMatrix[10] = entry(6060, "Repairs", "Expense");
	//-----------------------------------------------------------------------
	dataMatrix[11] = entry(2000, "Accounts Receivable", "Balance Sheet");
	dataMatrix[12] = entry(4000, "Accounts Payable", "Balance Sheet"); //setting more stuff up, but less than last time
}

//-----------------------------------------------------------------------

void processJEFile(vector <header>& data)
{
	string tempDate;
	string tempMemo;
	string tempID;
	int tempDebit;
	int tempCredit; //wow thats a lot of vars
	int tempAccNum;
	int tempLineNum;
	int vecIndex = -1;
	//-----------------------------------------------------------------------
	string strInput;
	ifstream input;
	cout << "What file would you like to load? (Include the .txt)\n"; //asking the user for what file they want to open
	cin >> strInput;
	input.open(strInput.c_str());
	while (input.fail())
	{
		cout << "Error, file not found. Please enter a new file:\n\n";
		cout << "What file would you like to load? (Include the .txt)\n"; //in case the user doesn't know what they are looking for
		cin >> strInput;
		input.open(strInput.c_str());
	}
	//-----------------------------------------------------------------------
	cout << "Loading journal... \n";
	while (!input.eof())
	{
		input >> tempLineNum;
		//-----------------------------------------------------------------------
		if (tempLineNum == 0)
		{
			input >> tempDate >> tempMemo >> tempID;
			data.push_back(header(tempDate, tempMemo, tempID)); //for the first line in every entry, loading in the date, memo, and id
			vecIndex += 1;
		}
		//-----------------------------------------------------------------------
		else
		{
			input >> tempDebit >> tempCredit >> tempAccNum; //loading in the line data for every other nonzero jounal line
			data[vecIndex].setNextLine(tempAccNum, tempDebit, tempCredit);
		}
		//-----------------------------------------------------------------------
	}
	//-----------------------------------------------------------------------
	input.close();
	cout << "Done!\n\nEntries loaded...\n\n\n\n";
}

//-----------------------------------------------------------------------

void validateTransactions(vector <header>& data, entry dataMatrix[])
{
	int totCred;
	int totDeb; //not as much variables this time
	cout << "Validating Journals...\n";
	//-----------------------------------------------------------------------
	for (int i = 0; i < data.size(); i++)
	{
		totCred = 0;
		totDeb = 0;
		vector <line> transactions = data[i].getLine(); //setting things up in the for loop like a cool kid
		int numLines = data[i].getLine().size();
		//-----------------------------------------------------------------------
		for (int j = 0; j < numLines; j++)
		{
			int tempAccNum = transactions[j].getAccNum();
			int tempCredit = transactions[j].getAccCred(); //setting things up in a nested for loop, like a cooler cool kid
			int tempDebit = transactions[j].getAccDeb();
			totCred += tempCredit;
			totDeb += tempDebit;
			//-----------------------------------------------------------------------
			if (tempDebit != 0 && tempCredit != 0)
			{
				data[i].setValid(false); //sometimes, everybody could use a bit of validation
				cout << "Credits and debits cannot both be nonzero on any given transaction\n" << data[i].getID() << " is invalid!\n\n";
			}
			//-----------------------------------------------------------------------
			if (tempDebit < 0)
			{
				data[i].setValid(false); //more validating
				cout << "Debit cannot be negative\n" << data[i].getID() << " is invalid!\n\n";
			}
			//-----------------------------------------------------------------------
			if (tempCredit < 0)
			{
				data[i].setValid(false); //negative credit ain't possible
				cout << "Credit cannot be negative\n" << data[i].getID() << " is invalid!\n\n";
			}
			//-----------------------------------------------------------------------
			bool match = false;
			for (int k = 0; k < 13; k++)
			{
				if (tempAccNum == dataMatrix[k].getAccNum()) //what's a for loop like you doing all the way down here?
				{
					match = true;
				}
			}
			//-----------------------------------------------------------------------
			if (!match)
			{
				data[i].setValid(false); //gotta make sure the numbers line up
				cout << "Invalid account number\n" << data[i].getID() << " is invalid!\n\n";
			}
			//-----------------------------------------------------------------------
		}
		//-----------------------------------------------------------------------
		if (totCred != totDeb)
		{
			data[i].setValid(false); //balancing the books
			cout << "Total debits does not match total credits\n" << data[i].getID() << " is invalid!\n\n";
		}
	}
}

//-----------------------------------------------------------------------

void addToAccounts(vector <header> data, entry dataMatrix[])
{
	for (int i = 0; i < data.size(); i++) //oh boy, time for some numbers
	{
		//-----------------------------------------------------------------------
		bool valid = data[i].getValid();
		if (valid)
		{
			vector <line> transactions = data[i].getLine(); //settin up some vectors
			int numLines = data[i].getLine().size();
			//-----------------------------------------------------------------------
			for (int j = 0; j < numLines; j++)
			{
				int lineAccNum = transactions[j].getAccNum();
				int lineCredit = transactions[j].getAccCred(); //more vars in a nested for loop, with an if statement to shake things up a little
				int lineDebit = transactions[j].getAccDeb();
				//-----------------------------------------------------------------------
				if (lineAccNum == 1000)
				{
					dataMatrix[0].changeAccBal(lineCredit); //adding funds to account 1
					dataMatrix[0].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 1010)
				{
					dataMatrix[1].changeAccBal(lineCredit); //adding funds to account 2
					dataMatrix[1].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 1020)
				{
					dataMatrix[2].changeAccBal(lineCredit); //adding funds to account 3
					dataMatrix[2].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 1030)
				{
					dataMatrix[3].changeAccBal(lineCredit); //adding funds to account 4
					dataMatrix[3].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 1040)
				{
					dataMatrix[4].changeAccBal(lineCredit); //adding funds to account 5
					dataMatrix[4].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 6000)
				{
					dataMatrix[5].changeAccBal(lineCredit); //adding funds to account 6
					dataMatrix[5].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 6005)
				{
					dataMatrix[6].changeAccBal(lineCredit); //adding funds to account 7
					dataMatrix[6].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 6010)
				{
					dataMatrix[7].changeAccBal(lineCredit); //adding funds to account 8
					dataMatrix[7].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 6020)
				{
					dataMatrix[8].changeAccBal(lineCredit); //adding funds to account 9
					dataMatrix[8].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 6050)
				{
					dataMatrix[9].changeAccBal(lineCredit); //adding funds to account 10
					dataMatrix[9].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 6060)
				{
					dataMatrix[10].changeAccBal(lineCredit); //adding funds to account 11
					dataMatrix[10].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 2000)
				{
					dataMatrix[11].changeAccBal(lineCredit); //adding funds to account 12
					dataMatrix[11].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
				if (lineAccNum == 4000)
				{
					dataMatrix[12].changeAccBal(lineCredit); //adding funds to account 13, my favorite number (woohoo!)
					dataMatrix[12].changeAccBal(lineDebit);
				}
				//-----------------------------------------------------------------------
			}
		}
	}
}

//-----------------------------------------------------------------------

void printIncomeStatement(vector <header> data, entry dataMatrix[])
{
	addToAccounts(data, dataMatrix);
	//-----------------------------------------------------------------------
	int tempRev = 0;
	int tempExp = 0; //oooh look some tmeporary variables
	int income = 0;
	cout << "Simple Income Statment:\nAcct#   Account          Balance\n"; //formatting isnt fun
	//-----------------------------------------------------------------------
	for (int i = 0; i < 3; i++)
	{
		cout << setw(5) << setfill('.') << left << dataMatrix[i].getAccNum() << setw(14) << setfill('.') << right << dataMatrix[i].getAccName() << "." << setw(11) << setfill('.') << right << dataMatrix[i].getAccBal() << "\n";
		tempRev += dataMatrix[i].getAccBal(); //printing some lines and adding to total
	}
	//-----------------------------------------------------------------------
	for (int i = 3; i < 5; i++)
	{
		cout << setw(5) << setfill('.') << left << dataMatrix[i].getAccNum() << setw(14) << setfill('.') << right << dataMatrix[i].getAccName() << "." << setw(10) << setfill('.') << right << "-" << dataMatrix[i].getAccBal() << "\n";
		tempRev -= dataMatrix[i].getAccBal(); //same thing, but subtraction this time
	}
	//-----------------------------------------------------------------------
	cout << "Total Revenue = " << tempRev << "\n\nAcct#   Account          Balance\n";
	//-----------------------------------------------------------------------
	for (int i = 5; i < 11; i++)
	{
		cout << setw(5) << setfill('.') << left << dataMatrix[i].getAccNum() << setw(14) << setfill('.') << right << dataMatrix[i].getAccName() << "." << setw(10) << setfill('.') << right << "-" << dataMatrix[i].getAccBal() << "\n";
		tempExp += dataMatrix[i].getAccBal(); //same thing, but these are expenses now
	}
	//-----------------------------------------------------------------------
	income = tempRev - tempExp; //ooh totals now how nice
	cout << "Total Expense = -" << tempExp << "\nNet Income = " << income << "\nAccounts Recievable: " << dataMatrix[11].getAccBal() << "\nAccounts Payable: " << dataMatrix[12].getAccBal();
	//-----------------------------------------------------------------------

}

//-----------------------------------------------------------------------

int main() //we on main street now
{
	int choice;
	entry accounts[13];
	vector<header> transactions; //setting up shop
	initializeAccounts(accounts);
	//-----------------------------------------------------------------------
	do
	{
		cout << "\n\n\nPlease select a menu option:\n1) Process Journal File\n2) Validate Loaded Transactions\n3) Display Income Statement\n4) Exit\n";
		cin >> choice; //oooh a menu
		//-----------------------------------------------------------------------
		while (cin.fail() || (choice != 1 && choice != 2 && choice != 3 && choice != 4))
		{
			cout << "Invalid input, please enter a number between 1 and 4:\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			cin >> choice; //gotta do some input validation
		}
		//-----------------------------------------------------------------------
		switch (choice)
		{
		case 1:
			processJEFile(transactions); //look, its a switch! how neat!
			break;
			//-----------------------------------------------------------------------
		case 2:
			validateTransactions(transactions, accounts);
			break;
			//-----------------------------------------------------------------------
		case 3:
			printIncomeStatement(transactions, accounts);
			break;
			//-----------------------------------------------------------------------
		case 4:
			system("cls");
			break;
			//-----------------------------------------------------------------------
		}
	} while (choice != 4);
	//-----------------------------------------------------------------------
	system("pause"); //fin
	return 0;
}