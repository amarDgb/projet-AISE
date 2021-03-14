typedef struct buffer buffer;
struct buffer
{
  int tid;
  int ppid;
  char euser[50];
  unsigned priority;
  unsigned nice;
  unsigned long vm_size;
  char stat;
  int last;
  char cmd[500];
};
