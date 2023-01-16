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
create table CLIENTSAMERIQUE as (select * from ryori.clients@LINKAMERIQUETORYORI
                        where pays in ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie',
                                       'Bresil', 'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba',
                                       'Republique dominicaine', 'Dominique', 'Equateur', 'Etats-Unis', 'Grenade',
                                       'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaique', 'Mexique', 'Nicaragua',
                                       'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nieves', 'Sainte-Lucie',
                                       'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago',
                                       'Uruguay', 'Venezuela'));

-- creation de la table commandes
create table COMMANDESAMERIQUE as (select c.* from ryori.commandes@LINKAMERIQUETORYORI c
                            inner join CLIENTSAMERIQUE on ( c.code_client = CLIENTSAMERIQUE.CODE_CLIENT ));

-- creation de la table details_commandes
create table DETAILS_COMMANDESAMERIQUE as (select dc.*
                                      from ryori.details_commandes@LINKAMERIQUETORYORI dc
                                      inner join COMMANDESAMERIQUE on (dc.no_commande = COMMANDESAMERIQUE.NO_COMMANDE));

-- creation de la table stock
create table STOCKAMERIQUE as (select * from ryori.stock@LINKAMERIQUETORYORI
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
alter table CLIENTSAMERIQUE add constraint pk_code_client_cli
                            primary key (CODE_CLIENT);

-- table commandes
alter table COMMANDESAMERIQUE add constraint pk_no_commande_comm
                              primary key (NO_COMMANDE);
alter table COMMANDESAMERIQUE add constraint fk_code_client_comm
                              foreign key (CODE_CLIENT)
                              references CLIENTSAMERIQUE (CODE_CLIENT);
alter table COMMANDESAMERIQUE add constraint fk_no_employe_comm
                              foreign key (NO_EMPLOYE)
                              references EMPLOYES (NO_EMPLOYE);
-- table details_commandes
alter table DETAILS_COMMANDESAMERIQUE add constraint pk_no_comm_ref_prod_det
                                      primary key (NO_COMMANDE, REF_PRODUIT);
alter table DETAILS_COMMANDESAMERIQUE add constraint fk_no_commande_det
                                      foreign key (NO_COMMANDE)
                                      references COMMANDESAMERIQUE (NO_COMMANDE);

-- table stock
alter table STOCKAMERIQUE add constraint pk_ref_prod_pays_stock
                          primary key (REF_PRODUIT, PAYS);


--- triggers pour les fk sur des tables distantes
-- verif que le produit existe avant de l'ajouter / modifier dans le stock
/
create or replace trigger trig_stock
    before insert or update on STOCKAMERIQUE
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
    before insert or update on DETAILS_COMMANDESAMERIQUE
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
        from (select * from COMMANDESAMERIQUE union all
              select * from cgillier.commandesEuropeSud@LINKAMERIQUETOEUROPESUD union all
              select * from smalard.Commandes_EN@LINKAMERIQUETOEUROPENORD union all
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
grant select on CLIENTSAMERIQUE to CGILLIER, SMALARD;
grant select on COMMANDESAMERIQUE to CGILLIER, SMALARD;
grant select on DETAILS_COMMANDESAMERIQUE to CGILLIER, SMALARD;
grant select on STOCKAMERIQUE to CGILLIER, SMALARD;



----- SYNONYMES ET VUES
--- vues
-- vues pour reunir les tables fragmentees
create view clients as
    select * from CLIENTSAMERIQUE
             where pays in ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie',
                                       'Bresil', 'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba',
                                       'Republique dominicaine', 'Dominique', 'Equateur', 'Etats-Unis', 'Grenade',
                                       'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaique', 'Mexique', 'Nicaragua',
                                       'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nieves', 'Sainte-Lucie',
                                       'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago',
                                       'Uruguay', 'Venezuela')
        union all
    select * from cgillier.clientsEuropeSud@LINKAMERIQUETOEUROPESUD
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
    select * from COMMANDESAMERIQUE
        union all
    select * from cgillier.commandesEuropeSud@LINKAMERIQUETOEUROPESUD
        union all
    select * from smalard.commandes_EN@LINKAMERIQUETOEUROPENORD
        union all
    select * from smalard.commandes_Autre@LINKAMERIQUETOEUROPENORD;

create view details_commandes as
    select * from DETAILS_COMMANDESAMERIQUE
        union all
    select * from cgillier.details_commandesEuropeSud@LINKAMERIQUETOEUROPESUD
        union all
    select * from smalard.details_Commandes_EN@LINKAMERIQUETOEUROPENORD
        union all
    select * from smalard.details_Commandes_Autre@LINKAMERIQUETOEUROPENORD;

create view stock as
    select * from STOCKAMERIQUE
        union all
    select * from cgillier.stockEuropeSud@LINKAMERIQUETOEUROPESUD
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
select * from CLIENTSAMERIQUE;
select * from COMMANDESAMERIQUE;
select * from DETAILS_COMMANDESAMERIQUE;
select * from STOCKAMERIQUE;

-- test des triggers
insert into DETAILS_COMMANDESAMERIQUE values(999, 80, 12.1, 4, 0);   -- cette ref_produit n'existe pas
insert into STOCKAMERIQUE values(80, 'Etats-Unis', 42, null, 0);     -- cette ref_produit n'existe pas
delete from EMPLOYES where NO_EMPLOYE = 1;                      -- cet employe a deja fait des commandes

-- tests des vues
select * from clients;
select * from commandes;
select * from details_commandes;
select * from stock;

-- tests des liens & synonymes
select * from produits;
select * from categories;
select * from fournisseurs;
