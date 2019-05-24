#include "pch.h"
int l_stt = 5, l_malop = 10, l_masv = 10, l_ngaysinh = 15, l_diemtb = 7;
int n;
int stt = 0; // Số thứ tự sinh viên trong danh sách
int i = 0;  //i là bước nhảy dòng trong DS ứng vs sinh viên
DataType sv[N];
using namespace std;

void SetSizeConsole() // thay doi kich thuoc man hinh co the noi tren win 7 hoac 8 do khong cho phep thay doi kick thuoc Console
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	// thay doi tieu de cua so
	SetConsoleTitle(TEXT("Nguyen Huu Tien"));
	// thay doi kich thuoc console
	SMALL_RECT windowSize = { 0, 0, cRong - 1, cCao - 1 };
	SetConsoleWindowInfo(h, TRUE, &windowSize);
	// thay doi kich thuoc bo dem
	COORD bufferSize = { cRong, cCao };
	SetConsoleScreenBufferSize(h, bufferSize);
}
void setColor(int x)
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
}

void gotoxy(int x, int y)
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void Init(List& list)
{
	list.head = NULL;
	list.tail = NULL;
	n = 0;
}

Node* creatNode(DataType x)
{
	Node* temp = new Node;
	if (temp == NULL) exit(1);
	else
	{
		temp->data = x;
		temp->next = NULL;
		temp->prev = NULL;
	}
	return temp;
}

bool isEmpty(List list)
{
	if (list.head == NULL) return true;
	return false;
}
void addHead(List & list, DataType x)
{
	/*
	Buoc1:Chen
		Co 2 TH: 1, neu list rong ;
				 2, neu list khong rong;
	Buoc2:
		so luong phan tu tang len 1;
	*/
	Node* temp = creatNode(x);
	if (isEmpty(list))
	{
		list.head = temp;
		list.tail = temp;
	}
	else
	{
		temp->next = list.head;
		list.head->prev = temp;
		list.head = temp;
	}
	stt++;
	i += 2;
	if (i == 20)
	{
		i = 0;
	}
	n++;

}
void addTail(List & list, DataType x)
{
	/*
	Buoc1:Chen
		Co 2 TH: 1, neu list rong ;
				 2, neu list khong rong;
	Buoc2:
		so luong phan tu tang len 1;
	*/
	Node* temp = creatNode(x);
	if (isEmpty(list))
	{
		addHead(list, x);
	}
	else
	{
		list.tail->next = temp;
		temp->prev = list.tail;
		list.tail = temp;
		n++;
		stt++;
		i += 2;
		if (i == 20)
		{
			i = 0;
		}
	}


}
void insertInList(List & list, int k, DataType x)
{
	/*
	 Buoc1:Chen
		 Co 3 TH: 1, neu list rong hoac k <= 0 -> chen dau;
				  2, neu k>= n                 -> chen cuoi;
				  3, sau do thi bat dau chen;
	 Buoc2:
		 so luong phan tu tang len 1;
	 */
	Node* temp = creatNode(x);
	if (isEmpty(list) || k <= 0) addHead(list, x);
	else if (k >= n) addTail(list, x);
	else
	{
		//tim den vi tri node tu k - 1;
		Node* i = list.head;
		int dem = 0;
		while (i != NULL)
		{
			if (dem == k - 1) break;
			dem++;
			i = i->next;
		}
		temp->next = i->next;
		i->next->prev = temp;
		temp->prev = i;
		i->next = temp;
		n++;
	}
}
//In ra file text
void inText(List list)
{
	string file = "";
	gotoxy(4, 15); cout << "File Name: ";
	getline(cin, file);
	std::ofstream fileOutput(file);

	if (fileOutput.fail())
	{
		std::cout << "Cannot open file at " << file << std::endl;
		return;
	}
	int l_hoten = cRong - sizemenu - l_stt - l_malop - l_masv - l_ngaysinh - l_diemtb - 7;
	fileOutput << left << setfill(' ') << setw(l_malop) << "Ma Lop" << setw(l_masv) << " MSV"
		<< setw(l_hoten - 5) << "Ho Va Ten" << setw(l_ngaysinh) << "Ngay Sinh" << setw(l_diemtb) << " Diem TB" << endl;
	Node * s = list.head;
	while (s != NULL)
	{
		fileOutput << left << setfill(' ') << setw(l_malop) << s->data.MaLop << setw(l_masv) << s->data.MaSinhVien
			<< setw(l_hoten - 5) << s->data.HoTen << setw(2) << s->data.NgS << "/" << setw(2) << s->data.TS << "/" << setw(4) << s->data.NS << setw(l_diemtb) << right << s->data.DiemTB << endl;
		s = s->next;
	}
	fileOutput.close();

}

void sapXepDiemTB(List & list, DataType x)
{
	/*
	1, Chen vao dau;
	2, Chen vao cuoi;
	3, Chen vao 1 vi tri bat ki ;
	*/
	//Tim ra vi tri can chen
	Node* i = list.head;
	int count = 0;
	while (i != NULL)
	{
		if (i->data.DiemTB >= x.DiemTB) break;
		if (i->next == NULL)
		{
			count++;
			break;
		}
		if (i->data.DiemTB <= x.DiemTB && x.DiemTB <= i->next->data.DiemTB)
		{
			count++;
			break;
		}
		count++;
		i = i->next;
	}
	insertInList(list, count, x);
}
void sapXepML(List & list, DataType x)
{
	/*
	1, Chen vao dau;
	2, Chen vao cuoi;
	3, Chen vao 1 vi tri bat ki ;
	*/
	//Tim ra vi tri can chen
	Node* i = list.head;
	int count = 0;
	while (i != NULL)
	{
		if (strcmp(x.MaLop, i->data.MaLop) < 0) break;
		if (i->next == NULL)
		{
			count++;
			break;
		}
		if (strcmp(x.MaLop, i->data.MaLop) > 0 && strcmp(x.MaLop, i->next->data.MaLop) < 0)
		{
			count++;
			break;
		}
		count++;
		i = i->next;
	}
	insertInList(list, count, x);
}
void sapXepMSV(List & list, DataType x)
{
	/*
	1, Chen vao dau;
	2, Chen vao cuoi;
	3, Chen vao 1 vi tri bat ki ;
	*/
	//Tim ra vi tri can chen
	Node* i = list.head;
	int count = 0;
	while (i != NULL)
	{
		if (strcmp(x.MaSinhVien, i->data.MaSinhVien) < 0) break;
		if (i->next == NULL)
		{
			count++;
			break;
		}
		if (strcmp(x.MaSinhVien, i->data.MaSinhVien) > 0 && strcmp(x.MaSinhVien, i->next->data.MaSinhVien) < 0)
		{
			count++;
			break;
		}
		count++;
		i = i->next;
	}
	insertInList(list, count, x);
}
void sapXepNS(List & list, DataType x)
{
	Node* i = list.head;
	int count = 0;
	while (i != NULL)
	{
		if (x.NS < i->data.NS) break;
		if (x.NS == i->data.NS)
		{
			if (x.TS < i->data.TS) break;
			else if (x.TS == i->data.TS)
			{
				if (x.NgS <= i->data.NgS) break;
			}

		}
		if (i->next == NULL)
		{
			count++;
			break;
		}
		if (x.NS > i->data.NS && x.NS < i->next->data.NS)
		{

			count++;
			break;
		}
		count++;
		i = i->next;
	}
	insertInList(list, count, x);
}
void tachName(string s1, string & firstName, string & midName, string & lastName)
{
	int length = s1.length();
	for (int i = s1.size() - 1; i >= 0; i--) {
		if (s1.at(i) == ' ') {
			lastName = s1.substr(i + 1, s1.size() - 1 - (i));
			for (int j = 0; j <= i; j++) {
				if (s1.at(j) == ' ') {
					firstName = s1.substr(0, j);
					midName = s1.substr(j + 1, i - (j + 1));
					break;
				}
			}
			break;
		}

	}
}
void sapXepHoTen(List & list, DataType x)
{
	/*
	1, Chen vao dau;
	2, Chen vao cuoi;
	3, Chen vao 1 vi tri bat ki ;
	*/
	//Tim ra vi tri can chen
	Node* i = list.head;
	int count = 0;
	string firstName, midName, lastName, firstName1, midName1, lastName1, firstName3, midName3, lastName3;
	while (i != NULL)
	{
		tachName(x.HoTen, firstName, midName, lastName);
		tachName(i->data.HoTen, firstName1, midName1, lastName1);
		if (lastName.compare(lastName1) < 0)  break;
		if (lastName.compare(lastName1) == 0)
		{
			if (midName.compare(midName1) < 0) break;
			else if (midName.compare(midName1) == 0)
			{
				if (firstName.compare(firstName1) <= 0) break;
			}
		}
		if (i->next == NULL)
		{
			count++;
			break;
		}
		tachName(i->next->data.HoTen, firstName3, midName3, lastName3);
		if (lastName.compare(lastName1) > 0 && lastName.compare(lastName3) < 0)
		{
			count++;
			break;
		}
		count++;
		i = i->next;
	}
	insertInList(list, count, x);
}


