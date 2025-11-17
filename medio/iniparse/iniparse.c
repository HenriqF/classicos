#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char* key; 
    char* value;
} KeyValue;

typedef struct{
    char* name;
    KeyValue* pairs;
    int pairs_count;
} Section;

typedef struct{
    Section* sections;
    int sections_count;
} Config;

char* config_file;
size_t size;
void readFile(){
    FILE* f = fopen("config.ini", "rb");
    if (f == NULL){
        printf("Deu merda");
        return;
    }
    else{
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        config_file = malloc(size+1);
        if (config_file){
            size = fread(config_file, 1, size, f);
            config_file[size] = '\0';
        }
        fclose(f);
    }
}

int getLineType(int* i){ //i = index inicio da linha, 0 = section, 1 = keyvalue, 2 = ignore.
    int j = *i;
    int nextLineIndex = size;
    int hasEqual = 0;

    while(j++ < size){
        if (config_file[j] == '=') hasEqual = 1;
        if (config_file[j] == '\n'){
            nextLineIndex = j+1;
            j--;
            if (config_file[j] == '\r'){
                j--;
            } 
            break;
        }
    }
    
    if (config_file[*i] == '[' && config_file[j] == ']'){
        *i = nextLineIndex;
        return 0;
    }
    *i = nextLineIndex;
    if (hasEqual == 1){
        return 1;
    }
    return 2;

}

int main(){
    readFile();
    Config* config = NULL;

    int index = 0;
    int start_index = 0;
    while (index < size){
        start_index = index;
        int type = getLineType(&index);
    }

    return 0;
}