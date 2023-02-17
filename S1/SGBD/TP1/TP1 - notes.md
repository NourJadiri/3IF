#### **Problème 1**
###### 1.1
```sql
-- capitale doit être une ville connue
alter table COUNTRY
add constraint fk_capitalCity
FOREIGN KEY (CAPITAL, CODE, PROVINCE)
references CITY(NAME, COUNTRY, PROVINCE); 
```
**Problème :** le nom des attributs n’est pas assez expressif (country.code et city.country representent la meme chose et pas country.name)

###### 1.2
```sql
-- pays doivent avoir des noms differents
alter table COUNTRY
add constraint pk_uniqueName
unique(NAME); 
```
**Problème :** la primary key existait déjà, cetait juste pour check

###### 1.3
```sql
-- nom pays doit être connu
alter table COUNTRY
add constraint nameNotNull
check(NAME is not null); 
```
**Problème :** aucun tout est bon (meme si cette contrainte était déjà check)

###### 1.4
```sql
-- capitale province doit être dans ville
alter table PROVINCE
add constraint fk_capitalProvince
FOREIGN KEY (CAPITAL, COUNTRY, NAME)
references CITY(NAME, COUNTRY, PROVINCE); 
```
**qui ne marche pas donc :**
```sql
alter table PROVINCE
add constraint fk_capitalProvince
FOREIGN KEY (NAME, COUNTRY, CAPPROV)
references CITY(NAME, COUNTRY, PROVINCE); 
```
**Problème :** clés parents introuvables pour la première version car les données ne vérifient pas la contrainte, faut juste faire gaffe à bien faire correspondre les attributs, et ici remplacer NAME par CAPPROV (problème de choix d'attributs)

###### 1.5
```sql
-- pays province doit être dans pays
alter table PROVINCE
add constraint fk_paysProvince
FOREIGN KEY (COUNTRY)
references COUNTRY(CODE);
```

###### 1.6
```sql
-- pays ville doit être dans pays
alter table CITY
add constraint fk_paysCity
FOREIGN KEY (COUNTRY)
references COUNTRY(CODE);
```

###### 1.7
```sql
-- province ville doit être dans province
alter table CITY
add constraint fk_provinceCity
FOREIGN KEY (PROVINCE, COUNTRY)
references PROVINCE(NAME, COUNTRY);
```

###### 1.8
```sql
-- longueur frontière doit être strictement positive
alter table BORDERS
add constraint positiveBorder
check (length > 0);
```

###### 1.9
```sql
-- coordonnées uniques pour chaque ville
alter table CITY
add constraint pk_coord
unique(latitude, longitude);
```
**Problème :** certaines cities overlapent (9 doublons), donc cette contrainte n'est pas applicable à cette base de données, on ne la considère juste pas
```sql
-- pour voir les doublons  
select c1.NAME, c1.COUNTRY, c2.NAME, c2.COUNTRY  
from CITY c1, CITY c2  
where c1.LATITUDE = c2.LATITUDE  
and c1.LONGITUDE = c2.LONGITUDE  
and c1.NAME < c2.NAME;
```

#### **Problème 1**
###### 2.1
**Problème :** si on fait un insert lambda, sans rien modifier, alors on aura des violations de contrainte, car par exemple, la capitale n'existe pas dans `CITY`. Pour remédier à ça, trois solutions s'offrent à nous :
1. On disable une par une les contraintes et on les re-enable progressivement pour ajouter un à un les tuples dans les trois tables `PROVINCE`, `CITY` et `COUNTRY`, **MAIS** c'est pas bien de jouer avec le feu comme ça. Imaginons qu'on est plusieurs à travailler sur la même base en même temps, certains pourraient ajouter/modifier des tuples sans que les contraintes les vérifient.
2. On crée un pays avec des valeurs `NULL` là où ca pose problème (capitale, province et ville) -- ça peut être la seule solution possible si on n'a pas les accès aux contraintes 
3. On défère les contraintes au moment de l'insertion -- c'est la *best* solution (si on est admin évidemment). Pour ça, on crée les contraintes en déférable, mais par défaut on laisse en *verification effective immediately* (le prof préfère ça). **Sauf que** évidemment si on fait juste ça en rajoutant la ligne `deferrable ...` ça ne marchera pas parce que les contraintes existent déjà, elles ne seront donc pas updated. 
	1. soit on drop les constraints une à une pour les recréer comme on veut en faisant juste un truc comme : `alter table COUNTRY drop constraint fk_capitalCity`
	2. soit on est prévoyants, et on se dit qu'on aura ptet besoin de la version initiale des contraintes plus tard. La meilleure solution c'est donc de créer une version v2 en rajouter le `deferrable ...`  , puis de desable la version initiale. (si on a besoin de se servir de la version 1, on peut alors juste enable v1 et desable v2 :))

