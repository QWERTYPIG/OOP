#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
int min(int a, int b){
    return a < b ? a : b;
}
typedef struct var_func{
    char name[32];
    int frequency;
}var_func;
var_func new_var_func(){
    var_func ans;
    ans.name[0] = '\0';
    ans.frequency = 0;
    return ans;
}
bool is_reserved(char target[]){
    char res[12][8] = {"if", "else", "while", "for", "switch", "case", "break", "return", "void", "int", "float", "char"};
    bool found = 0;
    for(int i = 0; i < 12 && !found; i++){
        if(strcmp(target, res[i]) == 0)found = 1;
    }
    return found;
}
bool find_previous(char target[], var_func var_funcs[], int var_func_sz){
    bool found = 0;
    for(int i = 0; i < var_func_sz && !found; i++){
        if(strncmp(target, var_funcs[i].name, 24) == 0){
            var_funcs[i].frequency++;
            found = 1;
        }
    }
    return found;
}
int main(){
    char inp[32], c, res[12][8] = {"if", "else", "while", "for", "switch", "case", "break", "return", "void", "int", "float", "char"};
    int sz = 0, inplen = 0;
    var_func var_funcs[30];
    for(int i = 0; i < 30; i++)var_funcs[i] = new_var_func();
    while(scanf("%c", &c) != EOF){
        if(isalnum(c) || c == '_'){
            inp[inplen] = c;
            inplen++;
            inp[inplen] = '\0';
        }
        else{
            if(inplen != 0 && (isalpha(inp[0]) || inp[0] == '_')){
                if(is_reserved(inp)){
                    inplen = 0;
                    continue;
                }
                if(!find_previous(inp, var_funcs, sz)){
                    strncpy(var_funcs[sz].name, inp, 24);
                    var_funcs[sz].name[min(24, inplen)] = '\0';
                    var_funcs[sz].frequency = 1;
                    sz++;
                }
            }
            inplen = 0;
        }
    }
    if(inplen != 0 && (isalpha(inp[0]) || inp[0] == '_')){
        bool found = is_reserved(inp);
        if(!found)found = find_previous(inp, var_funcs, sz);
        if(!found){
            strncpy(var_funcs[sz].name, inp, 24);
            var_funcs[sz].name[min(24, inplen)] = '\0';
            var_funcs[sz].frequency = 1;
            sz++;
        }
        inplen = 0;
    }
    for(int i = 0; i < sz; i++)printf("%s %d\n", var_funcs[i].name, var_funcs[i].frequency);
    return 0;
}
