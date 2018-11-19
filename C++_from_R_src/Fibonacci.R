
setwd('/Users/pawankarki/Desktop/sta705/C++_from_R_src')
dyn.load("Fibonacci.so")

n      <- 10
# create memory for the result
f      <- vector(mode = "integer", length = n);
# f    <- rep(0, n)   # this would also work
result <- .C("Fibonacci", as.integer(n), as.integer(f))
# result contains a list with an element for
# each argument
print( result[[2]] )

