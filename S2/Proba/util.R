
binary <- function(x)
{
  if((x<2^31)&(x>=0))
    return( as.integer(intToBits(as.integer(x))) )
  else{
    if((x<2^32)&(x>0))
      return( c(binary(x-2^31)[1:31], 1) )
    else{
      cat('Erreur dans binary : le nombre etudie n est pas un entier positif en 32 bits.\n')
      return(c())
    }
  }
}

Frequency <- function(x,nb = 32){
  s <- rep(0,length(x))

  # Conversion en séquence de bits
  for(i in seq_along(x)){
    bSeq <- binary(x[i])[1:nb]
    s[i] <- sum(2 * bSeq[1:nb] - 1)
  }

  # Calcul de s_obs
  s_obs <- abs(sum(s))/sqrt(nb * length(x))

  p_value <- 2 * (1 - pnorm(s_obs))

  return (p_value)
}

Runs <- function(x , nb = 32){
  tau <- 2/(sqrt(nb*length(x)))
  bSeq <- c()

  # Pre-test
  for(i in seq_along(x)){
    # Concaténation de toutes les séquences de bits
    bSeq <- c(bSeq , binary(x[i])[1:nb])
  }

  pi <- sum(bSeq == 1)/length(bSeq)

  # Si le pretest échoue, on retourne p_value = 0
  if(abs(pi - 0.5) >= tau){
    return(0)
  }

  # Sinon on continue

  V_n <- sum(bSeq[-length(bSeq)] != bSeq[-1])
  V_n <- V_n + 1

  p_value <- 2*(1 - pnorm(abs(V_n - 2 * nb*length(x) * pi * (1-pi))/(2 * sqrt(nb*length(x)) * pi * (1-pi))))

  return(p_value)
}


