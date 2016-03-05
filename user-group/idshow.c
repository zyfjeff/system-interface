#define _GNU_SOURCE
#include <unistd.h>
#include <sys/fsuid.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "ugid_functions.h"


#define SG_SIZE (NGROUPS_MAX + 1)

int main(int argc,char *argv[])
{
    uid_t ruid,euid,suid,fsuid;
    gid_t rgid,egid,sgid,fsgid;
    gid_t suppGrpups[SG_SIZE];
    int numGroups,j;
    char *p;

    if(getresuid(&ruid,&euid,&suid) == -1) {
        perror("get uid information");
        exit(EXIT_FAILURE);
    }

    if(getresgid(&rgid,&egid,&sgid) == -1) {
        perror("get gid information");
        exit(EXIT_FAILURE);
    }

    fsuid = setfsuid(0);
    fsgid = setfsgid(0);
    printf("UID: ");
    p = user_name_formid(ruid);
    printf("real=%s (%ld); ",(p == NULL)?"???":p,(long)ruid);
    p = user_name_formid(euid);
    printf("eff=%s (%ld); ",(p == NULL)?"???":p,(long)euid);
    p = user_name_formid(suid);
    printf("save=%s (%ld); ",(p == NULL)?"???":p,(long)suid);

    p = user_name_formid(fsuid);
    printf("fs=%s (%ld); ",(p == NULL)?"???":p,(long)fsuid);
    printf("\n");

    printf("GID: ");
    p = group_name_fromid(rgid);
    printf("real=%s (%ld); ",(p == NULL)?"???":p,(long)rgid);
    p = group_name_fromid(egid);
    printf("eff=%s (%ld); ",(p == NULL)?"???":p,(long)egid);
    p = group_name_fromid(sgid);
    printf("saved=%s (%ld); ",(p == NULL)?"???":p,(long)sgid);
    p = group_name_fromid(fsgid);
    printf("fs=%s (%ld); ",(p == NULL)?"???":p,(long)fsgid);
    printf("\n");

    numGroups = getgroups(SG_SIZE,suppGrpups);
    if(numGroups == -1) {
        perror("getgroups:");
        exit(EXIT_FAILURE);
    }

    printf("Supplementary groups (%d): ",numGroups);
    for(j = 0; j < numGroups; j++ ) {
        p = group_name_fromid(suppGrpups[j]);
        printf("%s (%ld); ",(p == NULL)?"???":p,(long)suppGrpups[j]);
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}
