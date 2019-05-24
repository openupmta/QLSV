// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<stdio.h>
#include <math.h>
#include<cstdlib>
#include <regex>
#define cRong 119
#define cCao 29
#define sizemenu 35
#define N 1000
#pragma warning(disable : 4996)


using namespace std;
typedef struct ThongKe
{
	int stt;
	string malop;
	int tong;
	int xuat_sac, gioi, kha, TB, yeu;
};
typedef struct DataType
{
	char MaLop[11];
	char MaSinhVien[11];
	string HoTen;
	int NgS, TS, NS;
	float DiemTB;
};

typedef struct Node
{
	DataType data;
	Node* next; //tro den vi tri Node tiep theo
	Node* prev; // tro den vi tri Node sau no
};
typedef struct List
{
	Node* head;
	Node* tail;
};

//Cac thao tac tren danh sach
void Init(List& list);
Node* creatNode(DataType x);
bool isEmpty(List list);

//Cac thao tac chen
void addHead(List& list, DataType x);
void addTail(List& list, DataType x);
void insertInList(List& list, int k, DataType x);


//Cac thao tac xoa
int phimDiChuyen(int c, int choice, int line);
void chuanHoaDauCuoi(string& str);
void xoaKhoangTrang(string& str);
void DelHead(List& list);
void DelTail(List& list);
void DelInList(List& list, int k);
void display(List list);
void display2(List list, float trang);
void displayInit();
void display1(List list, int stt);

void input(List& list);
void output(const char* fileName, List list);
void inText(List list);

void SetSizeConsole();
void setColor(int x);
void gotoxy(int x, int y);
void chonM(List& list);
void background();
void backgroundDS();
void menuChinh(int choice);
void menuM1(int choice);
void khungThongKe();
void chonM4_5(List list);

void sapXepDiemTB(List& list, DataType x);
void sapXepML(List& list, DataType x);
void sapXepMSV(List& list, DataType x);
void sapXepNS(List& list, DataType x);
void sapXepHoTen(List& list, DataType x);

void inThongKe(ThongKe tk[], int count);
void kiemTraDiem(float diem, int& xuat_sac, int& gioi, int& kha, int& TB, int& yeu, int& soSV);
void timHocLucSV(List list);
void thongKe(List list);
int binarySearch(List& l1, DataType arr[], float from, float to, int left1) ;
void timKiemDiem(List list, float from, float to, List& temp, int& temp1);
void timKiemMSV(List list, char* x, List& temp, int& temp1);
void timKiemHoTen(List list, string x, List& temp, int& temp1);
void timKiemTheoNgaySinh(List list, string x, List& temp, int& temp1);
void timKiemMaLop(List list, string x, List& temp, int& stt1);

void menuChinh(int choice);
void menuM1(int choice);
void menuM3_2(int choice);
void menuM3_1(int choice);
void menuM4_2(int choice);
void menuM4_1(int choice);
void backgroundDS();
void backgroundMenu();
void background();

void khungThongKe();
void bubbleSort(List& list);
void insertSort(List& list);
void quickSort(List& list, Node* low, Node* high, int left, int right);
int compareDiem(DataType data1, DataType data3);
int compareMSV(DataType data1, DataType data3);
int compareNS(DataType data1, DataType data3);
int compareHT(DataType data1, DataType data3);

void chonM1(List& list);
void chonM2(List& list);
void chonM3(List& list);
void chonM4(List list);
void chonM5(List list);

// TODO: add headers that you want to pre-compile here
#endif //PCH_H