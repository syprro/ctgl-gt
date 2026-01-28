#include <iostream>
#include <string>      
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
	"In file thông tin",
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
string mn_sua[] = {
	"LỰA CHỌN NỘI DUNG SỬA",
	"Sửa theo tên công việc",
	"Sửa theo hạn nộp",
	"Sửa số lượng cần tuyển",
	"Sửa theo mức lương",
	"Sửa tất cả",
	"BACK!"
};
string mn_mdsx[] = {
	"LỰA CHỌN MỨC ĐỘ",
	"Tăng dần",
	"Giảm dần",
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
	file.close();
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
	gotoxy(cot + 8, dong);   cout << "Tên công việc";
	gotoxy(cot + 33, dong);  cout << "Hạn nộp";
	gotoxy(cot + 47, dong);  cout << "Số lượng";
	gotoxy(cot + 62, dong);  cout << "Mức lương";
	if (vt == -1) {
		for (int i = 0; i < sl; i++)
		{
			dong = i + 3;
			gotoxy(cot, dong);        cout << ds[i].stt;
			gotoxy(cot + 8, dong);    cout << ds[i].tenCV;
			gotoxy(cot + 33, dong);   cout << ds[i].ngay << "/" << ds[i].thang << "/" << ds[i].nam;
			gotoxy(cot + 50, dong);   cout << ds[i].soluong;
			gotoxy(cot + 64, dong);   cout << ds[i].luong;
		}
	}
	else
	{
		dong = 3;
		gotoxy(cot, dong);        cout << ds[vt].stt;
		gotoxy(cot + 8, dong);    cout << ds[vt].tenCV;
		gotoxy(cot + 33, dong);   cout << ds[vt].ngay << "/" << ds[vt].thang << "/" << ds[vt].nam;
		gotoxy(cot + 50, dong);   cout << ds[vt].soluong;
		gotoxy(cot + 64, dong);   cout << ds[vt].luong;
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
			cout << "\n\n\n Nhấn phím bất kì để quay lại...";
			stop = _getch();
			return;
		}
	}
	system("cls");
	cout << "\nKhông tìm thấy công việc!";
	cout << "\n\n\n Nhấn phím bất kì để quay lại...";
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
			cout << "\n\n\n Nhấn phím bất kì để quay lại...";
			stop = _getch();
			return;
		}
	}
	system("cls");
	cout << "\nKhông tìm thấy thông tin công việc!";
	cout << "\n\n\n Nhấn phím bất kì để quay lại...";
	stop = _getch();
}
void LinearSearchLuong(TuyenDung ds[], int sl)
{
	int stop;
	float l;
	int dem = 0;
	cout << "\nNhập mức lương của công việc mà bạn muốn tìm: ";
	cin >> l;
	system("cls");
	int cot = 0;
	int dong = 1;
	gotoxy(cot, dong);       cout << "STT";
	gotoxy(cot + 8, dong);   cout << "Tên công việc";
	gotoxy(cot + 33, dong);  cout << "Hạn nộp";
	gotoxy(cot + 47, dong);  cout << "Số lượng";
	gotoxy(cot + 62, dong);  cout << "Mức lương";
	for (int i = 0; i < sl; i++)
	{
		if (ds[i].luong == l)
		{
			dong = 3 + dem;
			gotoxy(cot, dong);        cout << ds[i].stt;
			gotoxy(cot + 8, dong);    cout << ds[i].tenCV;
			gotoxy(cot + 33, dong);   cout << ds[i].ngay << "/" << ds[i].thang << "/" << ds[i].nam;
			gotoxy(cot + 50, dong);   cout << ds[i].soluong;
			gotoxy(cot + 64, dong);   cout << ds[i].luong;
			dem++;
		}
	}
	if (dem == 0)
	{
		system("cls");
		cout << "\nKhông tìm thấy mức lương phù hợp!";
	}
	cout << "\n\n\n Nhấn phím bất kì để quay lại...";
	stop = _getch();
}
void BubbleSortSTT(TuyenDung ds[], int sl, int kieu)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if ((kieu == 1 && strcmp(ds[j].stt, ds[j - 1].stt) < 0) || (kieu == 2 && strcmp(ds[j].stt, ds[j - 1].stt) > 0))
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BubbleSortTen(TuyenDung ds[], int sl, int kieu)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if ((kieu == 1 && strcmp(ds[j].tenCV, ds[j - 1].tenCV) < 0) || (kieu == 2 && strcmp(ds[j].tenCV, ds[j - 1].tenCV) > 0))
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BubbleSortHanNop(TuyenDung ds[], int sl, int kieu)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if ((kieu == 1 && (strcmp(ds[j].nam, ds[j - 1].nam) < 0 ||
				(strcmp(ds[j].nam, ds[j - 1].nam) == 0 && strcmp(ds[j].thang, ds[j - 1].thang) < 0) ||
				(strcmp(ds[j].nam, ds[j - 1].nam) == 0 && strcmp(ds[j].thang, ds[j - 1].thang) == 0 && strcmp(ds[j].ngay, ds[j - 1].ngay) < 0)))
				||
				(kieu == 2 && (strcmp(ds[j].nam, ds[j - 1].nam) > 0 ||
					(strcmp(ds[j].nam, ds[j - 1].nam) == 0 && strcmp(ds[j].thang, ds[j - 1].thang) > 0) ||
					(strcmp(ds[j].nam, ds[j - 1].nam) == 0 && strcmp(ds[j].thang, ds[j - 1].thang) == 0 && strcmp(ds[j].ngay, ds[j - 1].ngay) > 0))))
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BubbleSortSoLuong(TuyenDung ds[], int sl, int kieu)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if ((kieu == 1 && ds[j].soluong < ds[j - 1].soluong) || (kieu == 2 && ds[j].soluong > ds[j - 1].soluong))
			{
				t = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = t;
			}
		}
}
void BubbleSortLuong(TuyenDung ds[], int sl, int kieu)
{
	TuyenDung t;
	for (int i = 0; i < sl - 1; i++)
		for (int j = sl - 1; j > i; j--)
		{
			if ((kieu == 1 && ds[j].luong < ds[j - 1].luong) || (kieu == 2 && ds[j].luong > ds[j - 1].luong))
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
	BubbleSortSTT(ds, sl, 1);
	system("cls");
	cout << "Lưu ý: Danh sách đã được sắp xếp theo số thứ tự công việc! (MĐ: Tăng dần)\n";
	int dau = 0;
	int cuoi = sl - 1;
	while (dau <= cuoi)
	{
		int giua = (dau + cuoi) / 2;
		int cmp = strcmp(ds[giua].stt, x);
		if (cmp == 0)
		{
			InDS(ds, sl, giua);
			cout << "\n\n\n Nhấn phím bất kì để quay lại...";
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
	cout << "\n\n\n Nhấn phím bất kì để quay lại...";
	stop = _getch();
}
void BinarySearchTen(TuyenDung ds[], int sl)
{
	int stop;
	char ten[50];
	cin.ignore();
	cout << "\nNhập tên công việc cần tìm: ";
	cin.getline(ten, 50);
	BubbleSortTen(ds, sl, 1);
	system("cls");
	cout << "Lưu ý: Danh sách đã được sắp xếp theo tên công việc! (MĐ: Tăng dần)\n";
	int dau = 0, cuoi = sl - 1;
	while (dau <= cuoi)
	{
		int giua = (dau + cuoi) / 2;
		int cmp = strcmp(ds[giua].tenCV, ten);

		if (cmp == 0)
		{
			InDS(ds, sl, giua);
			cout << "\n\n\n Nhấn phím bất kì để quay lại...";
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
	cout << "\n\n\n Nhấn phím bất kì để quay lại...";
	stop = _getch();
}
void BinarySearchLuong(TuyenDung ds[], int sl)
{
	int stop;
	float l;
	cout << "\nNhập lương công việc cần tìm: ";
	cin >> l;
	BubbleSortLuong(ds, sl, 1);
	system("cls");
	cout << "Lưu ý: Danh sách đã được sắp xếp theo mức lương! (MĐ: Tăng dần)\n";
	int dau = 0, cuoi = sl - 1;
	int giua;
	int vt = -1;  
	while (dau <= cuoi)
	{
		giua = (dau + cuoi) / 2;
		if (ds[giua].luong == l)
		{
			vt = giua;
			break;
		}
		else if (ds[giua].luong < l)
			dau = giua + 1;
		else
			cuoi = giua - 1;
	}
	int kq[MAX];
	int dem = 0;
	if (vt != -1)
	{
		int i = vt;
		while (i >= 0 && ds[i].luong == l)
		{
			kq[dem++] = i;
			i--;
		}
		i = vt + 1;
		while (i < sl && ds[i].luong == l)
		{
			kq[dem++] = i;
			i++;
		}
		int cot = 0, dong = 2;
		gotoxy(cot, dong);       cout << "STT";
		gotoxy(cot + 8, dong);   cout << "Tên công việc";
		gotoxy(cot + 33, dong);  cout << "Hạn nộp";
		gotoxy(cot + 47, dong);  cout << "Số lượng";
		gotoxy(cot + 62, dong);  cout << "Mức lương";
		for (int j = 0; j < dem; j++)
		{
			dong = 4 + j;
			gotoxy(cot, dong);        cout << ds[kq[j]].stt;
			gotoxy(cot + 8, dong);    cout << ds[kq[j]].tenCV;
			gotoxy(cot + 33, dong);   cout << ds[kq[j]].ngay << "/" << ds[kq[j]].thang << "/" << ds[kq[j]].nam;
			gotoxy(cot + 50, dong);   cout << ds[kq[j]].soluong;
			gotoxy(cot + 64, dong);   cout << ds[kq[j]].luong;
		}
	}
	else
	{
		cout << "\nKhông tìm thấy công việc!";
	}
	cout << "\n\n\n Nhấn phím bất kì để quay lại...";
	stop = _getch();
}
void Swap(TuyenDung& a, TuyenDung& b)
{
	TuyenDung sw = a;
	a = b;
	b = sw;
}
void SelectionSortSTT(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && strcmp(ds[j].stt, ds[min].stt) < 0) || (kieu == 2 && strcmp(ds[j].stt, ds[min].stt) > 0))
			{
				min = j;
			}
		}
		if (min != i)
		{
			Swap(ds[i], ds[min]);
		}
	}
}
void SelectionSortTen(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && strcmp(ds[j].tenCV, ds[min].tenCV) < 0) || (kieu == 2 && strcmp(ds[j].tenCV, ds[min].tenCV) > 0))
			{
				min = j;
			}
		}
		if (min != i)
		{
			Swap(ds[i], ds[min]);
		}
	}
}
void SelectionSortHanNop(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < sl; j++)
		{
			if (kieu == 1 &&(strcmp(ds[j].nam, ds[min].nam) < 0 || 
				(strcmp(ds[j].nam, ds[min].nam) == 0 &&strcmp(ds[j].thang, ds[min].thang) < 0) || 
				(strcmp(ds[j].nam, ds[min].nam) == 0 &&strcmp(ds[j].thang, ds[min].thang) == 0 && strcmp(ds[j].ngay, ds[min].ngay) < 0)))
			{
				min = j;
			}
			if (kieu == 2 && (strcmp(ds[j].nam, ds[min].nam) > 0 ||
				(strcmp(ds[j].nam, ds[min].nam) == 0 && strcmp(ds[j].thang, ds[min].thang) > 0) ||
				(strcmp(ds[j].nam, ds[min].nam) == 0 && strcmp(ds[j].thang, ds[min].thang) == 0 && strcmp(ds[j].ngay, ds[min].ngay) > 0)))
			{
				min = j;
			}
		}
		if (min != i)
		{
			Swap(ds[i], ds[min]);
		}
	}
}
void SelectionSortSoluong(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && ds[j].soluong < ds[min].soluong) || (kieu == 2 && ds[j].soluong > ds[min].soluong))
			{
				min = j;
			}
		}
		if (min != i)
		{
			Swap(ds[i], ds[min]);
		}
	}
}
void SelectionSortLuong(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && ds[j].luong < ds[min].luong) || (kieu == 2 && ds[j].luong > ds[min].luong))
			{
				min = j;
			}
		}
		if (min != i)
		{
			Swap(ds[i], ds[min]);
		}
	}
}
void ShakerSortSTT(TuyenDung ds[], int sl, int kieu)
{
	int l = 0, r = sl - 1, k = sl - 1;
	while (l < r)
	{
		for (int i = r; i > l; i--)
		{
			if ((kieu == 1 && strcmp(ds[i].stt, ds[i - 1].stt) < 0) || (kieu == 2 && strcmp(ds[i].stt, ds[i - 1].stt) > 0))
			{
				Swap(ds[i], ds[i - 1]);
				k = i;
			}
		}
		l = k;
		for (int j = l; j < r; j++)
		{
			if ((kieu == 1 && strcmp(ds[j].stt, ds[j + 1].stt) > 0) || (kieu == 2 && strcmp(ds[j].stt, ds[j + 1].stt) < 0))
			{
				Swap(ds[j], ds[j + 1]);
				k = j;
			}
		}
		r = k;
	}
}
void ShakerSortTen(TuyenDung ds[], int sl, int kieu)
{
	int l = 0, r = sl - 1, k = sl - 1;
	while (l < r)
	{
		for (int i = r; i > l; i--)
		{
			if ((kieu == 1 && strcmp(ds[i].tenCV, ds[i - 1].tenCV) < 0) || (kieu == 2 && strcmp(ds[i].tenCV, ds[i - 1].tenCV) > 0))
			{
				Swap(ds[i], ds[i - 1]);
				k = i;
			}
		}
		l = k;
		for (int j = l; j < r; j++)
		{
			if ((kieu == 1 && strcmp(ds[j].tenCV, ds[j + 1].tenCV) > 0) || (kieu == 2 && strcmp(ds[j].tenCV, ds[j + 1].tenCV) < 0))
			{
				Swap(ds[j], ds[j + 1]);
				k = j;
			}
		}
		r = k;
	}
}
void ShakerSortHanNop(TuyenDung ds[], int sl, int kieu)
{
	int l = 0, r = sl - 1, k = sl - 1;
	while (l < r)
	{
		for (int i = r; i > l; i--)
		{
			if ((kieu == 1 && (strcmp(ds[i].nam, ds[i - 1].nam) < 0 ||
				(strcmp(ds[i].nam, ds[i - 1].nam) == 0 && strcmp(ds[i].thang, ds[i - 1].thang) < 0) ||
				(strcmp(ds[i].nam, ds[i - 1].nam) == 0 && strcmp(ds[i].thang, ds[i - 1].thang) == 0 && strcmp(ds[i].ngay, ds[i - 1].ngay) < 0)))
				||
				(kieu == 2 && (strcmp(ds[i].nam, ds[i - 1].nam) > 0 ||
					(strcmp(ds[i].nam, ds[i - 1].nam) == 0 && strcmp(ds[i].thang, ds[i - 1].thang) > 0) ||
					(strcmp(ds[i].nam, ds[i - 1].nam) == 0 && strcmp(ds[i].thang, ds[i - 1].thang) == 0 && strcmp(ds[i].ngay, ds[i - 1].ngay) > 0))))
			{
				Swap(ds[i], ds[i - 1]);
				k = i;
			}
		}
		l = k;
		for (int j = l; j < r; j++)
		{
			if ((kieu == 1 && (strcmp(ds[j].nam, ds[j + 1].nam) > 0 ||
				(strcmp(ds[j].nam, ds[j + 1].nam) == 0 && strcmp(ds[j].thang, ds[j + 1].thang) > 0) ||
				(strcmp(ds[j].nam, ds[j + 1].nam) == 0 && strcmp(ds[j].thang, ds[j + 1].thang) == 0 && strcmp(ds[j].ngay, ds[j + 1].ngay) > 0)))
				||
				(kieu == 2 && (strcmp(ds[j].nam, ds[j + 1].nam) < 0 ||
					(strcmp(ds[j].nam, ds[j + 1].nam) == 0 && strcmp(ds[j].thang, ds[j + 1].thang) < 0) ||
					(strcmp(ds[j].nam, ds[j + 1].nam) == 0 && strcmp(ds[j].thang, ds[j + 1].thang) == 0 && strcmp(ds[j].ngay, ds[j + 1].ngay) < 0))))
			{
				Swap(ds[j], ds[j + 1]);
				k = j;
			}
		}
		r = k;
	}
}
void ShakerSortSoluong(TuyenDung ds[], int sl, int kieu)
{
	int l = 0, r = sl - 1, k = sl - 1;
	while (l < r)
	{
		for (int i = r; i > l; i--)
		{
			if ((kieu == 1 && ds[i].soluong < ds[i - 1].soluong) || (kieu == 2 && ds[i].soluong > ds[i - 1].soluong))
			{
				Swap(ds[i], ds[i - 1]);
				k = i;
			}
		}
		l = k;
		for (int j = l; j < r; j++)
		{
			if ((kieu == 1 && ds[j].soluong > ds[j + 1].soluong) || (kieu == 2 && ds[j].soluong < ds[j + 1].soluong))
			{
				Swap(ds[j], ds[j + 1]);
				k = j;
			}
		}
		r = k;
	}
}
void ShakerSortLuong(TuyenDung ds[], int sl, int kieu)
{
	int l = 0, r = sl - 1, k = sl - 1;
	while (l < r)
	{
		for (int i = r; i > l; i--)
		{
			if ((kieu == 1 && ds[i].luong < ds[i - 1].luong) || (kieu == 2 && ds[i].luong > ds[i - 1].luong))
			{
				Swap(ds[i], ds[i - 1]);
				k = i;
			}
		}
		l = k;
		for (int j = l; j < r; j++)
		{
			if ((kieu == 1 && ds[j].luong > ds[j + 1].luong) || (kieu == 2 && ds[j].luong < ds[j + 1].luong))
			{
				Swap(ds[j], ds[j + 1]);
				k = j;
			}
		}
		r = k;
	}
}
void InsertionSortSTT(TuyenDung ds[], int sl, int kieu)
{
	int t;
	TuyenDung a;
	for (int i = 1; i < sl; i++)
	{
		a = ds[i];
		t = i - 1;

		while (t >= 0 &&
			((kieu == 1 && strcmp(a.stt, ds[t].stt) < 0) || (kieu == 2 && strcmp(a.stt, ds[t].stt) > 0)))
		{
			ds[t + 1] = ds[t];
			t--;
		}
		ds[t + 1] = a;
	}
}
void InsertionSortTen(TuyenDung ds[], int sl, int kieu)
{
	int t;
	TuyenDung a;
	for (int i = 1; i < sl; i++)
	{
		a = ds[i];
		t = i - 1;
		while (t >= 0 && 
			((kieu == 1 && strcmp(a.tenCV, ds[t].tenCV) < 0) || (kieu == 2 && strcmp(a.tenCV, ds[t].tenCV) > 0)))
		{
			ds[t + 1] = ds[t];
			t--;
		}
		ds[t + 1] = a;
	}
}
void InsertionSortHanNop(TuyenDung ds[], int sl, int kieu)
{
	int t;
	TuyenDung a;

	for (int i = 1; i < sl; i++)
	{
		a = ds[i];
		t = i - 1;

		while (t >= 0 && ((kieu == 1 && (strcmp(a.nam, ds[t].nam) < 0 ||
			(strcmp(a.nam, ds[t].nam) == 0 && strcmp(a.thang, ds[t].thang) < 0) ||
			(strcmp(a.nam, ds[t].nam) == 0 && strcmp(a.thang, ds[t].thang) == 0 && strcmp(a.ngay, ds[t].ngay) < 0)))
			|| (kieu == 2 && (strcmp(a.nam, ds[t].nam) > 0 ||
				(strcmp(a.nam, ds[t].nam) == 0 && strcmp(a.thang, ds[t].thang) > 0) ||
				(strcmp(a.nam, ds[t].nam) == 0 && strcmp(a.thang, ds[t].thang) == 0 && strcmp(a.ngay, ds[t].ngay) > 0)))))
		{
			ds[t + 1] = ds[t];
			t--;
		}
		ds[t + 1] = a;
	}
}
void InsertionSortSoluong(TuyenDung ds[], int sl, int kieu)
{
	int t;
	TuyenDung a;
	for (int i = 1; i < sl; i++)
	{
		a = ds[i];
		t = i - 1;
		while (t >= 0 && ((kieu == 1 && a.soluong < ds[t].soluong) || (kieu == 2 && a.soluong > ds[t].soluong)))
		{
			ds[t + 1] = ds[t];
			t--;
		}
		ds[t + 1] = a;
	}
}
void InsertionSortLuong(TuyenDung ds[], int sl, int kieu)
{
	int t;
	TuyenDung a;
	for (int i = 1; i < sl; i++)
	{
		a = ds[i];
		t = i - 1;
		while (t >= 0 && ((kieu == 1 && a.luong < ds[t].luong) || (kieu == 2 && a.luong > ds[t].luong)))
		{
			ds[t + 1] = ds[t];
			t--;
		}
		ds[t + 1] = a;
	}
}
void InterchangeSortSTT(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && strcmp(ds[i].stt, ds[j].stt) > 0) || (kieu == 2 && strcmp(ds[i].stt, ds[j].stt) < 0))
			{
				Swap(ds[i], ds[j]);
			}
		}
	}
}
void InterchangeSortTen(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && strcmp(ds[i].tenCV, ds[j].tenCV) > 0) || (kieu == 2 && strcmp(ds[i].tenCV, ds[j].tenCV) < 0))
			{
				Swap(ds[i], ds[j]);
			}
		}
	}
}
void InterchangeSortHanNop(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && (strcmp(ds[i].nam, ds[j].nam) > 0 ||
				(strcmp(ds[i].nam, ds[j].nam) == 0 && strcmp(ds[i].thang, ds[j].thang) > 0) ||
				(strcmp(ds[i].nam, ds[j].nam) == 0 && strcmp(ds[i].thang, ds[j].thang) == 0 && strcmp(ds[i].ngay, ds[j].ngay) > 0)))
				||
				(kieu == 2 && (strcmp(ds[i].nam, ds[j].nam) < 0 ||
					(strcmp(ds[i].nam, ds[j].nam) == 0 && strcmp(ds[i].thang, ds[j].thang) < 0) ||
					(strcmp(ds[i].nam, ds[j].nam) == 0 && strcmp(ds[i].thang, ds[j].thang) == 0 && strcmp(ds[i].ngay, ds[j].ngay) < 0))))
			{
				Swap(ds[i], ds[j]);
			}
		}
	}
}
void InterchangeSortSoluong(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && ds[i].soluong > ds[j].soluong) || (kieu == 2 && ds[i].soluong < ds[j].soluong))
			{
				Swap(ds[i], ds[j]);
			}
		}
	}
}
void InterchangeSortLuong(TuyenDung ds[], int sl, int kieu)
{
	for (int i = 0; i < sl - 1; i++)
	{
		for (int j = i + 1; j < sl; j++)
		{
			if ((kieu == 1 && ds[i].luong > ds[j].luong) || (kieu == 2 && ds[i].luong < ds[j].luong))
			{
				Swap(ds[i], ds[j]);
			}
		}
	}
}
void ThemTTCV(TuyenDung ds[], int& sl)
{
	if (sl >= MAX)
	{
		cout << "\nDanh sách đã đầy!";
		int stop = _getch();
		return;
	}
	int vt;
	TuyenDung x;
	do
	{
		cout << "\nNhập vị trí muốn thêm (0 -> " << sl << "): ";
		cin >> vt;
		if (vt < 0 || vt > sl)
			cout << "Vị trí không hợp lệ!\n";
	} while (vt < 0 || vt > sl);
	for (int i = sl; i > vt; i--)
	{
		ds[i] = ds[i - 1];
	}
	int trung;
	do
	{
		trung = 0;
		cout << "Nhập số thứ tự (3 ký tự): ";
		cin >> x.stt;
		if (strlen(x.stt) != 3)
		{
			cout << "STT phải đúng 3 ký tự!\n";
			trung = 1;
		}
		else
		{
			for (int i = 0; i < sl; i++)
			{
				if (strcmp(x.stt, ds[i].stt) == 0)
				{
					cout << "STT đã tồn tại, vui lòng nhập lại!\n";
					trung = 1;
					break;
				}
			}
		}
	} while (trung == 1);
	cin.ignore();
	cout << "Nhập tên công việc: ";
	cin.getline(x.tenCV, 50);
	cout << "Nhập ngày hạn nộp (dd): ";
	cin >> x.ngay;
	cout << "Nhập tháng hạn nộp (mm): ";
	cin >> x.thang;
	cout << "Nhập năm hạn nộp (yy): ";
	cin >> x.nam;
	cout << "Nhập số lượng cần tuyển: ";
	cin >> x.soluong;
	cout << "Nhập mức lương: ";
	cin >> x.luong;
	ds[vt] = x;
	sl++;
	cout << "\nThêm công việc thành công!";
	cout << "\nMuốn xem danh sách sau khi thêm, nhấn 1 ngay sau khi bạn nhấn ENTER!";
	int stop = _getch();
}
void XoaTTCV(TuyenDung ds[], int& sl)
{
	if (sl == 0)
	{
		cout << "\nDanh sách rỗng, không thể xoá!";
		int stop = _getch();
		return;
	}
	int chon;
	system("cls");
	cout << "LỰA CHỌN XÓA";
	cout << "\n1. Xóa theo vị trí";
	cout << "\n2. Xóa theo STT";
	cout << "\n3. Quay lại";
	cout << "\nChọn: ";
	cin >> chon;
	switch (chon)
	{
	case 1:
	{
		int vtx;
		do
		{
			cout << "\nNhập vị trí cần xóa (0 -> " << sl - 1 << "): ";
			cin >> vtx;
			if (vtx < 0 || vtx >= sl)
				cout << "Vị trí xóa không hợp lệ!\n";
		} while (vtx < 0 || vtx >= sl);
		for (int i = vtx; i < sl - 1; i++)
		{
			ds[i] = ds[i + 1];
		}
		sl--;
		cout << "\nXóa thành công!";
		int stop = _getch();
		break;
	}
	case 2: 
	{
		char stt[4];
		int tim = -1;
		cout << "\nNhập STT cần xóa: ";
		cin >> stt;
		for (int i = 0; i < sl; i++)
		{
			if (strcmp(ds[i].stt, stt) == 0)
			{
				tim = i;
				break;
			}
		}
		if (tim == -1)
		{
			cout << "\nKhông tìm thấy STT cần xóa!";
			int stop = _getch();
			break;
		}
		for (int i = tim; i < sl - 1; i++)
		{
			ds[i] = ds[i + 1];
		}
		sl--;
		cout << "\nXóa thành công!";
		int stop = _getch();
		break;
	}
	case 3:
		return;
	}
}
void SuaTTCV(TuyenDung ds[], int& sl)
{
	int stop;
	if (sl == 0)
	{
		cout << "\nDanh sách rỗng, không thể sửa!";
		stop = _getch();
		return;
	}
	char stt[4];
	int tim = -1;
	system("cls");
	cout << "SỬA THÔNG TIN CÔNG VIỆC";
	cout << "\nNhập STT cần sửa: ";
	cin >> stt;
	for (int i = 0; i < sl; i++)
	{
		if (strcmp(ds[i].stt, stt) == 0)
		{
			tim = i;
			break;
		}
	}
	if (tim == -1)
	{
		cout << "\nKhông tìm thấy STT cần sửa!";
		stop = _getch();
		return;
	}
	int chon;
	do
	{
		system("cls");
		InMenu(mn_sua, size(mn_sua));
		cout << "\nLựa chọn của bạn: ";
		cin >> chon;
		switch (chon)
		{
		case 1:
			cin.ignore();
			cout << "Nhập tên công việc mới: ";
			cin.getline(ds[tim].tenCV, 50);
			cout << "\nĐã cập nhật!";
			stop = _getch();
			break;
		case 2:
			cout << "Nhập ngày (dd): ";
			cin >> ds[tim].ngay;
			cout << "Nhập tháng (mm): ";
			cin >> ds[tim].thang;
			cout << "Nhập năm (yy): ";
			cin >> ds[tim].nam;
			cout << "\nĐã cập nhật!";
			stop = _getch();
			break;
		case 3:
			cout << "Nhập số lượng mới: ";
			cin >> ds[tim].soluong;
			cout << "\nĐã cập nhật!";
			stop = _getch();
			break;
		case 4:
			cout << "Nhập mức lương mới: ";
			cin >> ds[tim].luong;
			cout << "\nĐã cập nhật!";
			stop = _getch();
			break;
		case 5:
			cin.ignore();
			cout << "Nhập tên công việc: ";
			cin.getline(ds[tim].tenCV, 50);
			cout << "Nhập ngày (dd): ";
			cin >> ds[tim].ngay;
			cout << "Nhập tháng (mm): ";
			cin >> ds[tim].thang;
			cout << "Nhập năm (yy): ";
			cin >> ds[tim].nam;
			cout << "Nhập số lượng: ";
			cin >> ds[tim].soluong;
			cout << "Nhập mức lương: ";
			cin >> ds[tim].luong;
			cout << "\nĐã cập nhật tất cả thông tin!";
			stop = _getch();
			break;
		case 6:
			return;
		}
	} while (chon != 6);
}
void WriteFile(string filename, TuyenDung ds[], int sl)
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
}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	TuyenDung danhsach[MAX];
	int socv = 0, stop;
	string FileIn = "TuyenDung.txt";
	// Nếu không đọc được file -> kết thúc
	if (ReadFile(FileIn, danhsach, socv))
	{
		cout << "\nKhông đọc được file. Chương trình kết thúc!";
		stop = _getch();
		return 0;
	}
	int chon, chontk, chonls, chonmd;
	int chonsx, chontcsx;
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
			stop = _getch();
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
						cin >> chontcsx;
						switch (chontcsx)
						{
						case 1:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									BubbleSortSTT(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									BubbleSortSTT(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 2:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									BubbleSortTen(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									BubbleSortTen(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 3:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									BubbleSortHanNop(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									BubbleSortHanNop(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 4:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									BubbleSortSoLuong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									BubbleSortSoLuong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 5:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									BubbleSortLuong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									BubbleSortLuong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 6:
							system("cls");
							cout << "\n Nhấn phím bất kì để quay lại...";
							stop = _getch();
							break;
						}
					} while (chontcsx != 6);
					break;
				case 2: //Selection Sort
					do {
						system("cls");
						InMenu(mn_tcsx, size(mn_tcsx));
						cout << "\nChọn tiêu chí: ";
						cin >> chontcsx;
						switch (chontcsx)
						{
						case 1:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									SelectionSortSTT(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									SelectionSortSTT(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 2:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									SelectionSortTen(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									SelectionSortTen(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 3:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									SelectionSortHanNop(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									SelectionSortHanNop(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 4:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									SelectionSortSoluong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									SelectionSortSoluong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 5:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									SelectionSortLuong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									SelectionSortLuong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 6:
							system("cls");
							cout << "\n Nhấn phím bất kì để quay lại...";
							stop = _getch();
							break;
						}
					} while (chontcsx != 6);
					break;
				case 3: //Shaker Sort
					do {
						system("cls");
						InMenu(mn_tcsx, size(mn_tcsx));
						cout << "\nChọn tiêu chí: ";
						cin >> chontcsx;
						switch (chontcsx)
						{
						case 1:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									ShakerSortSTT(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									ShakerSortSTT(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 2:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									ShakerSortTen(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									ShakerSortTen(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 3:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									ShakerSortHanNop(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									ShakerSortHanNop(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 4:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									ShakerSortSoluong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									ShakerSortSoluong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 5:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									ShakerSortLuong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									ShakerSortLuong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 6:
							system("cls");
							cout << "\n Nhấn phím bất kì để quay lại...";
							stop = _getch();
							break;
						}
					} while (chontcsx != 6);
					break;
				case 4: //Insertion Sort
					do {
						system("cls");
						InMenu(mn_tcsx, size(mn_tcsx));
						cout << "\nChọn tiêu chí: ";
						cin >> chontcsx;
						switch (chontcsx)
						{
						case 1:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InsertionSortSTT(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InsertionSortSTT(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 2:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InsertionSortTen(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InsertionSortTen(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 3:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InsertionSortHanNop(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InsertionSortHanNop(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 4:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InsertionSortSoluong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InsertionSortSoluong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 5:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InsertionSortLuong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InsertionSortLuong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 6:
							system("cls");
							cout << "\n Nhấn phím bất kì để quay lại...";
							stop = _getch();
							break;
						}
					} while (chontcsx != 6);
					break;
				case 5: //Interchange Sort
					do {
						system("cls");
						InMenu(mn_tcsx, size(mn_tcsx));
						cout << "\nChọn tiêu chí: ";
						cin >> chontcsx;
						switch (chontcsx)
						{
						case 1:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InterchangeSortSTT(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InterchangeSortSTT(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 2:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InterchangeSortTen(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InterchangeSortTen(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 3:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InterchangeSortHanNop(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InterchangeSortHanNop(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 4:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InterchangeSortSoluong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InterchangeSortSoluong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 5:
							do
							{
								system("cls");
								InMenu(mn_mdsx, size(mn_mdsx));
								cout << "\n Mời bạn chọn: ";
								cin >> chonmd;
								switch (chonmd)
								{
								case 1:
									system("cls");
									InterchangeSortLuong(danhsach, socv, 1);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 2:
									system("cls");
									InterchangeSortLuong(danhsach, socv, 2);
									InDS(danhsach, socv);
									stop = _getch();
									break;
								case 3:
									cout << "\n Nhấn phím bất kì để quay lại...";
									stop = _getch();
									break;
								}
							} while (chonmd != 3);
							break;
						case 6:
							system("cls");
							cout << "\n Nhấn phím bất kì để quay lại...";
							stop = _getch();
							break;
						}
					} while (chontcsx != 6);
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
							cout << "\n Nhấn phím bất kì để quay lại...";
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
							cout << "\n Nhấn phím bất kì để quay lại...";
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
		case 4:
			system("cls");
			ThemTTCV(danhsach, socv);
			break;
		case 5:
			system("cls");
			XoaTTCV(danhsach, socv);
			break;
		case 6:
			system("cls");
			SuaTTCV(danhsach, socv);
			break;
		case 7:
		{
			system("cls");
			string fileout = "Output.txt";
			WriteFile(fileout, danhsach, socv);
			cout << "\nĐã ghi danh sách ra file!";
			stop = _getch();
			break;
		}
		case 8:
			system("cls");
			cout << "\nKết thúc chương trình!";
			break;
		}
	} while (chon != 8);
	stop = _getch();
	return 0;
}