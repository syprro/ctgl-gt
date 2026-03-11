#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
using namespace std;
void gotoxy(int x, int y)
{
	COORD toado;
	toado.X = x;
	toado.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), toado);
}
struct TuyenDung
{
	char stt[4];
	char tenCV[50];
	char ngay[3], thang[3], nam[3];
	int soluong;
	float luong;
};
void NhapNV(TuyenDung& x)
{
	cout << "\n Nhập STT: ";
	cin.getline(x.stt, 4);
	cout << "\n Nhập Tên Công Việc: ";
	cin.getline(x.tenCV, 50);
	cout << "\n Nhập ngày: ";
	cin.getline(x.ngay, 3);
	cout << "\n Nhập tháng: ";
	cin.getline(x.thang, 3);
	cout << "\n Nhập năm: ";
	cin.getline(x.nam, 3);
	cout << "\n Nhập số lượng NV: ";
	cin >> x.soluong;
	cout << "\n Nhập lương: ";
	cin >> x.luong;
	cin.ignore();
}
struct Node
{
	TuyenDung info;
	Node* next;
};
typedef Node* pNode;
struct LinkList
{
	pNode Head;
	pNode Tail;
};
void Initial(LinkList& l)
{
	l.Head = l.Tail = NULL;
}
int IsEmpty(LinkList l)
{
	if (l.Head == NULL) return 1;
	else return 0;
}
pNode CreateNode(TuyenDung x)
{
	pNode p = new Node;
	if (!p)
		return 0;
	p->info = x;
	p->next = NULL;
	return p;
}
void AddtoHead(LinkList& l, TuyenDung x)
{
	pNode p = CreateNode(x);
	if (!p)
		return;
	if (IsEmpty(l))
	{
		l.Head = l.Tail = p;
	}
	else
	{
		p->next = l.Head;
		l.Head = p;
	}
}
//thêm cuối
/*void AddtoTail(LinkList& l, TuyenDung x)
{
	pNode p = CreateNode(x);   // tạo node mới
	if (!p)
		return;

	if (IsEmpty(l))            // nếu danh sách rỗng
	{
		l.Head = l.Tail = p;
	}
	else                       // nếu danh sách đã có phần tử
	{
		l.Tail->next = p;      // nối node cuối với node mới
		l.Tail = p;            // cập nhật Tail
	}
}*/
int RF(string filename, LinkList& l)
{
	fstream file(filename.c_str());
	if (!file.is_open())
	{
		cout << "Không thể mở file!";
		return 0;
	}
	string line;
	while (getline(file, line))
	{
		TuyenDung x;
		stringstream ss(line);
		ss.getline(x.stt, 4, ',');
		ss.getline(x.tenCV, 50, ',');
		ss.getline(x.ngay, 3, '/');
		ss.getline(x.thang, 3, '/');
		ss.getline(x.nam, 3, ',');
		ss >> x.soluong;
		ss.ignore();
		ss >> x.luong;
		AddtoHead(l, x);
	}
	file.close();
	return 1;
}
void AddafterQ(LinkList& l, char qs[], TuyenDung x)
{
	pNode q = l.Head;
	while (q != NULL)
	{
		if (strcmp(q->info.stt, qs) == 0)
		{
			pNode p = CreateNode(x);
			if (!p) return;
			p->next = q->next;
			q->next = p;
			return;
		}
		q = q->next;
	}
	cout << "\n Không tìm thấy số thứ tự để chèn!";
}
/*void PrintList(LinkList l)
{
	int cot = 0;
	int dong = 1;
	gotoxy(cot, dong);       cout << "STT";
	gotoxy(cot + 8, dong);   cout << "TÊN CÔNG VIỆC";
	gotoxy(cot + 33, dong);  cout << "HẠN NỘP";
	gotoxy(cot + 47, dong);  cout << "SỐ LƯỢNG";
	gotoxy(cot + 62, dong);  cout << "MỨC LƯƠNG";
	pNode p = l.Head;
	int i = 0;
	while (p != NULL)
	{
		dong = i + 3;
		gotoxy(cot, dong);
		cout << p->info.stt;
		gotoxy(cot + 8, dong);
		cout << p->info.tenCV;
		gotoxy(cot + 33, dong);
		cout << p->info.ngay << "/" << p->info.thang << "/" << p->info.nam;
		gotoxy(cot + 50, dong);
		cout << p->info.soluong;
		gotoxy(cot + 64, dong);
		cout << p->info.luong;
		p = p->next;
		i++;
	}
}
void PrintOne(TuyenDung x)
{
	int cot = 0;
	int dong = 7;
	gotoxy(cot, dong);       cout << x.stt;
	gotoxy(cot + 8, dong);   cout << x.tenCV;
	gotoxy(cot + 33, dong);  cout << x.ngay << "/" << x.thang << "/" << x.nam;
	gotoxy(cot + 50, dong);  cout << x.soluong;
	gotoxy(cot + 64, dong);  cout << x.luong;
}*/
void PrintList(LinkList l)
{
	pNode p = l.Head;
	cout << "STT" << "\t" << "TÊN CÔNG VIỆC" << "\t" << "HẠN NỘP" << " \t" << "SL" << "\t" << "LƯƠNG" << endl;

	while (p != nullptr)
	{
		cout << p->info.stt << "\t";
		cout << p->info.tenCV << "\t";
		cout << p->info.ngay << "/" << p->info.thang << "/" << p->info.nam << "\t";
		cout << p->info.soluong << "\t";
		cout << p->info.luong << endl;
		p = p->next;
	}
}
void PrintOne(TuyenDung x)
{
	cout << x.stt << "\t"
		<< x.tenCV << "\t"
		<< x.ngay << "/" << x.thang << "/" << x.nam << "\t"
		<< x.soluong << "\t"
		<< x.luong << endl;
}
pNode Search(LinkList l, char x[])
{
	pNode p = l.Head;
	while (p != NULL)
	{
		if (strcmp(p->info.stt, x) == 0)
			return p;
		else p = p->next;
	}
	return NULL;
}
//xóa đầu
void DeleteFirst(LinkList& l)
{
	pNode p = l.Head;
	l.Head = l.Head->next;
	p->next = NULL;
	delete p;
}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	LinkList list;
	Initial(list);
	RF("TuyenDung.txt", list);
	cout << "DANH SÁCH LIÊN KẾT" << endl;
	PrintList(list);
	//tìm
	char x[4];
	cout << "\n Nhập STT cần tìm: ";
	cin.getline(x, 4);
	pNode p = Search(list, x);
	if (p)
		PrintOne(p->info);
	else
		cout << "\n Không có số thứ tự này!";
	//thêm sau Q
	TuyenDung td;
	char qs[4];
	cout << "\n Nhập STT để thêm sau: ";
	cin.getline(qs, 4);
	NhapNV(td);
	AddafterQ(list, qs, td);
	cout << "\nDANH SACH SAU KHI THEM SAU Q" << endl;
	PrintList(list);
	//xóa đầu
	DeleteFirst(list);
	cout << "\n DANH SÁCH SAU KHI XÓA PHẦN TỬ ĐẦU" << endl;
	PrintList(list);
	int stop = _getch();
	return 0;
}