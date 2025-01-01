#include <stdio.h>
#include <stdlib.h>


const short DListOk = 0;
const short DListEmpty = 1;
const short DListNotMem = 2;
const short DListPtrE = 3;
const short DListPtrB = 4;
short DListError;

typedef int BaseType;
typedef struct element *elptr;

typedef struct element {
    BaseType data;
    elptr Llink;
    elptr Rlink;
} element ;

typedef struct DList {
    elptr ptr;
    elptr L;
    elptr R;
} DList ;


// интерфейс
void InitDList(DList *DL);

void PutPred(DList *DL, BaseType E);
void PutPost(DList *DL, BaseType E);

void GetPred(DList *DL, BaseType *E);
void GetPost(DList *DL, BaseType *E);

void DoneDList(DList *DL);
short EmptyDList(DList DL);

void MovePtrL(DList *DL);
void MovePtrR(DList *DL);

void PtrEnd(DList *DL);
void PtrBegin(DList *DL);


// реализация
void InitDList(DList *DL) {
    DL->L = NULL;
    DL->ptr = NULL;
    DL->R = NULL;
}


void PutPred(DList *DL, BaseType E) {
    const elptr new_element = (elptr) malloc(sizeof(element));
    if (new_element == NULL) {
        DListError = DListNotMem;
        return;
    }

    new_element->data = E;

    if (EmptyDList(*DL)) {
        new_element->Llink = DL;
        new_element->Rlink = NULL;
        DL->L = new_element;
        DL->ptr = new_element;
        DL->R = new_element;
    } else {
        if (DL->ptr == DL->L) {
            new_element->Rlink = DL->ptr;
            new_element->Llink = DL;
            DL->ptr->Llink = new_element;
            DL->R = new_element;
        } else {
            new_element->Rlink = DL->ptr;
            new_element->Llink = DL->ptr->Llink;
            DL->ptr->Llink->Rlink = new_element;
            DL->ptr->Llink = new_element;
        }
    }

    DListError = DListOk;
}


void PutPost(DList *DL, BaseType E) {
    const elptr new_element = (elptr) malloc(sizeof(element));
    if (new_element == NULL) {
        DListError = DListNotMem;
        return;
    }

    new_element->data = E;

    if (EmptyDList(*DL)) {
        new_element->Llink = DL;
        new_element->Rlink = NULL;
        DL->L = new_element;
        DL->ptr = new_element;
        DL->R = new_element;
    } else {
        if (DL->L == DL->ptr) {
            new_element->Llink = DL->ptr;
            new_element->Rlink = NULL;
            DL->L = new_element;
            DL->ptr->Rlink = new_element;
        } else {
            new_element->Llink = DL->ptr;
            new_element->Rlink = DL->ptr->Rlink;
            DL->ptr->Rlink->Llink = new_element;
            DL->ptr->Rlink = new_element;
        }
    }

    DListError = DListOk;
}


void GetPred(DList *DL, BaseType *E) {
    if (!EmptyDList(*DL)) {
        if (DL->L == DL->ptr) {
            *E = DL->ptr->data;
            free(DL->ptr);
            DL->L = NULL;
            DL->ptr = NULL;
            DL->R = NULL;
        } else {
            *E = DL->ptr->Llink->data;
            elptr temp = DL->ptr->Llink;
            DL->ptr->Llink->Llink->Rlink = DL->ptr;
            DL->ptr->Llink = DL->ptr->Llink->Llink;
            free(temp);
        }
        DListError = DListOk;
    } else {
        DListError = DListEmpty;
    }
}


void GetPost(DList *DL, BaseType *E) {
    if (!EmptyDList(*DL)) {
        if (DL->L == DL->ptr) {
            *E = DL->ptr->data;
            free(DL->ptr);
            DL->L = NULL;
            DL->ptr = NULL;
            DL->R = NULL;
        } else {
            *E = DL->ptr->Rlink->data;
            elptr temp = DL->ptr->Rlink;
            DL->ptr->Rlink->Rlink->Llink = DL->ptr;
            DL->ptr->Rlink = DL->ptr->Rlink->Rlink;
            free(temp);
        }
    } else {
        DListError = DListEmpty;
    }
}


void DoneDList(DList *DL) {
    PtrBegin(DL);
    while (DL->ptr->Rlink != NULL) {
        elptr temp = DL->ptr;
        MovePtrR(DL);
        free(temp);
    }
}


short EmptyDList(DList DL);



int main(void) {
    return 0;
}
