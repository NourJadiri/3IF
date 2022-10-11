#define _CRT_SECURE_NO_WARNINGS //pour Visual Studio
#include <stdio.h>

int main () {
    int n;
    scanf("%d", &n);
    int arrGrid[100][100];
    char temp;

    int nPosI, nPosJ;
    for (nPosI = 0; nPosI < n; nPosI++) {
        for (nPosJ = 0; nPosJ < n; nPosJ++) {
            scanf("%d%c", &arrGrid[nPosI][nPosJ], &temp);
        }
    }


    int nrOfPaths[100][100];
    nrOfPaths[0][0] = 1;
    for (nPosI = 0; nPosI < n; nPosI++) {
        for (nPosJ = 0; nPosJ < n; nPosJ++) {
            if (nPosI == 0 && nPosJ == 0) continue;
            else if (arrGrid[nPosI][nPosJ] == -1) nrOfPaths[nPosI][nPosJ] = 0;
            else if (nPosJ-1<0) nrOfPaths[nPosI][nPosJ] = nrOfPaths[nPosI-1][nPosJ];
            else if (nPosI-1<0) nrOfPaths[nPosI][nPosJ] = nrOfPaths[nPosI][nPosJ-1];
            else nrOfPaths[nPosI][nPosJ] = nrOfPaths[nPosI][nPosJ-1] + nrOfPaths[nPosI-1][nPosJ];
        }
    }

    printf("%d\r\n", nrOfPaths[n-1][n-1]);
    return 0; // on l'oublie pas
}