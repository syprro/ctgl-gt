#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
#define MAX 10
using namespace std;
struct Nhanvien
{
	char msnv[5];
	char hoten[50];
	char nam[10];
	float luong, hsl, thuong;
};
int RF(string filename, Nhanvien ds[], int& sl)
{
	ifstream filein(filename.c_str());
	if (!filein.is_open())
	{
		cout << "\nLoi mo file!";
		return 1;
	}
	string line;
	int i = 0;
	while (getline(filein, line) && i < MAX)
	{
		stringstream tach(line);
		tach.getline(ds[i].msnv, 5, ',');
		tach.getline(ds[i].hoten, 50, ',');
		tach.getline(ds[i].nam, 10, ',');
		tach >> ds[i].luong;
		tach >> ds[i].hsl;
		tach >> ds[i].thuong;
		i++;
	}
	sl = i;
	return 0;
}
float tl(Nhanvien nv)
{
	return nv.luong * nv.hsl + nv.thuong;
}
void InDS(Nhanvien ds[], int sl)
{
	cout << left
		<< setw(10) << "MSNV"
		<< setw(22.5) << "Ho ten"
		<< setw(10) << "Nam sinh"
		<< setw(11) << "Luong"
		<< setw(10) << "HSL"
		<< setw(10) << "Thuong"
		<< setw(12) << "Thuc lanh" << endl;

	for (int i = 0; i < sl; i++)
	{
		cout << left
			<< setw(8) << ds[i].msnv
			<< setw(25) << ds[i].hoten
			<< setw(10) << ds[i].nam
			<< setw(10) << ds[i].luong
			<< setw(10) << ds[i].hsl
			<< setw(10) << ds[i].thuong
			<< setw(12) << tl(ds[i]) << endl;
	}
}
void ThemNV(Nhanvien ds[], int& sl)
{
	int vt;
	do
	{
		cout << "\nNhap vi tri ma ban muon them nhan vien: ";
		cin >> vt;
	} while (vt<0 || vt>sl);
	for (int i = sl; i > vt; i--)
	{
		ds[i] = ds[i - 1];
	}
	cin.ignore();
	cout << "\nNhap ma so nhan vien can them: ";
	cin.getline(ds[vt].msnv, 5);
	cout << "\nNhap ho ten nhan vien can them: ";
	cin.getline(ds[vt].hoten, 50);
	cout << "\nNhap nam sinh nhan vien can them: ";
	cin.getline(ds[vt].nam, 10);
	cout << "\nNhap luong: ";
	cin >> ds[vt].luong;
	cout << "\nNhap he so luong: ";
	cin >> ds[vt].hsl;
	cout << "\nNhap thuong: ";
	cin >> ds[vt].thuong;
	sl++;
}
void TimKiem(Nhanvien ds[], int sl)
{
	char x[5];
	cout << "\nNhap ma so nhan vien can tim: ";
	cin >> x;
	for (int i = 0; i < sl; i++)
	{
		if (strcmp(ds[i].msnv, x) == 0)
		{
			cout << "\nLa nhan vien thu: " << i;
			cout << "\nHo ten nhan vien: " << ds[i].hoten;
			cout << "\nNam sinh: " << ds[i].nam;
			cout << "\nLuong: " << ds[i].luong;
			cout << "\nHe so luong: " << ds[i].hsl;
			cout << "\nThuong: " << ds[i].thuong;
			cout << "\nThuc Lanh: " << tl(ds[i]);
			return;
		}
	}
	cout << "\nKhong tim thay nhan vien!";
}
void Xoa(Nhanvien ds[], int& sl)
{
	int vtx;
	do
	{
		cout << "\nNhap vi tri can xoa: ";
		cin >> vtx;
	} while (vtx < 0 || vtx >= sl);
	for (int i = vtx; i < sl - 1; i++)
	{
		ds[i] = ds[i + 1];
	}
	sl--;
}
void Sapxep(Nhanvien ds[], int sl)
{
	Nhanvien t;
	for (int i = 0; i < sl; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if (strcmp(ds[j].msnv, ds[j - 1].msnv) < 0)
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void WriteFile(string filename, Nhanvien ds[], int sl)
{
	ofstream fileout(filename.c_str());
	if (!fileout)
	{
		cout << "\nLoi mo file!";
		return;
	}
	for (int i = 0; i < sl; i++)
	{
		fileout << ds[i].msnv << ", "
			<< ds[i].hoten << ", "
			<< ds[i].nam << ", "
			<< ds[i].luong << " "
			<< ds[i].hsl << " "
			<< ds[i].thuong << endl;
	}
	cout << "\nGhi file thanh cong";
}
int main()
{
	Nhanvien ds[MAX];
	int sonv = 0;
	string filein = "Vo.txt";
	RF(filein, ds, sonv);
	int chon;
	do {
		cout << "\n================ MENU ================";
		cout << "\n1. In danh sach nhan vien";
		cout << "\n2. Them nhan vien";
		cout << "\n3. Tim kiem nhan vien theo ma so";
		cout << "\n4. Xoa nhan vien theo vi tri";
		cout << "\n5. Sap xep nhan vien theo ma so";
		cout << "\n6. Ghi danh sach ra file";
		cout << "\n0. Thoat";
		cout << "\n======================================";
		cout << "\nNhap lua chon: ";
		cin >> chon;
		switch (chon) 
		{
		case 1:
			InDS(ds, sonv);
			break;
		case 2:
			ThemNV(ds, sonv);
			break;
		case 3:
			TimKiem(ds, sonv);
			break;
		case 4:
			Xoa(ds, sonv);
			break;
		case 5:
			Sapxep(ds, sonv);
			cout << "\nDanh sach sau khi sap xep:";
			InDS(ds, sonv);
			break;
		case 6: 
		{
			string fileout = "Ra.txt";
			WriteFile(fileout, ds, sonv);
			break;
		}
		case 0:
			cout << "\nThoat chuong trinh!";
			break;
		}
	} while (chon != 0);
	int stop = _getch();
	return 0;
}