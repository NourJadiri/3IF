.section .init9

main:
    /* initialisation de la diode rouge */ 
    mov.b #2, &50

    mov.b #0, r14
    /* valeur initiale de la valeur de la diode */
    mov #2, r15

loop:
    
    /* transferer ce qu'il y a dans r15 vers la diode */
    mov.b r15, &49
    
    /* xor 2 avec ce qu'il y a dans le registre r15
     stock le resultat dans r15*/
    xor #2, r15 

    /* add 1 to le registre 14 at each loop */
    add #1, r14

    jmp loop
