write.title.cell <-
function (title, r, c, cex = 1) 
{
    text(2 * c - 0.5, -r, title, cex = cex)
    rect((2 * (c - 1) + 0.5), -(r - 0.5), (2 * c + 0.5), -(r + 
        0.5))
}