void DelHead(List & list)
{
	if (isEmpty(list)) cout << "Empty list!" << endl;
	else if (list.head->next == NULL)
	{
		Init(list);
	}
	else
	{
		Node* temp = list.head;
		temp->next->prev = NULL;
		list.head = temp->next;
		delete temp;
		n--;
		stt--;
		i -= 2;

	}
}

void DelTail(List & list)
{
	if (isEmpty(list)) cout << "Empty list!" << endl;
	else if (list.head->next == NULL)
	{
		Init(list);
	}
	else
	{
		Node* temp = list.tail;
		temp->prev->next = NULL;
		list.tail = temp->prev;
		delete temp;
		stt--;
		i -= 2;
		n--;

	}
}

void DelInList(List & list, int k)
{
	if (isEmpty(list)) cout << "Empty list!" << endl;
	else if (k < 0 || k > stt) cout << "Vi tri xoa khong hop le!" << endl;
	else if (list.head->next == NULL)
	{
		Init(list);
	}
	else if (k == 0) DelHead(list);
	else if (k == stt - 1) DelTail(list);
	else
	{
		Node* sv = list.head;

		int dem = 0;
		while (sv != NULL)
		{
			if (dem == k - 1) break;
			dem++;
			sv = sv->next;
		}
		Node* temp = sv->next;
		sv->next = temp->next;
		temp->next->prev = sv;
		delete temp;
		n--;
		stt--;
		i -= 2;

	}
}
void inThongKe(ThongKe tk[], int count)
{
	int tong = stt, xuatsac = 0, gioi = 0, kha = 0, TB = 0, yeu = 0;
	int i = 0;
	for (int j = 0; j <= count; j++)
	{
		gotoxy(37, 8 + i); cout << tk[j].stt + 1;
		gotoxy(44, 8 + i); cout << tk[j].malop;
		gotoxy(58, 8 + i); cout << tk[j].tong;
		gotoxy(68, 8 + i); cout << tk[j].xuat_sac;
		gotoxy(79, 8 + i); cout << tk[j].gioi;
		gotoxy(90, 8 + i); cout << tk[j].kha;
		gotoxy(101, 8 + i); cout << tk[j].TB;
		gotoxy(112, 8 + i); cout << tk[j].yeu;
		i = i + 2;
		xuatsac += tk[j].xuat_sac;
		gioi += tk[j].gioi;
		kha += tk[j].kha;
		TB += tk[j].TB;
		yeu += tk[j].yeu;
	}

	gotoxy(58, 27); cout << tong;
	gotoxy(68, 27); cout << xuatsac;
	gotoxy(79, 27); cout << gioi;
	gotoxy(90, 27); cout << kha;
	gotoxy(101, 27); cout << TB;
	gotoxy(112, 27); cout << yeu;
	gotoxy(0, 0);
}
void kiemTraDiem(float diem, int& xuat_sac, int& gioi, int& kha, int& TB, int& yeu, int& soSV)
{
	soSV++;
	if (diem >= 9) xuat_sac++;
	if (diem >= 8 && diem < 9) gioi++;
	if (diem >= 7 && diem < 8) kha++;
	if (diem >= 6 && diem < 7) TB++;
	if (diem < 6) yeu++;

}
void timHocLucSV(List list)
{
	int stt = 0; //so thu tu trong mang
	int count = 0;//phan tu mang
	Node* x = list.head;
	ThongKe tk[100];
loop:int xuat_sac = 0, gioi = 0, kha = 0, TB = 0, yeu = 0;
	int so_luong_SV = 0;
	char* c = x->data.MaLop;
	kiemTraDiem(x->data.DiemTB, xuat_sac, gioi, kha, TB, yeu, so_luong_SV);
	x = x->next;
	if (x == NULL)
	{
		tk[count] = { stt,c,so_luong_SV,xuat_sac,gioi,kha,TB, yeu };
	}
	while (x != NULL)
	{
		if (strcmp(c, x->data.MaLop) == 0)
		{
			kiemTraDiem(x->data.DiemTB, xuat_sac, gioi, kha, TB, yeu, so_luong_SV);
			if (x == list.tail) tk[count] = { stt,c,so_luong_SV,xuat_sac,gioi,kha,TB, yeu };
		}
		else
		{

			tk[count] = { stt,c,so_luong_SV,xuat_sac,gioi,kha,TB, yeu };
			count++;
			stt++;
			goto loop;
		}
		x = x->next;
	}

	inThongKe(tk, count);

}
void thongKe(List list)
{
	List l1;
	Init(l1);
	int temp = stt;
	int temp_i = i;
	Node* x = list.head;
	while (x != NULL)
	{
		sapXepML(l1, x->data);
		x = x->next;
	}
	i = temp_i;
	stt = temp;
	timHocLucSV(l1);
}
void choVaoMang(List list)
{
	Node* temp = list.head;
	int i = 0;
	while (temp != NULL)
	{
		sv[i] = temp->data;
		temp = temp->next;
		i++;
	}
}

int binarySearch(List & l1, DataType arr[], float from, float to, int left1) {
	int left = left1, right = stt - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (arr[mid].DiemTB <= to && arr[mid].DiemTB >= from)
		{
			addHead(l1, arr[mid]);
			return mid; // tim thay
		}
		else if (arr[mid].DiemTB < from)
			left = mid + 1;
		else if (arr[mid].DiemTB > to) right = mid - 1;
	}
	return 0;
}
void timKiemDiem(List list, float from, float to, List & temp, int& temp1)
{
	int count = 0;
	Node* i = list.head;
	while (i != NULL)
	{
		if (i->data.DiemTB <= to && i->data.DiemTB >= from)
		{
			addHead(temp, i->data);
			count++;
		}
		i = i->next;
	}
	temp1 = count;
}
void timKiemMSV(List list, char* x, List & temp, int& temp1)
{
	int count = 0;
	Node* i = list.head;
	while (i != NULL)
	{
		if (strcmp(i->data.MaSinhVien, x) == 0)
		{
			count++;
			addHead(temp, i->data);
		}
		i = i->next;
	}
	if (count == 0)
	{
		gotoxy(10, 19); cout << "Khong Thay.";
	}
	temp1 = count;
}
void timKiemHoTen(List list, string x, List & temp, int& temp1)
{
	int count = 0;
	Node* i = list.head;
	chuanHoaDauCuoi(x);
	xoaKhoangTrang(x);
	_strlwr((char*)x.c_str());

	regex pattern(x);
	while (i != NULL)
	{
		string source = i->data.HoTen;
		_strlwr((char*)source.c_str());
		if (regex_search(source, pattern))
		{
			count++;
			addHead(temp, i->data);
		}
		i = i->next;
	}
	if (count == 0)
	{
		gotoxy(10, 19); cout << "Khong Thay.";
	}
	temp1 = count;
}
void tim_kiem_theo_NS(List list, string x, List & temp, int& temp1)
{
	int count = 0;
	Node* i = list.head;
	chuanHoaDauCuoi(x);
	xoaKhoangTrang(x);
	_strlwr((char*)x.c_str());

	regex pattern(x);
	while (i != NULL)
	{
		string NgS = to_string(i->data.NgS);
		string TS = to_string(i->data.TS);
		string NS = to_string(i->data.NS);
		string source;

		if (i->data.NgS > 0 && i->data.NgS < 10) NgS = "0" + NgS;
		if (i->data.TS > 0 && i->data.TS < 10) TS = "0" + TS;
		source = NgS + "/" + TS + "/" + NS;

		_strlwr((char*)source.c_str());
		if (regex_search(source, pattern))
		{
			count++;
			addHead(temp, i->data);
		}
		i = i->next;
	}
	if (count == 0)
	{
		gotoxy(10, 19); cout << "Khong Thay.";
	}
	temp1 = count;
}
void timKiemMaLop(List list, string x, List & temp, int& stt1)
{
	int count = 0;
	Node* i = list.head;
	chuanHoaDauCuoi(x);
	xoaKhoangTrang(x);
	_strlwr((char*)x.c_str());

	regex pattern(x);
	while (i != NULL)
	{
		string source = (string)i->data.MaLop;
		_strlwr((char*)source.c_str());
		if (regex_search(source, pattern))
		{
			count++;
			addHead(temp, i->data);
		}
		i = i->next;
	}
	if (count == 0)
	{
		gotoxy(10, 19); cout << "Khong Thay.";
	}
	stt1 = count;
}

