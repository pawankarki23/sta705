dat  <- read.table("plot.dat", header=TRUE)
maxx <- max(dat[, 1])
maxy <- max(dat[,-1])
k    <- dim(dat)[2]
plot(c(0, maxx), c(0,maxy), type="n", xlab="Time", ylab="Amount")
for(i in 2:k)
  lines(dat[,1], dat[,i])

