get_gtheta = function(theta)
{
  x1 = theta[1]
  x2 = theta[2]
  g_theta = c(-200*(x2-x1)-2*(1-x1),200*(x2-x1))
}

theta=c(-10, 10)
print(get_gtheta(theta))

# relate to Newton-Raphson presentation
get_H=function(theta)
{

  H = matrix(data = c(202,-200,-200,200), nrow = 2, ncol = 2, byrow = TRUE)
}

print(get_H(theta))

for(i in 1:10)
{
  print(theta)
  quad  = get_H(theta)
  print(quad)
  grad  = get_gtheta(theta)
  print(grad)
  if(max(abs(grad)) < 0.000001)
    break
  delta = solve(quad, -grad)
  print(delta)
  theta = theta+delta
}

print(theta)