void input(List & list)
{
	ifstream in;
	in.open("Text.dat");

	while (!in.eof())
	{
		DataType x;
		in >> x.MaLop;
		in >> x.MaSinhVien;
		in.ignore();
		getline(in, x.HoTen);
		in >> x.NgS;
		in >> x.TS;
		in >> x.NS;
		in >> x.DiemTB;
		addHead(list, x);
	}

	in.close();

}

void output(const char* fileName, List list)
{
	ofstream out;
	out.open(fileName);
	Node* i = list.head;
	if (i == NULL) cout << "Unsuccessful!" << endl;
	else
	{
		while (i != NULL)
		{
			if (i == list.tail) out << i->data.MaLop << "\n" << i->data.MaSinhVien << "\n" << i->data.HoTen << "\n" << i->data.NgS << "\n" << i->data.TS << "\n" << i->data.NS << "\n" << i->data.DiemTB;
			else
				out << i->data.MaLop << "\n" << i->data.MaSinhVien << "\n" << i->data.HoTen << "\n" << i->data.NgS << "\n" << i->data.TS << "\n" << i->data.NS << "\n" << i->data.DiemTB << endl;

			i = i->next;
		}
	}
	out.close();
}
//void DelDuplicate(List &list) {
//	if (isEmpty(list)) cout << "Empty list!" << endl;
//	else if (list.head->next == NULL)
//	{
//		cout << "There is only 1 element." << endl;
//	}
//	else
//	{
//		Node *i = list.head;
//		int k = 1;
//		while (i->next != NULL) {
//			if (i->data == i->next->data)
//			{
//				Node *temp = i->next;
//				i->next = temp->next;
//				temp->next->prev = i;
//				delete temp;
//				n--;
//			}
//			else
//			{
//				k++;
//				i = i->next;
//			}
//		}
//		cout << "Success!" << endl;
//
//	}
//}

