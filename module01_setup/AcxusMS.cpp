#include <iostream>
using namespace std;
int main()
{
	cout<<"\nWelcome to Acxus MS: Account Management Software! This is a prototype.\n\n";

	//menu template
	cout<<"\t\tMenu\n"<<string(38,'-')<<"\n";
	cout<<"1) Insert Entry.\n2) View Entry History.\n3) Delete Entry.\n4) Settings.\n5) Exit.";
	int input;cout<<"\n==> ";
	cin>>input;
	if(input==1){}
	else if(input==2){}
	else if(input==3){}
	else if(input==4){}
	else if(input==5){
		system("cls");
		cout<<"\nGoodbye!";
		cin>>input;
		return 0;}
}