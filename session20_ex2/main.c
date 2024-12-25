#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Merchandise{
    int id;
    char name[30];
    int inputPrice;
    int outputPtice;
    int amount;
}Merchandise;
int income=100;
void PrintlistM(Merchandise *listM, int *length);
void MENU();
void Initialization(Merchandise *listM, int *length);
void productImport(Merchandise *listM, int *length);
void update(Merchandise *listM, int *length);
void softT(Merchandise *listM, int *length);
void softG(Merchandise *listM, int *length);
void swap(Merchandise *a, Merchandise *b);
void search(Merchandise *listM,int *length);
void deleteListM(Merchandise *listM,int index,int *length);
void sellListM(Merchandise *listM, int *length);

int main(){
    int length=0;
    int options;
    char AorB;
    Merchandise *listM=(Merchandise *)calloc(length,sizeof(Merchandise));
    if(listM == NULL){
        printf("khong du bo nho.\n");
        return -1;
    }
    while(1){
        MENU();
        scanf("%d",&options);
        switch(options){
            case 1:
                printf("\n");
                Initialization(listM,&length);
                saveToFile(listM, length, "products.dat");
                break;
            case 2:
                printf("\n");
                loadFromFile(&listM, &length, "products.dat");
                PrintlistM(listM,&length);
                break;
            case 3:
                printf("\n");
                productImport(listM,&length);
                saveToFile(listM, length, "products.dat");
                break;
            case 4:
                printf("\n");
                update(listM,&length);
                saveToFile(listM, length, "products.dat");
                break;
            case 5:
                printf("\n");
                printf("a. Sap xep tang dan theo price.\n");
                printf("b. Sap xep giam dan theo price.\n");
                printf("Lua chon cua ban: ");
                scanf("%c", &AorB);
                if (AorB == 'a'){
                    printf("\n");
                    softT(listM, &length);
                }
                else if (AorB == 'b'){
                    printf("\n");
                    softG(listM, &length);
                }
                else printf("Khong hop le\n");
                saveToFile(listM, length, "products.dat");
                break;
            case 6:
                printf("\n");
                search(listM,&length);
                break;
            case 7:
                printf("\n");
                sellListM(listM,&length);
                saveToFile(listM, length, "products.dat");
                break;
            case 8:
                printf("\n");
                printf("doanh thu hienj tại : %d.\n",income);
                break;
            case 9:
                return 0;
            default:
                printf("khong hop le.\n");
                break;
        }
    }
    return 0;
}
void saveToFile(Merchandise *listM, int length, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Khong the mo tep de ghi.\n");
        return;
    }
    fwrite(&length, sizeof(int), 1, file); // Ghi số lượng sản phẩm
    fwrite(listM, sizeof(Merchandise), length, file); // Ghi danh sách sản phẩm
    fclose(file);
    printf("Da luu danh sach vao tep '%s'.\n", filename);
}

void loadFromFile(Merchandise **listM, int *length, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Khong the mo tep de doc.\n");
        return;
    }
    fread(length, sizeof(int), 1, file); // Đọc số lượng sản phẩm
    *listM = realloc(*listM, (*length) * sizeof(Merchandise)); // Cấp phát lại bộ nhớ
    if (*listM == NULL) {
        printf("Khong du bo nho.\n");
        fclose(file);
        *length = 0;
        return;
    }
    fread(*listM, sizeof(Merchandise), *length, file); // Đọc danh sách sản phẩm
    fclose(file);
    printf("Da tai danh sach tu tep '%s'.\n", filename);
}

void sellListM(Merchandise *listM, int *length){
    printf("nhap ma sp muon ban: ");
    int id;
    scanf("%d",&id);
    printf("nhap so luong can ban: ");
    int solg;
    scanf("%d",&solg);
    for(int i=0; i<*length; i++){
        if(listM[i].id==id && solg<=listM[i].amount){
            listM[i].amount=listM[i].amount-solg;
            income+=listM[i].outputPtice*solg;
            if(listM[i].amount==0){
                deleteListM(&listM,i,&length);
                printf("da ban san pham.\n");
                return 0;
            }
        }
    }
    printf("khong con san pham.\n");
}

void deleteListM(Merchandise *listM,int index, int *length){
    for(int i=index; i<*length; i++){
        listM[i]=listM[i+1];
    }
    (*length)--;
}

void swap(Merchandise *a, Merchandise *b){
    Merchandise temp = *a;
    *a = *b;
    *b = temp;
}

void MENU(){
    printf("\nOptions\n");
    printf("1.nhap so luong va thong tin san pham.\n");
    printf("2.hiem thi danh sach san pham.\n");
    printf("3.nhap san pham.\n");
    printf("4.cap nhat thong tin san pham.\n");
    printf("5.sap sep san pham theo gia.\n");
    printf("6.tim kiem san pham.\n");
    printf("7.ban san pham(nhap so lg can ban).\n");
    printf("8.doanh thu hien tai.\n");
    printf("9.thoat.\n");
    printf("Lua chon cua ban.\n");
}

