setwd('/Users/pawankarki/Desktop/sta705/homework8/gsl-linear')

dat  <- read.table("driver.dat", header=FALSE)
maxx <- max(dat[, 1])
maxy <- max(dat[,-1])
k    <- dim(dat)[2]

pdf("hw8.pdf")

plot(c(0, maxx), c(0,maxy), type="n", xlab="Time", ylab="Amount")
for(i in 2:k)
  lines(dat[,1], dat[,i], col=i, lwd=3)

legend('topleft', legend=c("Plasma", "Other", "Exterior"), col=2:k, lty=1, cex=0.8,lwd = 3)

dev.off()