write.cell <-
function (expr, r, c, cex = 1) 
{
    text(2 * c - 0.5, -r, expr, adj = c(0.5, 0.5), cex = cex)
    rect((2 * (c - 1) + 0.5), -(r - 0.5), (2 * c + 0.5), -(r + 
        0.5), border = "grey")
}
