plotonevariable <-
function (fr, vari, group, xax, window = TRUE, ...) 
{
    newwindow(window)
    plot(xax, fr[2, vari, group, ], type = "l", bty = "n", ylim = range(fr[, 
        vari, group, ], na.rm = TRUE), ...)
    lines(xax, fr[3, vari, group, ], lty = 2)
    lines(xax, fr[1, vari, group, ], lty = 2)
    try(lines(xax, lowess(fr[2, vari, group, ])$y, , lty = 2, 
        col = 2, cex = 2))
}
