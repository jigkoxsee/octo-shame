#include <cstdlib>
//#include <sys/types.h>
#include <dirent.h>
//#include <errno.h>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;



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
    list<string> filename;
    Node(string w){
        word=w;
    }

    bool add(string fn){
        if(filename.empty()||filename.back()!=fn){
            filename.push_back(fn);
            return true;
        }
        return false;
    }
    string getAll(){
        string all=word+":"+to_string(filename.size())+":";
        for (list<string>::iterator it = filename.begin(); it != filename.end(); it++)
            all+=(*it)+",";
        return all.substr(0, all.size()-1);
    }

    //~Node();
};

map <string, Node *> allmap;
void indexing(string word,string filename){
    map<string, Node *>::iterator it;
    it=allmap.find(word);
    Node *n;
    if(it!=allmap.end()){
        //cout<<"In:"<<(it->second)->getAll()<<endl;
        n = it->second;
        //n->add(filename);

     //   cout<<"2:"<<(it->second)->getAll()<<endl;
    }else{
        n = new Node(word);
    }
        n->add(filename);
        allmap[word]=n;
        //cout<<"1:"<<n->getAll()<<endl;

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
        //cout<<filename<<endl;
        infile.open(filename);
        while(1)
        {
            infile>>word;
            if (infile.fail()||infile.eof())

                break;
            //cout << word << endl;
            // Indexing
            indexing(word,to_string(count));
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
    
    cout<<dir<<endl;

    int count=fileCount(dir);
    cout<<"Count"<<count<<endl;


//-----------------------------------

    cout<<"map"<<allmap.size()<<endl;
    /*for (auto& x: allmap) {
        std::cout <<(x.second)->getAll() << endl;
    }*/
    return 0;
}