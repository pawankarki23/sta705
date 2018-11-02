dat <- matrix(scan(file="param-set-0.dat"), byrow=TRUE, ncol=4)
plot(c(0,2.5), c(0,1.5), type="n", xlab="time", ylab="amount")
lines(dat[,1], dat[,2],col="red")
lines(dat[,1], dat[,3],col="blue")
lines(dat[,1], dat[,4],col="green")

