#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


char* key[7]={"BEGIN","END","FOR","DO","IF","THEN","ELSE"};
char symbol[7]={':' , '+' , '*' , ',' , '(' , ')' , '='};
char* kout[8]={"","Begin","End","For","Do","If","Then","Else"};
char* sout[7]={"Colon","Plus","Star","Comma","LParenthesis","RParenthesis","Assign"};
 
int reserve(char* t){   //看看是第几个 
    for(int i=0; i<7; i++){
        if(strcmp(key[i],t)==0) return i+1;
    }
    return 0;
}

int main(int argc,char* argv[]){
    char ch;
    char token[1000];
    int flag; 

    char *fname=argv[1];
    FILE *in;
    in=fopen(fname,"r");

    ch = fgetc(in);
    while(ch != EOF){  //只要没有读到最后 
       
        if(isspace(ch)){  //空格就一直读 
            ch = fgetc(in) ;
            continue;
        }

        memset(token,'\0',sizeof(token));
        flag = 0;

        if(isalpha(ch)){  //如果是字符 
            flag = 1;
            while( ch!=EOF && (isalpha(ch) || isdigit(ch)) ){  //获取单词长度 
                int length = strlen(token);
                token[length] = ch;
                ch = fgetc(in);
            }
            int i = reserve(token);
            if(i > 0) printf("%s\n",kout[i]);
            else printf("Ident(%s)\n",token);
        }
        else if(isdigit(ch)){  //如果是数字 
            flag = 1;
            while(isdigit(ch)){
                int len = strlen(token);
                token[len] = ch;
                ch = fgetc(in);
            }
            printf("Int(%d)\n",atoi(token));
        }
        else{
            //printf("other\n");
            for(int i = 1;i <= 5; i++){  //如果是某一个符号  
                if(ch == symbol[i]){
                    flag = 1;
                    printf("%s\n",sout[i]);
                    break;
                }
            }
            if(ch == symbol[0]){
                flag = 1;
                char tmp;
                tmp = fgetc(in);
                if(tmp == symbol[6]){   //:=
                    printf("%s\n",sout[6]);
                }
                else{
                    fseek(in,-1,SEEK_CUR);  //就返回一位 
                    printf("%s\n",sout[0]);
                }
            }
            ch = fgetc(in);
        }
        if(flag == 0){
            printf("Unknown\n");
            break;
        }
    }
	return 0;
}
