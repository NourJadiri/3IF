FileMM1 <- function(lambda, mu, D){

  arrivees <- generate_arrivees(lambda , D)

  # de la meme maniere, on génère l'heure de départ du premier client
  depart1 <- arrivees[1] + rexp(1,mu)
  departs <- c()
  departs<- c(departs, depart1)

  for(i in 2:length(arrivees)) {
    # Deux cas possibles : le client arrive lorsqu'il n'y a personne, dans ce cas son heure de départ vaut arrivée + le temps de traitement par le magasin
    # le client arrive et il y a la queue : son heure de départ vaut l'heure de départ du client juste devant lui dans la queue + le temps de traitement de sa demande par le magasin
    departs <- c(departs , max(arrivees[i],departs[i-1]) + rexp(1,mu))

    # Si le service ferme, on garde les gens prisonniers
    if(departs[i] > arrivees[1] + D){
      departs <- departs[-length(departs)]
      break
    }

  }

  ma_liste <- list(arr = arrivees, dep = departs)

  return (ma_liste)

}

generateFileMM1 <- function(duration){
  ma_liste1 <- FileMM1(10,20,duration)
  ma_liste2 <- FileMM1(14,20,duration)
  ma_liste3 <- FileMM1(20,20,duration)
  ma_liste4 <- FileMM1(30,20,duration)

  return(list(test1 = ma_liste1, test2 = ma_liste2, test3 = ma_liste3, test4 = ma_liste4))
}

evolution_nb_clients <- function(arrivees , departs){
  #on crée deux data frame qui contiennent les heures d'arrivées et de départs de clients ainsi qu'un tag valant -1 si l'horaire correspond à une heure de départ et 1 si elle correspond à une heure d'arrivée
  a_df <- data.frame(Temps = arrivees, Tag = rep(1,length(arrivees)))
  d_df <- data.frame(Temps = departs, Tag = rep(-1,length(departs)))

  # On concatene ces deux data frame
  timeline <- rbind(a_df, d_df)

  # On trie le data frame dans l'ordre croissant et on fait une somme cumulée des tags. Cela représente le nombre de clients dans la file à chaque arrivée de client.
  timeline <- timeline[order(timeline$Temps), ]
  timeline$nb_clients <- cumsum(timeline$Tag)

  return (timeline)
}

temps_presence <- function(arrivee, depart) {
  delta <- c()
  for(i in seq_along(depart)) {
    delta <- c(delta, depart[i]-arrivee[i])
  }
  return(mean(delta))
}

compare_nb_clients <- function(liste_de_files){

  df1 <- evolution_nb_clients(liste_de_files$test1$arr, liste_de_files$test1$dep)
  df2 <- evolution_nb_clients(liste_de_files$test2$arr, liste_de_files$test2$dep)
  df3 <- evolution_nb_clients(liste_de_files$test3$arr, liste_de_files$test3$dep)
  df4 <- evolution_nb_clients(liste_de_files$test4$arr, liste_de_files$test4$dep)

  plot(df1$Temps, df1$nb_clients, type ='p' , col = "black" , xlab = "time" , ylab = "nb_clients" , main = "Evolution du nombre de clients en attente 10 arrivées/heure")
  plot(df2$Temps, df2$nb_clients, type ='p' , col = "black" , xlab = "time" , ylab = "nb_clients" , main = "Evolution du nombre de clients en attente 14 arrivées/heure")
  plot(df3$Temps, df3$nb_clients, type ='p' , col = "black" , xlab = "time" , ylab = "nb_clients" , main = "Evolution du nombre de clients en attente 20 arrivées/heure")
  plot(df4$Temps, df4$nb_clients, type ='p' , col = "black" , xlab = "time" , ylab = "nb_clients" , main = "Evolution du nombre de clients en attente 30 arrivées/heure")

  return (list(lambda10 = df1 , lambda14 = df2, lambda20 = df3, lambda30 = df4))
}

generate_means <- function(testLittle){
  mean1 <- weighted.mean(testLittle$lambda10$nb_clients, w = c(0,diff(testLittle$lambda10$Temps)))
  mean2 <- weighted.mean(testLittle$lambda14$nb_clients, w = c(0,diff(testLittle$lambda14$Temps)))
  mean3 <- weighted.mean(testLittle$lambda20$nb_clients, w = c(0,diff(testLittle$lambda20$Temps)))
  mean4 <- weighted.mean(testLittle$lambda30$nb_clients, w = c(0,diff(testLittle$lambda30$Temps)))

  return (c(mean1,mean2,mean3,mean4))
}

generate_average_duration <- function(liste_de_files){
  Ew1 <- temps_presence(liste_de_files$test1$arr, liste_de_files$test1$dep)
  Ew2 <- temps_presence(liste_de_files$test2$arr, liste_de_files$test2$dep)
  Ew3 <- temps_presence(liste_de_files$test3$arr, liste_de_files$test3$dep)
  Ew4 <- temps_presence(liste_de_files$test4$arr, liste_de_files$test4$dep)

  return (c(Ew1 , Ew2 , Ew3 , Ew4))
}

collect_results <- function(means, average_wait_times){
  results <- data.frame( En = means, Ew = average_wait_times , lambda = c(10 , 14 , 20 , 30))
  results$LittleFormula <- results$lambda * results$Ew
  results$Ecart_Relatif <- abs((results$En - results$LittleFormula)/results$En)

  return (results)
}

FileMM2 <- function(lambda, mu, D){

  arrivees <- generate_arrivees(lambda, D)

  departs <- c(arrivees[1] + rexp(1,mu) , arrivees[2] + rexp(1 ,mu))

  for(i in 3:length(arrivees)){
    # Plusieurs cas sont possibles:
      # Si le client arrive et que au moins un des serveurs est libre, alors son traitement se fait automatiquement ( arrivees[i] + rexp(1,mu) )
      # Si les deux serveurs sont occupés, le client attend le premier serveur qui se libère ( min(departs[i-1],departs[i-2]) + rexp(1,mu) )
    # On prend le max de ces deux possibilités
    departs[i] <- max(arrivees[i],min(departs[i-1],departs[i-2])) + rexp(1,mu)

    if(departs[i] > arrivees[1] + D){
      departs <- departs[-length(departs)]
      break
    }
  }

  return (list(arr = arrivees,dep = departs))
}

generateFileMM2 <- function(duration){
  ma_liste1 <- FileMM1(10,20,duration)
  ma_liste2 <- FileMM1(14,20,duration)
  ma_liste3 <- FileMM1(20,20,duration)
  ma_liste4 <- FileMM1(30,20,duration)

  return(list(test1 = ma_liste1, test2 = ma_liste2, test3 = ma_liste3, test4 = ma_liste4))
}


generate_arrivees <- function(lambda, D){
  arrivees <- rexp(1, lambda)

  fin <- arrivees[1] + D

  it <- 2
  # tant que l'heure d'arrivée du dernier client est inférieur à fin on rajoute une valeur d'heure d'arrivée qui correspond à l'heure d'arrivée du client précédent + une valeur générée par la loi exponentionnel
  while(arrivees[length(arrivees)] < fin )
  {
    arrivees <- c(arrivees, arrivees[it-1] + rexp(1,lambda))
    it <- it + 1
  }

  arrivees <- arrivees[-length(arrivees)]

  return (arrivees)
}