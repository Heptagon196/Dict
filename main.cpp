#include "TrieTree.h"
#include "text.h"
#include <fstream>
#include <vector>
#include <dirent.h>
#include <cstdlib>

#ifdef linux
#define SUFFIX ".txt"
#define HA "蛤？"
#include "Conio.h"
static vector<string> GetFile(const char * path,const char * grep) {
	vector<string> ans;
	DIR *pDir;
	struct dirent *ent;
	pDir=opendir(path);
	if (pDir==NULL)
		return (vector<string>){};
	while ((ent=readdir(pDir))!=NULL)
		if (!(ent->d_type & DT_DIR)) {
			string tmp=ent->d_name;
			if ((tmp.length()>=strlen(grep))&&(tmp.substr(tmp.length()-strlen(grep),strlen(grep))==(string)grep))
				ans.push_back(tmp);
		}
	closedir(pDir);
	return ans;
}
#else
#define SUFFIX ".win"
#include "Conio_Windows.h"
char HA[]={-72,-14,-93,-65,0};
static vector<string> GetFile(const char *path,const char *grep) {
	system(("dir /a /b "+(string)path+"\\*.win >dict.tmp").c_str());
	ifstream fin;
	vector<string> ans;
	fin.open("dict.tmp");
	string l;
	while (getline(fin,l,'\n'))
		ans.push_back(l);
	fin.close();
	system("del dict.tmp");
	return ans;
}
#endif

string convert(string &x) {
	string tmp;
	for (int i=0;i<x.size();i++)
		if ((x[i]<='Z')&&(x[i]>='A'))
			tmp.push_back(x[i]-'A'+'a');
		else
			tmp.push_back(x[i]);
	return tmp;
}

int main() {
#ifndef linux
	system("color F0");
	system("cls");
#endif
	ifstream fin;
	TrieTree x;
	string l,l2;
	int n;
	vector<string> dic=GetFile("dic",SUFFIX);
	for (int i=0;i<dic.size();i++) {
		fin.open("dic/"+dic[i]);
		while (getline(fin,l,'\n')) {
			getline(fin,l2,'\n');
			x.add(convert(l),convert(l2));
		}
		fin.close();
	}
	TextBar bar(5,1);
	Clear();
	while (1) {
		string l;
		gotoxy(1,1);
		HighLight();
		foreground(cyan);
		printf(">>> ");
		ClearColor();
		l=bar.Read();
		if (l==""||l=="-q") {
			Clear();
			return 0;
		}
		HighLight();
		foreground(green);
		Clear();
		gotoxy(1,2);
		if (x.query(convert(l))==-1) {
			puts("");
			puts(HA);
			puts("");
		}
		else
			puts("");
	}
	Clear();
	return 0;
}
