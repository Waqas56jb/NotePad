# include<iostream>
# include<conio.h>
#include<windows.h>
# include<string>
//#include <stdio.h>
# include<fstream>
# include<iomanip>
using namespace std;
class TrieNode
{
public:
	TrieNode* children[26];
	bool isEndOfWord;

	TrieNode() 
	{
		isEndOfWord = false;
		for (int i = 0; i < 26; i++) 
		{
			children[i] = nullptr;
		}
	}
};
struct stack
{
	stack* next;
	char data;
	
};
struct node
{
	char data;
	node* left, * right, * top, * bottom;
	node()
	{
		data = ' ';
		left = NULL;
		right = NULL;
		top = NULL;
		bottom = NULL;
	}
};
class advanceNotePad
{
	node* head,*current;
	string copytext;
	int wordcount = 1;
	int x, y,z=0,Z=0;
	string str;
public:

	advanceNotePad()		//constructor
	{
		head = NULL;
		current = NULL;
		copytext = " ";
		top = NULL;
		root = new TrieNode;
	}
	
	void AddText(char data)		//inserting data
	{
		if (data == ' '||int(data)<97||int(data)>122)
		{
			str = "";
			x++;
			Cursor(x, y);
		}
		else
		{
			str = str + data;
			suggestions(str);
			x++;
			Cursor(x, y);
		}

		push(data);
		
		node* temp = new node;
		node* n = new node;
		node* m = new node;
		temp->data = data;
		if (head == NULL)
		{
			temp->right = head;
			temp->left = NULL;
			temp->top = NULL;
			temp->bottom = NULL;
			
			head = temp;
		}
		else
		{
			current = head;
			while (current->bottom != NULL)
			{
				current = current->bottom;
			}
			while (current->right != NULL)
			{
				current = current->right;
			}
			temp->left = current;
			current->right = temp;
			temp->top = NULL;
			temp->right = temp->bottom = NULL;
		}
		
	}

	void AddTextHelper(int x,int y)		//recognizing the enterd data and giving to addtext function
	{
		char Data;
		while (1)
		{
			if (_kbhit)
			{
				Data = _getch();
				if (Data == ' ')
				{
					wordcount++;
				}
				if (int(Data) == 3)		//copy the text
				{
					copy(copytext);
					continue;
				}
				if (int(Data) == 5)		//end the program
				{
					break;
				}

				if (int(Data) == 1)		//save the text in file
				{
					saveText();
					continue;
				}
				if (int(Data) == 2)		//similarity checker
				{
					similarity();
					continue;
				}
				if (int(Data) == 4)		//delete the text
				{
					deleteText();
					continue;
				}
				if (int(Data) == 16)		//paste the text
				{
					paste(copytext);
					continue;
				}
				if (int(Data) == 26)		//undo 
				{
					undo();
					continue;
				}
				if (int(Data) == 6)		//replace the text
				{
					find();
					continue;
				}
				if (int(Data) == 19)		//search the text
				{
					search();
					continue;
				}
				if (int(Data) == 13)		//for enter key
				{
					system("cls");
					cout << endl;
					displayAfterDeletion();
				}
				if (int(Data) == 23)		//for total words count
				{
					cout << "\ntotal words:" << wordcount;
					continue;
				}
				if (Data == -32)			//for cursor movement
				{
					Data = _getch();
					if (Data == 72)  //up
					{
						//changeCursor(x, y--);
						continue;
					}
					else if (Data == 80)//down
					{
						//changeCursor(x, y++);
						continue;
					}
					else if (Data == 77)	//right
					{
						//changeCursor(x++, y);
						continue;
					}
					else if (Data == 75)	//left
					{
						//changeCursor(x--, y);
						continue;
					}
				}

				AddText(Data);
				display();
			}
		}
	}

