write.data.frame <-
function (dataf, nmaxrow = 50, titles = "") 
{
    savepar <- par(mar = rep(0, 4), pty = "m")
    nc <- ncol(dataf)
    nrt <- nrow(dataf)
    if (nrt > nmaxrow) {
        mf <- TRUE
        nit <- ifelse(nrt%%nmaxrow > 0, (nrt%/%nmaxrow) + 1, 
            nrt%/%nmaxrow)
        nnr <- c(rep(nmaxrow, (nrt%/%nmaxrow)), nrt%%nmaxrow)
        ntr <- c(0, (1:(nrt%/%nmaxrow)) * nmaxrow, nrt)
    }
    else {
        mf <- FALSE
        nit <- 1
        nnr <- nrt
        ntr <- c(0, nrt)
    }
    for (it in 1:nit) {
        nr <- nnr[it]
        cext <- ifelse(nr < 30, 1, 30/nr)
        tits <- colnames(dataf)
        selrows <- (ntr[it] + 1):(ntr[it + 1])
        rows <- rownames(dataf)[selrows]
        make.table(nr + 1, nc + 1, titles)
        i <- 1
        for (nt in tits) {
            i <- i + 1
            write.title.cell(nt, 1, i, cext)
        }
        i <- 1
        for (nrw in rows) {
            i <- i + 1
            write.title.cell(nrw, i, 1, cext)
        }
        for (r in 1:nr) {
            for (c in 1:nc) {
                write.cell(dataf[selrows[r], c], r + 1, c + 1, 
                  cext)
            }
        }
    }
    par(savepar)
}
