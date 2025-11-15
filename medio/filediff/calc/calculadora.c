#include <stdio.h>
#include <stdlib.h>
//implementacao de uma calculadora com ordem de precedencia *, + , - , /, (, ) 

typedef struct token{
    int num;
    char ope;
    int is_num;
    struct token* next; 
}token;

token* tokenize(char* line, size_t tamanho){
    token* head = NULL;
    token* tail = NULL;

    int i = 0;
    while(i < tamanho){
        char c = (char)line[i];
        if (c == ' ' || c == '\n' || c == '\r'){
            i++;
            continue;
        }

        token* new_token = malloc(sizeof(token));
        new_token->next = NULL;

        if (c>='0' && c<='9'){
            int n = c - '0';
            i++;
            while(i < tamanho && (char)line[i]>='0' && (char)line[i]<='9'){
                n = (n*10)+ ((char)line[i]-'0');
                i++;
            }
            new_token ->is_num = 1;
            new_token ->num = n;
        }
        else{
            new_token -> is_num = 0;
            new_token -> ope = c;
            i++;
        }

        if (!head){head = new_token;}
        else{tail->next = new_token;}
        tail = new_token;
    }
    return head;
};

int get_precedence(char c){
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '(' || c == ')') return -1;
}

token* revpolnot(token* tokens, size_t tamanho){
    token* current = tokens;
    char* op_stack = malloc(tamanho * sizeof(char));
    int op_stack_len = 0;

    token* head = NULL;
    token* tail = NULL;

    while (current != NULL){
        if(current->is_num == 1){
            token* new_token = malloc(sizeof(token));
            new_token->num = current->num;
            new_token->is_num = 1;
            new_token-> next = NULL;

            if(!head){head = new_token;}
            else{tail->next=new_token;}
            tail = new_token;
        }
        else if (get_precedence(current->ope) != -1){ // -1 indica que é ()
            int i = 0;
            int precedence = get_precedence(current->ope);

            while(op_stack_len>0){
                if(get_precedence(op_stack[op_stack_len-1]) >= precedence){
                    token* new_token = malloc(sizeof(token));
                    new_token->ope = op_stack[op_stack_len-1];
                    new_token->is_num = 0;
                    new_token-> next = NULL;

                    if(!head){head = new_token;}
                    else{tail->next=new_token;}
                    tail = new_token;

                    op_stack_len--;
                }
                else{
                    break;
                }
            }
            op_stack[op_stack_len++] = current->ope;

        }
        else if (current->ope == '('){
            op_stack[op_stack_len++] = current->ope;
        }
        else if (current->ope == ')'){
            while(op_stack_len>0 && op_stack[op_stack_len-1] != '('){
                token* new_token = malloc(sizeof(token));
                new_token->ope = op_stack[op_stack_len-1];
                new_token->is_num = 0;
                new_token-> next = NULL;

                if(!head){head = new_token;}
                else{tail->next=new_token;}
                tail = new_token;

                op_stack_len--;
            }
            op_stack_len--;
        }

        current = current->next;
    }
    while(op_stack_len>0){
        token* new_token = malloc(sizeof(token));
        new_token->ope = op_stack[op_stack_len-1];
        new_token->is_num = 0;
        new_token-> next = NULL;

        if(!head){head = new_token;}
        else{tail->next=new_token;}
        tail = new_token;

        op_stack_len--;
    }

    return head;
}

double eval(token* tokens, size_t tamanho){
    double* stack = malloc(tamanho* sizeof(double));
    int stack_len = 0;

    token* current = tokens;
    while(current!=NULL){
        if (current->is_num == 1){
            stack[stack_len++] = current->num;
        }
        else{
            double b = stack[--stack_len];
            double a = stack[--stack_len];
            if (current->ope == '+'){
                stack[stack_len++] = a+b;
            } 
            if (current->ope == '-'){
                stack[stack_len++] = a-b;
            } 
            if (current->ope == '*'){
                stack[stack_len++] = a*b;
            } 
            if (current->ope == '/'){
                stack[stack_len++] = a/b;
            } 
        }
        current = current->next;
    }
    return stack[0];
}

int main(){
    char* line = NULL;
    size_t l = 0;
    size_t tamanho = getline(&line, &l, stdin);


    token* tokens = tokenize(line, tamanho); // link list de tokens e tals
    token* tokens_processados = revpolnot(tokens, tamanho);

    while(tokens_processados!=NULL && 1 == 0){
        if(tokens_processados->is_num == 1){
            printf("%d ", tokens_processados->num);
        }
        else{
            printf("%c ",tokens_processados->ope);
        }

        tokens_processados = tokens_processados->next;
    }

    printf("%lf", eval(tokens_processados, tamanho));

    return 0;
}