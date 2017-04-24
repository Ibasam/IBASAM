make.table <-
function (nr, nc, titles = "") 
{
    plot(c(0, nc * 2 + 1), c(0, -(nr + 1)), type = "n", xlab = "", 
        ylab = "", axes = FALSE)
    text(nc + 0.5, 0, cex = 1.2, titles)
}
