#include<stdio.h>
#include<string.h>
FILE *in;
char str[1005];
char symbol[1005],opglist[1005];
int sp=0,op=0;
char re[500][500];
void initre(){
    re['+']['+']=1,re['+']['*']=-1,re['+']['i']=-1,re['+']['(']=-1,re['+'][')']=1,re['+']['#']=1;
    re['*']['+']=1,re['*']['*']=1,re['*']['i']=-1,re['*']['(']=-1,re['*'][')']=1,re['*']['#']=1;
    re['i']['+']=1,re['i']['*']=1,re['i'][')']=1,re['i']['#']=1;
    re['(']['+']=-1,re['(']['*']=-1,re['(']['i']=-1,re['(']['(']=-1,re['('][')']=2;
    re[')']['+']=1,re[')']['*']=1,re[')'][')']=1,re[')']['#']=1;
    re['#']['+']=-1,re['#']['*']=-1,re['#']['i']=-1,re['#']['(']=-1;
    opglist[++op]='#';
    symbol[++sp]='#';
}
int checklr(){
    if(op>=4){
        if(opglist[op]==')'&&opglist[op-1]=='E'&&opglist[op-2]=='('){
            return 1;
        }
    }
    return 0;
}
int check(char c){
    if(op>=4){
        if(opglist[op]=='E'&&opglist[op-1]==c&&opglist[op-2]=='E'){
            return 1;
        }
    }
    return 0;
}
void push(char c){
    opglist[++op]=c;
    symbol[++sp]=c;
    return ;
}
int solve(char c){
    if(symbol[sp]=='i'){
        sp--;
        opglist[op]='E';
        printf("R\n");
        return 1;
    }
    if(symbol[sp]==')'){
        if(checklr()){
            sp-=2;
            op-=3;
            opglist[++op]='E';
            printf("R\n");
            return 1;
        }
        else {
            printf("RE\n");
            return 0;
        }
    }
    if(symbol[sp]=='+'){
        if(check('+')){
            sp-=1;
            op-=3;
            opglist[++op]='E';
            printf("R\n");
            return 1;
        }
        else {
            printf("RE\n");
            return 0;
        }
    }
    if(symbol[sp]=='*'){
        if(check('*')){
            sp-=1;
            op-=3;
            opglist[++op]='E';
            printf("R\n");
            return 1;
        }
        else {
            printf("RE\n");
            return 0;
        }
    }
    printf("RE\n");
    return 0;
}
int main(int argc, char* argv[]){
    initre();
    in=fopen(argv[1],"r");
    //in=fopen("test.in","r");
    fscanf(in,"%s",str);
    strcat(str,"#");
    int len=strlen(str);
    int i;
    for(i=0;i<len;i++){
        char c=str[i];
        //printf("c:%c sp:%d symbol:%c op:%d opglist:%c\n",c,sp,symbol[sp],op,opglist[op]);
        if(c=='#'&&i!=len-1){
            printf("E\n");
            return 0;
        }
        else if(c=='#'){
            if(symbol[sp]=='#')return 0;
        }
        int p=re[symbol[sp]][c];
        //printf("%d\n",p);
        switch (p){
            case 0:
                printf("E\n");
                return 0;
            case 1:
                if(!solve(c)){
                    return 0;
                }
                i--;
                break;
            case -1:
                push(c);
                printf("I%c\n",c);
                break;
            case 2:
                push(c);
                printf("I%c\n",c);
                if(!solve(c)){
                    return 0;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}