	void deleteText()		//deleting specified text
	{
		node* temp = new node;
		node* temp1 = new node;
		current = head;
		string str;
		int q = 0,a=0;
		cout << "\nenter the string you want to delete " << endl;
		getline(cin >> ws, str);

		for (int i = 0; i < 1; i++)
		{
			for (int i = 0; i < str.length(); i++)
			{

				if (str[i] == current->data)
				{
					if (i == 0)
					{
						temp = temp1;
					}
					if (i == str.length() - 1)
					{
						break;
					}
				}
				else
				{
					i = -1;
					temp1 = current;
				}
				if (current->right != NULL)
				{
					current = current->right;
				}
				else
				{
					i = -1;
					current = current->bottom;
					if (current == NULL)
					{
						if (a == 0)
						{
							cout << "not found" << endl;
						}
						q++;
						return;
					}
					temp1 = current;
				}
			}
			a++;
		}
		for (int i = 0; i < str.length(); i++)
		{
			node* nn = new node;

			if (temp == head)
			{
				nn = temp->right;
				head = temp->right;
				head->left = NULL;
				delete nn;
			}
			else if (temp->right->right == NULL)
			{
				current = temp;
				nn = current->right;
				temp = nn->right;
				current->right->left = NULL;
				current->right = NULL;
				delete nn;
			}
			else
			{
				current = temp;
				nn = current->right;
				current->right = current->right->right;
				current->right->left = current;
				//temp = current;
				nn->left = nn->right = NULL;
				delete nn;
			}
		}
		cout << endl;
		system("cls");
		displayAfterDeletion();
	}

