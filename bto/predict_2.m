predict2
in
  A : matrix(row), Q : matrix(row)
inout
  P : matrix(row)
{
  P = A * P * A' + Q
}
