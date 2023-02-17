.section .init9

main:
    /* initialisation de la diode rouge */ 
    mov.b #2, &50

    /* valeur initiale de la valeur de la diode */
    mov #2, r15 

loop:
    /* initialise r13 à 50 000 */
    /* Petite note : il faut encoder la pause sur 2
    registres cuz un registre ne peut pas stocker un delay
    assez long :) */
    
    mov #50000, r13
    mov #50000, r14

    call #pause1
    call #pause2

    /* transferer ce qu'il y a dans r15 vers la diode */
    mov.b r15, &49
    
    /* xor 2 avec ce qu'il y a dans le registre r15
     stock le resultat dans r15*/
    xor #2, r15 

    jmp loop

pause1:
    /* decremente valeur de r13 de 1 */
    sub #1, r13

    /* if valeur de r13 n'est pas 0 on continue de decrementer*/
    jnz pause1

    ret

pause2:
    sub #1, r14
    jnz pause2
    ret
