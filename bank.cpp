#include<iostream>
#include<cstdlib>
#include<fstream>
using namespace std;
class account_query {//�b���d��
private:
	char account_number[20];
	char firstName[10];
	char lastName[10];
	float total_Balance;
public:
	void read_data();
	void show_data();
	void write_rec();
	void read_rec();
	void search_rec();
	void edit_rec();
	void delete_rec();
};
void account_query::read_data() {//Ū�����
	cout << "\nEnter Account Number: ";
	cin >> account_number;//��J�b��W
	cout << "Enter First Name: ";
	cin >> firstName;//��J�m
	cout << "Ente Last Name: ";
	cin >> lastName;//��J�W�l
	cout << "Enter Balance: ";//��J���B
	cin >> total_Balance;
	cout << endl;

}
void account_query::show_data() {//Ū�����
	cout << "Account Number: " << account_number << endl;//�b��W
	cout << "First Name: " << firstName << endl;//�m
	cout << "Last Name: " << lastName << endl;//�W�l
	cout << "Current Balacne :Rs. " << total_Balance << endl;//���B
	cout << "-----------------------------" << endl;


}
void account_query::write_rec() {//�g�J���
	ofstream outfile;
	outfile.open("record.bank", ios::binary | ios::app);//�s�W�O���ΤG����
	read_data();
	outfile.write(reinterpret_cast<char*>(this), sizeof(*this));//�g�J�ɮ�
	outfile.close();
	system("pause");
	system("cls");

}
void account_query::read_rec() {//Ū�����
	ifstream infile;
	infile.open("record.bank", ios::binary);//Ū���O���ΤG����
	if (!infile) {//�SŪ���ɮ�
		cout << "Erroe in Opeing! File Not Found!!" << endl;
		return;
	}
	cout << "\n****Data from file****" << endl;
	while (!infile.eof())//�u�n�SŪ���ɮק��A�N�~�����
	{
		if (infile.read(reinterpret_cast<char*>(this), sizeof(*this))){
			show_data();
		}
	}
	infile.close();
	system("pause");
	system("cls");
}
void account_query::search_rec() {//�j�M���
	int n;
	ifstream infile;//Ū�J
	infile.open("record.bank", ios::binary);//�j�M�O���ΤG����
	if (!infile) {//�SŪ���ɮ�
		cout << "Erroe in Opeing! File Not Found!!" << endl;
		return;
	}
	infile.seekg(0, ios::end);//�ɮ׫����Y�q�Y���
	int count = infile.tellg() / sizeof(*this);//���X�����
	cout << "\n There are " << count << " record in the file";
	cout << "\n Enter Record Number to Search ";
	cin >> n;
	infile.seekg((n - 1) * sizeof(*this));//��Ʀ�m
	infile.read(reinterpret_cast<char*>(this), sizeof(*this));
	show_data();
	system("pause");
	system("cls");


}
void account_query::edit_rec() {
	int n;
	fstream iofile;
	iofile.open("record.bank", ios::in || ios::binary);
	if (!iofile) {
		cout << "Erroe in Opeing! File Not Found!!" << endl;
		return;
	}
	iofile.seekg(0, ios::end);//�ɮ׫����Y�q�Y���
	int count = iofile.tellg() / sizeof(*this);//���X�����
	cout << "\n There are " << count << " record in the file";
	cout << "\n Enter Record Number to edit ";
	cin >> n;
	iofile.seekg((n - 1) * sizeof(*this)); // ��Ʀ�m
	iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
	cout << "Record " << n << " has following data" << endl;
	show_data();//�i�ܸ��
	iofile.close();
	iofile.open("record.bank", ios::out | ios::in | ios::binary);//�}�Ҽg�J�ɮ�
	iofile.seekp((n - 1) * sizeof(*this));// ��Ʀ�m
	cout << "\nEnter data to Modify " << endl;
	read_data();
	iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
	system("pause");
	system("cls");

}
void account_query::delete_rec() {
	int n;
	ifstream infile;//Ū�J
	infile.open("record.bank", ios::binary);//�j�M�O���ΤG����
	if (!infile) {//�SŪ���ɮ�
		cout << "Erroe in Opeing! File Not Found!!" << endl;
		return;
	}
	infile.seekg(0, ios::end);
	int count = infile.tellg() / sizeof(*this);//���X�����
	cout << "\n There are " << count << " record in the file";
	cout << "\n Enter Record Number to Delete ";
	cin >> n;
	fstream tmpfile;
	tmpfile.open("tmpfile.bank", ios::out | ios::binary);
	infile.seekg(0);
	for (int i = 0; i < count; i++) {
		infile.read(reinterpret_cast<char*>(this), sizeof(*this));
		if (i == (n - 1)) {
			continue;
		}
		tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
	infile.close();
	tmpfile.close();
	remove("record.bank");
	rename("tmpfile.bank", "record.bank");
	system("pause");
	system("cls");
}

int main(){

	account_query A;
	int choice;
	cout << "***Acount Information System***" << endl;
	while (true) {
		cout << "Select one option below";
		cout << "\n\t1-->Add record to file";
		cout << "\n\t2-->Show record form file";
		cout << "\n\t3-->Search Record from file";
		cout << "\n\t4-->Update Record";
		cout << "\n\t5-->Delete Record";
		cout << "\n\t6-->Quit";
		cout << "\nEnter your choice";
		cin >> choice;
		switch (choice) {
		case 1:
			A.write_rec();
			break;
		case 2:
			A.read_rec();
			break;
		case 3:
			A.search_rec(); 
			break;
		case 4:
			A.edit_rec();
			break;
		case 5:
			A.delete_rec();
			break;
		case 6:
			exit(0);
			break;
		default:
			cout << "\nEnter corret choice";
			exit(0);
		}
		
	}


	return 0;
}