.section .init9

main:
    /* initialisation de la diode rouge */ 
    mov.b #2, &50

    /* valeur initiale de la valeur de la diode */
    mov #2, r15 

loop:
    /* initialise r13 à 20 000 */
    mov #50000, r13

    call #pause

    /* transferer ce qu'il y a dans r15 vers la diode */
    mov.b r15, &49
    
    /* xor 2 avec ce qu'il y a dans le registre r15
     stock le resultat dans r15*/
    xor #2, r15 

    jmp loop

pause:
    /* decremente valeur de r13 de 1 */
    sub #1, r13

    /* if valeur de r13 n'est pas 0 on continue de decrementer*/
    jnz pause

    ret
