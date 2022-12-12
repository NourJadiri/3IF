-- ContrÃ´le de TP
--            NumEtudiant      Nom      PrÃ©nom 
-- Membre 1 : 
-- Membre 2 : 
-- Membre 3 : 

-- Probleme 1 - Question 1 : Donnez le code permettant de crÃ©er les tables correspondantes sous Oracle.

create table utilisateur(
  utilisateurId integer, 
  email varchar2(50), 
  nom varchar2(50)
);

create table post(
  postId integer, 
  texte varchar2(200), 
  adate date,
  utilisateurId integer
);

create table image(
  imageId integer, 
  url varchar2(200), 
  tite varchar2(50),
  postId integer
);

create table commente(
  utilisateurId integer,
  postId integer,
  adate date,
  text varchar2(200)
);

create table note(
  utilisateurId integer,
  postId integer,
  note integer,
  adate date
);
-- contraintes: primary keys
alter table utilisateur
add constraint PK_utilisateur
primary key(utilisateurId);

alter table post
add constraint PK_post
primary key(postId);

alter table image
add constraint PK_image
primary key(imageId);

alter table commente
add constraint PK_commente
primary key(utilisateurId, postId);

alter table note
add constraint PK_note
primary key(utilisateurId, postId);

-- contraintes: foreign keys
alter table post 
add constraint FK_post_utilisateur
foreign key (utilisateurId) references utilisateur(utilisateurId)
deferrable initially immediate;

alter table image 
add constraint FK_image_post
foreign key (postId) references post(postId)
deferrable initially immediate;

alter table commente 
add constraint FK_commente_utilisateur
foreign key (utilisateurId) references utilisateur(utilisateurId)
deferrable initially immediate;

alter table commente 
add constraint FK_commente_post
foreign key (postId) references post(postId)
deferrable initially immediate;

alter table note 
add constraint FK_note_utilisateur
foreign key (utilisateurId) references utilisateur(utilisateurId)
deferrable initially immediate;

alter table note 
add constraint FK_note_post
foreign key (postId) references post(postId)
deferrable initially immediate;

-- contraintes: checks
alter table note
add constraint note_domain
check (0 < note and note < 6);

commit;
