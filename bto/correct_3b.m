correct3b
in
  temp : matrix(row), P : matrix(row), C : matrix(row)
out
  K : matrix(row)
{
  K = P*C'*temp
}