void Initialization(Merchandise *listM, int *length){
    printf("nhap vao so luong san pham: ");
    scanf("%d",length);
    getchar();
    Merchandise *temp=realloc(listM,(*length)*sizeof(Merchandise));
    if (temp==NULL) {
        printf("khong du bo nho.\n");
        free(listM);
        listM=NULL;
        *length=0;
        return;
    }
    listM=temp;
    for(int i = 0; i < *length; i++) {
        printf("ma san pham: ");
        scanf("%d", &listM[i].id);
        getchar();
        printf("ten san pham: ");
        fgets(listM[i].name, sizeof(listM[i].name), stdin);
        listM[i].name[strcspn(listM[i].name, "\n")] = '\0';
        printf("gia nhap: ");
        scanf("%d",&listM[i].inputPrice);
        printf("gia ban: ");
        scanf("%d", &listM[i].outputPtice);
        printf("so luong san pham: ");
        scanf("%d",&listM[i].amount);
        getchar();
    }
}

void PrintlistM(Merchandise *listM, int *length){
    for(int i=0; i<*length; i++){
        printf("%d:_%d:_%s_nhap:%d$_ban:%d$_solg:%d\n",i,listM[i].id,listM[i].name,listM[i].inputPrice,listM[i].outputPtice,listM[i].amount);
    }
}

void productImport(Merchandise *listM, int *length) {
    int id, inputPrice, outputPrice, amount;
    printf("Nhap ma san pham: ");
    scanf("%d", &id);

    // Kiểm tra sản phẩm đã tồn tại
    for (int i = 0; i < *length; i++) {
        if (listM[i].id == id) {
            printf("San pham da ton tai. Nhap so luong muon them: ");
            scanf("%d", &amount);
            int totalCost = amount * listM[i].inputPrice;
            if (income >= totalCost) {
                listM[i].amount += amount;
                income -= totalCost;
                printf("Da cap nhat so luong san pham.\n");
            } else {
                printf("Khong du tien de nhap san pham.\n");
            }
            return;
        }
    }
    // Nếu không tồn tại, thêm sản phẩm mới
    printf("Nhap ten san pham: ");
    getchar();
    char name[30];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Nhap gia nhap: ");
    scanf("%d", &inputPrice);
    printf("Nhap gia ban: ");
    scanf("%d", &outputPrice);
    printf("Nhap so luong: ");
    scanf("%d", &amount);
    int totalCost = inputPrice * amount;
    if (income >= totalCost) {
        listM = realloc(listM, (*length + 1) * sizeof(Merchandise));
        if (!listM) {
            printf("Khong du bo nho.\n");
            return;
        }
        listM[*length].id = id;
        strcpy(listM[*length].name, name);
        listM[*length].inputPrice = inputPrice;
        listM[*length].outputPtice = outputPrice;
        listM[*length].amount = amount;

        (*length)++;
        income -= totalCost;
        printf("San pham moi da duoc them.\n");
    } else {
        printf("Khong du tien de nhap san pham.\n");
    }
}

void update(Merchandise *listM, int *length){
    printf("nhap ma san pham muon cap nhat lai: ");
    int id;
    scanf("%d",&id);
    for(int i=0; i<*length; i++){
        if(listM[i].id==id){
            printf("nhap thong tin moi.\n");
            printf("ma san pham: ");
            scanf("%d", &listM[i].id);
            getchar();
            printf("ten san pham: ");
            fgets(listM[i].name, sizeof(listM[i].name), stdin);
            listM[i].name[strcspn(listM[i].name, "\n")] = '\0';
            printf("gia nhap: ");
            scanf("%d",&listM[i].inputPrice);
            printf("gia ban: ");
            scanf("%d", &listM[i].outputPtice);
            printf("so luong san pham: ");
            scanf("%d",&listM[i].amount);
            getchar();
            printf("da cap nhat.\n");
            return 0;
        }
    }
    printf("khong ton tai san pham do.\n");
}

void softT(Merchandise *listM, int *length) {
    for (int i = 0; i < *length - 1; i++) {
        for (int j = 0; j < *length - 1 - i; j++) {
            if (listM[j].outputPtice > listM[j+1].outputPtice){
                swap(&listM[j].outputPtice, &listM[j+1].outputPtice);
            }
        }
    }
}

void softG(Merchandise *listM, int *length) {
    for (int i = 0; i < *length - 1; i++) {
        for (int j = 0; j < *length - 1 - i; j++) {
            if (listM[j].outputPtice < listM[j+1].outputPtice){
                swap(&listM[j].outputPtice, &listM[j+1].outputPtice);
            }
        }
    }
}

void search(Merchandise *listM,int *length){
    printf("nhap ten sach muon tim kiem. ");
    char x[30];
    fgets(x,sizeof(x),stdin);
    x[strcspn(x,"\n")]='\0';
    for(int i=0; i<*length; i++){
        if(strcmp(listM[i].name,x)==0){
            printf("sach ban can tim la:\n");
            printf("%d:_%d:_%s_nhap:%d$_ban:%d$_solg:%d\n",i,listM[i].id,listM[i].name,listM[i].inputPrice,listM[i].outputPtice,listM[i].amount);
            break;
        }
    }
    printf("ko ton tai sach.\n");
}
