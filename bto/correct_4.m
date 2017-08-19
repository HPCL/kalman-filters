correct4
in
  xhn : matrix(row), K : matrix(row), y : matrix(row), C : matrix(row), I : matrix(row)
inout
  P : matrix(row)
out
  xh : matrix(row)
{
  xh = xhn + K * (y - C * xhn)
  P = (I - K * C) * P
}

