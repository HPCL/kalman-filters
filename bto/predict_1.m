predict1
in
  A2 : matrix(row), A : matrix(row), xh : matrix(row), Q : matrix(row)
inout
  P : matrix(row), xhn : matrix(row)
{
  xhn = A2 * xh
  P = A * P * A' + Q
}

