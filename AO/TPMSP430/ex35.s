.section .init9

main:
    /* initialiser la LED et les boutons */
    mov #0 , &34
    mov #2 , &50

    /* valeur initiale de la valeur de la diode (on allume la diode) */
    mov.b #2 , &49

loop :
    /* attendre qu'un bouton soit appuyé */
    call #waitButtonPressed

    call #waitButtonReleased

    xor.b #2, &49

    jmp loop

waitButtonPressed:
    cmp #3, &32 /* Si le bouton n'est pas cliqué */
    jeq waitButtonPressed /* Si le bouton is not clicked , loop */
    ret

waitButtonReleased:
    cmp #3 , &32
    jnz waitButtonReleased
    ret
