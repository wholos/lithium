#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<libconfig.h>
#include"colorlib.h"
const char *dir;
const char *repository;
const char *logotype=R"(
| (_) |_| |_ (_)_  _ _ __  
| | |  _| ' \| | || | '  \ 
|_|_|\__|_||_|_|\_,_|_|_|_|
)";
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
            snprintf(ttyi,sizeof(ttyi),"wget -q --directory=%s %s%s",dir,repository,argv[i]);
            snprintf(chmd,sizeof(chmd),"chmod +x %s%s\n",dir,argv[i]);
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
            snprintf(ttyr,sizeof(ttyr),"rm -rf %s%s",dir,argv[i]);
            system(ttyr);
            return 0;
        }
    }
    if(yorn == 'n'){
        printf("Aborting.\n");
        return 0;
    }
}
int upd(int argc, char *argv[]){
    char yorn;
    printf("Confirm update packages? [y/n] ");
    scanf(" %c", &yorn);
    if(yorn == 'y'){
        printf(GREEN"lithium: updating package manager\n"reset);
        system("rm /bin/lithium");
        sleep(1);
        system("wget -q --directory=/bin/ https://raw.githubusercontent.com/wholos/LithiumPackages/main/lithium/lithium");
        sleep(1);
        system("chmod +x /bin/lithium");
        return 0;
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
    config_lookup_string(&confg,"dir",&dir);
    if(argc < 2) {
        printf("lithium: use --help for documentation if use\n");
        return 0;
    }
    if(strcmp(argv[1],"--help")==0){
        printf("lithium.\n");
        printf("version: print version lithium package manager (--version)\n");
        printf("load: install package to /bin/ directory\n");
        printf("kill: remove package from /bin/ directory\n");
        printf("upd: update packages from /bin/ directory\n");
        return 0;
    }
    if(strcmp(argv[1],"--version")==0){
        printf(BLUE"LITHIUM"reset);
        printf(logotype);
        printf("lithium version - 0.3\n");
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
    if(strcmp(argv[1],"upd")==0){
        upd(argc,argv);
        return 0;
    }
    printf("lithium: argument %s not found\n",argv[1]);
}
