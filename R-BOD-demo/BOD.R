# The BOD data has the biochemical oxygen demand versus time 
# in an evaluation of water quality.
# Bates, D.M. and Watts, D.G. (1988), Nonlinear Regression Analysis and
# Its Applications, Wiley, Appendix A1.4.
# Originally from Marske (1967), Biochemical Oxygen Demand Data Interpretation
# Using Sum of Squares Surface M.Sc. Thesis, University of Wisconsin – Madison.

t <- c(1,2,3,4,5,7)
y <- c(8.3,10.3,19.0,16, 15.6,19.8)

x1     <- seq(10, 30, by=0.1)
x2     <- seq(0, 1.5, by=0.05 )
range1 <- c(min(x1),max(x1))
range2 <- c(min(x2),max(x2))
values <- c(30, 60, 95, 130, 200)


eta <- function(theta)
  {
  theta[1]*(1.0-exp(-theta[2]*t))
  }

# first derivate of eta
d1eta <- function(theta)
  {
  1.0-exp(-theta[2]*t)
  }

d2eta <- function(theta)
  {
  theta[1]*t*exp(-theta[2]*t)
  }

# objective function
f <- function(theta)
  {
  sum((y-eta(theta))^2)
  }

# gradient vector
g <- function(theta)
  {
  V <- cbind(d1eta(theta), d2eta(theta)) # Jacobian matrix
  as.vector(-2*t(V) %*% (y-eta(theta)))
  }

# relate to Newton-Raphson presentation (Hassian matrix)
H <- function(theta)
  {
  res <- y - eta(theta)
  d   <- sum(res*t*exp(-theta[2]*t))             # h12 and h21 (see notes for the expression) res is residuals
  e   <- sum(-res*theta[1]*t^2*exp(-theta[2]*t)) # h22
  V   <- cbind(d1eta(theta), d2eta(theta))       # Jacobian
  H   <- 2*t(V) %*% V - 2*matrix(c(0, d, d, e), ncol=2) # t() is taking the transpose
  H
  }

# like above with 2nd derivative terms omitted, i.e. Gauss-Newton
H.p <- function(theta)
  {
  V   <- cbind(d1eta(theta), d2eta(theta))
  H   <- 2*t(V) %*% V
  H
  }

theta <- c(20, 0.24) # Bates & Watts starting value (see slides)
print(g(theta))
print(H(theta)/2)
print(H.p(theta)/2)

