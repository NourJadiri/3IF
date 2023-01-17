----- CREATION LIENS
create database link LinkAmeriqueToRyori
    connect to MROULIER identified by MDPORACLE
    using 'DB11';

create database link LinkAmeriqueToEuropeNord
    connect to MROULIER identified by MDPORACLE
    using 'DB12';

create database link LinkAmeriqueToEuropeSud
    connect to MROULIER identified by MDPORACLE
    using 'DB13';



----- CREATION TABLES
-- creation de la table employes
create table EMPLOYES as (select * from RYORI.employes@LinkAmeriqueToRyori);

-- creation de la table clients
create table CLIENTS_AM as (select * from ryori.clients@LINKAMERIQUETORYORI
                        where pays in ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie',
                                       'Bresil', 'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba',
                                       'Republique dominicaine', 'Dominique', 'Equateur', 'Etats-Unis', 'Grenade',
                                       'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaique', 'Mexique', 'Nicaragua',
                                       'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nieves', 'Sainte-Lucie',
                                       'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago',
                                       'Uruguay', 'Venezuela'));

-- creation de la table commandes
create table COMMANDES_AM
as (select c.* from ryori.commandes@LINKAMERIQUETORYORI c
                            inner join CLIENTS_AM on ( c.code_client = CLIENTS_AM.CODE_CLIENT ));

-- creation de la table details_commandes
create table DETAILS_COMMANDES_AM
as (select dc.* from ryori.details_commandes@LINKAMERIQUETORYORI dc
                            inner join COMMANDES_AM on (dc.no_commande = COMMANDES_AM.NO_COMMANDE));

-- creation de la table stock
create table STOCK_AM
as (select * from ryori.stock@LINKAMERIQUETORYORI
                        where pays in ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie',
                                       'Bresil', 'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba',
                                       'Republique dominicaine', 'Dominique', 'Equateur', 'Etats-Unis', 'Grenade',
                                       'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaique', 'Mexique', 'Nicaragua',
                                       'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nieves', 'Sainte-Lucie',
                                       'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago',
                                       'Uruguay', 'Venezuela'));


----- CONTRAINTES
--- contraintes 'classiques' (pas de contrainte avec une table distante)
-- table employes
alter table EMPLOYES add constraint pk_no_employe_emp
                     primary key (NO_EMPLOYE);
alter table EMPLOYES add constraint fk_rend_compte_emp
                     foreign key (REND_COMPTE)
                     references EMPLOYES (NO_EMPLOYE);

-- table clients
alter table CLIENTS_AM add constraint pk_code_client_cli
                            primary key (CODE_CLIENT);

-- table commandes
alter table COMMANDES_AM add constraint pk_no_commande_comm
                         primary key (NO_COMMANDE);
alter table COMMANDES_AM add constraint fk_code_client_comm
                         foreign key (CODE_CLIENT)
                         references CLIENTS_AM (CODE_CLIENT);
alter table COMMANDES_AM add constraint fk_no_employe_comm
                         foreign key (NO_EMPLOYE)
                         references EMPLOYES (NO_EMPLOYE);

-- table details_commandes
alter table DETAILS_COMMANDES_AM add constraint pk_no_comm_ref_prod_det
                                 primary key (NO_COMMANDE, REF_PRODUIT);
alter table DETAILS_COMMANDES_AM add constraint fk_no_commande_det
                                 foreign key (NO_COMMANDE)
                                 references COMMANDES_AM (NO_COMMANDE);

-- table stock
alter table STOCK_AM add constraint pk_ref_prod_pays_stock
                     primary key (REF_PRODUIT, PAYS);


--- triggers pour les fk sur des tables distantes
-- verif que le produit existe avant de l'ajouter / modifier dans le stock
/
create or replace trigger trig_stock
    before insert or update on STOCK_AM
    for each row
    declare
        counter$ number(8);
begin
        select count(*) into counter$
        from cgillier.produits@LINKAMERIQUETOEUROPESUD
        where ref_produit = :new.ref_produit;

        if (counter$ = 0) then
                raise_application_error(-20001,'le produit n`existe pas dans la table produits');
        end if;