void menuChinh(int choice) //menu chuong trinh chinh
{
	setColor(63);
	string menu[7] = { "     ***** MENU *****      ",
					"1. Cap nhat ho so             ",
					"2. Xem danh sach              ",
					"3. Sap xep                    ",
					"4. Tim kiem                   ",
					"5. Thong ke                   ",
					"6. Thoat                      " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 7; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menuM1(int choice)
{

	setColor(63);
	string menu[5] = { "     ** CAP NHAT HO SO **     ",
					"1. Them sinh vien             ",
					"2. Xoa sinh vien              ",
					"3. In ra file                 ",
					"4. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 5; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menuM3_2(int choice) //menu chon thuat toan sap xep
{
	setColor(63);
	string menu[6] = { "    CHON THUAT TOAN SAP XEP   ",
					"1. Sap xep chon               ",
					"2. Sap xep chen               ",
					"3. Sap xep noi bot            ",
					"4. Sap xep nhanh              ",
					"5. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 6; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menuM3_1(int choice) //menu chon khoa sap xep
{
	setColor(63);
	string menu[6] = { "       CHON KHOA SAP XEP      ",
					"1. Sap xep theo ma sinh vien  ",
					"2. Sap xep theo ho ten        ",
					"3. Sap xep theo ngay sinh     ",
					"4. Sap xep theo diem TB       ",
					"5. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 6; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menuM4_2(int choice)
{
	setColor(63);
	string menu[4] = { "   CHON THUAT TOAN TIM KIEM   ",
					"1. Tim kiem tuan tu           ",
					"2. Tim kiem nhi phan          ",
					"3. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 4; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void menuM4_1(int choice)
{
	setColor(63);
	string menu[7] = { "   CHON THUAT TOAN TIM KIEM   ",
					"1. Tim kiem theo ma lop       ",
					"2. Tim kiem theo ma sinh vien ",
					"3. Tim kiem theo ho ten       ",
					"4. Tim kiem theo ngay sinh    ",
					"5. Tim kiem theo diem TB      ",
					"6. Quay lai                   " };
	gotoxy(3, 4);
	cout << menu[0];
	gotoxy(3, 5);
	cout << "                              ";
	for (int i = 1; i < 7; i++)
	{
		gotoxy(3, 5 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(31);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}
void backgroundDS()
{
	/*
	In ra các hàng các cột Danh Sách
	In ra display
	*/

	char g1 = 218, ngang = 196, top = 194, g2 = 191;
	char xtt = 195, doc = 179, xcong = 197, xtp = 180;
	char g4 = 192, bot = 193, g3 = 217;

	char s[] = "DANH SACH SINH VIEN";
	setColor(240);
	int x = 35, y = 3, i = 0;

	int l_hoten = cRong - sizemenu - l_stt - l_malop - l_masv - l_ngaysinh - l_diemtb - 7;
	int width = l_stt + l_malop + l_masv + l_hoten + l_ngaysinh + l_diemtb + 5;
	// in tieu de
	gotoxy(x, y + i++);
	cout << g1 << setfill(ngang) << setw(width + 1) << g2;
	gotoxy(x, y + i++);
	cout << setfill(' ') << doc << setw(width / 2 + strlen(s) / 2) << s << setw(width - (width / 2 + strlen(s) / 2) + 1) << doc;
	gotoxy(x, y + i++);
	cout << setfill(ngang) << xtt << setw(l_stt + 1) << top << setw(l_malop + 1) << top << setw(l_masv + 1) << top
		<< setw(l_hoten + 1) << top << setw(l_ngaysinh + 1) << top << setw(l_diemtb + 1) << xtp;
	gotoxy(x, y + i++);
	cout << setfill(' ') << setiosflags(ios::left) << doc << setw(l_stt) << " STT" << doc << setw(l_malop) << "  Ma Lop" << doc
		<< setw(l_masv) << "  Ma SV" << doc << setw(l_hoten) << "     Ho Va Ten" << doc << setw(l_ngaysinh) << "   Ngay Sinh" << doc
		<< setw(l_diemtb) << "Diem TB" << doc << resetiosflags(ios::left);
	//in bang
	int n = 0;
	while (n != 10)
	{
		n++;
		gotoxy(x, y + i++);
		cout << setfill(ngang) << xtt << setw(l_stt + 1) << xcong << setw(l_malop + 1) << xcong << setw(l_masv + 1) << xcong << setw(l_hoten + 1) << xcong
			<< setw(l_ngaysinh + 1) << xcong << setw(l_diemtb + 1) << xtp;
		gotoxy(x, y + i++);
		cout << setfill(' ') << doc << setw(l_stt) << " " << doc << setw(l_malop) << " " << doc << setw(l_masv) << " "
			<< doc << setw(l_hoten) << " " << doc << setw(l_ngaysinh) << " " << doc << setw(l_diemtb) << " " << doc;
	}
	// in cuoi
	gotoxy(x, y + i++);
	cout << setfill(ngang) << g4 << setw(l_stt + 1) << bot << setw(l_malop + 1) << bot << setw(l_masv + 1)
		<< bot << setw(l_hoten + 1) << bot << setw(l_ngaysinh + 1) << bot << setw(l_diemtb + 1) << g3;
}
void hinhChuNhat(int x, int y, int width, int height, int color)
{
	char g1 = 201, ngang = 205, g2 = 187, doc = 186, g3 = 188, g4 = 200;
	setColor(color);
	gotoxy(x, y);
	cout << setfill(ngang) << g1 << setw(width - 1) << g2;
	for (int i = 1; i < height; i++)
	{
		gotoxy(x, y + i); cout << setfill(' ') << doc << setw(width - 1) << doc;
	}
	gotoxy(x, y + height); cout << setfill(ngang) << g4 << setw(width - 1) << g3;

}
void hinhChuNhatManh(int x, int y, int width, int height, int color)
{
	char g1 = 218, ngang = 196, g2 = 191, doc = 179, g3 = 217, g4 = 192;
	setColor(color);
	gotoxy(x, y);
	cout << setfill(ngang) << g1 << setw(width - 1) << g2;
	for (int i = 1; i < height; i++)
	{
		gotoxy(x, y + i); cout << setfill(' ') << doc << setw(width - 1) << doc;
	}
	gotoxy(x, y + height); cout << setfill(ngang) << g4 << setw(width - 1) << g3;

}
void backgroundMenu()
{
	/*
	In ra khung hình chữ nhật menu()
	*/
	gotoxy(0, 3);
	hinhChuNhat(0, 3, sizemenu, 25, 63);
}
void background()
{
	/*
	In ra menu();
	In ra Danh sách ();
	*/
	char s[] = "QUAN LY SINH VIEN";
	string tt[2] = { "Chao: NGUYEN HUU TIEN ","CNTT" };
	SetSizeConsole();
	gotoxy(0, 0); setColor(47);
	cout << setw(cRong) << setfill(' ') << " ";
	gotoxy(0, 1); cout << setw(cRong / 2 + strlen(s) / 2) << setfill(' ') << s << setw(cRong - (cRong / 2 + strlen(s) / 2)) << setfill(' ') << " ";
	cout << tt[0] << setw(cRong - tt[0].length() - tt[1].length()) << setfill(' ') << tt[1] << setw(tt[0].length() + tt[1].length()) << setfill(' ') << " ";
	backgroundMenu();
	backgroundDS();
	gotoxy(0, 0);
}
void khungThongKe()
{
	char gtt = 218, ngang = 196, top = 194, gpt = 191;
	char xtt = 195, xt = 179, xcong = 197, xtp = 180;
	char gtd = 192, bot = 193, gpd = 217;

	char s[] = "THONG KE KET QUA HOC TAP";
	setColor(240);
	int x = 35, y = 3, i = 0;
	int l_stt = 5, l_tongsv = 10, l_xuat_sac = 10, l_gioi = 10, l_kha = 10, l_trungbinh = 10, l_yeu = 10;
	int l_malop = cRong - sizemenu - l_stt - l_tongsv - l_gioi - l_kha - l_trungbinh - l_yeu - l_xuat_sac - 8;
	int width = l_malop + l_stt + l_tongsv + l_gioi + l_kha + l_trungbinh + l_yeu + l_xuat_sac + 6;
	// in tieu de
	gotoxy(x, y + i++);
	cout << setfill(ngang) << gtt << setw(width + 1) << gpt;
	gotoxy(x, y + i++);
	cout << setfill(' ') << xt << setw(width / 2 + strlen(s) / 2) << s << setw(width - (width / 2 + strlen(s) / 2) + 1) << xt;
	gotoxy(x, y + i++);
	cout << setfill(ngang) << xtt << setw(l_stt + 1) << top << setw(l_malop) << top << setw(l_tongsv + 1) << top << setw(l_xuat_sac + 1) << top << setw(l_gioi + 1) << top
		<< setw(l_kha + 1) << top << setw(l_trungbinh + 1) << top << setw(l_yeu + 1) << xtp;
	gotoxy(x, y + i++);
	cout << setfill(' ') << setiosflags(ios::left) << xt << setw(l_stt) << " STT" << xt << setw(l_malop - 1) << "Ma Lop" << xt << setw(l_tongsv) << "Tong " << xt << setw(l_xuat_sac) << "Xuat Sac" << xt
		<< setw(l_gioi) << " Gioi" << xt << setw(l_kha) << "  Kha" << xt << setw(l_trungbinh) << "TB" << xt
		<< setw(l_yeu) << " Yeu" << xt << resetiosflags(ios::left);
	int n = 0;
	while (n != 9) {
		n++;
		gotoxy(x, y + i++);
		cout << setfill(ngang) << xtt << setw(l_stt + 1) << xcong << setw(l_malop) << xcong << setw(l_tongsv + 1) << xcong << setw(l_xuat_sac + 1) << xcong << setw(l_gioi + 1) << xcong << setw(l_kha + 1) << xcong
			<< setw(l_trungbinh + 1) << xcong << setw(l_yeu + 1) << xtp;
		gotoxy(x, y + i++);
		cout << setfill(' ') << xt << setw(l_stt) << " " << xt << setw(l_malop - 1) << " " << xt << setw(l_tongsv) << " " << xt << setw(l_xuat_sac) << " " << xt << setw(l_gioi) << " "
			<< xt << setw(l_kha) << " " << xt << setw(l_trungbinh) << " " << xt << setw(l_yeu) << " " << xt;
	}
	// in cuoi
	gotoxy(x, y + i++);
	cout << setfill(ngang) << gtd << setw(l_stt + 1) << bot << setw(l_malop) << bot << setw(l_tongsv + 1) << bot << setw(l_xuat_sac + 1) << bot << setw(l_gioi + 1)
		<< bot << setw(l_kha + 1) << bot << setw(l_trungbinh + 1) << bot << setw(l_yeu + 1) << gpd;

	gotoxy(x, y + i++);
	cout << setfill(ngang) << gtt << setw(l_stt + l_malop + 1) << top << setw(l_tongsv + 1) << top << setw(l_xuat_sac + 1) << top << setw(l_gioi + 1)
		<< top << setw(l_kha + 1) << top << setw(l_trungbinh + 1) << top << setw(l_yeu + 1) << gpt;
	gotoxy(x, y + i++);
	cout << setfill(' ') << xt << setw(l_stt + l_malop) << "TONG       " << xt << setw(l_tongsv) << " " << xt << setw(l_xuat_sac) << " " << xt << setw(l_gioi) << " "
		<< xt << setw(l_kha) << " " << xt << setw(l_trungbinh) << " " << xt << setw(l_yeu) << " " << xt;
	gotoxy(x, y + i++);
	cout << setfill(ngang) << gtd << setw(l_stt + l_malop + 1) << bot << setw(l_tongsv + 1) << bot << setw(l_xuat_sac + 1) << bot << setw(l_gioi + 1)
		<< bot << setw(l_kha + 1) << bot << setw(l_trungbinh + 1) << bot << setw(l_yeu + 1) << gpd;
	gotoxy(0, 0);
}

void swapNode(Node * a, Node * b)
{
	DataType temp = a->data;
	a->data = b->data;
	b->data = temp;
}
Node* partition(List & list, Node * low, Node * high, int left1, int right1)
{
	DataType pivot = high->data;    // pivot
	Node* lNode = low;
	Node* rNode = high;
	int left = left1;
	int right = right1;
	while (left <= right) {
		while (left <= right && lNode->data.DiemTB < pivot.DiemTB)
		{
			left++;
			lNode = lNode->next;
		}
		while (right >= left && rNode->data.DiemTB > pivot.DiemTB)
		{
			right--;
			rNode = rNode->prev;
		}
		if (left <= right)
		{
			swap(lNode, rNode);
			left++;
			lNode = lNode->next;
			right--;
			rNode = rNode->prev;

		}
	}
	return lNode;
}
/*
Cac ham so sanh cho vao Sort
< - true
> - flase
*/
int compareDiem(DataType data1, DataType data3)
{
	if (data1.DiemTB < data3.DiemTB) return 1;
	if (data1.DiemTB > data3.DiemTB) return -1;
	return 0;
}
int compareMSV(DataType data1, DataType data3)
{
	if (strcmp(data1.MaSinhVien, data3.MaSinhVien) < 0) return 1;
	if (strcmp(data1.MaSinhVien, data3.MaSinhVien) > 0) return -1;
	return 0;
}
int compareNS(DataType data1, DataType data3)
{
	if (data1.NS == data3.NS && data1.NgS == data3.NgS && data1.TS == data3.TS) return 0;
	if (data1.NS < data3.NS) return 1;
	if (data1.NS == data3.NS)
	{
		if (data1.TS < data3.TS) return 1;
		else if (data1.TS == data3.TS)
		{
			if (data1.NgS < data3.NgS) return 1;
			else return -1;
		}
		else return -1;

	}
	if (data1.NS > data3.NS) return -1;
}
int compareHT(DataType data1, DataType data3)
{
	string firstName, midName, lastName, firstName1, midName1, lastName1, firstName3, midName3, lastName3;
	tachName(data1.HoTen, firstName, midName, lastName);
	tachName(data3.HoTen, firstName1, midName1, lastName1);
	if (lastName.compare(lastName1) == 0 && midName.compare(midName1) == 0 && firstName.compare(firstName1) == 0) return 0;
	if (lastName.compare(lastName1) < 0)  return 1;
	if (lastName.compare(lastName1) == 0)
	{
		if (midName.compare(midName1) < 0) return 1;
		else if (midName.compare(midName1) == 0)
		{
			if (firstName.compare(firstName1) < 0) return 1;
			else return -1;
		}
		else return -1;
	}
	return -1;
}
void quickSort(List & list, Node * low, Node * high, int left, int right)
{
	Node* lNode = low;
	Node* rNode = high;
	int i = left;
	int j = right;
	DataType pivot = lNode->data;
	while (i <= j)
	{
		while (compareHT(lNode->data, pivot) < 0)
		{
			lNode = lNode->next;
			i++;
		}
		while (compareHT(rNode->data, pivot) > 0)
		{
			rNode = rNode->prev;
			j--;
		}
		if (i <= j)
		{
			swapNode(lNode, rNode);
			lNode = lNode->next;
			rNode = rNode->prev;
			i++;
			j--;
		}
	}
	if (right > i) quickSort(list, lNode, high, i, right);
	if (left < j) quickSort(list, low, rNode, left, j);
}
void insertSort(List & list)
{
	if (list.head == NULL || list.head->next == NULL) return;
	DataType temp;
	Node * j;
	Node * i;
	for (i = list.head->next; i != NULL; i = i->next)
	{
		temp = i->data;
		j = i->prev;
		while (j != NULL && temp.DiemTB < j->data.DiemTB)
		{
			j->next->data = j->data;
			j = j->prev;
		}
		if (j == NULL) {
			list.head->data = temp;
		}
		else {
			j->next->data = temp;
		}
	}

}
void bubbleSort(List & list)
{
	if (list.head == NULL || list.head->next == NULL) return;
	Node * i;
	for (i = list.head; i != list.tail->prev; i = i->next)
	{
		Node* j;
		for (j = list.tail; j != i; j = j->prev)
		{
			if (j->data.DiemTB < j->prev->data.DiemTB)
			{

				swapNode(j, j->prev);
			}
		}
	}
}
void displayInit()
{
	setColor(240);
	for (int i = 0; i <= 20; i += 2)
	{
		gotoxy(38, 8 + i); cout << setw(l_stt - 2) << setfill(' ') << " ";
		gotoxy(42, 8 + i); cout << setw(l_malop - 2) << setfill(' ') << " ";
		gotoxy(53, 8 + i); cout << setw(l_masv - 2) << setfill(' ') << " ";
		gotoxy(65, 8 + i); cout << setw(27) << setfill(' ') << " ";

		gotoxy(97, 8 + i); cout << setw(l_ngaysinh - 2) << setfill(' ') << " ";
		gotoxy(111, 8 + i); cout << setw(l_diemtb - 2) << setfill(' ') << " ";
	}
	gotoxy(0, 0);
}
void display1(List list, int stt)
{
	float trang1 = (float)stt / 10;
	setColor(240);
	displayInit();
	int trang = ceil(trang1);
	int stt1 = 1;
	int i = 0;
	Node* s = list.head;
	while (s != NULL)
	{
		if (stt1 > (trang * 10 - 10) && stt1 <= trang * 10)
		{
			gotoxy(38, 8 + i); cout << stt1;
			gotoxy(42, 8 + i); cout << s->data.MaLop;
			gotoxy(53, 8 + i); cout << s->data.MaSinhVien;
			gotoxy(65, 8 + i); cout << s->data.HoTen;
			gotoxy(99, 8 + i); cout << "/  /";
			gotoxy(97, 8 + i); cout << s->data.NgS;
			gotoxy(100, 8 + i); cout << s->data.TS;
			gotoxy(103, 8 + i); cout << s->data.NS;
			gotoxy(111, 8 + i); cout << s->data.DiemTB;

		}
		s = s->next;
		i += 2;
		stt1++;
		if (i % 20 == 0)
		{
			i = 0;
		}
	}
	gotoxy(0, 0);
}
void display2(List list, float trang1)
{
	setColor(240);
	displayInit();
	int trang = ceil(trang1);
	int stt1 = 1;
	int i = 0;
	Node* s = list.head;
	while (s != NULL)
	{
		if (stt1 > (trang * 10 - 10) && stt1 <= trang * 10)
		{
			gotoxy(38, 8 + i); cout << stt1;
			gotoxy(42, 8 + i); cout << s->data.MaLop;
			gotoxy(53, 8 + i); cout << s->data.MaSinhVien;
			gotoxy(65, 8 + i); cout << s->data.HoTen;
			gotoxy(99, 8 + i); cout << "/  /";
			gotoxy(97, 8 + i); cout << s->data.NgS;
			gotoxy(100, 8 + i); cout << s->data.TS;
			gotoxy(103, 8 + i); cout << s->data.NS;
			gotoxy(111, 8 + i); cout << s->data.DiemTB;

		}
		s = s->next;
		i += 2;
		stt1++;
		if (i % 20 == 0)
		{
			i = 0;
		}
	}
	gotoxy(0, 0);
}
void display(List list)
{
	setColor(240);
	int stt1 = 1;
	int i = 0;
	Node* s = list.head;
	while (s != NULL)
	{
		gotoxy(38, 8 + i); cout << stt1;
		gotoxy(42, 8 + i); cout << s->data.MaLop;
		gotoxy(53, 8 + i); cout << s->data.MaSinhVien;
		gotoxy(65, 8 + i); cout << s->data.HoTen;
		gotoxy(99, 8 + i); cout << "/  /";
		gotoxy(97, 8 + i); cout << s->data.NgS;
		gotoxy(100, 8 + i); cout << s->data.TS;
		gotoxy(103, 8 + i); cout << s->data.NS;
		gotoxy(111, 8 + i); cout << s->data.DiemTB;
		s = s->next;
		i += 2;
		stt1++;
		if (i % 20 == 0)
		{
			backgroundDS();
			i = 0;
		}
	}
	gotoxy(0, 0);
}
int phimEnterEsc()
{	//enter return true esc return false
	setColor(63);
	gotoxy(4, 15); cout << "ESC de thoat."; gotoxy(4, 16); cout << "ENTER tiep tuc.";
	int c;
	while (1)
	{
		c = _getch();
		if (c == 13) return 13;
		if (c == 27) return 27;
	}
}

int phimDiChuyen(int c, int choice, int line)
{
	if (c == 224)
	{
		c = _getch();
		if (c == 80)
		{
			if (choice == line || choice - 1 == line) choice = 1;
			else choice++;
		}
		if (c == 72)
		{
			if (choice == 1) choice = line;
			else choice--;
		}

	}
	return choice;
}
int menuChinhThaoTac(int last_line)
{
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phimDiChuyen(c, line, last_line);

			menuChinh(line);
		}
		if (c == 13)
		{
			return line;
		}
	}
}

bool setMaLop(char* s)
{
	/*48  -> 57   la ca so 1->9*/

	int lenght;
	lenght = strlen(s);
	if (!((int)s[lenght - 1] <= 57 && (int)s[lenght - 1] >= 48 && (int)s[lenght - 2] <= 57 && (int)s[lenght - 2] >= 48))
	{
		return false;
	}
	return true;
}
bool setNgaySinh(int& n)
{
	if (!(n > 0 && n <= 31)) return false;
	return true;
}
bool setThangSinh(int& n, int& ngay_sinh)
{
	if (n == 2 && ngay_sinh >= 30) return false;
	if (!(n > 0 && n < 13)) return false;
	return true;
}
bool setNamSinh(int& n)
{
	if (n > 2003 || n < 1960) return false;
	return true;
}
bool setMSV(char* s, List list)
{
	int lenght;
	lenght = strlen(s);
	if (lenght != 8) return false;
	else
	{
		for (int i = 0; i < lenght; i++)
		{
			if (!((int)s[i] <= 57 && (int)s[i] >= 48))
			{
				return false;
			}
		}
	}
	Node* x = list.head;
	while (x != NULL)
	{

		if (strcmp(s, x->data.MaSinhVien) == 0)
		{
			setColor(63);
			gotoxy(10, 19); cout << "Trung MSV";
			return false;
		}
		x = x->next;
	}
	return true;
}
//bool set_MSV(char* s)
//{
//	int lenght;
//	lenght = strlen(s);
//	if (lenght != 8) return false;
//	else
//	{
//		for (int i = 0; i < lenght; i++)
//		{
//			if (!((int)s[i] <= 57 && (int)s[i] >= 48))
//			{
//				return false;
//			}
//		}
//	}
//
//	return true;
//}
bool setDiem(float& d)
{
	if (!(d >= 0 && d <= 10)) return false;
	return true;
}
void chuanHoaDauCuoi(string & str)
{
	// Bước 1: Xóa hết tất cả các kí tự khoảng trắng thừa ở đầu chuỗi
	// cho vòng lặp while lặp cho đến khi nào kiểm tra kí tự đầu tiên - vị trí 0 không phải là khoảng trắng thì dừng
	while (str[0] == ' ')
	{
		str.erase(str.begin() + 0); // xóa kí tự tại vị trí 0
	}


	// Bước 2: Xóa hết tất cả các kí tự khoảng trắng thừa ở cuối chuỗi
	if (str != "")
	{
		while (str[str.length() - 1] == ' ')
		{
			str.erase(str.begin() + str.length() - 1); // xóa kí tự tại vị trí cuối của chuỗi
		}
	}

}

// hàm xóa khoảng trắng thừa ở giữa các từ
void xoaKhoangTrang(string & str)
{
	for (int i = 0; i < str.length(); i++)
	{
		// nếu 2 kí tự liên tiếp nhau mà là khoảng trắng ==> xóa đi 1 kí tự
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			str.erase(str.begin() + i);
			i--;
		}
	}
}

// hàm viết hoa kí tự đầu của mỗi từ
void in_hoa_ki_tu_dau_moi_tu(string & str)
{
	chuanHoaDauCuoi(str);
	xoaKhoangTrang(str);
	// Bước 1: chuyển chuỗi str về chuỗi in thường
	_strlwr((char*)str.c_str()); // hàm chuyển chuỗi str về chuỗi in thường
	// Bước 2: viết hoa kí tự đầu của mỗi từ
	if (str[0] != ' ')
	{
		if (str[0] >= 97 && str[0] <= 122)
		{
			str[0] -= 32;
		}

	}
	// kí tự tại vị trí i là khoảng trắng, i + i khác khoảng trắng thì kí tự tại vị trí i + 1 chính là kí tự đầu tiên của mỗi từ
	for (int i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
		{
			// A: 65
			// B: 66
			// Z: 90
			// a: 97
			// b: 98
			// c: 99
			// z: 122
			if (str[i + 1] >= 97 && str[i + 1] <= 122)
			{
				// - 32 là chuyển kí tự in thường về in hoa
				str[i + 1] -= 32; // <=> str[i + 1] = str[i + 1] - 32;
			}
		}
	}
}
void nhapMaLop(char maLop[11]) {
	int i = 0;
	int a;
	do {
		a = _getch();
		if (i < 6) {
			if (((a >= 65) && (a <= 90)) || ((a >= 97) && (a <= 122)) || ((a >= 48) && (a <= 57))) {
				cout << (char)a;
				maLop[i] = (char)a;
				i++;
			}
		}
		if (a == 8 && i > 0) {
			cout << "\b \b";
			i--;
		}
	} while (a != 13);
	maLop[i] = '\0';

}
void nhapMSV(char MaSinhVien[11]) {
	int i = 0;
	int a;
	do {
		a = _getch();
		if (i < 8) {
			if (((a >= 48) && (a <= 57))) {
				cout << (char)a;
				MaSinhVien[i] = (char)a;
				i++;
			}
		}
		if (a == 8 && i > 0) {
			cout << "\b \b";
			i--;
		}

	} while (a != 13);
	MaSinhVien[i] = '\0';
}
bool nhapNgay(int& ngay, int k)
{
	int i = 0;
	int a;
	char c[5];
	do {

		a = _getch();
		if (i < k) {
			if ((a >= 48) && (a <= 57)) {
				cout << (char)a;
				c[i] = (char)a;
				i++;
			}
		}
		if (a == 8 && i > 0) {
			cout << "\b \b";
			i--;
		}

	} while (a != 13 || i == 0);
	c[i] = '\0';
	ngay = atoi(c);
}
bool nhapDiem(float& diem)
{
	int i = 0;
	int a;
	char c[5];
	do {

		a = _getch();
		if (i < 4) {
			if (((a >= 48) && (a <= 57)) || a == 46) {
				cout << (char)a;
				c[i] = (char)a;
				i++;
			}
		}
		if (a == 8 && i > 0) {
			cout << "\b \b";
			i--;
		}

	} while (a != 13 || i == 0);
	c[i] = '\0';
	diem = atof(c);
}
void chonM1ThemSinhVien(List & list)
{
	/*
	Cho phép nhập các thông tin sinh viên
	có : i += 2; và stt ++ ;
	*/
	menuM1(1);
	int c;
	int stt1 = stt;
	while (1)
	{
		if ((stt1) % 10 == 0)
		{
			displayInit();
		}

		DataType x;

		setColor(240);
		gotoxy(38, 8 + i); cout << stt + 1;
		gotoxy(42, 8 + i);
		nhapMaLop(x.MaLop);

		while (!setMaLop(x.MaLop))
		{
			gotoxy(42, 8 + i);
			cout << setw(l_malop) << setfill(' ') << " "; gotoxy(42, 8 + i);
			nhapMaLop(x.MaLop);
		}
		strupr(x.MaLop);
		gotoxy(42, 8 + i);
		cout << x.MaLop;
		gotoxy(53, 8 + i);
		nhapMSV(x.MaSinhVien);
		while (!setMSV(x.MaSinhVien, list))
		{
			setColor(240);
			gotoxy(53, 8 + i);
			cout << setw(l_masv) << setfill(' ') << " "; gotoxy(53, 8 + i);
			nhapMSV(x.MaSinhVien);
			if (setMSV(x.MaSinhVien, list)) setColor(63); gotoxy(10, 19); cout << "          "; setColor(240);
		}
		fflush(stdin); gotoxy(65, 8 + i);
		getline(cin, x.HoTen);
		in_hoa_ki_tu_dau_moi_tu(x.HoTen);
		gotoxy(65, 8 + i);
		cout << x.HoTen;
		fflush(stdin);
		gotoxy(99, 8 + i); cout << "/  /";
		gotoxy(97, 8 + i);
		nhapNgay(x.NgS, 2);
		while (!setNgaySinh(x.NgS))
		{
			gotoxy(97, 8 + i);
			cout << setw(2) << setfill(' ') << " "; gotoxy(97, 8 + i);
			nhapNgay(x.NgS, 2);
		}
		gotoxy(97, 10);
		cin.clear();

		gotoxy(100, 8 + i);
		nhapNgay(x.TS, 2);
		while (!setThangSinh(x.TS, x.NgS))
		{
			gotoxy(100, 8 + i);
			cout << setw(2) << setfill(' ') << " "; gotoxy(100, 8 + i);
			nhapNgay(x.TS, 2);
		}
		cin.clear();
		gotoxy(103, 8 + i);
		nhapNgay(x.NS, 4);
		while (!setNamSinh(x.NS))
		{
			gotoxy(103, 8 + i);
			cout << setw(4) << setfill(' ') << " "; gotoxy(103, 8 + i);
			nhapNgay(x.NS, 4);
		}
		cin.clear();
		gotoxy(111, 8 + i);
		nhapDiem(x.DiemTB);
		while (!setDiem(x.DiemTB))
		{
			gotoxy(111, 8 + i);
			cout << setw(4) << setfill(' ') << " "; gotoxy(111, 8 + i);
			nhapDiem(x.DiemTB);
		}
		x.DiemTB = roundf(x.DiemTB * 10) / 10;
		gotoxy(111, 8 + i); cout << x.DiemTB << "    ";

		c = phimEnterEsc();
		if (c == 13)
		{
			addTail(list, x);
		}

		if (c == 27)
		{
			addTail(list, x);
			display1(list, stt);
			break;
		}
		stt1++;
		gotoxy(0, 0); cout << stt1;
	}

}
void xoaSinhVienM1(List & list, int choice)
{
	if ((choice - 1) % 10 == 0 || choice == stt || choice % 10 == 0)
	{
		displayInit();
	}
	float trang1 = (float)choice / 10;
	int trang = ceil(trang1);
	setColor(240);
	Node* n = list.head;
	int stt = 1;
	int i = 0;
	while (n != NULL)
	{
		if (stt > (trang * 10 - 10) && stt <= trang * 10)
		{
			if (stt != choice)
			{
				gotoxy(38, 8 + i); cout << stt;
				gotoxy(42, 8 + i); cout << n->data.MaLop;
				gotoxy(53, 8 + i); cout << n->data.MaSinhVien;
				gotoxy(65, 8 + i); cout << n->data.HoTen;
				gotoxy(99, 8 + i); cout << "/  /";
				gotoxy(97, 8 + i); cout << n->data.NgS;
				gotoxy(100, 8 + i); cout << n->data.TS;
				gotoxy(103, 8 + i); cout << n->data.NS;
				gotoxy(111, 8 + i); cout << n->data.DiemTB;
			}
			else
			{
				setColor(241);
				gotoxy(38, 8 + i); cout << stt;
				gotoxy(42, 8 + i); cout << n->data.MaLop;
				gotoxy(53, 8 + i); cout << n->data.MaSinhVien;
				gotoxy(65, 8 + i); cout << n->data.HoTen;
				gotoxy(99, 8 + i); cout << "/  /";
				gotoxy(97, 8 + i); cout << n->data.NgS;
				gotoxy(100, 8 + i); cout << n->data.TS;
				gotoxy(103, 8 + i); cout << n->data.NS;
				gotoxy(111, 8 + i); cout << n->data.DiemTB;
				setColor(240);
			}

		}
		n = n->next;
		i += 2;
		stt++;
		if (i % 20 == 0)
		{
			i = 0;
		}
	}
	gotoxy(0, 0);
}
void chonM1XoaSV(List & list)
{

	xoaSinhVienM1(list, 1);
	int c;
	int line = 1;
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			line = phimDiChuyen(c, line, stt);
			gotoxy(0, 0); cout << line;

			xoaSinhVienM1(list, line);
		}
		if (c == 13)
		{
			DelInList(list, line - 1);
			displayInit();
			xoaSinhVienM1(list, line);

		}
		if (c == 27)
		{
			display1(list, stt);
			break;
		}

	}
}
void chonM1(List & list)
{
	backgroundMenu();
	menuM1(1);
	display1(list, stt);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			line = phimDiChuyen(c, line, 4);
			menuM1(line);
		}
		if (c == 13)
		{
			if (line == 1) chonM1ThemSinhVien(list);
			if (line == 2) chonM1XoaSV(list);
			if (line == 3)
			{
				inText(list);
				backgroundMenu();
				menuM1(3);
			}
			if (line == 4) break;
		}
	}
	fflush(stdin);
}

void chonM2(List & list)
{
	backgroundMenu();
	menuChinh(2);
	float trang1 = (float)stt / 10;
	int temp = ceil(trang1);
	int trang = 1;
	display2(list, trang);
	int c;
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			c = _getch();
			if (c == 77)
			{
				if (trang == temp) trang = 1;
				else trang++;
			}
			if (c == 75)
			{
				if (trang == 1) trang = temp;
				else trang--;
			}

			display2(list, trang);
		}
		if (c == 27)
		{
			break;
		}
	}
	fflush(stdin);
}

void chonM3_3(List & list)
{
	List l1;
	Init(l1);
	int temp = stt;
	int temp_i = i;
	Node* l = list.head;
	while (l != NULL)
	{
		sapXepNS(l1, l->data);
		l = l->next;
	}
	list = l1;
	i = temp_i;
	stt = temp;
	/*int temp = stt;
	quickSort(list, list.head, list.tail, 1, temp);*/
}
void chonM3_4(List & list)
{
	List l1;
	Init(l1);
	int temp = stt;
	int temp_i = i;
	Node* l = list.head;
	while (l != NULL)
	{
		sapXepDiemTB(l1, l->data);
		l = l->next;
	}
	list = l1;
	i = temp_i;
	stt = temp;
	/*int temp = stt;
	quickSort(list, list.head, list.tail,1,temp);*/
}
void chonM3_2(List & list)
{
	List l1;
	Init(l1);
	int temp = stt;
	int temp_i = i;
	Node* l = list.head;
	while (l != NULL)
	{
		sapXepHoTen(l1, l->data);
		l = l->next;
	}
	list = l1;
	i = temp_i;
	stt = temp;
	/*int temp = stt;
	quickSort(list, list.head, list.tail, 1, temp);*/
}
void chonM3_1(List & list)
{
	List l1;
	Init(l1);
	int temp = stt;
	int temp_i = i;
	Node* l = list.head;
	while (l != NULL)
	{
		sapXepMSV(l1, l->data);
		l = l->next;
	}
	list = l1;
	i = temp_i;
	stt = temp;
	/*int temp = stt;
	quickSort(list, list.head, list.tail, 1, temp);*/
}


void chonM3_2(List & list, int choice)
{
	background();
	menuM3_2(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phimDiChuyen(c, line, 5);
			menuM3_2(line);
		}
		if (c == 13)
		{

			if (line == 5)
			{
				break;
			}
		}
	}
}
void chonM3(List & list)
{

loop: display1(list, stt);
	backgroundMenu();
	menuM3_1(1);
	float trang1 = (float)stt / 10;
	int temp1 = ceil(trang1);
	int trang = 1;
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			c = _getch();
			if (c == 80)
			{
				if (line == 6) line = 1;
				else line++;
			}
			if (c == 72)
			{
				if (line == 1) line = 6;
				else line--;
			}
			menuM3_1(line);
			if (c == 72 || c == 80) continue;
			if (c == 77)
			{
				if (trang == temp1) trang = 1;
				else trang++;
			}
			if (c == 75)
			{
				if (trang == 1) trang = temp1;
				else trang--;
			}
			displayInit();
			display2(list, trang);
		}
		if (c == 13)
		{
			if (line == 1)
			{
				chonM3_1(list); goto loop;
			}
			if (line == 2)
			{
				chonM3_2(list); goto loop;
			}
			if (line == 3)
			{
				chonM3_3(list); goto loop;
			}
			if (line == 4)
			{
				chonM3_4(list); goto loop;
			}
			if (line == 5) break;
			//chonM3_2(list, line); goto loop;
		}
	}

}
void chonM4_2(List & list, int choice)
{
	background();
	menuM4_2(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phimDiChuyen(c, line, 3);
			menuM4_2(line);
		}
		if (c == 13)
		{

			if (line == 3)
			{
				break;
			}
		}
	}
}
void menuChonM4(int choice)
{
	setColor(63);
	string menu[3] = { "    " ,"Tiep Tuc.","Quay Lai." };
	for (int i = 1; i < 3; i++)
	{
		gotoxy(3, 13 + i);
		if (i != choice) cout << menu[i] << endl;
		else
		{
			setColor(60);
			cout << menu[i];
			setColor(63);
			cout << endl;
		}
	}
	gotoxy(0, 0);
}

