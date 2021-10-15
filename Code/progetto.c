#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 1024
//Globali
typedef struct nodo{
    char *s; //1024
    struct nodo * next; //8
}nodo;

typedef struct saveNode{
    struct nodo * headList;
    struct nodo * start;
    struct nodo * oldCoda;
    struct nodo * last;
    struct saveNode * next;
    int numNodi;
    char c;
}saveNode;

typedef nodo * puntNodo;
typedef saveNode * puntSave;

puntSave undoPile, redoPile;
puntNodo savedLast,saveToUpdate,saveToUpdatePrec,nodoCoda;

int cont=1,flagUpdate=0,contUndoPile=0,contRedoPile = 0,flagFixSalvataggi=0;

char c;

//CAST
int castToInt(char s[],int * i,int castedValue){
    if(s[*i]>47&&s[*i]<58)                                      //Entro se numero
    {
        castedValue = (castedValue*10) + ((int)s[*i]) - 48;     //Trasformo in intero
        ++(*i);
        return castToInt(s,i,castedValue);
    }   
    return castedValue;                                         //Ritorno valore castato a intero
}
int castComandi(char s[],int  valComandi[]){
    int i=0;
    valComandi[0] = castToInt(s,&i,0);
    if(s[i]=='u'||s[i]=='r')
        return i;
    ++i;
    valComandi[1] = castToInt(s,&i,0);
    return i;
}

//UPDATELISTA
void updateLista(puntNodo start,puntNodo  n){
    flagUpdate = 1;
    undoPile->start = start;
    undoPile->headList = n;
    undoPile->numNodi = cont;
    undoPile->oldCoda = nodoCoda;
    contUndoPile++;
}
//INSERIMENTI
puntNodo inserimento(puntNodo n, char input[]){
    puntNodo new = (puntNodo) malloc(sizeof(nodo));
    n->s = (char *) malloc(1+strlen(input));
    strcpy(n->s,input);
    cont++;
    n->next = new;
    gets(input);
    if(strcmp(input,".")==0){ 
        n->next = NULL;
        free(new);
        return n;
    }
    inserimento(new,input);
} 
puntNodo modifica(puntNodo n, char input[],int valComandi[]){
    puntNodo temp = n;
    puntNodo newHead = n;
    puntNodo prec = temp;
    puntNodo new = (puntNodo) malloc(sizeof(nodo));
    int i;
    for(i=1;i<valComandi[0];i++){
        prec = temp;
        temp = temp->next;
    }
    saveToUpdatePrec = prec;
    saveToUpdate = temp;
    if(valComandi[0]==1)
        newHead = new;
    else 
        prec->next = new;
    while(strcmp(input,".")!=0&&temp!=NULL){ //TEMP POS !=0 MODIFICO!
        new->s = (char *) malloc(1+strlen(input));
        strcpy(new->s,input);
        puntNodo newNodo = (puntNodo) malloc(sizeof(nodo));
        newNodo->next = NULL;
        new->next = newNodo;
        gets(input);
        if(i==valComandi[1]){
            free(newNodo);
            new->next = temp->next;
        }
        else{
            new = new->next;
            if(temp->next==NULL)
                savedLast = temp;
            temp = temp->next;
        }
        i++;
    }
    if(strcmp(input,".")!=0)
        inserimento(new,input);
    return newHead;
}

