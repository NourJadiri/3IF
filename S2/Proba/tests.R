# IMPORTS :
install.packages("randtoolbox")
source("C:\\Users\\Nour\\OneDrive - INSA Lyon\\Documents\\Cours\\3A\\3IF\\S2\\Proba\\generators.R")
source("C:\\Users\\Nour\\OneDrive - INSA Lyon\\Documents\\cours\\3A\\3IF\\S2\\Proba\\util.R")
source("C:\\Users\\Nour\\OneDrive - INSA Lyon\\Documents\\cours\\3A\\3IF\\S2\\Proba\\files_d_attente.R")
library(randtoolbox)

########################################################################################################

# Simple test visuel par historgramme de la distribution des valeurs renvoyées par les générateurs
test_visuel <- function(k) {
  par(mfrow = c(2,2))
  hist(RANDU(graine = 215, n = k) , xlab = "Valeur" , ylab = "fréquence" , main = "RANDU")
  hist(standardMinimal(graine = 215 , n = k) , xlab = "Valeur" , ylab = "fréquence" , main = "Standard Minimal")
  hist(VonNeumann(n = k , graine = 215), main = "Von Neumann")
  hist(MersenneTwister(n = k, graine = 215), main = "Mersenne-Twister")
}

# Tracage de S(n) = f(S(n-1))
tracage <- function(){
  n <- 100
  u_RANDU <- RANDU(graine = 215, n =100)
  u_SM <- standardMinimal(graine = 215, n =100)
  u_VonNeumann <- VonNeumann(n = 100, graine = 215)
  u_MersenneTwister <- MersenneTwister(n = 100 , graine = 215)


  plot(u_RANDU[1:(n-1)] , u_RANDU[2:n] , xlab = "S(n-1)" , ylab = "(S_n)", main = "RANDU")
  plot(u_SM[1:(n-1)] , u_SM[2:n] , xlab = "S(n-1)" , ylab = "(S_n)" , main = "Standard Minimal")
  plot(u_VonNeumann[1:(n-1)] , u_VonNeumann[2:n] , xlab = "S(n-1)" , ylab = "(S_n)", main = "von Neumann")
  plot(u_MersenneTwister[1:(n-1)] , u_MersenneTwister[2:n] , xlab = "S(n-1)" , ylab = "(S_n)" , main = "Mersenne-Twister")
}

test_frequence <- function(seeds){
  freq_RANDU <- NULL
  freq_SM <- NULL
  freq_VonNeumann <- NULL
  freq_MersenneTwister <- NULL

  # On parcourt le vecteur de seeds
  for(i in seq_along(seeds)){
    # Pour chaque graine, on génère une séquence
    u_RANDU <- RANDU(graine = seeds[i], n = 200)
    u_SM <- standardMinimal(graine = seeds[i] , n = 200)
    u_VonNeumann <- VonNeumann(graine = seeds[i] , n = 200)[,1]
    u_MersenneTwister <- MersenneTwister(graine = seeds[i] , n = 200)[,1]

    # Ensuite on rajoute la p-valeur retournée par la séquence du générateur correspondant dans le vecteur correspondant
    freq_RANDU <- c(freq_RANDU,Frequency(u_RANDU , 31))
    freq_SM <- c(freq_SM,Frequency(u_SM , 31))
    freq_VonNeumann <- c(freq_VonNeumann,Frequency(u_VonNeumann , 14))
    freq_MersenneTwister <- c(freq_MersenneTwister,Frequency(u_MersenneTwister))
  }

  # On retourne une liste comportant les résultats de tous les générateurs
  return (list(RANDU = freq_RANDU, SM = freq_MersenneTwister, VN = freq_VonNeumann , MT = freq_MersenneTwister))
}



test_runs <- function(seeds){
  runs_RANDU <- NULL
  runs_SM <- NULL
  runs_VonNeumann <- NULL
  runs_MersenneTwister <- NULL

  for(i in seq_along(seeds)){
    # Pour chaque graine, on génère une séquence
    u_RANDU <- RANDU(graine = seeds[i], n = 200)
    u_SM <- standardMinimal(graine = seeds[i] , n = 200)
    u_VonNeumann <- VonNeumann(graine = seeds[i] , n = 200)[,1]
    u_MersenneTwister <- MersenneTwister(graine = seeds[i] , n = 200)[,1]

    runs_RANDU <- c(runs_RANDU,Runs(u_RANDU , 31))
    runs_SM <- c(runs_SM,Runs(u_SM , 31))
    runs_VonNeumann <- c(runs_VonNeumann,Runs(u_VonNeumann , 14))
    runs_MersenneTwister <- c(runs_MersenneTwister,Runs(u_MersenneTwister))
  }

  return(list(RANDU = runs_RANDU, SM = runs_SM, VN = runs_VonNeumann, MT = runs_MersenneTwister))
}

test_order <- function(seeds){
  order_RANDU <- NULL
  order_SM <- NULL
  order_VonNeumann <- NULL
  order_MersenneTwister <- NULL

  for(i in seq_along(seeds)){
    # Pour chaque graine, on génère une séquence
    u_RANDU <- RANDU(graine = seeds[i], n = 200)
    u_SM <- standardMinimal(graine = seeds[i] , n = 200)
    u_VonNeumann <- VonNeumann(graine = seeds[i] , n = 200)[,1]
    u_MersenneTwister <- MersenneTwister(graine = seeds[i] , n = 200)[,1]

    order_RANDU <- c(order_RANDU,order.test(u_RANDU , d = 4, echo = FALSE)$p.value)
    order_SM <- c(order_SM,order.test(u_SM , d = 4, echo = FALSE)$p.value)
    order_VonNeumann <- c(order_VonNeumann,order.test(u_VonNeumann , d = 4, echo = FALSE)$p.value)
    order_MersenneTwister <- c(order_MersenneTwister,order.test(u_MersenneTwister , d = 4, echo = FALSE)$p.value)
  }

  return (list(RANDU = order_RANDU, SM = order_SM, VN = order_VonNeumann, MT = order_MersenneTwister))
}
