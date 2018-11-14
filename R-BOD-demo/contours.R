
source("BOD.R")
par(ask=TRUE)

x <- c(16.8, 0.38)
o <- optim(x, f, g, method="BFGS",hessian=TRUE )

# fq = function quadratic
# x  = varialbe
# x0 = provisional value
fq <- function(x, x0)
  {
  d <- x - x0
  f(x0) + sum(g(x0)*d) + 0.5*t(d) %*% H(x0) %*% d
  }

fq.p <- function(x, x0)
  {
  d <- x - x0
  f(x0) + sum(g(x0)*d) + 0.5*t(d) %*% H.p(x0) %*% d
  }

# make grid for contours
m  <- length(x1)
n  <- length(x2)
z  <- matrix(rep(0,m*n), ncol=n)
zq <- z
for(i in 1:m)
  for(j in 1:n)
    z[i,j]  <- f(c(x1[i],x2[j]))

GN <- TRUE
#GN <- FALSE # GaussNewton false
x <- c(20, 0.24) # Bates @ Watts
#x <- c(21, .6)
for(i in 1:3)
  {
  contour(x1, x2, z,  levels=values, xlim=range1, ylim=range2)
  points(o$par[1], o$par[2], col="red", pch=16, xlim=range1, ylim=range2)
  points(x[1],x[2],col="green",  pch=16, xlim=range1, ylim=range2)
  gr    <- g(x)
  level <- c(f(x))
  if(max(abs(gr)) < 0.000001) break;
  if(GN)
    {
    for(i in 1:m)
      for(j in 1:n)
        zq[i,j] <- fq.p(c(x1[i],x2[j]), x)
    x <- x - solve(H.p(x), gr)
    }
  else
    {
    for(i in 1:m)
      for(j in 1:n)
        zq[i,j] <- fq(c(x1[i],x2[j]),x)
    x <- x - solve(H(x), gr)
    }
  contour(x1, x2, zq, levels=level, col="blue", xlim=range1, ylim=range2, add=TRUE)
  points(x[1],x[2],   pch=16,         col="blue", xlim=range1, ylim=range2)
  }
#print(o)

