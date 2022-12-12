-- ContrÃ´le de TP
--            NumEtudiant      Nom      PrÃ©nom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 7 : Pour chaque utilisateur, donnez le code permettant de lister ses posts les mieux notÃ©s.

with best_note as
  (select utilisateurId, max(note) as max_note
  from utilisateur natural join (post natural join note)
  group by utilisateurId)
  
select nom, postId
from utilisateur natural join (post natural join note) natural join best_note
where note = max_note;
