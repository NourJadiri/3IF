-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 2 - Question 6 : Pays ayant au moins deux langues parlées et qui ne font partie d'aucune organisation.

-- tous les noms des pays
select NAME
from COUNTRY
minus
-- moins ceux qui sont membres d'une orga => on obtient ceux qui ne sont pas membres
(select NAME
 from ISMEMBER, COUNTRY
 where COUNTRY = CODE
 and ORGANIZATION is not null)
minus
-- moins ceux qui parlent strictement - de 2 langues => on obtient ceux
-- qui parlent au moins 2 langues et qui sont non-membre d'une orga
(select c.NAME
 from LANGUAGE l
 left outer join country c on (c.CODE = l.COUNTRY)
 group by c.NAME
 having count(l.NAME) < 2)
minus
-- moins ceux qui ne sont pas référencés car on ne sait pas combien de langues ils parlent
(select NAME
 from country c
 where code not in
       (select country
        from LANGUAGE))
order by NAME;


-- on obtient 2 lignes, Gaza Strip et West Bank
