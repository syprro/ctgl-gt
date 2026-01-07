#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#define MAX 10
using namespace std;
struct NhanVien
{
	char msnv[6];
	char hoten[50];
	char phong[20];
	float luong, hsl, thuong;
};
int ReadFile(string filename, NhanVien ds[], int& sl)
{
	ifstream file(filename.c_str());
	if (!file.is_open())
	{
		cout << "\nKhong tim thay file!";
		return 1;
	}
	string line;
	int i = 0;
	while (getline(file, line) && i < MAX)
	{
		stringstream tach(line);
		tach.getline(ds[i].msnv, 6, ',');
		tach.getline(ds[i].hoten, 50, ',');
		tach.getline(ds[i].phong, 20, ',');
		tach >> ds[i].luong;
		tach >> ds[i].hsl;
		tach >> ds[i].thuong;
		i++;
	}
	sl = i;
	return 0;
}
void InDS(NhanVien ds[], int sl)
{
	system("cls");
	cout << "MSNV \t Ho ten \t\t Phong     LCB    HSL    Thuong    ThucLanh" << endl;
	for (int i = 0; i < sl; i++)
	{
		cout << ds[i].msnv << "\t";
		cout << ds[i].hoten << "\t";
		cout << ds[i].phong << "      ";
		cout << ds[i].luong << "   ";
		cout << ds[i].hsl << "    ";
		cout << ds[i].thuong << "       ";
		float tl = ds[i].luong * ds[i].hsl + ds[i].thuong;
		cout << tl;
		cout << "\n";
	}
}
void Nhap1NV(NhanVien& nv)
{
	cin.ignore();
	cout << "\nNhap MSNV: ";
	cin.getline(nv.msnv, 6);

	cout << "Nhap ho ten: ";
	cin.getline(nv.hoten, 50);

	cout << "Nhap phong: ";
	cin.getline(nv.phong, 20);

	cout << "Nhap luong co ban: ";
	cin >> nv.luong;

	cout << "Nhap he so luong: ";
	cin >> nv.hsl;

	cout << "Nhap thuong: ";
	cin >> nv.thuong;
}
void ThemNhanVien(NhanVien ds[], int& sl)
{
	int them;
	cout << "\nNhap so nhan vien muon them: ";
	cin >> them;

	if (sl + them > MAX)
	{
		cout << "\nVuot qua so luong toi da!";
		return;
	}

	for (int i = 0; i < them; i++)
	{
		cout << "\n--- Nhap nhan vien thu " << i + 1 << " ---";
		Nhap1NV(ds[sl]);
		sl++;
	}
}
void WriteFile(string filename, NhanVien ds[], int sl)
{
	ofstream outfile(filename.c_str());
	if (!outfile)
	{
		cout << "\nLoi mo...";
		return;
	}
	for (int i = 0; i < sl; i++)
	{
		outfile << ds[i].msnv << ", ";
		outfile << ds[i].hoten << ", ";
		outfile << ds[i].phong << ", ";
		outfile << ds[i].luong << " ";
		outfile << ds[i].hsl << " ";
		outfile << ds[i].thuong << "\n";
	}
}
int main()
{
	NhanVien ds[MAX];
	int sonv = 0;
	string Filein = "InFile.txt";
	if (ReadFile(Filein, ds, sonv) == 0)
	{
		InDS(ds, sonv);
	}
	ThemNhanVien(ds, sonv);

	cout << "\nDanh sach sau khi them:";
	InDS(ds, sonv);

	string Fileout = "Conc.txt";
	WriteFile(Fileout, ds, sonv);
	cout << "\nIn file thanh cong~";
	int stop = _getch();
	return 0;
}