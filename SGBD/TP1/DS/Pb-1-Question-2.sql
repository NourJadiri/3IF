-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 2 : Donnez le code permettant de garantir que le nom d'une personne débute par un caractère alphabétique.
alter table utilisateur
add constraint nom_commence_par_lettre
check(utilisateur.nom like '[^A-Z]%' or UTILISATEUR.nom like '[^a-z]%');
