.section .init9

main:
    /* initialisation de la diode rouge */ 
    mov.b #2, &50

    mov.b #0, r14
    /* valeur initiale de la valeur de la diode */
    mov #2, r15 

loop:
    /* initialise r13 à 20 000 */
    mov #20000, r13

    /* transferer ce qu'il y a dans r15 vers la diode */
    mov.b r15, &49
    
    /* xor 2 avec ce qu'il y a dans le registre r15
     stock le resultat dans r15*/
    xor #2, r15 

    /* add 1 to le registre 14 at each loop */
    add #1, r14

    jmp delay

    jmp loop

delay:
    /* decremente valeur de r13 de 1 */
    sub #1, r13

    /* if valeur de r13 n'est pas 0 on continue de decrementer*/
    jnz delay

    /* else on a fini de perdre du temps donc on retourne a loop */
    jmp loop
