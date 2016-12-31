#ifndef TEXT_H
#define TEXT_H
#ifdef linux
#include "Conio.h"
#else
#include "Conio_Windows.h"
#endif
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

#define KEY_MOVEUP -100000
#define KEY_MOVEDOWN -200000
#define KEY_MOVELEFT -300000
#define KEY_MOVERIGHT -400000
#ifdef linux
#define KEY_BACKSPACE 127
#else
#define KEY_BACKSPACE 8
#endif
#define KEY_HOME -500000
#define KEY_END -600000
class TextBar {
	private:
		vector<string> history;
		int x,y;
		vector<char> buf;
#ifdef linux
		int GetCh() {
			char ch=getch();
			if (ch==(char)27) {
				ch=getch();
				if (ch==91) {
					ch=getch();
					if (ch=='A')
						return KEY_MOVEUP;
					if (ch=='B')
						return KEY_MOVEDOWN;
					if (ch=='D')
						return KEY_MOVERIGHT;
					if (ch=='C')
						return KEY_MOVELEFT;
					if (ch=='H')
						return KEY_HOME;
					if (ch=='F')
						return KEY_END;
					return 0;
				}
			} else
				return ch;
			return 0;
		}
#else
		int GetCh() {
			char ch=getch();
			if (ch==(char)224) {
				ch=getch();
				if (ch=='H')
					return KEY_MOVEUP;
				if (ch=='P')
					return KEY_MOVEDOWN;
				if (ch=='K')
					return KEY_MOVERIGHT;
				if (ch=='M')
					return KEY_MOVELEFT;
				if (ch=='G')
					return KEY_HOME;
				if (ch=='O')
					return KEY_END;
				return 0;
			} else
				return ch;
			return 0;
		}
#endif
	public:
		void loca(int _x,int _y)  {
			x=_x;y=_y;
		}
		TextBar(int _x,int _y) {
			loca(_x,_y);
		}
		void SaveHistory(string filename) {
			ofstream fout;
			fout.open(filename);
			for (int i=max(0,(int)history.size()-21);i<history.size();i++)
				if (history[i]!="")
					fout << history[i] << '|' << endl;
			fout.close();
		}
		void ReadHistory(string filename) {
			ifstream fin;
			fin.open(filename);
			string l;
			while (getline(fin,l,'\n')) {
				l.pop_back();
				history.push_back(l);
			}
			fin.close();
		}
		string Read() {
			int his=history.size();
			history.push_back("");
			string *ans=&history[history.size()-1];
			int loc=x;
			int ch;
			while ((ch=GetCh())!=13&&ch!=3&&ch!=4) {
				int bakhis=his;
				int bakloc=loc;
				if (ch==KEY_MOVEUP)
					his--;
				if (ch==KEY_MOVEDOWN)
					his++;
				if (ch==KEY_MOVERIGHT)
					loc--;
				if (ch==KEY_MOVELEFT)
					loc++;
				if (ch==KEY_BACKSPACE)
					loc--;
				if (ch==KEY_HOME)
					loc=x;
				if (ch==KEY_END)
					loc=x+ans->size();

				if (his!=bakhis) {
					if ((history.size()==0)||((his>=history.size())||(his<0))) {
						his=bakhis;
						continue;
					}
					gotoxy(x,y);
					for (int i=0;i<ans->size()+1;i++)
						putchar(' ');
					gotoxy(x,y);
					cout << history[his];
					ans=&history[his];
					loc=ans->size()+x;
				} else if (loc!=bakloc) {
					if (ans->size()==0||ans->size()+x+1<=loc||loc<x) {
						loc=bakloc;
						continue;
					} else
					if (ch==KEY_BACKSPACE) {
						if (loc==ans->size()+x)
							ans->erase(ans->begin()+bakloc-x-2,ans->begin()+bakloc-x-1);
						else
							ans->erase(ans->begin()+bakloc-x-1,ans->begin()+bakloc-x);
						gotoxy(x,y);
						for (int i=0;i<ans->size()+1;i++)
							putchar(' ');
						gotoxy(x,y);
						cout << (*ans);
						gotoxy(loc,y);
					} else {
						if (loc<x||loc>x+ans->size())
							continue;
						gotoxy(loc,y);
					}
				} else if (ch!=KEY_HOME&&ch!=KEY_END){
					ans->insert(ans->begin()+loc-x,(char)ch);
					loc++;
					gotoxy(x,y);
					for (int i=0;i<ans->size();i++)
						putchar(' ');
					gotoxy(x,y);
					cout << (*ans);
					gotoxy(loc,y);
				}
			}
			gotoxy(x,y);
			for (int i=0;i<ans->size();i++)
				putchar(' ');
			return (*ans);
		}
};

#endif
