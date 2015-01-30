#include "stdio.h"
#include "string.h"
#include <glib.h>

#include <glib/gstdio.h>


#define FILENAME char *
//#define INDEXNODE node

typedef struct node node;
struct node
{
  char *str;
  GSList *link;
};

void indexing(const gchar *contents){
   GHashTable* hashTB = g_hash_table_new(g_str_hash, g_direct_equal);
}

//Read file by asc order
void readfile(const char *dir,int count){
  printf("=====\nRead file\n");
  gchar *filename=NULL;
  gchar *contents=NULL;
  gsize *length=NULL;
  GError *error=NULL;
  int i;
  for(i=1;i<=count;i++){

	char fn[8];
	sprintf(fn, "%d", i);

  	/*
  	//TODO : when
  	with / Dir = data/ 
  	with out / Dir = data
  	*/
    filename = g_strconcat(dir,"/file",fn,".txt",NULL);//g_array_index(array, FILENAME, i);

    //printf("fn : %s\n", filename);
    int f = g_file_get_contents (filename,&contents,length,&error);
    //printf("%s\n",contents );
    if(!f){ // Use for check file open status
    	printf("fn : %s\n", filename);
      printf("%s\n",error->message );
    }else{
    	printf("fn : %s\n", filename);
    }
    //free memory of file that was indexed

  }
  indexing(contents);
}

int fileCount(char const *dir){
  int count=0;


  DIR *directory;
  struct dirent *fileList;
  directory = opendir(dir);
  if (directory){
    while ((fileList = readdir(directory)) != NULL)
    {
      char *filename=fileList->d_name;
      if(g_strcmp0(filename,".")!=0&&g_strcmp0(filename,"..")!=0){
        count++;
      }
    }
    closedir(directory);
  }
  return count;
}

int main(int argc, char const *argv[])
{
  printf("Hello param: %s\n",argv[1]);
  int count=0;
  char *filename;
  GArray *filearray;
  int i=0;

  count=fileCount(argv[1]);
  printf("No : %d\n",count);
  readfile(argv[1],count);

/*
  filearray=fileList(argv[1],&count);
  printf("%d\n", count);

  for (i = 0; i < count; ++i)
  {
    filename = g_array_index(filearray, FILENAME, i);
    printf("%s\n", filename);
  }
  readfile(filearray,count);
*/
  return 0;
}