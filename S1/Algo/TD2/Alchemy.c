#include <stdio.h>

#define TRUE 1
#define FALSE 0

int op1 (int volume){
    return volume * 3;
}

int op2 (int volume){
    return volume * 2;
}

int op3 (int volume){
    return volume / 5;
}

void test_operation(int volumes [] ,int volumeSolution, int volumeMax){ //I don't know why but it works
    if(op1(volumeSolution) <= volumeMax && !volumes[op1(volumeSolution)]){
        volumes[op1(volumeSolution)] = TRUE;
        test_operation(volumes,op1(volumeSolution),volumeMax);
    }
    if(op2(volumeSolution) <= volumeMax && !volumes[op2(volumeSolution)]){
        volumes[op2(volumeSolution)] = TRUE;
        test_operation(volumes,op2(volumeSolution),volumeMax);
    }
    if(op3(volumeSolution) <= volumeMax && !volumes[op3(volumeSolution)]){
        volumes[op3(volumeSolution)] = TRUE;
        test_operation(volumes,op3(volumeSolution),volumeMax);
    }

}

int main(){
    int volumeMax , volumeSubstance;

    scanf("%d",&volumeMax);
    scanf("%d",&volumeSubstance);

    int volumes [volumeMax+1] ;

    volumes[volumeSubstance] = TRUE;
    int i;

    //initializing the array to full 0 sauf la case avec le volume actuel
    for(i = 0 ; i < sizeof(volumes)/sizeof(int) ; i ++){
        if(i != volumeSubstance) volumes[i] = FALSE;
    }

    test_operation(volumes,volumeSubstance,volumeMax);

    int max = 0;

    //on cherche le volume max atteint
    for(i = 0 ; i < sizeof(volumes)/sizeof(int) ; i++){
        if(volumes[i]) max = i;
    }

    printf("%d\r\n",max);


    return 0;
}
