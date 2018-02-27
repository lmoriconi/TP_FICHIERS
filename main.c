//LENNY MORICONI
//BUT : programme qui demande à un utilisateur les informations de sa carte d'identité et qui les ajoute à des fichiers textes et binaires
//ENTREE : ouverture/lecture des fichiers .txt et .bin
//SORTIE : écriture de ces fichiers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CONSTANTES
#define SIZE_STRING 30       //taille pour les chaines
#define MAX 100              //taille max d'une ligne
#define MIN_DATE 1           //valeur minimale d'un jour ou d'un mois
#define MAX_DAY 31           //valeur maximale d'un jour
#define MAX_MONTH 12         //valeur maximale d'un mois
#define CURRENT_YEAR 2018    //année en cours

//TYPES STRUCTURES
typedef struct Date{
    int d, m, y;
}Date;

typedef struct Id{
    int num;
    char lastName[SIZE_STRING];
    char firstName[SIZE_STRING];
    char city[SIZE_STRING];
    char gender;
    Date birthdate;
}Id;

//PROTOTYPES
Id setCard();
Date setDate();
void write(Id);

//PROGRAMME PRINCIPAL
int main()
{
    Id test = setCard();
    Id card;
    char* line;

    FILE* text = fopen("idCards.txt", "a");
    FILE* bin;

    //Texte
    if(text != NULL){
        fprintf(text, "%d %s %s %c %s %d/%d/%d\n", test.num, test.lastName, test.firstName, test.gender, test.city, test.birthdate.d, test.birthdate.m, test.birthdate.y);
        fclose(text);
    }
    else{
        printf("File idCards.txt not find\n");
        printf("New file idCards.txt created");
        getc(stdin);
        fflush(stdin);
    }

    //Lecture de fichier texte
    text = fopen("idCards.txt", "r");

    if(text != NULL){
        line = (char*)malloc(sizeof(char) * MAX);

        if(line != NULL){
            printf("ID cards (text) :\n");
            do{
                line = fgets(line, sizeof(char) * MAX, text);
                if(line != NULL)
                    printf("%s", line);
            }while(feof(text) == 0);
            free(line);
        }
        else{
            printf("An error occured while reading the file");
            getc(stdin);
            fflush(stdin);
        }
    }
    else{
        printf("An error occured while trying to access idCards.txt");
        getc(stdin);
        fflush(stdin);
    }
    fflush(stdin);

    //Binaire
    bin = fopen("idCards.bin", "ab");

    if(bin != NULL){
        fwrite(&test, sizeof(Id), 1, bin);
        fclose(bin);
    }
    else{
        printf("Bin idCards.bin not found\n");
        printf("New bin idCards.bin created");
    }

    //Lecture du fichier binaire
    bin = fopen("idCards.bin", "rb");
    if(bin != NULL){
        printf("\nID cards (binary) :\n");
        do{
            fread(&card, sizeof(card), 1, bin);
            if(feof(bin) == 0)
                write(card);
        }while(feof(bin) == 0);
        fclose(bin);
    }
    else{
        printf("An error occured while trying to access idCards.bin");
    }

    return 0;
}

Id setCard(){
//BUT : procédure qui retourne une structure de type Id intialisée par l'utilisateur

    Id newCard;

    printf("Card number :\n");
    scanf("%d", &newCard.num);
    printf("\nLast name :\n");
    scanf("%s", newCard.lastName);
    printf("\nFirst name :\n");
    scanf("%s", newCard.firstName);
    fflush(stdin);
    printf("\nGender (M/F) :\n");
    scanf("%c", &newCard.gender);
    printf("\nBirthdate :\n");
    newCard.birthdate = setDate();
    printf("\nCity :\n");
    scanf("%s", newCard.city);

    system("cls");

    return newCard;
}

Date setDate(){
//BUT : fonction qui retourne une structure de type Date initialisée par l'utilisateur

    Date birth;

    printf("Day :\n");
    do{
        scanf("%d", &birth.d);
        if(birth.d < MIN_DATE || birth.d > MAX_DAY)
            printf("The day of birth must be between %d and %d. Please try again.\n", MIN_DATE, MAX_DAY);
    }while(birth.d < MIN_DATE || birth.d > MAX_DAY);

    printf("Month :\n");
    do{
        scanf("%d", &birth.m);
        if(birth.m < MIN_DATE || birth.m > MAX_MONTH)
            printf("The month of birth must be between %d and %d. Please try again.\n", MIN_DATE, MAX_MONTH); 
    }while(birth.m < MIN_DATE || birth.m > MAX_MONTH);

    printf("Year :\n");
    do{
        scanf("%d", &birth.y);
        if(birth.y > CURRENT_YEAR)
            printf("The year of birth cannot be higher than %d. Please try Again.\n", CURRENT_YEAR);
    }while (birth.y > CURRENT_YEAR);

    return birth;
}

void write(Id card){
//BUT : procédure qui écrit les informations de la carte d'identité

    printf("%d %s %s %c %d/%d/%d %s\n", card.num, card.lastName, card.firstName, card.gender, card.birthdate.d, card.birthdate.m, card.birthdate.y, card.city);
}
