.section .init9

main:
    /* initialisation de la diode rouge */
    mov.b #2, &50


loop:
    /* éteindre */
    mov.b #0, &49

    /* allumer */
    mov.b #2, &49
    
    jmp loop
