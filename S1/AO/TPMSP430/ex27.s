.section .init9

main:
    /* initialisation du haut parleur en output*/ 
    mov.b #32, &26
    mov.b #0, r14
    mov #32, r15 

loop:
    mov #300, r12
    jmp pin

pin:
    mov.b r15, &25
    xor #32, r15
    mov #400, r13
    jmp delayPin

finDelayPin:
    dec r12
    jnz pin
    mov #200, r12
    jmp pon

pon:
    mov.b r15, &25
    xor #32, r15
    mov #1000, r13
    jmp delayPon

finDelayPon:
    dec r12
    jnz pon
    jmp loop

delayPin:
    /* decremente valeur de r13 de 1 */
    sub #1, r13
    /* if valeur de r13 n'est pas 0 on continue de decrementer*/
    jnz delayPin
    /* else on a fini de perdre du temps donc on retourne a loop */
    jmp finDelayPin

delayPon:
    /* decremente valeur de r13 de 1 */
    sub #1, r13
    /* if valeur de r13 n'est pas 0 on continue de decrementer*/
    jnz delayPon
    /* else on a fini de perdre du temps donc on retourne a loop */
    jmp finDelayPon
