#include <stdio.h>
const int rows = 6;
const int columns = 7;

int check_horizontal_alignement(const char tab[columns]);
char check_vertical_alignement(char tab[rows][columns] , int l);
char check_diagonal_alignement(char tab[rows][columns] , int l);

int main(){
    //lecture du tableau
    char tab[6][7];

    char tmp;
    int i,j;
    for (i=0;i<6;i++) {
        for (j=0;j<7;j++) {
            fscanf(stdin,"%c",&(tab[i][j]));
        }
        fscanf(stdin,"%c",&tmp);//* new line *//*
    }

    for(i = 5 ; i >=0 ; i--){
        if(check_horizontal_alignement(tab[i]) == 1){
            printf("%c\n",tab[i][3]);
            return 0;
        }
    }

    char diagonalState;
    char verticalState;

    i = 5;

    do{
        verticalState = check_vertical_alignement(tab,i);
        diagonalState = check_diagonal_alignement(tab,i);
        i--;
    }while(diagonalState == '0' && verticalState == '0' && i >= 0);
    if(diagonalState != '0' ) fprintf(stdout , "%c\n" , diagonalState);
    else if (verticalState != '0') fprintf(stdout, "%c\n" , verticalState);
    else fprintf(stdout,"%c\n",'0');

    return 0;
}

// check l'alignement horizontal sur toute une ligne
int check_horizontal_alignement(const char tab[]){
    int i,j;
    int c = columns - 4 + 1; // on checkera seulement pour la première moitié du tableau (cuz on a un piti tableau)

    // if we are in the left half of the board, no need to check à gauche cuz on a que 3 cases au max anyways
    int counter = 0;
    for(i = 0 ; i < c ; i++){
        for(j = i ; j < i+4 ; j++){
            if(tab[j] == '0') break;
            if(tab[i] == tab[j]){
                counter++;
            }else break;
        }
        if(counter == 4) return 1;
        else counter = 0;
    }

    return 0;
}

// Check l'alignement vertical sur les pions de la même ligne aussi
char check_vertical_alignement(char tab[rows][columns] , int l){
    int counter = 0 ;
    int i,j;
    if(l >= 3) {
       for(j = 0 ; j < columns ; j++) {
           for (i = l; i > l - 4; i--) {
               if(tab[i][j] == '0') break;
               if (tab[i][j] == tab[l][j]) counter++;
           }
           if (counter == 4) return tab[l][j];
           else counter = 0;
       }

    }
    return '0';
}

char check_diagonal_alignement(char tab[rows][columns] , int l){
    //printf("checkin diagonal alignement\n");
    int i,j,c;


    int counter = 0;
    int counter_2 = 0; //utile seulement si on est au milieu du tableau

    for(c = 0 ; c < columns ; c++) {
        // Si on est sur la moitié supérieure du tableau
        if (l < 3) {
            // Et qu'on est sur la moitié gauche du tableau
            if (c < 3) {
                i = l;
                j = c;
                while (tab[i][j] != '0' && tab[i][j] == tab[l][c] && i < l + 4) {
                    counter++;
                    i++;
                    j++;
                }
                if(counter == 4) return tab[l][c];
                else counter = 0;
            }

            // Si on est sur la moitié droite du tableau
            else if (c > 3) {
                i = l;
                j = c;
                while (tab[i][j] != '0' && tab[i][j] == tab[l][c] && i < l + 4) {
                    counter++;
                    i++;
                    j--;
                }

                if(counter == 4) return tab[l][c];
                else counter = 0;
            }


            // Si on est pile au milieu, on combine les deux procédures précédentes
            else {
                i = l;
                j = c;
                while (tab[i][j] != '0' && tab[i][j] == tab[l][c] && i < l + 4) {
                    counter++;
                    i++;
                    j++;
                }

                i = l;
                j = c;
                while (tab[i][j] != '0' && tab[i][j] == tab[l][c] && i < l + 4) {
                    counter_2++;
                    i++;
                    j--;
                }

                if(counter == 4 || counter_2 == 4) return tab[l][c];
                else counter = counter_2 = 0;
            }
        }

        // Sinon si on est sur la moitié inférieure du tableau
        else {
            // Et qu'on est sur la moitié gauche du tableau
            if (c < 3) {
                i = l;
                j = c;
                while (tab[i][j] != '0' && tab[i][j] == tab[l][c] && i > l - 4) {
                    counter++;
                    i--;
                    j++;
                }
                if(counter == 4) return tab[l][c];
                else counter = 0;
            }

            // Si on est sur la moitié droite du tableau
            else if (c > 3) {
                i = l;
                j = c;
                while (tab[i][j] != '0' && tab[i][j] == tab[l][c] && i > l - 4) {
                    counter++;
                    i--;
                    j--;
                }
                if(counter == 4) return 1;
                else counter = 0;
            }

            // Si on est pile au milieu, on combine les deux procédures précédentes
            else {
                i = l;
                j = c;
                while (tab[i][j] != '0' && tab[i][j] == tab[l][c] && i > l - 4) {
                    counter++;
                    i--;
                    j++;
                }
                while (tab[i][j] != '0' && tab[i][j] == tab[l][c] && i > l - 4) {
                    counter_2++;
                    i--;
                    j--;
                }
                if(counter == 4 || counter_2 == 4) return tab[l][c];
                else counter = counter_2 = 0;

            }

        }
    }

    return '0';
}

