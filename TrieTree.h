#ifndef TRIETREE_H
#define TRIETREE_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
class TrieTree {
	private:
		int word=-1;
		map<char,TrieTree> n;
		string info;
	public:
		void add(string str,string text) {
			TrieTree* p=this;
			for (int i=0;i<str.length();i++) {
				p=&p->n[str[i]];
				if (p->word==-1)
					p->word=0;
			}
			p->word=1;
			p->info+=text;
		}
		int query(string str,int l) {
			TrieTree* p=this;
			for (int i=l;i<str.length();i++) {
				if (str[i]=='\\'||str[i]=='\n'||str[i]=='\r'||str[i]=='\t'||str[i]==' ')
					continue;
				p=&p->n[str[i]];
				if (p->word==-1)
					return -1;
				if (p->word==1&&i==str.length()-1) {
					for (int i=0;i<p->info.size()-1;i++)
						if (p->info[i]=='\\'&&p->info[i+1]=='n')
							putchar('\n'),i++;
						else
							putchar(p->info[i]);
					putchar(p->info[p->info.size()-1]);
					putchar('\n');
					return i+1;
				}
			}
			return -1;
		}
		int query(string str) {
			return query(str,0);
		}
};
#endif
