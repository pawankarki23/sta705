setwd('/Users/pawankarki/Desktop/sta705/C++_from_R_src')

dyn.load("Convolve.so")

# wrapper to set the lengths using the C library
lengths <- function(na, nb)
  {
  .C("setup", as.integer(length(a)),
                              as.integer(length(b)))
  sprintf("For vectors of length %d and %d.\n", na, nb)
  }

# wrapper to do the calculation using the C library
convolution <- function(a, b)
  {
  ab <- rep(0.0, length(a)+length(b)-1)
  r  <- .C("evaluate", as.numeric(a), as.numeric(b),
                                      as.numeric(ab))
  r[[3]]
  }

a <- rep(1,6)/6.0
b <- a

# setup the lengths for vector
lengths(length(a), length(b))

# do the calculation
ab <- convolution(a, b)

# print the results
print(a)
print(b)
dist <- data.frame(values = 2:12, probs = ab)
print(dist)

