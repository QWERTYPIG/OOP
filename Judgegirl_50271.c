#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
int min(int a, int b){
    return a < b ? a : b;
}
int main(){
    char name[30][32], inp[32], c, res[12][8] = {"if", "else", "while", "for", "switch", "case", "break", "return", "void", "int", "float", "char"};
    int cnt[30], namelen[30], sz = 0, inplen = 0;
    for(int i = 0; i < 30; i++)cnt[i] = 0;
    while(scanf("%c", &c) != EOF){
        if(isalnum(c) || c == '_'){
            inp[inplen] = c;
            inplen++;
            inp[inplen] = '\0';
        }
        else{
            if(inplen != 0 && (isalpha(inp[0]) || inp[0] == '_')){
                bool reserved = 0;
                for(int i = 0; i < 12; i++){
                    if(strcmp(res[i], inp) == 0){
                        inplen = 0;
                        reserved = 1;
                        break;
                    }
                }
                if(reserved)continue;
                bool found = 0;
                for(int i = 0; i < sz && !found; i++){
                    if(strncmp(inp, name[i], 24) == 0){
                        cnt[i]++;
                        found = 1;
                        inplen = 0;
                    }
                }
                if(!found){
                    strncpy(name[sz], inp, 24);
                    name[sz][min(24, inplen)] = '\0';
                    cnt[sz] = 1;
                    namelen[sz] = min(24, inplen);
                    sz++;
                    inplen = 0;
                }
            }
            inplen = 0;
        }
    }
    if(inplen != 0 && (isalpha(inp[0]) || inp[0] == '_')){
        bool reserved = 0;
        for(int i = 0; i < 12; i++){
            if(strcmp(res[i], inp) == 0){
                inplen = 0;
                reserved = 1;
                break;
            }
        }
        bool found = reserved;
        for(int i = 0; i < sz && !found; i++){
            if(strncmp(inp, name[i], 24) == 0){
                cnt[i]++;
                found = 1;
                inplen = 0;
            }
        }
        if(!found){
            strncpy(name[sz], inp, 24);
            name[sz][min(24, inplen)] = '\0';
            cnt[sz] = 1;
            namelen[sz] = min(24, inplen);
            sz++;
            inplen = 0;
        }
    }
    for(int i = 0; i < sz; i++)printf("%s %d\n", name[i], cnt[i]);
    return 0;
}
