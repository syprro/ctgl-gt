#include <iostream>
#include <string>      // ← THIẾU DÒNG NÀY
#include <conio.h>
#include <Windows.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
#define MAX 100
string mn_chinh[] = {
	"CHƯƠNG TRÌNH TUYỂN DỤNG CỦA CÔNG TY X",
	"In danh sách thông tin công việc",
	"Sắp xếp thông tin công việc",
	"Tìm kiếm thông tin công việc",
	"Thêm thông tin công việc",
	"Xóa thông tin công việc",
	"Sửa thông tin công việc",
	"Kết thúc chương trình!."
};
string mn_sx[] = {
	"LỰA CHỌN PHƯƠNG PHÁP SẮP XẾP",
	"Bubblen Sort",
	"Selection Sort",
	"Shaker Sort",
	"Insertion Sort",
	"Interchange Sort",
	"BACK!"
};
string mn_tcsx[] = {
	"LỰA CHỌN TIÊU CHÍ",
	"Sắp xếp theo số thứ tự",
	"Sắp xếp theo tên",
	"Sắp xếp theo hạn nộp",
	"Sắp xếp theo số lượng nhân viên cần tuyển",
	"Sắp xếp theo mức lương",
	"BACK!"
};
string mn_tk[] = {
	"LỰA CHỌN PHƯƠNG PHÁP TÌM KIẾM",
	"Linear Search",
	"Binary Search",
	"BACK!"
};
string mn_tctk[] = {
	"LỰA CHỌN TIÊU CHÍ",
	"Tìm kiếm theo số thứ tự",
	"Tìm kiếm theo tên",
	"Tìm kiếm theo mức lương",
	"BACK!"
};
struct TuyenDung
{
	char stt[4];
	char tenCV[50];
	char ngay[3], thang[3], nam[3];
	int soluong;
	float luong;
};
void gotoxy(int x, int y)
{
	COORD toado;
	toado.X = x;
	toado.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), toado);
}
int ReadFile(string filename, TuyenDung ds[], int& sl)
{
	fstream file(filename.c_str());
	if (!file.is_open())
	{
		cout << "\nKhông thể mở file!";
		return 1;
	}
	string line;
	int i = 0;
	while (getline(file, line) && i < MAX)
	{
		stringstream ss(line);
		ss.getline(ds[i].stt, 4, ',');
		ss.getline(ds[i].tenCV, 50, ',');
		ss.getline(ds[i].ngay, 3, '/');
		ss.getline(ds[i].thang, 3, '/');
		ss.getline(ds[i].nam, 3, ',');
		ss >> ds[i].soluong;
		ss >> ds[i].luong;
		i++;
	}
	sl = i;
	return 0;
}
void InMenu(string mn[], int len)
{
	cout << mn[0] << endl;
	for (int i = 1; i < len; i++)
	{
		cout << i << "." << mn[i] << endl;
	}
}
void InDS(TuyenDung ds[], int sl, int vt = -1)
{
	int cot = 0;
	int dong = 1;
	gotoxy(cot, dong);       cout << "STT";
	gotoxy(cot + 8, dong);  cout << "Tên công việc";
	gotoxy(cot + 33, dong);  cout << "Hạn nộp";
	gotoxy(cot + 47, dong);  cout << "Số lượng";
	gotoxy(cot + 62, dong);  cout << "Mức lương";
	if (vt == -1) {
		for (int i = 0; i < sl; i++)
		{
			dong = i + 3;
			gotoxy(cot, dong);        cout << ds[i].stt;
			gotoxy(cot + 8, dong);   cout << ds[i].tenCV;
			gotoxy(cot + 33, dong);   cout << ds[i].ngay << "/" << ds[i].thang << "/" << ds[i].nam;
			gotoxy(cot + 50, dong);   cout << ds[i].soluong;
			gotoxy(cot + 64, dong);   cout << fixed << setprecision(0) << ds[i].luong;
		}
	}
	else
	{
		dong = 3;
		gotoxy(cot, dong);        cout << ds[vt].stt;
		gotoxy(cot + 8, dong);   cout << ds[vt].tenCV;
		gotoxy(cot + 33, dong);   cout << ds[vt].ngay << "/" << ds[vt].thang << "/" << ds[vt].nam;
		gotoxy(cot + 50, dong);   cout << ds[vt].soluong;
		gotoxy(cot + 64, dong);   cout << fixed << setprecision(0) << ds[vt].luong;
	}
}
void LinearSearchSTT(TuyenDung ds[], int sl)
{
	int stop;
	char x[4];
	do
	{
		cout << "\nNhập số thứ tự cần tìm: ";
		cin >> x;
		if (strlen(x) != 3)
		{
			system("cls");
			cout << "\nSố thứ tự không hợp lệ, vui lòng nhập lại!";
		}
	} while (strlen(x) != 3);
	for (int i = 0; i < sl; i++)
	{
		if (strcmp(ds[i].stt, x) == 0)
		{
			system("cls");
			InDS(ds, sl, i);  
			cout << "\n\n\nNhấn Enter để quay lại!";
			stop = _getch();
			return;
		}
	}
	system("cls");
	cout << "\nKhông tìm thấy công việc!";
	cout << "\n\n\nNhấn Enter để quay lại!";
	stop = _getch();
}
void LinearSearchTen(TuyenDung ds[], int sl)
{
	int stop;
	char ten[50];
	cin.ignore(); 
	cout << "\nNhập tên công việc cần tìm: ";
	cin.getline(ten, 50);
	for (int i = 0; i < sl; i++)
	{
		if (strcmp(ds[i].tenCV, ten) == 0)
		{
			system("cls");
			InDS(ds, sl, i);
			cout << "\n\n\nNhấn Enter để quay lại!";
			stop = _getch();
			return;
		}
	}
	system("cls");
	cout << "\nKhông tìm thấy thông tin công việc!";
	cout << "\n\n\nNhấn Enter để quay lại!";
	stop = _getch();
}
void LinearSearchLuong(TuyenDung ds[], int sl)
{
	int stop;
	float l;
	cout << "\nNhập mức lương của công việc mà bạn muốn tìm: ";
	cin >> l;
	for (int i = 0; i < sl; i++)
	{
		if (l==ds[i].luong)
		{
			system("cls");
			InDS(ds, sl, i);
			cout << "\n\n\nNhấn Enter để quay lại!";
			stop = _getch();
			return;
		}
	}
	system("cls");
	cout << "\nKhông tìm thấy mức lương phù hợp!";
	cout << "\n\n\nNhấn Enter để quay lại!";
	stop = _getch();
}
void BubbleSortSTT(TuyenDung ds[], int sl)
{
	TuyenDung t;
	for (int i = 0; i < sl; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if (strcmp(ds[j].stt, ds[j - 1].stt) < 0)
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BubbleSortTen(TuyenDung ds[], int sl)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if (strcmp(ds[j].tenCV, ds[j - 1].tenCV) < 0)
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BubbleSortHanNop(TuyenDung ds[], int sl)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if (
				strcmp(ds[j].nam, ds[j - 1].nam) < 0 ||
				(strcmp(ds[j].nam, ds[j - 1].nam) == 0 &&
					strcmp(ds[j].thang, ds[j - 1].thang) < 0) ||
				(strcmp(ds[j].nam, ds[j - 1].nam) == 0 &&
					strcmp(ds[j].thang, ds[j - 1].thang) == 0 &&
					strcmp(ds[j].ngay, ds[j - 1].ngay) < 0)
				)
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BubbleSortSoLuong(TuyenDung ds[], int sl)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if (ds[j].soluong < ds[j - 1].soluong)
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BubbleSortLuong(TuyenDung ds[], int sl)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if (ds[j].luong < ds[j - 1].luong)
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BinarySearchSTT(TuyenDung ds[], int sl)
{
	int stop;
	char x[4];
	do
	{
		cout << "\nNhập số thứ tự cần tìm: ";
		cin >> x;
		if (strlen(x) != 3)
		{
			system("cls");
			cout << "\nSố thứ tự không hợp lệ, vui lòng nhập lại!";
		}
	} while (strlen(x) != 3);
	BubbleSortSTT(ds, sl);
	int dau = 0;
	int cuoi = sl - 1;
	while (dau <= cuoi)
	{
		int giua = (dau + cuoi) / 2;
		int cmp = strcmp(ds[giua].stt, x);
		if (cmp == 0)
		{
			system("cls");
			InDS(ds, sl, giua);
			cout << "\n\n\nNhấn Enter để quay lại!";
			stop = _getch();
			return;
		}
		else if (cmp < 0)
		{
			dau = giua + 1;
		}
		else
		{
			cuoi = giua - 1;
		}
	}
	system("cls");
	cout << "\nKhông tìm thấy công việc!";
	cout << "\n\n\nNhấn Enter để quay lại!";
	stop = _getch();
}
void BinarySearchTen(TuyenDung ds[], int sl)
{
	int stop;
	char ten[50];
	cin.ignore();
	cout << "\nNhập tên công việc cần tìm: ";
	cin.getline(ten, 50);
	BubbleSortTen(ds, sl);
	int dau = 0, cuoi = sl - 1;
	while (dau <= cuoi)
	{
		int giua = (dau + cuoi) / 2;
		int cmp = strcmp(ds[giua].tenCV, ten);
		if (cmp == 0)
		{
			system("cls");
			InDS(ds, sl, giua);
			cout << "\n\n\nNhấn Enter để quay lại!";
			stop = _getch();
			return;
		}
		else if (cmp < 0)
		{
			dau = giua + 1;
		}
		else
		{
			cuoi = giua - 1;
		}
	}
	system("cls");
	cout << "\nKhông tìm thấy công việc!";
	cout << "\n\n\nNhấn Enter để quay lại!";
	stop = _getch();
}
void BinarySearchLuong(TuyenDung ds[], int sl)
{
	int stop;
	float l;
	cout << "\nNhập lương công việc cần tìm: ";
	cin >> l;
	BubbleSortLuong(ds, sl);
	int dau = 0, cuoi = sl - 1;
	while (dau <= cuoi)
	{
		int giua = (dau + cuoi) / 2;
		if (ds[giua].luong ==l)
		{
			system("cls");
			InDS(ds, sl, giua);
			cout << "\n\n\nNhấn Enter để quay lại!";
			stop = _getch();
			return;
		}
		else if (ds[giua].luong < l)
		{
			dau = giua + 1;
		}
		else
		{
			cuoi = giua - 1;
		}
	}
	system("cls");
	cout << "\nKhông tìm thấy công việc!";
	cout << "\n\n\nNhấn Enter để quay lại!";
	stop = _getch();
}
/*void WriteFile(string filename, TuyenDung ds[], int sl)
{

	ofstream outfile(filename.c_str());
	if (!outfile)
	{
		cout << "Lỗi mở file!";
		return;
	}
	for (int i = 0; i < sl; i++)
	{
		outfile << ds[i].stt << ", ";
		outfile << ds[i].tenCV << ", ";
		outfile << ds[i].ngay << "/" << ds[i].thang << "/" << ds[i].nam << ",";
		outfile << ds[i].soluong << " ";
		outfile << ds[i].luong << " " << endl;
	}
}*/
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	TuyenDung danhsach[MAX];
	int socv = 0, stop;
	string FileIn = "TD.txt";
	// Nếu không đọc được file -> kết thúc
	if (ReadFile(FileIn, danhsach, socv))
	{
		cout << "\nKhông đọc được file. Chương trình kết thúc!";
		stop=_getch();
		return 0;
	}	
	int chon, chontk, chonls, chonbs;
	int chonsx, chonsxbb;
	do
	{
		system("cls");
		InMenu(mn_chinh, size(mn_chinh));
		cout << "\nNhập lựa chọn: ";
		cin >> chon;
		switch (chon)
		{
		case 1:
			system("cls");
			InDS(danhsach, socv);
			stop=_getch();
			break;
		case 2:
			do
			{
				system("cls");
				InMenu(mn_sx, size(mn_sx));
				cout << "\nLựa chọn của bạn: ";
				cin >> chonsx;
				switch (chonsx)
				{
				case 1: // Bubble Sort
					do {
						system("cls");
						InMenu(mn_tcsx, size(mn_tcsx));
						cout << "\nChọn tiêu chí: ";
						cin >> chonsxbb;
						switch (chonsxbb)
						{
						case 1:
							system("cls");
							BubbleSortSTT(danhsach, socv);
							InDS(danhsach, socv);
							stop = _getch();
							break;
						case 2:
							system("cls");
							BubbleSortTen(danhsach, socv);
							InDS(danhsach, socv);
							stop = _getch();
							break;
						case 3:
							system("cls");
							BubbleSortHanNop(danhsach, socv);
							InDS(danhsach, socv);
							stop = _getch();
							break;
						case 4:
							system("cls");
							BubbleSortSoLuong(danhsach, socv);
							InDS(danhsach, socv);
							stop = _getch();
							break;
						case 5:
							system("cls");
							BubbleSortLuong(danhsach, socv);
							InDS(danhsach, socv);
							stop = _getch();
							break;
						case 6:
							system("cls");
							cout << "\nNhấn Enter để quay lại!";
							stop = _getch();
							break;
						}
					} while (chonsxbb != 6);
					break;
				case 6:
					system("cls");
					cout << "\nQuay trở lại.";
					stop = _getch();
					break;
				}
			} while (chonsx != 6);
			break;    
		case 3:
			do
			{
				system("cls");
				InMenu(mn_tk, size(mn_tk));
				cout << "\nLựa chọn của bạn: ";
				cin >> chontk;
				switch (chontk)
				{
				case 1:
					do
					{
						system("cls");
						InMenu(mn_tctk, size(mn_tctk));
						cout << "\nChọn tiêu chí: ";
						cin >> chonls;
						switch (chonls)
						{
						case 1:
							system("cls");
							LinearSearchSTT(danhsach, socv);
							break;
						case 2:
							system("cls");
							LinearSearchTen(danhsach, socv);
							break;
						case 3:
							system("cls");
							LinearSearchLuong(danhsach, socv);
							break;
						case 4:
							system("cls");
							cout << "\nQuay trở lại.";
							stop = _getch();
							break;
						}
					} while (chonls != 4);
					break;
				case 2:
					do
					{
						system("cls");
						InMenu(mn_tctk, size(mn_tctk));
						cout << "\nChọn tiêu chí: ";
						cin >> chonls;
						switch (chonls)
						{
						case 1:
							system("cls");
							BinarySearchSTT(danhsach, socv);
							break;
						case 2:
							system("cls");
							BinarySearchTen(danhsach, socv);
							break;
						case 3:
							system("cls");
							BinarySearchLuong(danhsach, socv);
							break;
						case 4:
							system("cls");
							cout << "\nQuay trở lại.";
							stop = _getch();
							break;
						}
					} while (chonls != 4);
					break;
				case 3:
					system("cls");
					cout << "\nQuay trở lại.";
					stop = _getch();
					break;
				}
			} while (chontk != 3);
			break;
		case 7:
			system("cls");
			cout << "\nKết thúc chương trình!";
			break;
		}
	} while (chon != 7);
	stop=_getch();
	return 0;
}