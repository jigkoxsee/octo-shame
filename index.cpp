#include <cstdlib>
//#include <sys/types.h>
#include <dirent.h>
//#include <errno.h>
#include <list>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

class Node
{
public:
    string word;
    list<int> file;
    Node(string w){
        word=w;
    }

    bool add(int fn){
        //list<int>::iterator it=mylist.end()
        //.empty()
        if(file.empty()||file.back()!=fn){
            file.push_back(fn);
            return true;
        }
        return false;
    }
    string getAll(){
        string all=word+":"+to_string(file.size())+":";
        for (list<int>::iterator it = file.begin(); it != file.end(); it++){
            all+=to_string(*it);
            all+=",";
        }

        return all.substr(0, all.size()-1);
    }

    //~Node();
};

/*function... might want it in some class?*/
/*
List file and read it to 

*/
int fileCount (string dir)
{
    int count=0;
    DIR *dp;
    struct dirent *dirp;
    string filename;
    string word;
    ifstream infile;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout<<"Error : Can't open directory"<<endl;
        exit(1);
    }
    while ((dirp = readdir(dp)) != NULL) {
        //count++;
        //-----------------------------
        filename=dir+"/file"+to_string(++count)+".txt";
        cout<<filename<<endl;
        infile.open(filename);
        while(1)
        {
            //getline(infile, word);
            infile>>word;
            if (infile.fail()||infile.eof())
                break;
            cout << word << endl;
            // Indexing
        }
        infile.close();
        //-----------------------------
    }
    closedir(dp);
    return count-2;
}

int main(int argc, char* const argv[])
{
    string dir = string(argv[1]);
    
    //cout<<dir<<endl;
    int count=fileCount(dir);
    cout<<"Count"<<count<<endl;
    Node i1= Node("hello");
    i1.add(1);
    i1.add(2);
    i1.add(3);
    cout<<i1.getAll()<<endl;


//-----------------------------------
    
    return 0;
}