void enter_from_to(float& from, float& to)
{

	gotoxy(11, 8);
	cin >> from;
	while (!setDiem(from))
	{
		gotoxy(11, 8);
		cout << setw(4) << setfill(' ') << " "; gotoxy(11, 8);
		cin >> from;
	}
	gotoxy(11, 11);
	cin >> to;
	while (!setDiem(to) || to < from)
	{
		gotoxy(11, 11);
		cout << setw(4) << setfill(' ') << " "; gotoxy(11, 11);
		cin >> to;
	}
}
void chonM4_5(List list)
{
loop:backgroundMenu();
	int c;
	int line = 1;
	List l1;
	Init(l1);
	float from, to;
	gotoxy(3, 5);  cout << "       TIM KIEM THEO DIEM     ";
	gotoxy(3, 8);  cout << "From   ";
	hinhChuNhatManh(10, 7, 8, 2, 63);
	gotoxy(3, 11);  cout << "To   ";
	hinhChuNhatManh(10, 10, 8, 2, 63);

	gotoxy(3, 15); cout << "Quay Lai.";
	gotoxy(3, 14); cout << "Tiep Tuc.";

	enter_from_to(from, to);
	int stt1 = 0;
	int temp = stt;
	int temp_i = i;
	timKiemDiem(list, from, to, l1, stt1);

	//chonM3_4(list);//sap xep theo diem 
	//choVaoMang(list);
	//int tim = binarySearch(l1, sv, from, to, 0);
	//if (tim == 0)
	//{
	//	gotoxy(0, 0); cout << "Khong Thay" << endl;
	//}
	//while (tim != 0)
	//{
	//	tim = binarySearch(l1, sv, from, to, tim--);
	//}
	stt = temp;
	i = temp_i;

	float trang1 = (float)stt1 / 10;
	int temp1 = ceil(trang1);
	int trang = 1;
	displayInit();
	display(l1);
	menuChonM4(1);
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			c = _getch();
			if (c == 80)
			{
				if (line == 2) line = 1;
				else line++;
			}
			if (c == 72)
			{
				if (line == 1) line = 2;
				else line--;
			}
			menuChonM4(line);
			if (c == 72 || c == 80) continue;
			if (c == 77)
			{
				if (trang == temp1) trang = 1;
				else trang++;
			}
			if (c == 75)
			{
				if (trang == 1) trang = temp1;
				else trang--;
			}
			displayInit();
			display2(l1, trang);


		}
		if (c == 13)
		{
			if (line == 1) goto loop;
			if (line == 2) break;
		}
	}

}
void chonM4_1(List list)
{
loop:backgroundMenu();
	int c;
	string x;
	int line = 1;
	List l1;
	Init(l1);
	float from, to;
	gotoxy(3, 5);  cout << "      TIM KIEM THEO MA LOP    ";
	gotoxy(3, 10);  cout << "Ma Lop ";
	hinhChuNhatManh(10, 9, 11, 2, 63);

	gotoxy(3, 15); cout << "Quay Lai.";
	gotoxy(3, 14); cout << "Tiep Tuc.";

	gotoxy(11, 10);
	cin.clear();
	getline(cin, x);

	int stt1 = 0; //so luong phan tu tim thay trong list 1
	int temp = stt;
	int temp_i = i;
	timKiemMaLop(list, x, l1, stt1);
	stt = temp;
	i = temp_i;

	float trang1 = (float)stt1 / 10;
	int temp1 = ceil(trang1);
	int trang = 1;
	displayInit();
	display(l1);
	menuChonM4(1);
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			c = _getch();
			if (c == 80)
			{
				if (line == 2) line = 1;
				else line++;
			}
			if (c == 72)
			{
				if (line == 1) line = 2;
				else line--;
			}
			menuChonM4(line);
			if (c == 72 || c == 80) continue;
			if (c == 77)
			{
				if (trang == temp1) trang = 1;
				else trang++;
			}
			if (c == 75)
			{
				if (trang == 1) trang = temp1;
				else trang--;
			}
			displayInit();
			display2(l1, trang);


		}
		if (c == 13)
		{
			if (line == 1) goto loop;
			if (line == 2) break;
		}
	}
}
void chonM4_3(List list)
{
loop:backgroundMenu();
	int c;
	string x;
	int line = 1;
	List l1;
	Init(l1);
	float from, to;
	gotoxy(3, 5);  cout << "      TIM KIEM THEO HO TEN    ";
	gotoxy(3, 10);  cout << "Name ";
	hinhChuNhatManh(10, 9, 20, 2, 63);

	gotoxy(3, 15); cout << "Quay Lai.";
	gotoxy(3, 14); cout << "Tiep Tuc.";

	gotoxy(11, 10);
	cin.clear();
	getline(cin, x);
	int stt1 = 0;
	int temp = stt;
	int temp_i = i;
	timKiemHoTen(list, x, l1, stt1);
	stt = temp;
	i = temp_i;


	float trang1 = (float)stt1 / 10;
	int temp1 = ceil(trang1);
	int trang = 1;
	displayInit();
	display(l1);
	menuChonM4(1);
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			c = _getch();
			if (c == 80)
			{
				if (line == 2) line = 1;
				else line++;
			}
			if (c == 72)
			{
				if (line == 1) line = 2;
				else line--;
			}
			menuChonM4(line);
			if (c == 72 || c == 80) continue;
			if (c == 77)
			{
				if (trang == temp1) trang = 1;
				else trang++;
			}
			if (c == 75)
			{
				if (trang == 1) trang = temp1;
				else trang--;
			}
			displayInit();
			display2(l1, trang);


		}
		if (c == 13)
		{
			if (line == 1) goto loop;
			if (line == 2) break;
		}
	}
}
void chonM4_4(List list)
{
loop:backgroundMenu();
	int c;
	string x;
	int line = 1;
	List l1;
	Init(l1);
	float from, to;
	gotoxy(3, 5);  cout << "    TIM KIEM THEO NGAY SINH   ";
	gotoxy(3, 10);  cout << "Nhap ";
	hinhChuNhatManh(10, 9, 20, 2, 63);

	gotoxy(3, 15); cout << "Quay Lai.";
	gotoxy(3, 14); cout << "Tiep Tuc.";
	fflush(stdin);
	gotoxy(11, 10);
	getline(cin, x);

	int stt1 = 0;
	int temp = stt;
	int temp_i = i;
	tim_kiem_theo_NS(list, x, l1, stt1);
	stt = temp;
	i = temp_i;

	float trang1 = (float)stt1 / 10;
	int temp1 = ceil(trang1);
	int trang = 1;
	displayInit();
	display(l1);
	menuChonM4(1);
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			c = _getch();
			if (c == 80)
			{
				if (line == 2) line = 1;
				else line++;
			}
			if (c == 72)
			{
				if (line == 1) line = 2;
				else line--;
			}
			menuChonM4(line);
			if (c == 72 || c == 80) continue;
			if (c == 77)
			{
				if (trang == temp1) trang = 1;
				else trang++;
			}
			if (c == 75)
			{
				if (trang == 1) trang = temp1;
				else trang--;
			}
			displayInit();
			display2(l1, trang);


		}
		if (c == 13)
		{
			if (line == 1) goto loop;
			if (line == 2) break;
		}
	}
}
void chonM4_2(List list)
{
	List l1;
	Init(l1);
loop: backgroundMenu();


	char x[11];
	int c;
	int line = 1;

	gotoxy(3, 5);  cout << "       TIM KIEM THEO MSV     ";
	gotoxy(3, 10);  cout << "MSV   ";
	hinhChuNhatManh(10, 9, 11, 2, 63);

	gotoxy(3, 15); cout << "Quay Lai.";
	gotoxy(3, 14); cout << "Tiep Tuc.";

	gotoxy(11, 10);
	cin >> x;
	while (!setMSV(x,list))
	{
		gotoxy(11, 10);
		cout << setw(l_masv - 1) << setfill(' ') << " "; gotoxy(11, 10);
		cin >> x;
	}

	int stt1 = 0;
	int temp = stt;
	int temp_i = i;
	timKiemMSV(list, x, l1, stt1);
	stt = temp;
	i = temp_i;

	float trang1 = (float)stt1 / 10;
	int temp1 = ceil(trang1);
	int trang = 1;
	displayInit();
	display(l1);
	menuChonM4(1);
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			c = _getch();
			if (c == 80)
			{
				if (line == 2) line = 1;
				else line++;
			}
			if (c == 72)
			{
				if (line == 1) line = 2;
				else line--;
			}
			menuChonM4(line);
			if (c == 72 || c == 80) continue;
			if (c == 77)
			{
				if (trang == temp1) trang = 1;
				else trang++;
			}
			if (c == 75)
			{
				if (trang == 1) trang = temp1;
				else trang--;
			}
			displayInit();
			display2(l1, trang);


		}
		if (c == 13)
		{
			if (line == 1) goto loop;
			if (line == 2) break;
		}
	}
}
void chonM4(List list)
{

loop: display1(list, stt);
	backgroundMenu();
	menuM4_1(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();

		if (c == 224)
		{
			line = phimDiChuyen(c, line, 6);
			menuM4_1(line);
		}
		if (c == 13)
		{
			if (line == 1)
			{
				chonM4_1(list); goto loop;
			}
			if (line == 2)
			{
				chonM4_2(list); goto loop;
			}
			if (line == 3)
			{
				chonM4_3(list); goto loop;
			}
			if (line == 4)
			{
				chonM4_4(list); goto loop;
			}
			if (line == 5)
			{
				chonM4_5(list); goto loop;
			}
			if (line == 6) break;

		}
	}
	fflush(stdin);
}
void chonM5(List list)
{
	fflush(stdin);
	backgroundMenu();
	menuChinh(5);
	khungThongKe();
	thongKe(list);
	getchar();
}
void chonM(List & list)
{
loop: background();
	display1(list, stt);
	menuChinh(1);
	int line = 1;
	int c;
	while (1)
	{
		c = _getch();
		if (c == 224)
		{
			line = phimDiChuyen(c, line, 6);
			menuChinh(line);
		}
		if (c == 13)
		{
			if (line == 1)
			{
				chonM1(list);  goto loop;
			}
			if (line == 2)
			{
				chonM2(list);  goto loop;
			}
			if (line == 3)
			{
				chonM3(list); goto loop;
			}
			if (line == 4)
			{
				chonM4(list); goto loop;
			}
			if (line == 5)
			{
				chonM5(list); system("cls"); goto loop;
			}
			if (line == 6) break;
		}
	}
}


// In general, ignore this file, but keep it around if you are using pre-compiled headers.