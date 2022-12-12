-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 6 : Écrire une fonction PL/SQL qui retourne la moyenne des notes obtenues par un post dont l'identifiant est passé en paramètre.
create or replace function moyenneNote(post$id in post.postID%type)
    return float is moyenne float;
        
        begin 
            select avg(note) into moyenne
            from post
            where post = post$id;
            
            return moyenne;
        end;