end;
/

-- verif que le produit existe avant de l'ajouter / modifier dans les details de commande
/
create or replace trigger trig_details_commandes
    before insert or update on DETAILS_COMMANDES_AM
    for each row
    declare
        counter$ number(8);
begin
        select count(*) into counter$
        from cgillier.produits@LINKAMERIQUETOEUROPESUD
        where ref_produit = :new.ref_produit;

        if (counter$ = 0) then
            raise_application_error(-20002,'le produit n`existe pas dans la table produits');
        end if;
end;
/

-- empecher suppression / modif d'un employe s'il apparait dans une commande
/
create or replace trigger trig_employes
    before update or delete on EMPLOYES
    for each row
    declare
        counter$ number(8);
begin
        select count(*) into counter$
        from (select * from COMMANDES_AM
                    union all
              select * from cgillier.Commandes_ES@LINKAMERIQUETOEUROPESUD
                       union all
              select * from smalard.Commandes_EN@LINKAMERIQUETOEUROPENORD
                       union all
              select * from smalard.Commandes_Autre@LINKAMERIQUETOEUROPENORD)
        where NO_EMPLOYE = :old.no_employe;

        if (counter$ > 0) then
            raise_application_error(-20003,'l`employe existe dans une commande');
        end if;
end;
/


----- DROITS
-- dons du droit de selection aux autres sites (pas besoin d'update ou delete)
grant select on EMPLOYES to CGILLIER, SMALARD;
grant select on CLIENTS_AM to CGILLIER, SMALARD;
grant select on COMMANDES_AM to CGILLIER, SMALARD;
grant select on DETAILS_COMMANDES_AM to CGILLIER, SMALARD;
grant select on STOCK_AM to CGILLIER, SMALARD;



----- SYNONYMES ET VUES
--- vues
-- vues pour reunir les tables fragmentees
create view clients as
    select * from CLIENTS_AM
             where pays in ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie',
                                       'Bresil', 'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba',
                                       'Republique dominicaine', 'Dominique', 'Equateur', 'Etats-Unis', 'Grenade',
                                       'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaique', 'Mexique', 'Nicaragua',
                                       'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nieves', 'Sainte-Lucie',
                                       'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago',
                                       'Uruguay', 'Venezuela')
        union all
    select * from cgillier.clients_ES@LINKAMERIQUETOEUROPESUD
             where pays in ('Espagne', 'Portugal', 'Andorre', 'France', 'Gibraltar', 'Italie', 'Saint-Marin', 'Vatican', 'Malte',
                           'Albanie', 'Bosnie-Herzegovine', 'Croatie', 'Grece', 'Macedoine', 'Montenegro', 'Serbie', 'Slovenie', 'Bulgarie')
        union all
    select * from smalard.clients_EN@LINKAMERIQUETOEUROPENORD
             where pays in ('Allemagne', 'Norvege', 'Suede', 'Danemark', 'Islande', 'Finlande', 'Royaume-Uni',
             'Irlande', 'Belgique', 'Luxembourg', 'Pays-Bas', 'Pologne')
        union all
    select * from smalard.clients_Autre@LINKAMERIQUETOEUROPENORD
             where pays not in ('Norvege', 'Suede', 'Danemark', 'Islande', 'Finlande', 'Royaume-Uni',
'Irlande', 'Belgique', 'Luxembourg', 'Pays-Bas', 'Pologne', 'France','Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil',
'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique',
'Equateur', 'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haiti', 'Honduras', 'Jamaique',
'Mexique', 'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nieves', 'SainteLucie', 'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay',
'Venezuela','Espagne', 'Portugal', 'Andorre', 'Gibraltar', 'Italie', 'SaintMarin', 'Vatican', 'Malte', 'Albanie', 'Bosnie-Herzegovine', 'Croatie', 'Grece', 'Macedoine',
'Montenegro', 'Serbie', 'Slovenie', 'Bulgarie');

