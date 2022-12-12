-- ContrÃ´le de TP
--            NumEtudiant      Nom         PrÃ©nom 
-- Membre 1 : 4023359          ROULIER     Marie
-- Membre 2 : 4023929          ELJADIRI    Nour
-- Membre 3 : 4027126          VOIGTLANDER Vincent

-- Probleme 1 - Question 1 : Donnez le code permettant de crÃ©er les tables correspondantes sous Oracle.

-- create tables
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
  commenteId integer,
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

-- add data
insert into utilisateur values (1, 'tom@mail.com', 'Tom');
insert into utilisateur values (2, 'emma@mail.com', 'Emma');
insert into utilisateur values (3, 'sophie@mail.com', 'Sophie');

insert into post values (1, 'Je mapelle Tom.', TO_DATE('2000/01/01', 'yyyy/mm/dd'), 1);
insert into post values (2, 'Ca ninteresse personne ici!', TO_DATE('2000/01/02', 'yyyy/mm/dd'), 2);

insert into image values (1, 
  'https://sayingimages.com/wp-content/uploads/thats-funny-don-t-care-meme.jpg',
  'spongesbob', 2);
  
insert into commente values (1, 1, 2, TO_DATE('2000/01/03', 'yyyy/mm/dd'), ':/');

insert into note values (3, 2, 5, TO_DATE('2000/01/03', 'yyyy/mm/dd'));

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
primary key(commenteId);

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
