#include<fstream>
#include<string.h>
#include<iostream>
#include <stdlib.h>

using namespace std;

class contact
{
	long ph;
	char name[20],add[20],email[30];

	public:

	void create_contact()
	{
        system("cls");
		cout<<"Phone: ";
		cin>>ph;
		cout<<"Name: ";
		cin.ignore();
		cin>>name;
		cout<<"Address: ";
		cin.ignore();
		cin>>add;

		cout<<"Email address: ";
		cin.ignore();
		cin>>email;

		cout<<"\n";
	}

	void show_contact()
	{
		cout<<endl<<"Phone #: "<<ph;
		cout<<endl<<"Name: "<<name;
		cout<<endl<<"Address: "<<add;
		cout<<endl<<"Email Address : "<<email;
	}

	long getPhone()
	{
		return ph;
	}

	char* getName()
	{
		return name;
	}

	char* getAddress()
	{
		return add;
	}

	char* getEmail()
	{
		return email;
	}
};

fstream fp;
contact cont;

void save_contact()
{
	fp.open("userAddress.txt",ios::out|ios::app);
	cont.create_contact();
	fp.write((char*)&cont,sizeof(contact));
	fp.close();
	cout<<endl<<endl<<"Contact Has Been Sucessfully Created...";
	getchar();
}

void show_all_contacts()
{
    system("cls");
	cout<<"\n\t\t\t================================\n\t\t\t\tLIST OF USERS\n\t\t\t================================\n";
	fp.open("userAddress.txt",ios::in);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		cont.show_contact();
		cout<<endl<<"=================================================\n"<<endl;
	}
	fp.close();
}

void display_contact(int num)
{
    system("cls");
	bool found;
	int ch;

	found=false;
	fp.open("userAddress.txt",ios::in);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		if(cont.getPhone()==num)
		{
		cont.show_contact();
		found=true;
		}
	}
	fp.close();
	if(found == false){
	cout<<"\n\nNo record found...";}
	getchar();
}

void edit_contact()
{
    system("cls");
	int num;
	bool found=false;

	cout<<"Edit User\n===============================\n\n\t..::Enter the number of contact to edit: ";
	cin>>num;
	fp.open("userAddress.txt",ios::in|ios::out);
	while(fp.read((char*)&cont,sizeof(contact)) && found==false)
	{
		if(cont.getPhone()==num)
		{
			cont.show_contact();
			cout<<"\nPlease Enter The New Details of Contact: "<<endl;
			cont.create_contact();
			int pos=-1*sizeof(cont);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&cont,sizeof(cont));
			cout<<endl<<endl<<"\t Contact Successfully Updated...";
			found=true;
		}
	}
	fp.close();
	if(found==false)
	cout<<endl<<endl<<"Contact Not Found...";
}

void delete_contact()
{
    system("cls");
	int num;
	cout<<endl<<endl<<"Please Enter The contact #: ";
	cin>>num;
	fp.open("userAddress.txt",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.txt",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		if(cont.getPhone()!=num)
		{
			fp2.write((char*)&cont,sizeof(contact));
		}
	}
	fp2.close();
	fp.close();
	remove("userAddress.txt");
	rename("Temp.txt","userAddress.txt");
	cout<<endl<<endl<<"\tContact Deleted...";
}

int main(int argc, char *argv[])
{
	for(;;)
	{
		int ch;
		cout<<"\n\t ========= USER ADDRESS MANAGEMENT SYSTEM =========";
		cout<<"\n\n\n\t\t\t\tMAIN MENU\n\t\t\t=====================\n\t\t\t[1] Add new User\n\t\t\t[2] List all Users\n\t\t\t[3] Search for User\n\t\t\t[4] Modify a User\n\t\t\t[5] Delete a User\n\t\t\t[0] Exit\n\t\t\t=================\n\t\t\t";
		cout<<"Enter your choice: ";
		cin>>ch;

		switch(ch)
		{
			case 0: cout<<"\n\n\t\tThank you!...";
				break;

			case 1:save_contact();
				break;

			case 2:show_all_contacts();
				break;
			case 3:
			    system("cls");
				int num;
				cout<<"\n\n\tPhone: ";
				cin>>num;
				display_contact(num);
				break;
			case 4:edit_contact();
				break;

			case 5:delete_contact();
				break;
			default:
				break;
		}

		int opt;
		cout<<"\n\n\n..::Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n";
		cin>>opt;

		switch (opt)
		{
 			case 1:
 			    system("cls");
				continue;

			case 0:
			    system("cls");
				break;
 		}
	}
	return 0;
}
