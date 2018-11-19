setwd('/Users/pawankarki/Desktop/sta705/homework10')
dyn.load("matrix.so")
m = 2
n = 3
# create memory for the result
result = vector(mode = "integer", length = m*n);
# get the value from the C program
result = .C("get_my_values", as.integer(m),as.integer(n), as.integer(result))

result_mat = matrix(result[[3]], ncol = n, byrow = TRUE)

print(result_mat)

