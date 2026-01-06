#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<libconfig.h>
#include"colorlib.h"
const char *repository;
int instl(int argc,char *argv[]){
    char yorn;
    if(argc < 3){
        printf("use lithium load <pkg>\n");
        return 0;
    }
    printf("Confirm download package(s)? [y/n]: ");
    scanf(" %c", &yorn);
    if(yorn == 'y'){
        for(int i=2; i<argc;i++){
            char ttyi[256];
            char chmd[256];
            printf(GREEN"lithium: installing %s\n"reset,argv[i]);
            snprintf(ttyi,sizeof(ttyi),"wget -q --directory=/bin/ %s%s",repository,argv[i]);
            snprintf(chmd,sizeof(chmd),"chmod +x /bin/%s\n",argv[i]);
            system(ttyi);
            system(chmd);
            return 0;
        }
    }
    if(yorn == 'n'){
        printf("Aborting.\n");
        return 0;
    }
}
int rmv(int argc,char *argv[]){
    char yorn;
    if(argc < 3){
        printf("use lithium kill <pkg>\n");
        return 0;
    }
    printf("Confirm remove package(s)? [y/n]: ");
    scanf(" %c", &yorn);
    if(yorn == 'y'){
        for(int i=2; i<argc;i++){
            char ttyr[256];
            printf(GREEN"lithium: removing %s\n"reset,argv[i]);
            snprintf(ttyr,sizeof(ttyr),"rm -rf /bin/%s",argv[i]);
            system(ttyr);
            return 0;
        }
    }
    if(yorn == 'n'){
        printf("Aborting.\n");
        return 0;
    }
}
int main(int argc,char *argv[]){
    config_t confg;
    config_init(&confg);
    config_read_file(&confg,"/etc/lithium.conf");
    config_lookup_string(&confg,"repo",&repository);
    if(argc < 2) {
        printf("lithium: use --help for documentation if use\n");
        return 0;
    }
    if(strcmp(argv[1],"--help")==0){
        printf("lithium.\n");
        printf("load: install package to /bin/ directory\n");
        printf("kill: remove package from /bin/ directory\n");
        return 0;
    }
    if(strcmp(argv[1],"load")==0){
        instl(argc,argv);
        return 0;
    }
    if(strcmp(argv[1],"kill")==0){
        rmv(argc,argv);
        return 0;
    }
    printf("lithium: argument %s not found\n",argv[1]);
}
