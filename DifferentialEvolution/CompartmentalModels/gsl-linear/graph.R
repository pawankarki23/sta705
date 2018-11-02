dat <- read.table("driver.dat")
m   <- max(dat[,-1])
plot(dat[,1],dat[,-1], type="l");

#plot(dat$time, dat$u, type="l", xlab="Time", ylab="Reading")

