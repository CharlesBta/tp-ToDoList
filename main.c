#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tache{
    int ID;
    char note[1024];
    int done; //0 to do | 1 done
    struct Tache* next;
}Tache;

int compteur = 0;

void ajouter_tache(Tache** list, char string[]){
    Tache * item = malloc(sizeof(Tache));
    item->ID = compteur;
    strcpy(item->note,string);
    item->next = *list;
    *list = item;
    compteur++;
}

void afficher_all(Tache *list){
    if(list == NULL)return;
    if(list->next == NULL) {
        printf("%s | id: %d\n",list->note,list->ID);
        return;
    }
    afficher_all(list->next);
    printf("%s | id: %d\n",list->note,list->ID);
}

int afficher_todo(Tache *list){
    int compteur_tache = 0;
    if(list == NULL)return compteur_tache;
    if(list->next == NULL) {
        if(list->done != 1){
            printf("%s | id: %d\n",list->note,list->ID);
            compteur_tache++;
        }
        return compteur_tache;
    }
    compteur_tache++;
    afficher_todo(list->next);
    if(list->done != 1){
        printf("%s | id: %d\n",list->note,list->ID);
    }
}

void afficher_done(Tache *list){
    if(list == NULL)return;
    if(list->next == NULL) {
        if(list->done != 0){
            printf("%s | id: %d\n",list->note,list->ID);
        }
        return;
    }
    afficher_done(list->next);
    if(list->done != 0){
        printf("%s | id: %d\n",list->note,list->ID);
    }
}

int tache_done(Tache* list,int ID){
    if(list == NULL)return 1;
    while(list != NULL){
        if(list->ID == ID){
            if(list->done == 1){
                return 1;
            }
            list->done = 1;
            return 0;
        }
        list = list->next;
    }
    return 1;
}


int main() {
    Tache *ToDoList = NULL;
    char buffer[1024];

    int menu_value = 0;
    printf("||| TO DO LIST MENU |||\n1. Add task\n2. Show all task\n3. Show done task\n4. Show to do task\n5. Mark as done task\n-1. Exit\n");
    scanf("%d",&menu_value);
    getchar();
    while(menu_value != -1){
        if(menu_value == 1){
            printf("\n");
            printf("Name of task: ");
            fgets(buffer, 1024, stdin);
            ajouter_tache(&ToDoList,buffer);
        }
        if(menu_value == 2){
            printf("\n");
            printf("All task ->\n");
            afficher_all(ToDoList);
        }if(menu_value == 3){
            printf("\n");
            printf("All done task ->\n");
            afficher_done(ToDoList);
        }
        if(menu_value == 4){
            printf("\n");
            printf("All to do task ->\n");
            afficher_todo(ToDoList);
        }
        if(menu_value == 5){
            int value_ID = 0;
            int res,done = 0;

            printf("\n");
            printf("All to do task ->\n");
            if(afficher_todo(ToDoList) == 0){
                printf("All task done\n");
                done = 1;
            }
            while(done != 1){
                printf("ID of task: ");
                scanf("%d",&value_ID);
                getchar();
                res = tache_done(ToDoList,value_ID);
                if(res != 1){
                    done = 1;
                }else{
                    printf("Value error, try again\n");
                }
            }
        }
        if(menu_value != 1 && menu_value != 2 && menu_value != 3 && menu_value != 4 && menu_value != 5 && menu_value != -1){
            printf("Value error, try again\n");
            scanf("%d",&menu_value);
            getchar();
        }else{
            printf("\n");
            printf("||| TO DO LIST MENU |||\n1. Add task\n2. Show all task\n3. Show done task\n4. Show to do task\n5. Mark as done task\n-1. Exit\n");
            scanf("%d",&menu_value);
            getchar();
        }
    }
    return 0;
}
