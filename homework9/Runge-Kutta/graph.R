setwd('/Users/pawankarki/Desktop/sta705/homework9/Runge-Kutta')

dat  <- read.table("plot.dat", header=TRUE)
maxx <- max(dat[, 1])
maxy <- max(dat[,-1])
k    <- dim(dat)[2]
plot(c(0, maxx), c(0,maxy), type="n", xlab="Time", ylab="Amount")

pdf("hw9.pdf")

for(i in 2:(k-1))
  lines(dat[,1], dat[,i], col=i, lwd = 3)
legend('topleft', legend=c("Plasma", "Other"), col=2:(k-1), lty=1, cex=0.8,lwd = 3)

dev.off()