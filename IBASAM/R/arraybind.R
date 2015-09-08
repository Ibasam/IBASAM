arraybind <-
function (x, y = NULL) 
{
    if (!is.null(y)) {
        y <- as.vector(unlist(y))
        tm <- c(as.vector(x), y)
        dix <- dim(x)
        dit <- dix
        w <- length(dix)
        dit[w] <- dix[w] + 1
        if (length(y) < prod(dit[-w])) 
            warning("Recycling x at the end of arraybind(x,y)")
        if (length(y) > prod(dit[-w])) 
            warning("Cutting y at the end of arraybind(x,y)")
        tm <- array(tm, dim = dit)
        return(tm)
    }
    else {
        return(x)
    }
}
