\name{write.data.frame}
\alias{write.data.frame}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
write.data.frame
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
write.data.frame(dataf, nmaxrow = 50, titles = "")
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{dataf}{
%%     ~~Describe \code{dataf} here~~
}
  \item{nmaxrow}{
%%     ~~Describe \code{nmaxrow} here~~
}
  \item{titles}{
%%     ~~Describe \code{titles} here~~
}
}
\details{
%%  ~~ If necessary, more details than the description above ~~
}
\value{
%%  ~Describe the value returned
%%  If it is a LIST, use
%%  \item{comp1 }{Description of 'comp1'}
%%  \item{comp2 }{Description of 'comp2'}
%% ...
}
\references{
%% ~put references to the literature/web site here ~
}
\author{
Cyril Piou
}
\note{
%%  ~~further notes~~
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
%% ~~objects to See Also as \code{\link{help}}, ~~~
}
\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function (dataf, nmaxrow = 50, titles = "") 
{
    savepar <- par(mar = rep(0, 4), pty = "m")
    nc <- ncol(dataf)
    nrt <- nrow(dataf)
    if (nrt > nmaxrow) {
        mf <- TRUE
        nit <- ifelse(nrt\%\%nmaxrow > 0, (nrt\%/\%nmaxrow) + 1, 
            nrt\%/\%nmaxrow)
        nnr <- c(rep(nmaxrow, (nrt\%/\%nmaxrow)), nrt\%\%nmaxrow)
        ntr <- c(0, (1:(nrt\%/\%nmaxrow)) * nmaxrow, nrt)
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
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
