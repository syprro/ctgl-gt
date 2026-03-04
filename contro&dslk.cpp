#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
struct NhanVien
{
	char msnv[5];
	char hoten[50];
	char phong[20];
	float luong;
};
void NhapNV(NhanVien& nv)
{
	cout << "\nMSNV: ";
	cin.getline(nv.msnv, 5);
	cout << "\nHo tên: ";
	cin.getline(nv.hoten, 50);
	cout << "\nPhong ban: ";
	cin.getline(nv.phong, 20);
	cout << "\nLuong: ";
	cin >> nv.luong;
	cin.ignore();
}
void XuatNV(NhanVien nv)
{
	cout << nv.msnv << "\t";
	cout << nv.hoten << "\t";
	cout << nv.phong << "\t";
	cout << nv.luong << endl;
}
// DANH SÁCH LIÊN KẾT ĐƠN
struct Node
{
	//nội dung của Node
	NhanVien info;
	//con tro
	Node *next;
};
//Khai báo danh sách
typedef Node* pNode;
struct LinkList
{
	pNode Head;
	pNode Tail;
};
//Hàm khởi tạo danh sách
void Initial(LinkList& l)
{
	l.Head = l.Tail = nullptr;
}
int IsEmpty(LinkList l)
{
	if (l.Head == nullptr) return 1;
	else return 0;
}
//Hàm tạo node
pNode CreateNode(NhanVien x)
{
	pNode p = new Node;
	//kiểm tra tình trạng tạo node
	if (!p)
		return 0;
	p->info = x;
	p->next = nullptr;
	return p;
}
// hàm thêm 1 nút vào đầu danh sách
void AddtoHead(LinkList& l, NhanVien x)
{
	pNode p = CreateNode(x);
	if (!p)
	{
		cout << "\n Không tạo được nút";
		return;
	}
	//TH danh sách rỗng
	if (IsEmpty(l))
	{
		l.Head = p;
		l.Tail = p;
	}
	else
	{
		p->next = l.Head;
		l.Head = p;
	}
}
//hàm in ds
void XuatList(LinkList l)
{
	pNode p = l.Head;
	cout << "\nMSNV\tHOTEN\tPhong\tLuong\t\n";
	while (p != nullptr)
	{
		XuatNV(p->info);
		p = p->next;
	}
	////for
	//pNode p1;
	//for (p1 = l.Head; p1 != nullptr; p1->next)
	//{
	//	cout << p->info << "\t";
	//}
}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	//khai báo, gọi hàm
	LinkList list;
	Initial(list);
	NhanVien n1, n2;
	NhapNV(n1);
	NhapNV(n2);
	AddtoHead(list, n1);
	AddtoHead(list, n2);
	cout << "\nDANH SÁCH LIÊN KẾT\n";
	XuatList(list);
	int stop = _getch();
	return 0;
}
