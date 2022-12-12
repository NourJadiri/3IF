-- ContrÃ´le de TP
--            NumEtudiant      Nom      PrÃ©nom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 1 : Donnez le code permettant de crÃ©er les tables correspondantes sous Oracle.

create table utilisateur(
  UtilisatuerId integer, 
  email varchar2(50), 
  nom varchar2(50)
);

create table post(
  postId integer, 
  texte varchar2(200), 
  adate date,
  UtilisatuerId integer
);

create table image(
  imageId integer, 
  url varchar2(200), 
  tite varchar2(50),
  postId integer
);

create table commente(
  utilisatuerId integer,
  postId integer,
  adate date,
  text varchar2(200)
);

create table note(
    utilisatuerId integer,
  postId integer,
  note integer,
  adate date
);
commit;
