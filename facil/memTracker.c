#include <stdio.h>
#include <stdlib.h>

//variaveis em c tem que ser completamente minusculas com _

//porraloca pra manter os alloc em mente
typedef struct Alloc{
    void* ptr;
    size_t size;
    struct Alloc* next;
}Alloc;
size_t global_heapmem_counter = 0;
size_t global_max_heapmem_counter = 0;
Alloc* head = NULL;

void new_alloc(void* ptr, size_t size){
    Alloc* node = malloc(sizeof(Alloc));
    node->ptr = ptr;
    node->size = size;
    node->next = head;
    head = node;
}
void remove_alloc(void* ptr){
    Alloc** current = &head;
    while(*current){
        if ((*current)->ptr == ptr){
            Alloc* bai = *current;
            *current = (*current)->next;
            free(bai);
            return;
        }
        current = &(*current)->next;
    }
}
size_t get_alloc_size(void* ptr){
    Alloc* node = head;
    while(node){
        if(node->ptr == ptr){
            return node->size;
        }
        node = node->next;
    }
    return 0;
}
void update_max(){
    if (global_heapmem_counter > global_max_heapmem_counter){
        global_max_heapmem_counter = global_heapmem_counter;
    }
    //printf("%d bytes current | %d maximum.\n", global_heapmem_counter, global_max_heapmem_counter);
}

//funcoes com trakck
void* track_malloc(size_t size){
    void* ptr = malloc(size);
    if (!ptr) return NULL;
    global_heapmem_counter += size;
    new_alloc(ptr, size);
    update_max();
    return ptr;
}

void* track_calloc(size_t members, size_t size){
    void* ptr = calloc(members, size);
    if (!ptr) return NULL;
    global_heapmem_counter += members*size;
    new_alloc(ptr, members*size);
    update_max();
    return ptr;
}

void* track_realloc(void* ptr, size_t size){
    size_t osize = ptr ? get_alloc_size(ptr) : 0;
    void* nptr = realloc(ptr, size);
    if (!nptr && size != 0) return NULL;

    if (ptr) remove_alloc(ptr);
    if (size == 0){
        global_heapmem_counter -= osize;
        return NULL;
    }

    if (size >= osize){
        global_heapmem_counter += size-osize;
    } 
    else{
        global_heapmem_counter -= osize-size;
    }   
    new_alloc(nptr, size);
    update_max();
    return nptr;
}

void track_free(void* ptr){
    global_heapmem_counter -= get_alloc_size(ptr);
    update_max();
    remove_alloc(ptr);
    free(ptr);
}

void show_heap_mem(){
    printf("%d bytes current | %d maximum.\n", global_heapmem_counter, global_max_heapmem_counter);
}

int main(){
    int* wow = NULL;
    for (int i = 0; i < 10; i++){
        void* sigma = track_malloc(10);
        if (i == 2){
            int* porraloca = track_calloc(10, sizeof(int));
            wow = porraloca;
        }
        if (i == 4){
            track_free(wow);
        }
        if (i == 5){
            track_realloc(sigma, 5);
        }
        if (i == 7){
            track_realloc(sigma, 15);
        }
    }
    show_heap_mem();
    return 0;
}