create view commandes as
    select * from COMMANDES_AM
        union all
    select * from cgillier.commandes_ES@LINKAMERIQUETOEUROPESUD
        union all
    select * from smalard.commandes_EN@LINKAMERIQUETOEUROPENORD
        union all
    select * from smalard.commandes_Autre@LINKAMERIQUETOEUROPENORD;

create view details_commandes as
    select * from DETAILS_COMMANDES_AM
        union all
    select * from cgillier.details_commandes_ES@LINKAMERIQUETOEUROPESUD
        union all
    select * from smalard.details_Commandes_EN@LINKAMERIQUETOEUROPENORD
        union all
    select * from smalard.details_Commandes_Autre@LINKAMERIQUETOEUROPENORD;

create view stock as
    select * from STOCK_AM
        union all
    select * from cgillier.stock_ES@LINKAMERIQUETOEUROPESUD
        union all
    select * from smalard.stock_EN@LINKAMERIQUETOEUROPENORD
        union all
    select * from smalard.stock_Autre@LINKAMERIQUETOEUROPENORD
        union all
    select * from smalard.stock_Allemagne@LINKAMERIQUETOEUROPENORD;


--- synonymes
-- synonymes pour les tables distantes non fragmentees
create or replace synonym produits for cgillier.produits@LINKAMERIQUETOEUROPESUD;
create or replace synonym categories for cgillier.categories@LINKAMERIQUETOEUROPESUD;
create or replace synonym fournisseurs for smalard.fournisseurs@LINKAMERIQUETOEUROPENORD;



----- TESTS
-- test vers base centralisée
select * from RYORI.clients@LinkAmeriqueToRyori;

-- tests pour verifier la bonne creation des tables
select * from EMPLOYES;
select * from CLIENTS_AM;
select * from COMMANDES_AM;
select * from DETAILS_COMMANDES_AM;
select * from STOCK_AM;

-- test des triggers
insert into DETAILS_COMMANDES_AM values(999, 80, 12.1, 4, 0);   -- cette ref_produit n'existe pas
insert into STOCK_AM values(80, 'Etats-Unis', 42, null, 0);     -- cette ref_produit n'existe pas
delete from EMPLOYES where NO_EMPLOYE = 1;                      -- l`employe existe dans une commande

-- tests des vues
select * from ryori.CLIENTS@LINKAMERIQUETORYORI
       minus (select * from clients);
select * from ryori.COMMANDES@LINKAMERIQUETORYORI
       minus (select * from commandes);
select * from ryori.DETAILS_COMMANDES@LINKAMERIQUETORYORI
       minus (select * from details_commandes);
select * from ryori.STOCK@LINKAMERIQUETORYORI
       minus (select * from stock);

-- tests des liens & synonymes
select * from ryori.PRODUITS@LINKAMERIQUETORYORI
       minus (select * from produits);
select * from ryori.CATEGORIES@LINKAMERIQUETORYORI
       minus (select * from categories);
select * from ryori.FOURNISSEURS@LINKAMERIQUETORYORI
       minus (select * from fournisseurs);


---- Question 3

select * from clients;

select * from clients where pays in ('Etats-Unis', 'Argentine', 'Salvador');

select * from CLIENTS_AM;

select * from cgillier.clients_ES@LINKAMERIQUETOEUROPESUD;

select * from clients where pays in ('Norvege', 'Suede');

select * from produits;

select count(*)
  from produits;
  
select count(*)
  from fournisseurs;  
  
  select count(*)
  from categories; 
  
-- Question 4
create materialized view dmv_categories
  refresh complete
  next sysdate + (1/24/60)
  as select * from cgillier.categories@LINKAMERIQUETOEUROPESUD;

create materialized view dmv_fournisseurs
  refresh complete
  next sysdate + (1/24/60)
  as select * from smalard.fournisseurs@LINKAMERIQUETOEUROPENORD;
  
create materialized view dmv_produits
  refresh fast
  next sysdate + (1/24/60)
  as select * from cgillier.produits@LINKAMERIQUETOEUROPESUD;
  
select * from dmv_categories;
select * from dmv_fournisseurs;
select * from dmv_produits;
