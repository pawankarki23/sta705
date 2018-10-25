dat <- read.table("Van-der-Pol.dat", header=TRUE)
plot(dat$time, dat$u, type="l", xlab="Time", ylab="Reading")

