// Calculator2.cpp : Defines the entry point for the console application.
//

// �alculator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <string>

using namespace std;


bool isSeparator(char symbol)
{
	return (symbol == ' ');
}
bool isOperator(char symbol)
{
	return (symbol == '-' || symbol == '+' || symbol == '*' || symbol == '/');
}
bool isLetter(char symbol)
{
	return(symbol >= 'a'&&symbol <= 'z' || symbol >= 'A'&&symbol <= 'Z');
}
bool isNum(char symbol)
{
	return (symbol >= '0'&&symbol <= '9');
}
bool isBracket(char symbol)
{
	return (symbol == '(' || symbol == ')');
}
int getRange(char symbol)//������������ ����� ��� ���������� 
{
	if (symbol == '-' || symbol == '+')
	{
		return 0;
	}
	else
	{
		return 1;
	}

}
bool isDot(char symbol)
{
	return (symbol == '.' || symbol == ',');
}

string RPN(string inData)//������� ��� �������������� ��������� � ����������� (�������� ��������) ������
{
	stack <char> st;
	string outData;
	int numBrOp = 0, numBrCl = 0;//���������� ��� �������� ���������� ������
	char temp = ' ';
	bool minus = false, incorrect = false;//��� �������� �� ������� ����� � ������������ ����
	for (int i = 0; i <= inData.length(); i++)
	{
		if (isSeparator(inData[i]))
		{
			continue;
		}
		if (isNum(inData[i]))
		{
			minus = false;
			while (isNum(inData[i]))
			{
				outData += inData[i];
				i++;
				if (isDot(inData[i]))
				{
					incorrect = true;
					outData += '.';
					i++;
				}
			}
			i--;
			outData += ' ';
		}

		if (isBracket(inData[i]))
		{
			if (inData[i] == '(')
			{
				numBrOp++;
				st.push(inData[i]);
				minus = true;
			}
			else if (inData[i] == ')')
			{
				numBrCl++;
				temp = st.top();
				st.pop();
				while (temp != '('&&!st.empty())
				{
					outData += temp;
					outData += ' ';
					temp = st.top();
					st.pop();
				}
			}
		}

		if (isOperator(inData[i]))
		{
			incorrect = true;
			if (minus)
			{
				if (inData[i] == '-' && isNum(inData[i + 1]))
				{
					outData += '~';//��������� �������� ������ ��� ����������� ���������
					minus = false;
					continue;
				}
			}
			if (st.empty())
			{
				st.push(inData[i]);
			}
			else
			{
				while (!st.empty())
				{
					temp = st.top();
					st.pop();
					if (temp == '(')
					{
						st.push(temp);
						break;
					}
					else if (isOperator(temp))
					{
						if (getRange(temp) < getRange(inData[i]))
						{
							st.push(temp);
							break;
						}
						else if (getRange(temp) >= getRange(inData[i]))
						{
							outData += temp;
							outData += ' ';
						}
					}
				}
				st.push(inData[i]);
			}
		}
		if (isLetter(inData[i]))
		{
			cout << "Incorrect entry. You have entered the letters";
			exit(1);
		}
		if (incorrect)
		{
			if (isOperator(inData[i + 1]) || isDot(inData[i + 1]))
			{

				cout << "Incorrect entry. You have entered the excess sign";
				exit(1);
			}
			else
			{
				incorrect = false;
			}
		}
	}

	if (numBrCl != numBrOp)
	{
		cout << "Wrong number of brackets";
		exit(2);
	}

	while (!st.empty())
	{
		outData += st.top();
		outData += ' ';
		st.pop();
	}
	return outData;
}
float calculate(string inData)//���������� ���������� ������������ ���������
{
	stack <double> st;

	for (int i = 0; i < inData.length(); i++)
	{
		char temp[12] = {};
		if (inData[i] == '~')
		{
			int j = 0;
			temp[j++] = '-';
			i++;
			while (!isSeparator(inData[i]))
			{
				temp[j++] = inData[i];
				i++;
			}
			st.push(atof(temp));
		}
		if (isNum(inData[i]))
		{
			int j = 0;
			while (!isSeparator(inData[i]))
			{
				temp[j++] = inData[i];
				i++;
			}
			st.push(atof(temp));
		}

		if (isOperator(inData[i]))
		{
			if (inData[i] == '+')
			{
				double a = st.top();
				st.pop();
				double b = st.top();
				st.pop();
				st.push(b + a);
			}
			if (inData[i] == '-')
			{
				if (st.size() == 1)//���� �����, � � ����� ������ ���� �������, �� ��� ������� �����
				{
					double a = st.top()*(-1);
					st.pop();
					st.push(a);
				}
				else
				{
					double a = st.top();
					st.pop();
					double b = st.top();
					st.pop();
					st.push(b - a);
				}

			}
			if (inData[i] == '/')
			{
				double a = st.top();
				st.pop();
				double b = st.top();
				st.pop();
				st.push(b / a);
			}
			if (inData[i] == '*')
			{
				double a = st.top();
				st.pop();
				double b = st.top();
				st.pop();
				st.push(b * a);
			}
		}

	}



	return st.top();
}
int main()
{
	string inData;
	getline(cin, inData);
	cout << calculate(RPN(inData));
	return 0;
}

