panel.cor.plot <-
function (x, y, ...) 
{
    points(x, y, pch = 46, ...)
    lw <- lowess(x, y)
    lines(lw, col = 2)
}
