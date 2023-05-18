# Fonction qui simule un générateur générique basé sur la congruence linéaire
congruenceLineaire <- function(graine , a , b , m , n){
  seed <- rep(graine,n)

  for(i in 2:n){
    seed[i] <- (a*seed[i-1] + b)%%m
  }

  return (seed)
}

# générateur RANDU
RANDU <- function(graine = 69420 , n){
  a <- 65539
  b <- 0
  m <- 2^31
  return (congruenceLineaire(graine, a , b , m , n))
}

# Générateur Standard Minimal
standardMinimal <- function(graine = 69420, n){
  a <- 16807
  b <- 0
  m <- 2^31 - 1

  return (congruenceLineaire(graine , a , b , m , n))
}

# Générateur de Von Neumann
VonNeumann <- function(n, p=1, graine)
{
  x <-  rep(graine,n*p+1)
  for(i in 2:(n*p+1))
  {
    numbers <- strsplit(format(x[i-1]^2,scientific=FALSE),'')[[1]]
    while(length(numbers)>4){
      numbers <- numbers[2:(length(numbers)-1)]
    }
    x[i] <- as.numeric(numbers)%*%(10^seq(length(numbers)-1,0,-1))
  }
  x <- matrix(x[2:(n*p+1)],nrow=n,ncol=p)
  return(x)
}

# Générateur de MersenneTwister
MersenneTwister <- function(n, p=1, graine)
{
  set.seed(graine,kind='Mersenne-Twister')
  x <- sample.int(2^32-1,n*p)
  x <- matrix(x,nrow=n,ncol=p)
  return(x)
}