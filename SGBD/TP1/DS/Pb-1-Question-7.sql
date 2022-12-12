-- ContrÃ´le de TP
--            NumEtudiant      Nom      PrÃ©nom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 7 : Pour chaque utilisateur, donnez le code permettant de lister ses posts les mieux notÃ©s.

with best_note as
  (select u.UTILISATEURID, max(n.note) as max_note
  from utilisateur u, post p, note n 
  where u.UTILISATEURID = p.UTILISATEURID and p.postId = n.postId
  group by u.UTILISATEURID)
  
select u.nom, p.postId
  from utilisateur u, post p, note n, best_note
  where u.UTILISATEURID = p.UTILISATEURID 
    and p.postId = n.postId
    and best_note.UTILISATEURID = u.UTILISATEURID
    and n.note = best_note.max_note;
