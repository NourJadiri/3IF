.section .init9

main:
 
    mov.b #2, &50     /* initialisation de la diode rouge */
    
    mov #0, r15   
    mov #0, r13
    mov.b #0 , &49 /* valeur initiale de la diode (éteinte) */
    
    mov #0, &34 /* On set les boutons en input */

    mov.b #3, &37 /* Activer les interruptions du port 1 */
    mov.b #0, &35 /* On force flag = 0 pour le bouton */
    mov #0, &36 /* On dit à l'interrupt de se lancer au front montant */
    
    eint /* enable interrupts */

loop:
    jmp loop

.global __isr_20
__isr_20:
    xor #2, r15
    mov.b r15, &49
    mov.b #0, &35
    reti
 