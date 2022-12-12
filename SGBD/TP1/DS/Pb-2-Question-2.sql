-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 2 - Question 2 : Afficher toutes les informations des villes situées dans une province dont le nom contient 'East'.

select *
from city
where province like '%East%'
-- les pourcentages permettent de dire "contient", que ca soit au debut
-- ou a la fin d'une chaine de caractères
order by province, name;


-- on obtient 45 tuples, de Tabriz à Bolgatanga
