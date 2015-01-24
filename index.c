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

  DIR *directory;
  struct dirent *fileList;
  directory = opendir(dir);
  if (directory){
    while ((fileList = readdir(directory)) != NULL)
    {
      char *filename=fileList->d_name;
      if(g_strcmp0(filename,".")!=0&&g_strcmp0(filename,"..")!=0){

        //printf("%s\n", filename);
        filename=g_strconcat(dir,filename,NULL);
        g_array_append_val (garray,filename);
        //item = g_string_new(filename);
        (*count)++;
      }
    }
    closedir(directory);
  }
  return garray;
}

void indexing(GArray *array,int count){
  printf("=====\nInverted indexing\n");
  gchar *filename=NULL;
  gchar *contents=NULL;
  gsize *length=NULL;
  GError *error=NULL;
  int i=0;
  for(i=0;i<count;i++){
    filename = g_array_index(array, FILENAME, i);
    printf("%s\n", filename);
    int f = g_file_get_contents (filename,&contents,length,&error);
    printf("%s\n",contents );
    if(!f){
      printf("%s\n",error->message );
    }
    //free memory of file that was indexed
  }

}

int main(int argc, char const *argv[])
{
  printf("Hello param: %s\n",argv[1]);
  int count=0;
  char *filename;
  GArray *filearray;
  int i=0;

  filearray=fileList(argv[1],&count);
  printf("%d\n", count);

  for (i = 0; i < count; ++i)
  {
    filename = g_array_index(filearray, FILENAME, i);
    printf("%s\n", filename);
  }
  indexing(filearray,count);


  return 0;
}