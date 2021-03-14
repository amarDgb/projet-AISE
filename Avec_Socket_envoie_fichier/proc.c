
#include <stdio.h>
#include <string.h>
#include <proc/readproc.h>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char** argv)
{
 // fillarg used for cmdline
 // fillstat used for cmd
 PROCTAB* proc = openproc(PROC_FILLARG | PROC_FILLSTAT | PROC_FILLMEM | PROC_FILLSTATUS );

 proc_t proc_info;
  FILE* fichier = NULL;
 
    
   FILE* fichier1 = fopen("test2.txt","w+");

    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
   char arg ;
   size_t size = 0;
  while((arg = getc(cpuinfo)) != EOF)
        putc(arg, fichier1);
   fclose(cpuinfo);
  

 // zero out the allocated proc_info memory
 //while(1){
   fichier = fopen("test.txt", "w+");
 memset(&proc_info, 0, sizeof(proc_info));
    if (fichier != NULL)
    {
fprintf(fichier,"PID \t PPID       Etat \t  command \t NI \t PR \t VM_S \t CPU \n\n");
 while (readproc(proc, &proc_info) != NULL) {
 //printf("%-10d %-10d", proc_info.tid, proc_info.ppid);
  

  //printf("    %c \t", proc_info.state);
//fprintf(fichier,"%-10d %-10d     %c \t \n", proc_info.tid, proc_info.ppid,proc_info.state);
  if (proc_info.cmdline != NULL) {
   // print full cmd line if available
  //printf("%s\n", *proc_info.cmdline);
   fprintf(fichier,"%-10d %-10d     %c \t  %s \t  %ld \t  %ld \t  %lu \t %u \n", proc_info.tid, proc_info.ppid,proc_info.state,*proc_info.cmdline, proc_info.nice,proc_info.priority, proc_info.vm_size, proc_info.pcpu);
  } else {
   // if no cmd line use executable filename
 //printf(" \n", proc_info.cmd);
   fprintf(fichier,"%-10d %-10d     %c \t [%s] \t %ld \t  %ld \t  %lu \t %u \n", proc_info.tid, proc_info.ppid,proc_info.state,proc_info.cmd, proc_info.nice,proc_info.priority,proc_info.vm_size,proc_info.pcpu);
  }


}
    }// 
  fclose(fichier);
//   }
 

 closeproc(proc);

 return 0;
}







