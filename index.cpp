#include <cstdlib>
//#include <sys/types.h>
#include <dirent.h>
//#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <glib.h>


using namespace std;

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
/*
void readfile(string dir,int count)
{
	string word;
	ifstream infile;
	string filename;

	for (int i = 1; i <= count; ++i)
	{
		filename=dir+"/file"+to_string(i)+".txt";
		//cout<<filename<<endl;
		infile.open(filename);
	    while(1)
	    {
	    	//getline(infile, word);
	    	infile>>word;
	    	if (infile.fail()||infile.eof())
	    		break;
	    	//cout << word << endl;
	    }
	    infile.close();
	}
}
*/

int main(int argc, char* const argv[])
{
    string dir = string(argv[1]);
    vector<string> files = vector<string>();
    //cout<<dir<<endl;
    int count=fileCount(dir);
    cout<<"Count"<<count<<endl;


    return 0;
}