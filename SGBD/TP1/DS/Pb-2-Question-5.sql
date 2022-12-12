with
  -- on trouve les villes avec le plus d'apparitions
    villeMaxOccurence as (
        select name , count(NAME)
        from CITY
        group by name
        having count(name) in (select max(count(name))
                               from CITY
                               group by name)
        order by name) ,
  -- on cherche les pays dans lesquels ces villes apparaissent
    countryVilleMaxOccurence as (
        select villeMaxOccurence.* , city.COUNTRY , POPULATION
        from villeMaxOccurence , CITY
        where villeMaxOccurence.name = city.name and POPULATION is not null
        order by villeMaxOccurence.NAME) ,
  -- ensuite on les filtre pour avoir que des noms uniques
    uniqueCities as (
        select distinct name
        from countryVilleMaxOccurence
        order by NAME
    )
    -- autojointure entre uniqueCities et countryVilleMaxOccurence et trouver la ou la population est maximale
    select * from uniqueCities;

