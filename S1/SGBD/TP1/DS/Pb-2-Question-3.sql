-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 2 - Question 3 : Pour chaque province qui contient 'East' dans son nom et qui contient au moins deux villes, afficher son nom ainsi que le nombre de villes qu'elle contient.

select province, count(name) as nbVilles
from CITY
-- on selectionne les provinces qui contiennent 'East'
where province like '%East%'
-- group by pour pouvoir executer le count
group by province
-- on selectionne uniquement les provinces ayant un nombre de villes >= 2
having count(name) >= 2
order by province desc;

-- on obtient 7 lignes, de South East à East Midlands
