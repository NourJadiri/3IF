.section .init9

main:
    /* initialisation de la diode rouge */ 
    mov.b #2, &50
    /* valeur initiale de la valeur de la diode */
    mov #0, r15 
    mov #0, r13
    mov.b #0 , &49

loop:
    call #waitButtonPressed
    call #waitButtonReleased
    call #blinkLed
    jmp loop

blinkLed:
    mov.b r15, &49
    xor #2, r15
    call #pause
    dec r13
    jnz blinkLed
    ret

waitButtonPressed:
    cmp #3, &32 /* Si le bouton n'est pas cliqué */
    jeq waitButtonPressed /* Si le bouton is not clicked , loop */   
    ret

waitButtonReleased:
    call #pause
    /* Garde une trace de combien de fois pause a été appelée */
    /* Donne le nombre de demi secondes attendues */
    add #1, r13 
    cmp #3, &32
    jnz waitButtonReleased
    ret

pause:
    /* initialise r13 à 50 000 */
    /* Petite note : il faut encoder la pause sur 2
    registres cuz un registre ne peut pas stocker un delay
    assez long :) */
    mov #50000, r12
    mov #50000, r14
    call #pause1
    call #pause2
    ret

pause1:
    /* decremente valeur de r13 de 1 */
    sub #1, r12
    /* if valeur de r13 n'est pas 0 on continue de decrementer*/
    jnz pause1
    ret

pause2:
    sub #1, r14
    jnz pause2
    ret
