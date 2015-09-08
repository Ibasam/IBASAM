draw.plotmath.cell <-
function (expr, i, nr, string = NULL) 
{
    r <- get.r(i, nr)
    c <- get.c(i, nr)
    if (is.null(string)) {
        string <- deparse(expr)
        string <- substr(string, 12, nchar(string) - 1)
    }
    text((2 * (c - 1) + 1), -r, string, col = "grey")
    text((2 * c), -r, expr, adj = c(0.5, 0.5))
    rect((2 * (c - 1) + 0.5), -(r - 0.5), (2 * c + 0.5), -(r + 
        0.5), border = "grey")
}
