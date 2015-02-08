// TODO : ifstream problem in < v 4.8.2 must use .c_str()
#include <algorithm>
#include <cstdlib>
//#include <sys/types.h>
#include <dirent.h>
//#include <errno.h>
#include <ctype.h>

#include <regex>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

using namespace std;

class Node
{
public:
  string word;
  list<int> filename;
  Node(){
  }
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


char easytolower(char in){
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;
}

unordered_map<string, Node> allmap;
void indexing(string word,int filename){
  transform(word.begin(), word.end(), word.begin(), easytolower);
  unordered_map<string, Node >::iterator it;

  Node n = Node(word);
  n.add(filename);
  pair<unordered_map<string, Node>::iterator, bool>  status=allmap.emplace(word,n);

  if(!status.second){
    
    //TODO : Check is this file already in the list
    
    allmap[word].add(filename);
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
  regex alphab("[a-zA-Z]+");
  string filename;
  string word="";
  ifstream infile;
  for (int i = 1; i <= count; i++)
  {
    //-----------------------------
    filename=dir+"/file"+to_string(i)+".txt";
    //cout<<filename<<endl;
    infile.open(filename);
    char ch;
    while((ch = infile.get())!=EOF)
    {
      //cout << word;
      if(isalpha(ch)){
        word +=ch;
      }else{
        if(word.size()>0){
          indexing(word,i);
          //cout<<word<<endl;
        }
        word="";
      }
    }
    infile.close();
    //-----------------------------
  }

  //---------------------------------------
  
}

//TODO change to read until Can't read
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
  while (readdir(dp) != NULL) count++;
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
//
  if(count>3000)
      allmap.reserve(600000);
  else if(count>6500) {
      allmap.reserve(1400000);
  }else{
      allmap.reserve(400000);
  }

  fileRead(dir,count);

  ofstream of;
  of.open("output");
  of<<allmap.size()<<endl;
  map<string, Node> ordered(allmap.begin(), allmap.end());

  for(auto it = ordered.begin(); it != ordered.end(); ++it){
    //std::cout << it->second;
    of<<(it->second).getAll()<<endl;
  }

  of.close();


  //-----------------------------------
  /*for (auto& x: allmap) {
      cout << (x.second).getAll() << endl;
  }*/
  cout<<"MAP:"<<allmap.size()<<endl;
  return 0;
}
