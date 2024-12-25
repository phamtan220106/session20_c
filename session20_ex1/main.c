#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BOOK {
    int maSach;
    char nameBook[20];
    char nameAuthor[30];
    int price;
} BOOK;
void search(BOOK *listB,int *length);
void swap(BOOK *a, BOOK *b);
void softT(BOOK *listB, int *length);
void softG(BOOK *listB, int *length);
void MENU();
void Initialization(BOOK *listB, int *length);
void printListB(BOOK *listB, int *length);
void addBook(BOOK *listB, int *length);
void deleteListB(BOOK *listB, int *length);
void update(BOOK *listB, int *length);

int main() {
    int options;
    int length;
    char AorB;
    BOOK *listB = (BOOK *)calloc(length, sizeof(BOOK));
    if (listB == NULL) {
        printf("khong du bo nho.\n");
        return -1;
    }
    while (1) {
        MENU();
        scanf("%d", &options);
        getchar();
        switch (options) {
            case 1:
                printf("\n");
                Initialization(listB, &length);
                saveBooksToFile(listB, &length);
                break;
            case 2:
                printf("\n");
                printListB(listB, &length);
                loadBooksFromFile(listB,&length);
                break;
            case 3:
                printf("\n");
                addBook(listB,&length);
                saveBooksToFile(listB, &length);
                break;
            case 4:
                printf("\n");
                deleteListB(listB,&length);
                saveBooksToFile(listB, &length);
                break;
            case 5:
                printf("\n");
                update(listB,&length);
                saveBooksToFile(listB, &length);
                break;
            case 6:
                printf("\n");
                printf("a. Sap xep tang dan theo price.\n");
                printf("b. Sap xep giam dan theo price.\n");
                printf("Lua chon cua ban: ");
                scanf("%c", &AorB);
                if (AorB == 'a'){
                    printf("\n");
                    softT(listB, &length);
                }
                else if (AorB == 'b'){
                    printf("\n");
                    softG(listB, &length);
                }
                else printf("Khong hop le\n");
                saveBooksToFile(listB, &length);
                break;
            case 7:
                printf("\n");
                search(listB, &length);
                break;
            case 8:
                free(listB);
                return 0;
            default:
                printf("ko hop le.\n");
                break;
        }
    }
    printf("Hello world!\n");
    return 0;
}
void search(BOOK *listB,int *length){
    printf("nhap ten sach muon tim kiem. ");
    char x[30];
    fgets(x,sizeof(x),stdin);
    x[strcspn(x,"\n")]='\0';
    for(int i=0; i<*length; i++){
        if(strcmp(listB[i].nameBook,x)==0){
            printf("mon ban can tim la:\n");
            printf("/%d: %s t/g: %s : %dvnd.\n",listB[i].maSach,listB[i].nameBook,listB[i].nameAuthor,listB[i].price);
            break;
        }
    }
    printf("ko ton tai sach.\n");
}
void softT(BOOK *listB, int *length) {
    for (int i = 0; i < *length - 1; i++) {
        for (int j = 0; j < *length - 1 - i; j++) {
            if (listB[j].price > listB[j + 1].price){
                swap(&listB[j], &listB[j + 1]);
            }
        }
    }
}
void softG(BOOK *listB, int *length) {
    for (int i = 0; i < *length - 1; i++) {
        for (int j = 0; j < *length - 1 - i; j++) {
            if (listB[j].price < listB[j + 1].price){
                swap(&listB[j], &listB[j + 1]);
            }
        }
    }
}
void swap(BOOK *a, BOOK *b) {
    BOOK temp = *a;
    *a = *b;
    *b = temp;
}
void update(BOOK *listB, int *length){
    printf("nhap ma sach ban muon sua: ");
    int masach;
    scanf("%d",&masach);
    if(masach>=1 && masach<=length){
        for(int i=0;i<*length; i++){
            if(listB[i].maSach==masach){
                printf("thong tin moi:\n");
                printf("ten sach: ");
                fgets(listB[i].nameBook, sizeof(listB[i].nameBook), stdin);
                listB[i].nameBook[strcspn(listB[i].nameBook, "\n")] = '\0';
                printf("ten tac gia: ");
                fgets(listB[i].nameAuthor, sizeof(listB[i].nameAuthor), stdin);
                listB[i].nameAuthor[strcspn(listB[i].nameAuthor, "\n")] = '\0';
                printf("gia tien: ");
                scanf("%d", &listB[i].price);
                getchar();
            }
        }
    }else{
        printf("khong hop le.\n");
    }
}
void deleteListB(BOOK *listB, int *length){
    printf("nhap vi tri muon xoa: ");
    int index;
    scanf("%d",&index);
    if(index>=1 && index<=length){
        for(int i=index-1; i<*length-1; i++){
            listB[i]=listB[i+1];
        }
        (*length)--;
    }else{
        printf("khong hop le.\n");
    }
}
void MENU() {
    printf("\n");
    printf("options.\n");
    printf("1. nhap so luong va thong tin sach.\n");
    printf("2. hien thi thong tin sach.\n");
    printf("3. them sach vao vi tri.\n");
    printf("4. xoa sach theo ma sach.\n");
    printf("5. cap nhat thong tin sach theo ma sach.\n");
    printf("6. sap xep sach theo gia.\n");
    printf("7. tim kiem sach theo ten sach.\n");
    printf("8. thoat.\n");
    printf("lua chon cua ban: ");
}
void Initialization(BOOK *listB, int *length) {
    printf("nhap vao so luong sach: ");
    scanf("%d",length);
    BOOK *temp=realloc(listB,(*length)*sizeof(BOOK));
    if (temp==NULL) {
        printf("khong du bo nho.\n");
        free(listB);
        listB=NULL;
        *length=0;
        return;
    }
    listB=temp;
    for(int i = 0; i < *length; i++) {
        printf("ma sach: ");
        scanf("%d", &listB[i].maSach);
        getchar();
        printf("ten sach: ");
        fgets(listB[i].nameBook, sizeof(listB[i].nameBook), stdin);
        listB[i].nameBook[strcspn(listB[i].nameBook, "\n")] = '\0';
        printf("ten tac gia: ");
        fgets(listB[i].nameAuthor, sizeof(listB[i].nameAuthor), stdin);
        listB[i].nameAuthor[strcspn(listB[i].nameAuthor, "\n")] = '\0';
        printf("gia tien: ");
        scanf("%d", &listB[i].price);
        getchar();
    }
}
void printListB(BOOK *listB, int *length){
        for(int i=0; i<*length; i++){
            printf("/%d: %s t/g: %s : %dvnd.\n",listB[i].maSach,listB[i].nameBook,listB[i].nameAuthor,listB[i].price);
        }
}
void addBook(BOOK *listB, int *length){
    printf("nhap vi tri muon them: ");
    int index,x;
    scanf("%d",&x);
    index=x-1;
    if(x>=1 && x<=length){
        for(int i=*length; i>=x-1; i--){
            listB[i]=listB[i-1];
        }
        printf("nhap thong tin sach.\n");
        printf("ma sach: ");
        scanf("%d", &listB[index].maSach);
        getchar();
        printf("ten sach: ");
        fgets(listB[index].nameBook, sizeof(listB[index].nameBook), stdin);
        listB[index].nameBook[strcspn(listB[index].nameBook, "\n")] = '\0';
        printf("ten tac gia: ");
        fgets(listB[index].nameAuthor, sizeof(listB[index].nameAuthor), stdin);
        listB[index].nameAuthor[strcspn(listB[index].nameAuthor, "\n")] = '\0';
        printf("gia tien: ");
        scanf("%d", &listB[index].price);
        getchar();
        (*length)++;
    }else{
        printf("khong hop le.\n");
    }
}
void saveBooksToFile(BOOK *listB, int *length) {
    // mở file
    FILE *fptr=fopen("BOOK.dat","ab");
    if(fptr==NULL){
        printf(" file ko ton tai.\n");
        return;
    }
    //thao tác file
    fwrite(listB,sizeof(BOOK),length,fptr);// lưu dữ liệu vào trong file
    printf("luu du lieu thanh cong.\n");
    //đóng file
    fclose(fptr);
}
void loadBooksFromFile(BOOK *listB, int *length) {
    FILE *fptr=fopen("BOOK.dat","rb");
    if(fptr==NULL){
        printf(" file ko ton tai.\n");
        return;
    }
    BOOK savebook[*length];
    *length=fread(savebook,sizeof(BOOK),*length,fptr);
    for(int i=0; i<*length; i++){
        printf("/%d: %s t/g: %s : %dvnd.\n",listB[i].maSach,listB[i].nameBook,listB[i].nameAuthor,listB[i].price);
    }
    printf("lay thong tin thanh cong.\n");
    fclose(fptr);
}
