#include <cstdlib>
#include <dirent.h>
#include <forward_list>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>

using namespace std;
string dir;

char lower(char in){
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;
}

static unordered_map<string, vector<int>*> allmap;

void indexing(string word,int filename){
  transform(word.begin(), word.end(), word.begin(), lower);
  vector<int> *n = new vector<int>;
  if(n->empty()||n->back()!=filename){
    n->push_back(filename);
  }
  pair<unordered_map<string, vector<int>*>::iterator, bool>  status=allmap.emplace(word,n);

  if(!status.second){

    if(allmap[word]->empty()||allmap[word]->back()!=filename){
      allmap[word]->push_back(filename);
    }

    delete n;
  }
}

bool isAlphabet(char ch){
  if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
    return true;
  }
  return false;
}

/*
List file and read it to 
*/
void fileRead(string dir,int count)
{
  string filename;
  string word="";
  ifstream infile;
  for (int i = 1; i <= count; i++)
  {
    filename=dir+"/file"+to_string(i)+".txt";
    infile.open(filename.c_str());
    char ch;
    while((ch = infile.get())!=EOF)
    {
      if(isalpha(ch)){
        word +=ch;
      }else{
        if(word.size()>0){
          indexing(word,i);
        }
        word="";
      }
    }
    infile.close();
  }
}


int fileCount (string dir)
{
  int count=0;
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    cout<<"Error : Can't open directory"<<endl;
    exit(1);
  }
  while (readdir(dp) != NULL) count++;
  closedir(dp);
  return count-2;
}

int main(int argc, char* const argv[])
{
  dir = string(argv[1]);
  int count=fileCount(dir);
/*  if(count>3000)
      allmap.reserve(600000);
  else if(count>6500) {
      allmap.reserve(2400000);
  }else{
      allmap.reserve(400000);
  }
*/
  fileRead(dir,count);

  ofstream of;
  of.open("output");
  of<<allmap.size()<<endl;
  map<string, vector<int>*> ordered(allmap.begin(), allmap.end());
  allmap.clear();
  for(auto it = ordered.begin(); it != ordered.end(); ++it){
    of<<(it->first);
    vector<int> *filename=(it->second);

    string all=":"+to_string(filename->size())+":";
    for(vector<int>::iterator it = filename->begin(); it != filename->end(); it++)
      all+=to_string(*it)+",";
    of<<all.substr(0, all.size()-1)<<endl;
  }
  of.close();

  return 0;
}
