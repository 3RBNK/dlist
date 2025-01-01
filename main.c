#include <stdio.h>
#include <stdlib.h>

// Статусы ошибок
const short DListOk = 0;
const short DListEmpty = 1;
const short DListNotMem = 2;
const short DListPtrE = 3;
const short DListPtrB = 4;
short DListError;

// Типы данных
typedef int BaseType;
typedef struct element *elptr;

typedef struct element {
    BaseType data;
    elptr Llink;
    elptr Rlink;
} element;

typedef struct DList {
    elptr ptr; // Рабочий указатель
    elptr L; // Левый край списка
    elptr R; // Правый край списка
} DList;

// Интерфейс
void InitDList(DList *DL);

void PutPred(DList *DL, BaseType E);

void PutPost(DList *DL, BaseType E);

void GetPred(DList *DL, BaseType *E);

void GetPost(DList *DL, BaseType *E);

void DoneDList(DList *DL);

short EmptyDList(DList DL);

void MovePtrL(DList *DL);

void MovePtrR(DList *DL);

void PtrBegin(DList *DL);

void PtrEnd(DList *DL);

// Реализация
void InitDList(DList *DL) {
    DL->L = NULL;
    DL->ptr = NULL;
    DL->R = NULL;
}

void PutPred(DList *DL, BaseType E) {
    elptr new_element = (elptr) malloc(sizeof(element));
    if (new_element == NULL) {
        DListError = DListNotMem;
        return;
    }

    new_element->data = E;

    if (EmptyDList(*DL)) {
        new_element->Llink = NULL;
        new_element->Rlink = NULL;
        DL->L = new_element;
        DL->ptr = new_element;
        DL->R = new_element;
    } else {
        new_element->Rlink = DL->ptr;
        new_element->Llink = DL->ptr->Llink;

        if (DL->ptr->Llink != NULL) {
            DL->ptr->Llink->Rlink = new_element;
        } else {
            DL->L = new_element;
        }

        DL->ptr->Llink = new_element;
    }

    DListError = DListOk;
}

void PutPost(DList *DL, BaseType E) {
    elptr new_element = (elptr) malloc(sizeof(element));
    if (new_element == NULL) {
        DListError = DListNotMem;
        return;
    }

    new_element->data = E;

    if (EmptyDList(*DL)) {
        new_element->Llink = NULL;
        new_element->Rlink = NULL;
        DL->L = new_element;
        DL->ptr = new_element;
        DL->R = new_element;
    } else {
        new_element->Llink = DL->ptr;
        new_element->Rlink = DL->ptr->Rlink;

        if (DL->ptr->Rlink != NULL) {
            DL->ptr->Rlink->Llink = new_element;
        } else {
            DL->R = new_element;
        }

        DL->ptr->Rlink = new_element;
    }

    DListError = DListOk;
}

void GetPred(DList *DL, BaseType *E) {
    if (EmptyDList(*DL)) {
        DListError = DListEmpty;
        return;
    }

    if (DL->ptr->Llink == NULL) {
        // Если элемент один (или это первый элемент)
        *E = DL->ptr->data;
        free(DL->ptr);
        DL->L = NULL;
        DL->R = NULL;
        DL->ptr = NULL;
        DListError = DListPtrB;
        return;
    }

    *E = DL->ptr->Llink->data;
    elptr temp = DL->ptr->Llink;

    if (temp->Llink != NULL) {
        temp->Llink->Rlink = DL->ptr;
    } else {
        DL->L = DL->ptr;
    }
    DL->ptr->Llink = temp->Llink;

    free(temp);
    DListError = DListOk;
}

void GetPost(DList *DL, BaseType *E) {
    if (EmptyDList(*DL)) {
        DListError = DListEmpty;
        return;
    }

    if (DL->ptr->Rlink == NULL) {
        // Если элемент один (или это последний элемент)
        *E = DL->ptr->data;
        free(DL->ptr);
        DL->L = NULL;
        DL->R = NULL;
        DL->ptr = NULL;
        DListError = DListPtrE;
        return;
    }

    *E = DL->ptr->Rlink->data;
    elptr temp = DL->ptr->Rlink;

    if (temp->Rlink != NULL) {
        temp->Rlink->Llink = DL->ptr;
    } else {
        DL->R = DL->ptr;
    }
    DL->ptr->Rlink = temp->Rlink;

    free(temp);
    DListError = DListOk;
}


void DoneDList(DList *DL) {
    while (!EmptyDList(*DL)) {
        PtrBegin(DL);
        BaseType temp;
        GetPost(DL, &temp);
    }
    DListError = DListOk;
}

short EmptyDList(DList DL) {
    return DL.L == NULL;
}

void MovePtrL(DList *DL) {
    if (DL->ptr != NULL && DL->ptr->Llink != NULL) {
        DL->ptr = DL->ptr->Llink;
        DListError = DListOk;
    } else {
        DListError = DListPtrB;
    }
}

void MovePtrR(DList *DL) {
    if (DL->ptr != NULL && DL->ptr->Rlink != NULL) {
        DL->ptr = DL->ptr->Rlink;
        DListError = DListOk;
    } else {
        DListError = DListPtrE;
    }
}

void PtrBegin(DList *DL) {
    DL->ptr = DL->L;
    DListError = DListOk;
}

void PtrEnd(DList *DL) {
    DL->ptr = DL->R;
    DListError = DListOk;
}


void print_list(DList DL) {
    elptr temp = DL.ptr;
    PtrBegin(&DL);
    while (DL.ptr->Rlink != NULL && DL.ptr != NULL) {
        if (DL.ptr == temp) {
            printf("%dp <-> ", DL.ptr->data);
        } else {
            printf("%d <-> ", DL.ptr->data);
        }

        MovePtrR(&DL);
    }
    printf("%d\n", DL.ptr->data);
}


int main(void) {
    DList dl;
    InitDList(&dl);

    BaseType x1 = 1;
    BaseType x2 = 2;
    BaseType x3 = 3;
    BaseType x4 = 4;

    PutPost(&dl, x1);
    PutPost(&dl, x2);
    PutPost(&dl, x3);
    PutPost(&dl, x4);

    BaseType read;
    printf("gets 1: \n");
    while (!EmptyDList(dl)) {
        GetPost(&dl, &read);
        printf("get: %d\n", read);
    }
    printf("\n");

    PutPred(&dl, x1);
    PutPred(&dl, x2);
    PutPred(&dl, x3);
    PutPred(&dl, x4);

    printf("gets 2: \n");
    while (!EmptyDList(dl)) {
        GetPred(&dl, &read);
        printf("get: %d\n", read);
    }
    printf("\n");

    return 0;
}
