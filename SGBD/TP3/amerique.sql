create  database link LinkAmToRyori
    connect to MROULIER identified by MDPORACLE
    using 'DB11';


CREATE TABLE employes AS SELECT * FROM  (select * from ryori.employes@LINKAMTORYORI);

select distinct pays from ryori.clients@LINKAMTORYORI;

create table clients as (select * from ryori.clients@LINKAMTORYORI
                                        where pays in ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil', 'Canada', 'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique', 'Equateur', 'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaique', 'Mexique', 'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nieves', 'Sainte-Lucie', 'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay', 'Venezuela'));


create table commandes as (select c.* from ryori.commandes@LINKAMTORYORI c
                            inner join clients on ( c.code_client = clients.CODE_CLIENT ));

create table detail_commandes as (select dc.*
                                      from ryori.details_commandes@LINKAMTORYORI dc
                                      inner join commandes on ( dc.no_commande = commandes.NO_COMMANDE ));

create table stock as (
    select *
    from ryori.stock@LINKAMTORYORI s
    where pays in ('Antigua-et-Barbuda', 'Argentine', 'Bahamas', 'Barbade', 'Belize', 'Bolivie', 'Bresil', 'Canada',
                   'Chili', 'Colombie', 'Costa Rica', 'Cuba', 'Republique dominicaine', 'Dominique', 'Equateur',
                   'Etats-Unis', 'Grenade', 'Guatemala', 'Guyana', 'Haïti', 'Honduras', 'Jamaique', 'Mexique',
                   'Nicaragua', 'Panama', 'Paraguay', 'Perou', 'Saint-Christophe-et-Nieves', 'Sainte-Lucie',
                   'Saint-Vincent-et-les Grenadines', 'Salvador', 'Suriname', 'Trinite-et-Tobago', 'Uruguay',
                   'Venezuela')
);