btw, pour les données qu'on ne connaît pas (latitude, longitude et élévation, on met bien évidemment en Et pour les latitude, longitude et elevation qui sont pas données, on met juste en `NULL`.
*finalement*, ça donne un truc du style :
```sql
-- un exemple de "update" d'une contrainte
-- capitale doit être une ville connue
alter table COUNTRY
add constraint fk_capitalCity
FOREIGN KEY (CAPITAL, CODE, PROVINCE)
references CITY(NAME, COUNTRY, PROVINCE); 

-- pour insertion d'un nouveau pays  
alter table COUNTRY  
add constraint fk_capitalCity2  
FOREIGN KEY (CAPITAL, CODE, PROVINCE)  
references CITY(NAME, COUNTRY, PROVINCE)  
deferrable initially immediate;

alter table COUNTRY  
disable constraint fk_capitalCity;

-- et puis l'insertion en elle meme du pays
set constraints fk_capitalCity2, fk_capitalProvince2, fk_paysProvince2, fk_provinceCity2, fk_paysCity2 deferred;  
  
insert into COUNTRY (NAME, CODE, CAPITAL, PROVINCE, AREA, POPULATION)  
values ('Bascrit', 'BC', 'Demoi', 'Bascrit', 1250, 1250000);  
  
insert into PROVINCE(name, country, population, area, capital, capprov)  
values ('Bascrit', 'BC', 1250000, 1250, 'Demoi', 'Bascrit');  
  
insert into CITY(name, country, province, population, latitude, longitude, elevation)  
values ('Demoi', 'BC', 'Bascrit', 1250000, null, null, null);  
commit;
```

###### 2.2
```sql
-- liste par ordre alphabetique des pays  
select NAME  
from COUNTRY  
order by NAME;
```
<img width="291" alt="Capture d’écran 2022-11-21 à 21 33 43" src="https://user-images.githubusercontent.com/100949054/203164576-6a1892da-5660-4480-89df-8115fd5330a0.png">

###### 2.3
```sql
-- orga plus grand nombre de membres  
select m.ORGANIZATION, o.NAME, COUNT(*)  
from ISMEMBER m, ORGANIZATION o  
where m.ORGANIZATION = o.ABBREVIATION  
    group by ORGANIZATION, NAME  
    having count(*) = (  
        select max(count(*))  
        from ISMEMBER  
        group by ORGANIZATION  
    );
```
<img width="593" alt="Capture d’écran 2022-11-21 à 21 37 10" src="https://user-images.githubusercontent.com/100949054/203164644-4160bd85-60f9-4727-a914-23755800ae00.png">

**Problème :** bien faire gaffe parce que dans la table isMember on n'a pas le nom complet de l'orga, alors qu'on demande son abbreviation + nom complet **ET** on n'oublie pas de mettre les attributs du `SELECT` dans le `GROUP BY`!!!

