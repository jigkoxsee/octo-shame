#include <cstdlib>
#include <dirent.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>
#include <mutex>

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
mutex mtex;
bool haveNext=true;
string dir;
class Node
{
public:
  vector<int> filename;
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
    for (vector<int>::iterator it = filename.begin(); it != filename.end(); it++)
      all+=to_string(*it)+",";
    return all.substr(0, all.size()-1);
  }
};


char easytolower(char in){
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;
}


vector<pair<string,int>> word_queue[4];

static unordered_map<string, Node*> allmap;
static chrono::duration<double> time_span;

void indexing(string word,int filename){
  transform(word.begin(), word.end(), word.begin(), easytolower);
  /*
  Node *n = new Node();
  n->add(filename);
  
  pair<unordered_map<string, Node*>::iterator, bool>  status=allmap.emplace(word,n);

  if(!status.second){
    allmap[word]->add(filename);
    delete n;
  }*/

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
void fileRead(int start,int end,int thread)
{
  string filename;
  string word="";
  ifstream infile;
  for (int i = start; i <= end; i++)
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
//          mtex.lock();
          word_queue[thread].push_back(make_pair(word,i));
//          mtex.unlock();
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

/*
void job2(){
  while(haveNext||!word_queue.empty()){
    if(!word_queue.empty()){
      pair<string,int> w=word_queue.front();
//      mtex.lock();
      indexing(w.first,w.second);
//      mtex.unlock();
     word_queue.pop();
    }
  }
}
*/

int main(int argc, char* const argv[])
{
 // thread job(job2);
  dir = string(argv[1]);
  cout<<dir<<endl;
  int count=fileCount(dir);
  if(count>3000)
      allmap.reserve(600000);
  else if(count>6500) {
      allmap.reserve(2400000);
  }else{
      allmap.reserve(400000);
  }

//  fileRead(dir,count);
  int part=count/4;
  thread fr1(fileRead,1,part,1);
  thread fr2(fileRead,1+part,part*2,2);
  thread fr3(fileRead,1+part*2,part*3,3);
  thread fr4(fileRead,1+part*3,count,4);
  fr1.join();
  fr2.join();
  fr3.join();
  fr4.join();

  cout<<"1 "<<word_queue[1].size()<<endl;
  cout<<"2 "<<word_queue[2].size()<<endl;
  cout<<"3 "<<word_queue[3].size()<<endl;
  cout<<"4 "<<word_queue[4].size()<<endl;

/*
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
*/
  return 0;
}