	void search()		//searching the word
	{
		int x = 1, y = 1, q = 0,a=0;
		node* temp = new node;
		node* temp1 = new node;
		current = head;
		string str;
		cout << "\nenter the string you want to search " << endl;
		getline(cin >> ws, str);
		while (current != NULL)
		{
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == current->data)
				{
					if (i == 0)
					{
						temp = temp1;
					}
					if (i == str.length() - 1)
					{
						break;
					}
				}
				else
				{
					i = -1;
					temp1 = current;
				}
				if (current->right != NULL)
				{
					x++;
					current = current->right;
				}
				else
				{
					i = -1;
					current = current->bottom;
					if (current == NULL)
					{
						if (a == 0)
						{
							cout << "word not found" << endl;
							q++;
						}
						return;
					}
					y++;
					temp1 = current;
				}
			}
			if (q == 0)
			{
				a++;
				cout << str << " found at x:" << x - (str.length()) << " y:" << y << endl;
			}
		}
	}

	void copy(string &str)		// copy data in string
	{
		node* temp;
		string Copy = " ";
		current = head;
		int sx, sy,ex,ey;
		cout << "\nenter the starting postion of string you want to copy: "; cin >> sx >> sy;
		cout << "enter the ending postion of string you want to copy: "; cin >> ex >> ey;
		for (int j = 1; j < sy; j++)
		{
			current = current->bottom;
		}
		for (int i = 0; i < sx; i++)
		{
			current = current->right;
		}
		for (int i = sy; i <= ey; i++)
		{
			temp = current;
			for (int j = sx; j <= ex; j++)
			{
				Copy += current->data;
				current = current->right;
			}
			temp = temp->bottom;
			current = temp;
			sx = 0;
		}
		str = Copy;
		cout << " copied string:" << Copy << endl;
	}

	void paste(string str)		//paste the text
	{
		char choice;
		int d = 0; 
		node* temp;
		string Copy = " ";
		current = head;
		int x, y;
		cout << "\nenter the postion  you want to paste copied data: "; cin >> x >> y;
		if (y > this->y)
		{
			cout << " out of bound wre enter y position " << endl;
			cin >> y;
		}
		
		for (int j = 1; j < y; j++)
		{
			current = current->bottom;
		}
		for (int i = 0; i < x; i++)
		{
			current = current->right;
		}
		if (current->data == ' '&&current->right->data==' ')
		{
			for (int i = 1; i < str.length(); i++)
			{
				if (current != NULL)
				{
					current->data = str[i];
					current = current->right;
				}
				else
				{
					cout << " out of bound" << endl;
				}
			}
		}
		else
		{
			cout << "text already placed at this position do you want to rewrite it?(y/n)" << endl;
			cin >> choice;
			if (choice == 'y')
			{
				for (int i = 1; i < str.length(); i++)
				{
					if (current != NULL)
					{
						current->data = str[i];
						current = current->right;
					}


				}
			}
			else
			{
				return;
			}
		}
		system("cls");
		displayAfterDeletion();
	}

	void find()		//find the text
	{
		int count = 0;
		char choice;
		int X[10]={0}, Y[10]={0};
		int x = 1, y = 1, q = 0,a=0;
		node* temp = new node;
		node* temp1 = new node;
		current = head;
		string str, replace;
		cout << "\nenter the string you want to find " << endl;
		getline(cin >> ws, str);
		while (current != NULL)
		{
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == current->data)
				{
					if (i == 0)
					{
						temp = temp1;
					}
					if (i == str.length() - 1)
					{
						break;
					}
				}
				else
				{
					i = -1;
					temp1 = current;
				}
				if (current->right != NULL)
				{
					x++;
					current = current->right;
				}
				else
				{
					i = -1;
					current = current->bottom;
					if (current == NULL)
					{
						if (a== 0)
						{
							cout << "not found" << endl;
							return;
						}
						q++;
						break;
					}
					y++;
					temp1 = current;
				}
			}
			if (q == 0)
			{
				a++;
				X[count] = x - (str.length());
				Y[count] = y;
				cout << str << " found at x:" << x - (str.length()) << " y:" << y << endl;
				count++;
			}
		}
		cout << "enter the word you want to replace "; cin >> replace;
		cout << " you want to replace first word or whole file (f/w):"; cin >> choice;
		if (choice == 'f')
		{
			current = head;
			for (int i = 1; i < Y[0]; i++)
			{
				current = current->bottom;
			}
			for (int j = 0; j < X[0]; j++)		//going to exact location
			{
				current = current->right;
			}
			for (int j = 0; j<replace.length(); j++)		//replacing the word
			{
				current->data = replace[j];
				current = current->right;
			}
			displayAfterDeletion();

		}
		if (choice == 'w')
		{
			for (int i = 0; i < count; i++)
			{
				current = head;
				for (int k = 1; k < Y[i]; k++)
				{
					current = current->bottom;
				}
				for (int m = 0; m < X[i]; m++)		//going to exact location
				{
					current = current->right;
				}
				for (int j = 0; j < replace.length(); j++)		//replacing the word
				{
					current->data = replace[j];
					current = current->right;
				}
			}
			displayAfterDeletion();

		}
	}

	void undo()  // undo an operation
	{
		pop();
	}

	void saveText()		//saving data in file
	{
		ofstream Text("save.txt");
		ofstream File("file.txt");
		node* temp = new node;
		current = head;
		while (current->right != NULL)
		{
			temp = current;
			while (current->bottom != NULL)
			{
				Text << endl;
				File << endl;
				current = current->bottom;
			}
			while (current->right != NULL)
			{
				Text << current->data;
				File << current->data;
				current = current->right;
			}
			Text << current->data;
			File << current->data;
			/*temp = temp->bottom;
			current = temp;*/
		}
		Text.close();
		File.close();
		cout << "\ntext saved in file" << endl;
	}

	void similarity()
	{
		string str1, str2;
		ifstream Text("save.txt");
		ifstream File("file.txt");
		getline(Text >> ws, str1);
		getline(File >> ws, str2);
		Text.close();
		File.close();
		if (str1 == str2)
		{
			cout << "file data matches " << endl;
			cout << "data of file 1:" << str1 << endl;
			cout << "data of file 2:" << str2 << endl;
		}
		else
		{
			cout << "file data not matches " << endl;
		}
	}

	void displayAfterDeletion()
	{
		node* temp = new node;
		current = head;
		while (current != NULL)
		{
			temp = current;
			while (current->right != NULL)
			{
				cout << current->data;
				current = current->right;
			}
			cout << current->data;
			if (current->bottom != NULL)
			{
				cout << endl;
			}
			temp = temp->bottom;
			current = temp;
		}
		cout << endl;
	}

	void Cursor(int columnPos, int rowPos)		//changing position of cursor
	{
		HANDLE handle;
		COORD coord;
		coord.X = columnPos;
		coord.Y = rowPos;
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, coord);
	}

	void changeCursor(int columnPos, int rowPos)		//changing position of cursor
	{
		this->y = rowPos;
		this->x = columnPos;
		this->Z = columnPos;
		current = head;
		HANDLE handle;   
		COORD coord;
		coord.X = columnPos;
		coord.Y = rowPos;
		node* a = new node;
		for (int j = 0; j < rowPos; j++)		//initializing skipped nodes with blank spaces
		{
			node* temp = new node;
			temp->data = ' ';
			if (j > 0)
			{
				while (current->bottom != NULL)
				{
					current = current->bottom;
				}
				temp->top = current;
				current->bottom = temp;
				temp->left = NULL;
				temp->right = NULL;
				temp->bottom = NULL;
				a = current;
				current = temp;
			}
			for (int i = 0; i < columnPos; i++)
			{
				node* temp = new node;
				temp->data = ' ';
				if (head == NULL)
				{
					temp->right = head;
					temp->left = NULL;
					temp->top = NULL;
					temp->bottom = NULL;

					head = temp;
					current = head;
				}
				else
				{
					
					while (current->right != NULL)
					{
						
						current = current->right;
					}
					temp->left = current;
					current->right = temp;
					if (j > 0)
					{
						temp->top = a;
						a->bottom = temp;
						a = a->right;
					}
					else
					{
						temp->top = NULL;
					}
					
					temp->right = temp->bottom = NULL;
					
				}
			}
			current = head;
		}


		handle = GetStdHandle(STD_OUTPUT_HANDLE);   
		SetConsoleCursorPosition(handle, coord);  
	}

	void display()		//displaying data
	{
		current = head;
		while (current->bottom != NULL)
		{
			current = current->bottom;
		}
		while (current->right != NULL)
		{
			current = current->right;
		}
		cout << current->data;
	}
	TrieNode* root;
	TrieNode* curr = root;
	void wordSuggestion()		//copying data from file in trie tree
	{
		string str;;
		ifstream File("suggestions.txt");
		while (!File.eof())
		{
			getline(File >> ws, str);
			Insert(str);
		}
		File.close();
	}

	void suggestions(string prefix)		//finding suggestions
	{
		TrieNode* curr = root;
		for (char c : prefix) 
		{
			int index = c - 'a';
			if (!curr->children[index]) 
			{
				//cout << "\nNo suggestions found." << endl;
				return;
			}
			curr = curr->children[index];
		}
		cout << endl;
		z = 0;
		traverseTrie(curr, prefix);
	}

	void traverseTrie(TrieNode* node, string prefix)		//displaying suggestions
	{

		if (node->isEndOfWord)
		{
			if (z < 10)
			{
				z++;
				cout << prefix << endl;
				
			}
		}
		
		for (int i = 0; i < 26; i++)
		{
			if (node->children[i])
			{
				char c = 'a' + i;
				traverseTrie(node->children[i], prefix + c);
			}
		}
	}

	void Insert(string word)
	{
		TrieNode* curr = root;
		for (char ch : word)
		{
			int index = ch - 'a';
			if (curr->children[index] == nullptr)
			{
				curr->children[index] = new TrieNode();
			}
			curr = curr->children[index];
		}
		curr->isEndOfWord = true;
	}

	stack* top = new stack;
	void push(char data)
	{
		stack* current = new stack;
		stack* temp = new stack;
		temp->data = data;
		if (top == NULL)
		{
			temp->next = top;
			top = temp;
		}
		else
		{
			current = top;
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = temp;
			temp->next = NULL;
		}
	}

	void pop()
	{
		system("cls");
		for (int i = 0; i < (this->y)-1; i++)
		{
			cout << endl;
		}
		cout << setw(this->Z+1);
		stack* current = new stack;
		current = top;
		while (current != NULL)
		{
			cout << current->data;
			current = current->next;
		}
	}

};
int main()
{
	advanceNotePad obj;
	
	int x, y;
	cout << "###########################################" << endl;
	cout << "#    ADVANCE NOTE PAD                     #" << endl;
	cout << "#    Instructions                         #" << endl;
	cout << "#    1:for deletion (ctrl+d)              #" << endl;
	cout << "#    2:for searching (ctrl+s)             #" << endl;
	cout << "#    3:for copy (ctrl+c)                  #" << endl;
	cout << "#    4:for paste text (ctrl+p)            #" << endl;
	cout << "#    5:for find and replace (ctrl+f)      #" << endl;
	cout << "#    6:for undo (ctrl+z)                  #" << endl;
	cout << "#    7:for save text (ctrl+a)             #" << endl;
	cout << "#    8:for similarity check (ctrl+b)      #" << endl;
	cout << "#    9:total words (ctrl+w)               #" << endl;
	cout << "###########################################" << endl;
	system("pause");
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$ Enter (X,Y) coordinates where you want to enter data $" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cin >> x>> y;
	system("cls");
	obj.changeCursor(x,y);
	obj.wordSuggestion();
	obj.AddTextHelper(x,y);
	
}