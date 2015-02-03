// TODO : ifstream problem in < v 4.8.2 must use .c_str()
#include <algorithm>
#include <cstdlib>
//#include <sys/types.h>
#include <dirent.h>
//#include <errno.h>
#include <regex>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <thread> 

using namespace std;

//thread first;
/*
Node i1= Node("hello");
i1.add(1);
i1.add(2);
i1.add(3);
cout<<i1.getAll()<<endl;
*/
class Node
{
public:
  string word;
  list<int> filename;
  Node(string w){
    word=w;
  }
  bool add(int fn){
    if(filename.empty()||filename.back()!=fn){
      filename.push_back(fn);
      return true;
    }
    return false;
  }
  string getAll(){
    string all=word+":"+to_string(filename.size())+":";
    for (list<int>::iterator it = filename.begin(); it != filename.end(); it++)
      all+=to_string(*it)+",";
    return all.substr(0, all.size()-1);
  }
    //~Node();
};

unordered_map<string, Node *> allmap;

char easytolower(char in){
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;
}

void indexing(string word,int filename){
  transform(word.begin(), word.end(), word.begin(), easytolower);
  unordered_map<string, Node *>::iterator it;

  Node *n;
  n = new Node(word);
  n->add(filename);
  pair<unordered_map<string, Node *>::iterator, bool>  status=allmap.emplace(word,n);
  //cout<<"1:"<<n->getAll()<<endl;
  n=allmap[word];
  if(!status.second){
    n=allmap[word];
      //cout<<"2:"<<n->getAll()<<endl;
    n->add(filename);
    allmap[word]=n;
  }
}

bool isAlphabet(char ch){
  if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
    return true;
  }
  return false;
}

/*
* Return "" if string not alphabet
*/
string filterWord(string word){
  int count=0;
  for (int i = 0; i < word.size(); ++i)
  {
    if (isAlphabet(word[i]))
      count++;
    else
      break;
  }
  word.resize(count);// resize
  return word;
}

/*
List file and read it to 
*/
int wc=0;
void fileRead(string dir,int count)
{
  regex alphab("[a-zA-Z]+");
  string filename;
  string word;
  ifstream infile;

  for (int i = 1; i <= count; i++)
  {
    //-----------------------------
    filename=dir+"/file"+to_string(i)+".txt";
    //cout<<filename<<endl;
    infile.open(filename);
    while(1)
    {
      infile>>word;
      if (infile.fail()||infile.eof())
        break;
        //cout << word << endl;
        //Indexing
      string w=filterWord(word);
      if(w.size()>0)
        wc++;//cout<<w<<endl;
      indexing(w,i);
    }
    infile.close();
    //-----------------------------
  }
}

/*function... might want it in some class?*/
/*
List file and read it to 
*/
int fileCount (string dir)
{
  int count=0;
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    cout<<"Error : Can't open directory"<<endl;
    exit(1);
  }
  while ((dirp = readdir(dp)) != NULL) count++;
  closedir(dp);
  return count-2;
}

//thread first;
int main(int argc, char* const argv[])
{
  string dir = string(argv[1]);

  cout<<dir<<endl;

  int count=fileCount(dir);
  cout<<"Count"<<count<<endl;
    // if(count>3000)
    //     allmap.reserve(400000);
    // else if(count>6500) {
    //     allmap.reserve(1340000);
    // }else{
    //     allmap.reserve(255000);
    // }

  fileRead(dir,count);

  //first.join();

  //-----------------------------------
  cout<<"MAP:"<<allmap.size()<<endl;
  cout<<"WRD:"<<wc<<endl;
  /*for (auto& x: allmap) {
      cout << (x.second)->getAll() << endl;
  }*/
  return 0;
}