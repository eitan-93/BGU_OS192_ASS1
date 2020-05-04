#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc <= 1){
    printf(1, "policy: please select a policy\n");
    exit(0);
  }
  if(*argv[1] == '1' || *argv[1] == '2' || *argv[1] == '3')
    policy(atoi(argv[1]));
  else
    printf(1, "policy: please select a legal policy\n");
  exit(0);
}
