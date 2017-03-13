draw.title.cell <-
function (title, i, nr) 
{
    r <- get.r(i, nr)
    c <- get.c(i, nr)
    text(2 * c - 0.5, -r, title)
    rect((2 * (c - 1) + 0.5), -(r - 0.5), (2 * c + 0.5), -(r + 
        0.5))
}
