#include <stdio.h>


int main(int argc,char *argv[]){
    int ages[] = {12,23,45,56,68,88};
    char *names[] = {"Car","Aien","Marry","Jonh","Lisa","Jack"};


    int count = sizeof(ages)/sizeof(int);

    for(int i=0;i<count;i++){
        printf("%s has %d years alive.\n",
            names[i], ages[i]);
    }
    printf("-------------------------\n");

    int *cur_age = ages;
    char **cur_name = names;

    for(int i=0;i<count;i++){
        printf("%s has %d years alive.\n",
            *(cur_name+i),*(cur_age+i));
    }
    printf("-------------------------\n");

    for(int i=0;i<count;i++){
        printf("%s has %d years alive.\n",
            cur_name[i],cur_age[i]);
    }
    printf("-------------------------\n");

    for(cur_age = ages,cur_name = names;cur_age - ages < count;cur_age++,cur_name++){
        printf("%s has %d years alive.\n",
            *cur_name,*cur_age);
    }
    printf("-------------------------\n");

    return 0;
}