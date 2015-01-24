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


/*
* Must ignore "." and ".."
*
*/
GArray * fileList(char const *dir,int *count){
  *count=0;

  GArray *garray;
  garray = g_array_new (FALSE, FALSE, sizeof (FILENAME));
  //GSList *list = NULL;

  //char *item;
  uint i=0;

  DIR *directory;
  struct dirent *fileList;
  directory = opendir(dir);
  if (directory){
    while ((fileList = readdir(directory)) != NULL)
    {
      char *filename=fileList->d_name;
      if(g_strcmp0(filename,".")!=0&&g_strcmp0(filename,"..")!=0){

        //printf("%s\n", filename);
        g_array_append_val (garray, g_strconcat(dir,filename,NULL));
        //item = g_string_new(filename);
        (*count)++;
      }
    }
    closedir(directory);
  }

  return garray;
}

void indexing(GArray *array){
  printf("=====\nInverted indexing\n");
  gchar *filename=NULL;
  gchar *contents=NULL;
  gsize *length=NULL;
  GError *error=NULL;

  filename = g_array_index(array, FILENAME, 0);
  printf("%s\n", filename);
  int f = g_file_get_contents ("tiny/data/file1.txt",&contents,length,&error);
  printf("%d\n",f );
  printf("%s\n",contents );
  //printf("%s\n",error->message );

  //free file memory that was indexed
}

int main(int argc, char const *argv[])
{
  printf("Hello param: %s\n",argv[1]);
  int size=0;
  char *filename;
  GArray *filearray;
  uint i=0;

  filearray=fileList(argv[1],&size);
  printf("%d\n", size);

  for (i = 0; i < size; ++i)
  {
    filename = g_array_index(filearray, FILENAME, i);
    printf("%s\n", filename);
  }
  indexing(filearray);


  return 0;
}