-- Contrôle de TP
--            NumEtudiant      Nom      Prénom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 4 : Donnez le code permettant de garantir que la date d'un commentaire soit postérieure à celle du post associé.

create or replace trigger comment_date_greater_than_post_date
    after insert or update on COMMENTE
    for each row
    declare
        datePost POST.aDate%type;
    begin
        select aDate into datePost
        from POST
        where :new.postID = POST.POSTID;

        if(datePost > :new.aDate) then
            raise_application_error(-20001,'Attention ,  la date du commentaire est non valide');
        end if;
    end;
