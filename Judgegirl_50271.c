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
bool find_previous(char target[], var_func var_funcs[], int var_funcs_sz){
    bool found = 0;
    for(int i = 0; i < var_funcs_sz && !found; i++){
        if(strncmp(target, var_funcs[i].name, 24) == 0){
            var_funcs[i].frequency++;
            found = 1;
        }
    }
    return found;
}
void add_new_name(char input[], int input_length, var_func var_funcs[], int *var_funcs_sz){
    if(input_length == 0 || !(isalpha(input[0]) || input[0] == '_'))return;
    if(is_reserved(input))return;
    if(!find_previous(input, var_funcs, *var_funcs_sz)){
        strncpy(var_funcs[*var_funcs_sz].name, input, 24);
        var_funcs[*var_funcs_sz].name[min(24, input_length)] = '\0';
        var_funcs[*var_funcs_sz].frequency = 1;
        (*var_funcs_sz)++;
    }
    return;
}
int main(){
    char inp[32], c;
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
            add_new_name(inp, inplen, var_funcs, &sz);
            inplen = 0;
        }
    }
    add_new_name(inp, inplen, var_funcs, &sz);
    inplen = 0;
    for(int i = 0; i < sz; i++)printf("%s %d\n", var_funcs[i].name, var_funcs[i].frequency);
    return 0;
}
