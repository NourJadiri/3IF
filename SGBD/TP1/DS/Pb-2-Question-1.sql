-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 :
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 2 - Question 1 : Affichez toutes les villes du pays ayant pour nom texttt{'France'


select city.name
from CITY, country
-- jointure car dans city, ce sont les codes des pays qui sont donnés
where country = country.CODE
and country.name = 'France'
order by city.name;


--on obtient 41 lignes, de Aix-en-Provence à Villeurbanne
