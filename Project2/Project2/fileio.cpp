#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void SaveFile(){
	string s;
	ofstream o("abc.txt");
	cout << "���Ͽ� �Է��� ������ �־��ּ���:";
	cin >> s;
	for (int i = 0; i < 3; i++) {
		o << s << endl;
	}
	o.close();
}

void ReadFile() {
	string s;
	ifstream i("abc.txt");
	if (i.is_open()) {
		while (getline(i, s)) {
			cout << s << endl;
		}
	}
	i.close();
}

int main() {
	ReadFile();
	return 0;
}