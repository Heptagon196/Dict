#ifndef TRIETREE_H
#define TRIETREE_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#ifdef linux
#include "Conio.h"
#else
#include "Conio_Windows.h"
#endif
using namespace std;
class TrieTree {
	private:
		int word=-1;
		map<char,TrieTree> n;
		string info;
		TrieTree * fa;
		void Rputs(TrieTree *p,string str,int *cnt) {
			if ((*cnt)>10)
				return ;
			for (char i='a';i<='z';i++) {
				if ((*cnt)>10)
					return ;
				if (p->n[i]!=-1) {
					if (p->n[i].word==0)
						Rputs(&p->n[i],str+(char)i,cnt);
					else
						puts((str+(char)i).c_str()),(*cnt)++;
				}
			}
		}
	public:
		TrieTree& operator [](char x) {return n[x];}
		TrieTree& at(char x) {return n[x];}
		bool operator == (int x) {return word==x;}
		bool operator != (int x) {return word!=x;}
		void add(string str,string text) {
			TrieTree* p=this;
			for (int i=0;i<str.length();i++) {
				TrieTree *tmp=p;
				p=&p->n[str[i]];
				p->fa=tmp;
				if (p->word==-1)
					p->word=0;
			}
			p->word=1;
			p->info+=text;
		}
		int query(string str,int l) {
			TrieTree* p=this;
			TrieTree* last;
			int line;
			for (int i=l;i<str.length();i++) {
				line=0;
				if (str[i]=='\\'||str[i]=='\n'||str[i]=='\r'||str[i]=='\t'||str[i]==' ')
					continue;
				last=p;
				p=&p->n[str[i]];
				if (p->word==-1) {
					int w=0;
					gotoxy(1,5+line);
					Rputs(last,str.substr(0,i),&w);
					return -1;
				}
				if (p->word==1&&i==str.length()-1) {
					gotoxy(1,3);
					int k;
					for (k=0;k<p->info.size();k++)
						if (p->info[k]!=' ')
							break;
					if (p->info[k]=='\\'&&p->info[k+1]=='n')
						k+=2;
					for (int i=k;i<p->info.size()-1;i++)
						if (p->info[i]=='\\'&&p->info[i+1]=='n')
							putchar('\n'),i++,line++;
						else
							putchar(p->info[i]);
					putchar(p->info[p->info.size()-1]);
					puts("\n\n");
					int w=0;
					Rputs(p,str,&w);
					return i+1;
				}
			}
			int w=0;
			gotoxy(1,5+line);
			Rputs(p,str,&w);
			return -1;
		}
		int query(string str) {
			return query(str,0);
		}
};
#endif
