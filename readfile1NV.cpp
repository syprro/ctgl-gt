#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#define MAX 10
using namespace std;
struct Nhanvien
{
	char msnv[6];
	char hoten[50];
	char phong[20];
	float lcb, hsl, thuong;
};
int ReadFile(string filename, Nhanvien& nv)
{
	ifstream fi(filename.c_str());
	if (fi.is_open()==false)
	{
		cout << "\nKhong tim thay file";
		return 1;
	}
	string line;
	getline(fi, line);
	//tach du lieu dong thanh cac thanh phan du lieu cua nhan vien
	stringstream ss(line);
	ss.getline(nv.msnv, 6, ',');
	ss.getline(nv.hoten, 50, ',');
	ss.getline(nv.phong, 20, ',');
	ss >> nv.lcb;
	ss >> nv.hsl;
	ss >> nv.thuong;
	return 0;
}
//Ham in thong tin nhan vien
void InNV(Nhanvien nv)
{
	//dung gotoxy
	system("cls");
	cout << "MSNV \t Ho ten \t\t Phong     LCB    HSL    Thuong    ThucLanh" << endl;
	cout << nv.msnv << "\t";
	cout << nv.hoten << "\t";
	cout << nv.phong << "      ";
	cout << nv.lcb << "   ";
	cout << nv.hsl << "    ";
	cout << nv.thuong << "       ";
	float tl = nv.lcb * nv.hsl + nv.thuong;
	cout << tl;

}
int main()
{
	Nhanvien nv;
	string filein = "Input.txt";
	if (ReadFile(filein, nv)==0)
		InNV(nv);

	int stop = _getch();
	return 0;
}