//STAMPA
void stampaLista(puntNodo n,int valComandi[]){
    puntNodo temp = n;
    if(valComandi[0]==0&&valComandi[1]==0)
        printf(".\n");
    else{
        for(int i=1;i<valComandi[0]&&temp!=NULL;i++)
            temp = temp->next;
        int val = valComandi[1] -valComandi[0] + 1;
        for(int i=0;i<val;i++){
            if(temp!=NULL){
                printf("%s\n",temp->s); 
                temp = temp->next;
            }
            else 
                printf(".\n");
        }   
    }
}
puntNodo deleteNode(puntNodo n,puntNodo succ,int valComandi[]){
    puntNodo prec = n;
    puntNodo toBeDel = succ;
    for(int i=1;i<valComandi[0]-1&&prec!=NULL;i++){
        prec = prec->next;
    }
    //SALVATAGGI
    if(valComandi[0]==1){
        toBeDel = prec;
        updateLista(NULL,toBeDel);
    }
    else{
        toBeDel = prec->next;
        updateLista(prec,toBeDel);
    }
    //ELIMINAZIONI
    puntNodo newHead;
    if(valComandi[1]-valComandi[0]==0){
        prec->next = toBeDel->next;
        undoPile->last = toBeDel;
    }
    else 
        if(valComandi[1]-valComandi[0]>0){
            for(int i=valComandi[0];i<valComandi[1]&&toBeDel->next!=NULL;i++)
                toBeDel = toBeDel->next;
            undoPile->last = toBeDel;
            if(valComandi[0]!=1)
                prec->next = toBeDel->next;
            else{ //DELETE TESTA
                if(toBeDel==NULL)
                    newHead = NULL;
                else 
                    newHead = toBeDel->next;
                return newHead;
            }
        }
}
puntNodo fixPos(puntNodo n,bool checkHead){
    puntNodo temp = n;
    if(checkHead){
        cont = 1;
        while(temp!=NULL){
            cont++;
            if(temp->next==NULL)
                return temp;
            temp = temp->next;
        }
    }
}
void noSenseDelete(){
    flagUpdate = 1;
    undoPile->headList = NULL;
    contUndoPile++;
}
void fixSalvataggi(){ //Svuoto pila redo
    puntSave toFreePile;
    while(redoPile!=NULL){ 
        toFreePile = redoPile;
        redoPile = redoPile->next;
        free(toFreePile);
    }
    contRedoPile = 0;
}
int swapPunt(puntNodo coda,int numNodi){
    puntNodo tempCoda = nodoCoda;
    nodoCoda = coda;
    coda = tempCoda;
    int contCurr = cont;
    cont = numNodi;
    return contCurr;

}
puntNodo change(puntNodo head,puntSave pile){
    puntNodo saved = pile->headList; 
    puntNodo prec = pile->start;
    puntNodo swap;
    pile->numNodi = swapPunt(pile->oldCoda,pile->numNodi);
    if(prec==NULL){
        swap = head;
        head = saved;
    }
    else{
        swap = prec->next;
        prec->next = saved;
    }
    pile->headList = swap;
    return head;
}
puntNodo undoDelete(puntNodo head,puntSave pile){
    puntNodo saved = pile->headList; 
    puntNodo prec = pile->start;
    pile->numNodi = swapPunt(pile->oldCoda,pile->numNodi);
    if(saved!=NULL){ //REINSERISCO
        if(prec==NULL)
            head = saved;
        else 
            prec->next = saved;
    } 
    return head;
}
puntNodo redoDelete(puntNodo head,puntSave pile){
    puntNodo saved = pile->headList; 
    puntNodo prec = pile->start;
    puntNodo last = pile->last;
    pile->numNodi = swapPunt(pile->oldCoda,pile->numNodi);
    if(saved!=NULL){ //REINSERISCO
        if(prec==NULL){
            if(last!=NULL)
                head = last->next;
            else 
                head = NULL;
        }
        else{
            if(last!=NULL)
                prec->next = last->next;
            else 
                prec->next = NULL;
        }
    } 
    return head;
}
void fixRedoPiles(){
    puntSave temp = redoPile;
    redoPile = temp->next;
    if(undoPile->next!=NULL)
        temp->next = undoPile->next;
    else 
        temp->next = NULL;
    undoPile->next = temp;
    contRedoPile--;
    contUndoPile++;
}
void fixUndoPiles(){
    puntSave temp = undoPile->next;
    undoPile->next = temp->next;
    if(redoPile==NULL)
        temp->next = NULL;
    else 
        temp->next = redoPile;
    redoPile = temp;
    contRedoPile++;
    contUndoPile--;
}
puntNodo redo(int valCom,puntNodo head,bool flagStart){
    for(int i=0;i<valCom&&redoPile!=NULL;i++){
        if(redoPile->c=='c')
            head = change(head,redoPile);
        else
            head = redoDelete(head,redoPile);
        fixRedoPiles();
    }
    return head;
}
puntNodo undo(int valCom,puntNodo head){
    puntSave pile = undoPile->next;
    for(int i=0;i<valCom&&pile!=NULL;i++){
        if(pile->c=='c')
            head = change(head,pile);
        else 
            head = undoDelete(head,pile);
        fixUndoPiles();
        pile = undoPile->next;
    }
    return head;
}
int main(){
    char rigaInput[N];
    puntNodo head = NULL;      
    undoPile = (puntSave) malloc(sizeof(saveNode));
    undoPile->next = NULL;
    redoPile = NULL;
    nodoCoda = head;                      
    gets(rigaInput);                 
    while(strncmp(rigaInput,"q",1)!=0)                          
    {
        int valComandi[2];
        int contCom = castComandi(rigaInput,valComandi);
        c = rigaInput[contCom];
        if(rigaInput[contCom]=='c'){
            if(flagFixSalvataggi&&contRedoPile!=0)
                fixSalvataggi();
            gets(rigaInput);
            if(valComandi[0]==cont){   
                puntNodo oldHead = nodoCoda;
                puntNodo oldPrec = savedLast;
                if(head!=NULL){
                    nodoCoda->next = (puntNodo) malloc(sizeof(nodo));
                    nodoCoda = nodoCoda->next;
                }
                else{
                    head = (puntNodo) malloc(sizeof(nodo));
                    nodoCoda = head;
                }
                nodoCoda = inserimento(nodoCoda,rigaInput); 
                if(valComandi[0]==1)
                    updateLista(NULL,NULL); 
                else 
                    updateLista(oldPrec,NULL);   
            }      
            else{
                if(valComandi[0]==1){
                    head = modifica(head,rigaInput,valComandi);
                    updateLista(NULL,saveToUpdate);
                }
                else{
                    modifica(head,rigaInput,valComandi); 
                    updateLista(saveToUpdatePrec,saveToUpdate);
                }
                if(flagUpdate)
                    nodoCoda = fixPos(head,true);
            }                     
        }
        else{
            if(rigaInput[contCom]=='p'){
                    stampaLista(head,valComandi);
            }
            else{
                if(rigaInput[contCom]=='d'){
                    if(flagFixSalvataggi&&contRedoPile!=0)
                        fixSalvataggi();
                    if(head==NULL||valComandi[0]>=cont) //Delete senza senso lista gia vuota
                        noSenseDelete();
                    else{ //Delete con senso
                        if(valComandi[0]==1&&valComandi[0]==valComandi[1]){
                            puntNodo temp = head->next;
                            updateLista(NULL,head);
                            undoPile->last = head;
                            head = temp;
                        }
                        else{
                            if(valComandi[0]==1)
                                head = deleteNode(head,head->next,valComandi); 
                            else
                                deleteNode(head,head->next,valComandi);
                        }              
                        if(head!=NULL)
                            nodoCoda = fixPos(head,true);
                        else{
                            cont = 1;
                            nodoCoda = head;
                        }  
                    }
                }
                else{
                    if(rigaInput[contCom]=='r'&&contRedoPile!=0)
                        head = redo(valComandi[0],head,false);
                    else{ 
                        if(rigaInput[contCom]=='u'&&contUndoPile!=0){
                            flagFixSalvataggi = 1;
                            head = undo(valComandi[0],head);
                        }
                    }
                }
            }
        }
        if(flagUpdate){
            undoPile->c = c;
            puntSave newNodoUndoPile = (puntSave) malloc(sizeof(saveNode));
            newNodoUndoPile->next = undoPile;
            undoPile = newNodoUndoPile;
            flagUpdate = 0;
        }
        gets(rigaInput);  
    }  
    return 0;
}


