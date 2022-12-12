-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 2 - Question 4 : Affichez les noms de villes qui sont les plus répandus ainsi que le nombre d'utilisations.

select name, count(name)
from city
group by name
-- on selectionne toutes les villes ainsi que leur nombre d'apparitions
-- uniquement s'il est égal au maximum d'apparations
having count(name) in (select max(count(name))
                       from city
                       group by name)
order by name;


-- on obtient 11 lignes, de Cordoba à Victoria
