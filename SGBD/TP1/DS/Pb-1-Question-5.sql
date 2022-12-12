-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 5 : Donner le code nécessaire correspondant à la contrainte suivante : ``Un utilisateur ne doit pas commenter ses propres posts''.
alter table COMMENTE
add constraint no_self_commenting
check(UTILISATEURID not in 
      -- on cherche s'il existe un utilisateur qui a commenté son propre post
      -- puis on check que les utilisateurs dans commente ne vérifient pas cette propriété (ligne 10)
      (select commente.UTILISATEURID
      from post , commente
      where post.postID = commente.POSTID
      and post.utilisateurID = commente.UTILISATEURID))
