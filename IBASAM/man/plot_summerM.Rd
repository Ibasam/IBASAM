\name{plot_summerM}
\alias{plot_summerM}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
plot_summerM
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
plot_summerM(summerM, window = TRUE, titles = "", startyear = 0)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{summerM}{
%%     ~~Describe \code{summerM} here~~
}
  \item{window}{
%%     ~~Describe \code{window} here~~
}
  \item{titles}{
%%     ~~Describe \code{titles} here~~
}
  \item{startyear}{
%%     ~~Describe \code{startyear} here~~
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
function (summerM, window = TRUE, titles = "", startyear = 0) 
{
    years <- startyear + (1:nrow(summerM))
    newwindow(window)
    plot(years, summerM[, 1], ylab = "Returns NBs", bty = "n", 
        type = "l", ylim = c(0, max(summerM[, 1], na.rm = TRUE)), 
        main = paste("Numbers of returns through time", titles))
    lines(years, summerM[, 3], lty = 2, col = 2)
    lines(years, summerM[, 5], lty = 3, col = 3)
    legend("topright", legend = c("grilses", "MSW", "Multiple returns"), 
        col = 1:3, lty = 1:3)
    newwindow(window)
    plot(years, summerM[, 2], ylab = "Returns sizes", bty = "n", 
        type = "l", ylim = c(min(summerM[, 2], na.rm = TRUE), 
            max(summerM[, c(4, 6)], na.rm = TRUE)), main = paste("Sizes of returns through time", 
            titles))
    lines(years, summerM[, 4], lty = 2, col = 2)
    lines(years, summerM[, 6], lty = 3, col = 3)
    legend("topright", legend = c("grilses", "MSW", "Multiple returns"), 
        col = 1:3, lty = 1:3)
    newwindow(window)
    plot(years, summerM[, 7], ylab = "Parrs NBs", bty = "n", 
        type = "l", ylim = c(0, max(summerM[, 7], na.rm = TRUE)), 
        main = paste("Numbers of parrs through time", titles))
    lines(years, summerM[, 9], lty = 2, col = 2)
    lines(years, summerM[, 11], lty = 3, col = 3)
    lines(years, summerM[, 13], lty = 4, col = 4)
    legend("topright", legend = c("0+ immature", "0+ mature", 
        "1++ immature", "1++ mature"), col = 1:4, lty = 1:4)
    newwindow(window)
    plot(years, summerM[, 8], ylab = "Parrs sizes", bty = "n", 
        type = "l", ylim = c(min(summerM[, 8], na.rm = TRUE), 
            max(summerM[, c(10, 12)], na.rm = TRUE)), main = paste("Sizes of parrs through time", 
            titles))
    lines(years, summerM[, 10], lty = 2, col = 2)
    lines(years, summerM[, 12], lty = 3, col = 3)
    lines(years, summerM[, 14], lty = 4, col = 4)
    legend("topright", legend = c("0+ immature", "0+ mature", 
        "1++ immature", "1++ mature"), col = 1:4, lty = 1:4)
    newwindow(window)
    plot(years, summerM[, 15], ylab = "Parrs Wini", bty = "n", 
        type = "l", main = paste("Wini of parrs through time", 
            titles))
    lines(years, summerM[, 16], lty = 2, col = 2)
    legend("topright", legend = c("0+ immature", "0+ mature"), 
        col = 1:2, lty = 1:2)
    newwindow(window)
    plot(years, summerM[, 17], ylab = "specific growth rate", 
        bty = "n", type = "l", main = paste("specific growth rate in river of returning individuals through time", 
            titles))
    lines(years, summerM[, 18], lty = 2, col = 2)
    legend("topright", legend = c("grilses", "MSW"), col = 1:2, 
        lty = 1:2)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
