#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct element{
    char hodnota;
    struct element* dalsi;
}Telement;

typedef struct stack{
    Telement* top;
    int size;
}Tstack;

typedef struct queue{
    Telement* top;
    Telement* bot;
    int size;
}Tqueue;

//stack
char pop(Tstack *s){
    if(s->top == NULL) return NULL;
    s->size--;
    Telement* temp = s->top;
    s->top = temp->dalsi;
    char ret = temp->hodnota;
    free(temp);
    return ret;
}

void push(Tstack* s, char x){
    Telement* t = malloc(sizeof(Telement));
    if(t == NULL) return;
    s->size++;
    t->dalsi = NULL;
    t->hodnota = x;
    t->dalsi = s->top;
    s->top = t;
}

Tstack* vytvorStack(){
    Tstack* s = malloc(sizeof(Tstack));
    if(s == NULL) return NULL;
    s->size = 0;
    s->top = NULL;
    return s;
}

void smazStack(Tstack* s){
    while(pop(s) != NULL){}
    free(s);
}

//queue
void enqueue(Tqueue *q, char x){
    Telement* t = malloc(sizeof(Telement));
    if(t == NULL) return;
    q->size++;
    t->hodnota = x;
    t->dalsi = NULL;
    if(q->top == NULL) {
        q->top = t;
        q->bot = t;
        return;
    }
    q->bot->dalsi = t;
    q->bot = t;
}

char dequeue(Tqueue *q){
    if(q->top == NULL) return NULL;
    q->size--;
    Telement* temp = q->top;
    q->top = temp->dalsi;
    if(q->top == NULL) q->bot = NULL;
    char ret = temp->hodnota;
    free(temp);
    return ret;
}

Tqueue* vytvorQueue(){
    Tqueue* q = malloc(sizeof(Tqueue));
    if(q == NULL) return NULL;
    q->size = 0;
    q->top = NULL; q->bot = NULL;
    return q;
}

void smazQueue(Tqueue* q){
    while(dequeue(q) != NULL){}
    free(q);
}

// Otestuj pomocí nich, zda ve vstupním textu jsou správné počty správně
// uzavřených a vnořených závorek. Uvažuj kulaté (), hranaté [] a složené zá-
// vorky {}. Například tohle „{([])}“ je správně, tohle „{[(])}“ je špatně.
bool zavorky(char* vstup){
    Tstack* stack = vytvorStack();
    for(int i=0; vstup[i] != '\0'; i++){
        if(vstup[i] == '(' || vstup[i] == '[' || vstup[i] == '{') 
            push(stack, vstup[i]);
        else if(vstup[i] == ')' || vstup[i] == ']' || vstup[i] == '}') 
            if(vstup[i] - pop(stack) > 2){
                smazStack(stack);
                return false;
            } 
    }
    if(!stack->size){
        smazStack(stack);
        return true;
    }
    smazStack(stack);
    return false;
}

//Použij je pro vypsání posledních N znaků vstupu předem neznámé délky.
void poslednichN(char* vstup){
    Tqueue* queue = vytvorQueue();
    for(int i=0; vstup[i] != '\0'; i++){
        if(queue->size > 9) dequeue(queue);
        enqueue(queue, vstup[i]);
    }
    char c;
    while(1){
        c = dequeue(queue);
        if(c == 0) return;
        printf("%c", c);
    }
}

int main(){
    char retezec[] = "f(aw)f{a(w)awf}as[gaosias(u)]oiasudioasudoiajsiofa"; 
    // poslednichN(&retezec);
    return 0;
}