###### 2.4
```sql
-- liste pays par ordre pourcentage population  
select p.NAME, (sum(v.POPULATION/p.POPULATION))*100 as pourcentage  
from COUNTRY p, CITY v  
where p.CODE = v.COUNTRY  
group by p.CODE, p.NAME  
having (sum(v.POPULATION/p.POPULATION))*100 is not null  
order by pourcentage;
```
<img width="714" alt="Capture d’écran 2022-11-21 à 21 48 02" src="https://user-images.githubusercontent.com/100949054/203164701-d6d65dd3-9361-42f2-8208-dedabf2eced7.png">

**Problème :** pour gérer les nuls, on a tout simplement enlever les résultats pour lesquels ça donnait du null (et encore une fois faire gaffe entre `CODE` et `NAME`) ((et d'ailleurs on avait 245 pays alors que là on n'a que 214 résultats ce qui montre bien qu'on avait des null))

###### 2.5
```sql
-- liste continents ordre croissant pop  
select c.NAME, sum(p.POPULATION) as pop  
from CONTINENT c, COUNTRY p, ENCOMPASSES e  
where p.code = e.COUNTRY  
and c.NAME = e.CONTINENT  
group by c.NAME  
order by pop;
```
<img width="323" alt="Capture d’écran 2022-11-21 à 21 54 55" src="https://user-images.githubusercontent.com/100949054/203164764-3776409c-7cac-49fd-879f-c705ad981356.png">

**Problème :** same thing on n'oublie pas de mettre les attributs du `SELECT` dans le `GROUP BY` :)

###### 2.6
```sql
-- pays avec plus longue frontière  
select c.NAME, sum(LENGTH) as frontière  
from BORDERS b, COUNTRY c  
where c.CODE = b.COUNTRY1 or c.CODE = b.COUNTRY2  
group by c.NAME  
having sum(length) = (  
    select max(sum(LENGTH))  
    from BORDERS b, COUNTRY c  
    where c.CODE = b.COUNTRY1 or c.CODE = b.COUNTRY2  
    group by c.NAME  
    );
```
<img width="285" alt="Capture d’écran 2022-11-21 à 22 11 54" src="https://user-images.githubusercontent.com/100949054/203164801-e174f527-b2b9-4d22-8f48-5e8440c480d8.png">

**Problème :** déjà faire gaffe à bien renommer les tables dans les requêtes imbriquées si jamais on veut (ré)utiliser les abréviations. Ensuite, il faut bien mettre `COUNTRY1` OU `COUNTRY2` dans les requetes pour bien avoir toutes les frontières d'un même pays

###### 2.7
```sql
-- villes qui sont dans plusieurs pays  
select NAME, count(*) as apparition  
from CITY  
group by NAME  
having count(*) > 1  
order by apparition desc, NAME;
```
<img width="327" alt="Capture d’écran 2022-11-21 à 22 19 52" src="https://user-images.githubusercontent.com/100949054/203164869-381b3c11-304d-4631-a10c-ff7726bb00d4.png">

###### 2.8
```sql
-- pays dont on ne connait pas la date d'independance  
select COUNTRY.NAME, CODE  
from COUNTRY, POLITICS  
where POLITICS.INDEPENDENCE is null  
and CODE = POLITICS.COUNTRY;
```
<img width="398" alt="Capture d’écran 2022-11-22 à 20 06 54" src="https://user-images.githubusercontent.com/100949054/203401567-5de3715f-d3d8-4fc8-8e94-c05ccaa26374.png">


###### 2.9
```sql
-- pays membre d'aucune orga  
select NAME, CODE  
from COUNTRY  
minus  
(select NAME, CODE  
 from ISMEMBER, COUNTRY  
 where COUNTRY = CODE  
 and ORGANIZATION is not null);
```
<img width="302" alt="Capture d’écran 2022-11-21 à 22 29 10" src="https://user-images.githubusercontent.com/100949054/203164957-b23742aa-4da4-4b69-8a5e-1d32d664f806.png">
