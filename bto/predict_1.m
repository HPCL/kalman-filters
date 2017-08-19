predict1
in
  A : matrix(row), xh : matrix(row), Y : matrix(row)
inout
  xhn : matrix(row)
{
  xhn = A * xh +Y
}

