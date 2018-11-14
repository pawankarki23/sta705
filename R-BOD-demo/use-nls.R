
t <- c(1,2,3,4,5,7)
y <- c(8.3,10.3,19.0,16, 15.6,19.8)

eta <- function(theta, t)
  {
  theta[1]*(1.0-exp(-theta[2]*t))
  }

theta0 <- c(theta1 =16.8, theta2 = 0.38)

# a non-linear model
o  <- nls(y ~ eta(c(theta1, theta2), t), start=theta0, trace=TRUE)

# dummy data so plots look smooth
P  <- data.frame(t=seq(1, 7, 0.1))
q  <- predict(o,interval="none",newdata=P)

# show the picture
plot(t, y, xlim=c(1, 7))
lines(P$t,q,col="blue")

