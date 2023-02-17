-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 3 : Donnez le code permettant de faire en sorte que le nom d'une personne soit stocké en majuscule dans la base.

create or replace trigger nom_personne_majuscule
    before insert or update on UTILISATEUR
    for each row
    begin
        :new.nom = upper(:new.nom);
    end;
