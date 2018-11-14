# make four runs
source("BOD.R")
#theta <- c(20, 0.24)
theta <- c(19, 0.5)  # fairly close

for(i in 1:10)
  {
  print(theta)
  quad  = H.p(theta)  # try with H and H.p
  print(quad)
  grad  = g(theta)
  if(max(abs(grad)) < 0.000001)
    break
  delta = solve(quad, -grad)
  theta = theta+delta
  }
print(sprintf("residual ss = %.6f",f(theta)))

theta <- c(20, 0.24) # Bates & Watts
o <- optim(theta, f, g, method="BFGS",hessian=TRUE )
#  Broyden–Fletcher–Goldfarb–Shanno (BFGS)
print(o$hessian)

