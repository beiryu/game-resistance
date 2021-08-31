﻿#include "Log.h"
vector<LOG> listLog;// danh sách log
void LOG::setH(int _h)
{
	h = _h;
}
int LOG::getH()
{
	return h;
}
void LOG::setM(int _m)
{
	m = _m;
}
int LOG::getM()
{
	return m;
}
void LOG::setS(int _s)
{
	s = _s;
}
int LOG::getS()
{
	return s;
}
void LOG::setDD(int _dd)
{
	dd = _dd;
}
int LOG::getDD()
{
	return dd;
}
void LOG::setMM(int _mm)
{
	mm = _mm;
}
int LOG::getMM()
{
	return mm;
}
void LOG::setYY(int _yy)
{
	yy = _yy;
}
int LOG::getYY()
{
	return yy;
}
void LOG::setUsername_1(string username)
{
	username_1 = username;
}
string LOG::getUsername_1()
{
	return username_1;
}
void LOG::setUsername_2(string username)
{
	username_2 = username;
}
string LOG::getUsername_2()
{
	return username_2;
}
void LOG::setListTuongPlayer_1(const vector<TUONG> x)
{
	for (int i = 0; i < x.size(); ++i)
	{
		TUONG t(x.at(i));
		player_1.push_back(t);
	}
}
vector<TUONG> LOG::getListTuongPlayer_1()
{
	return player_1;
}
void LOG::setListTuongPlayer_2(const vector<TUONG> x)
{
	for (int i = 0; i < x.size(); ++i)
	{
		TUONG t(x.at(i));
		player_2.push_back(t);
	}
}
vector<TUONG> LOG::getListTuongPlayer_2()
{
	return player_2;
}
void LOG::setMoiTruong(string _moiTruong)
{
	moiTruong = _moiTruong;
}
string LOG::getMoiTruong()
{
	return moiTruong;
}
void LOG::setKetQua(string _ketQua)
{
	ketQua = _ketQua;
}
string LOG::getKetQua()
{
	return ketQua;
}
ostream& operator << (ostream& outDev, LOG& x) // viết toán tử << cho log theo cấu trúc dễ đọc và đầy đủ
{
	outDev << "\n<" << x.h << ":" << x.m << ":" << x.s << " " << x.dd << "/" << x.mm << "/" << x.yy << ">\n";
	outDev << "<" << x.username_1 << ">\n";
	for (int i = 0; i < nChamp; i++)
	{
		x.player_1.at(i).print(outDev);
		outDev << "\n";
	}
	outDev << "<" << x.username_2 << ">\n";
	for (int i = 0; i < nChamp; i++)
	{
		x.player_2.at(i).print(outDev);
		outDev << "\n";
	}
	outDev << "<" << x.moiTruong << ">";
	outDev << x.ketQua;
	return outDev;
}
istream& operator >> (istream& inDev, LOG& x) // đọc ra lại 
{
	char c;
	inDev >> c; // bỏ dòng đầu
	string temp;
	getline(inDev, temp, ':');
	x.h = stoi(temp);
	getline(inDev, temp, ':');
	x.m = stoi(temp);
	getline(inDev, temp, ' ');
	x.s = stoi(temp);
	getline(inDev, temp, '/');
	x.dd = stoi(temp);
	getline(inDev, temp, '/');
	x.mm = stoi(temp);
	getline(inDev, temp, '>');
	x.yy = stoi(temp);
	inDev >> c;
	getline(inDev, temp, '>');
	x.username_1 = temp;
	for (int i = 0; i < nChamp; ++i)
	{
		TUONG tuong;
		inDev >> tuong;
		x.player_1.push_back(tuong);
	}
	inDev >> c;
	getline(inDev, temp, '>');
	x.username_2 = temp;
	for (int i = 0; i < nChamp; ++i)
	{
		TUONG tuong;
		inDev >> tuong;
		x.player_2.push_back(tuong);
	}
	inDev >> c;
	getline(inDev, temp, '>');
	x.moiTruong = temp;
	getline(inDev, temp, '\n');
	x.ketQua = temp;
	return inDev;
}
void LOG::docLog()
{
	listLog.clear();					// xóa listLog cũ
	fstream fileLog("Log.txt", ios::in);	// đọc log
	if (!fileLog)
	{
		cout << "\nCANNOT OPEN FILE!!!";
		exit(0);
	}
	string temp;
	getline(fileLog, temp, '\n');
	if (temp != "")  // xem định dạng file có dòng đầu hay không
	{
		fileLog.seekg(0);
	}
	while (!fileLog.eof())
	{
		LOG x;
		fileLog >> x;
		listLog.push_back(x);
	}
	fileLog.close();
}
int LOG::xemLog()
{
	cout << "\nHISTORY MATCH\n";
	cout << "\n		0. EXIT";            // nếu ko có log thì thoát
	for (int i = 0; i < listLog.size(); ++i) // in ra thời gian mỗi trận trong listLog
	{
		LOG temp = listLog.at(i);
		cout << "\n		" << i + 1 << ". " << temp.h << ":" << temp.m << ":" << temp.s << " " << temp.dd << "/" << temp.mm << "/" << temp.yy;
	}
	int idx;
	bool flag = true;
	while (flag)
	{
		try
		{										// bắt lỗi nhập 
			cout << "\nINPUT TIME (INDEX): ";
			cin >> idx;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				throw 1;
			}
			if (idx < 0 || idx > listLog.size())
			{
				throw 1;
			}
			flag = false;						// nếu nhập đúng thì dừng vòng lặp
		}
		catch (int x)
		{
			if (x)
			{
				flag = true;				// cho nhập lại
			}
		}
	}
	system("cls");
	return idx;
}
void LOG::xemLogChiTiet()
{
	int idx = xemLog();
	if (idx == 0)
	{
		cout << "\n\n\n\n\n";
		return;										// chọn thoát thì return
	}						
	LOG temp = listLog.at(idx - 1);
	cout << "\nMATCH DETAIL: \n";
	cout << temp.ketQua;
	cout << "\n\nTEAM " << temp.username_1;
	for (int i = 0; i < nChamp; ++i)
	{
		cout << "\n";
		temp.player_1.at(i).print(cout);
	}
	cout << "\n\nTEAM " << temp.username_2;

	for (int i = 0; i < nChamp; ++i)
	{
		cout << "\n";
		temp.player_2.at(i).print(cout);
	}
	cout << "\n\n\n\n\n";
}