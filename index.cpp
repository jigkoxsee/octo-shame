#include <cstdlib>
#include <dirent.h>
#include <forward_list>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <algorithm>

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

bool haveNext=true;

mutex mtex;


chrono::high_resolution_clock::time_point t1;
chrono::high_resolution_clock::time_point t2;

chrono::duration<double> time_span=(chrono::duration<double>)(0);

class Node
{
public:
  list<int> filename;
  Node(){
  }
  bool add(int fn){
    if(filename.empty()||filename.back()!=fn){
      filename.push_back(fn);
      return true;
    }
    return false;
  }

  string getAll(){
    string all=":"+to_string(filename.size())+":";
    for (list<int>::iterator it = filename.begin(); it != filename.end(); it++)
      all+=to_string(*it)+",";
    return all.substr(0, all.size()-1);
  }
};


char easytolower(char in){
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;
}


queue<pair<string,int>> word_queue;

static unordered_map<string, Node*> allmap;

void indexing(string word,int filename){
  transform(word.begin(), word.end(), word.begin(), easytolower);
  Node *n = new Node();
  n->add(filename);
  mtex.lock();
  pair<unordered_map<string, Node*>::iterator, bool>  status=allmap.emplace(word,n);

  if(!status.second){
    allmap[word]->add(filename);
    delete n;
  }
  mtex.unlock();
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
void fileRead(string dir,int start,int count,int step)
{
  string filename;
  string word="";
  ifstream infile;
  for (int i = start; i <= count; i+=step)
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
          t1=chrono::high_resolution_clock::now();
          indexing(word,i);
          t2=chrono::high_resolution_clock::now();

          time_span+=chrono::duration_cast<chrono::duration<double>>(t2 - t1);
        }
        word="";
      }
    }
    infile.close();
  }
  haveNext=false;
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

void jobFile(string dir,int start,int end,int step){
  fileRead(dir,start,end,step);
}

int main(int argc, char* const argv[])
{
//  thread job(job2);
  string dir = string(argv[1]);
  //cout<<dir<<endl;
  int count=fileCount(dir);
  if(count>3000)
      allmap.reserve(600000);
  else if(count>6500) {
      allmap.reserve(2400000);
  }else{
      allmap.reserve(400000);
  }
  cout<<count<<endl;
//  fileRead(dir,count);
  int half=count/2;
  //TODO  : small thread >2 => nothing
  //        Medium => more is better
  //        Large => CPU utilize not 100%
/*
  thread j1(fileRead,dir,0,half/2);
  thread j2(fileRead,dir,1+half/2,half);
  thread j3(fileRead,dir,1+half,count-half);
  thread j4(fileRead,dir,count-half+1,count);
  j1.join();
  j2.join();
  j3.join();
  j4.join();
*/

  thread j1(fileRead,dir,1  ,count,2);
  thread j2(fileRead,dir,2  ,count,2);
  j1.join();
  j2.join();

  ofstream of;
  of.open("output");
  of<<allmap.size()<<endl;
  map<string, Node*> ordered(allmap.begin(), allmap.end());
  allmap.clear();
  for(auto it = ordered.begin(); it != ordered.end(); ++it){
    of<<(it->first);
    of<<(it->second)->getAll()<<endl;
  }
  of.close();
/*
  chrono::high_resolution_clock::time_point t1=chrono::high_resolution_clock::now();
  chrono::high_resolution_clock::time_point t2=chrono::high_resolution_clock::now();

  time_span=chrono::duration_cast<chrono::duration<double>>(t2 - t1);
*/  cout<<time_span.count()<<endl;

  return 0;
}
