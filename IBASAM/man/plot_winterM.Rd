\name{plot_winterM}
\alias{plot_winterM}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
plot_winterM
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
plot_winterM(winterM, window = TRUE, titles = "", startyear = 0)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{winterM}{
%%     ~~Describe \code{winterM} here~~
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
function (winterM, window = TRUE, titles = "", startyear = 0) 
{
    years <- startyear + (1:nrow(winterM))
    newwindow(window)
    plot(years, winterM[, 1], ylab = "smolt NBs", bty = "n", 
        type = "l", ylim = c(0, max(winterM[, 1], na.rm = TRUE)), 
        main = paste("Numbers of smolts through time", titles))
    lines(years, winterM[, 3], lty = 2, col = 2)
    lines(years, winterM[, 5], lty = 3, col = 3)
    legend("topright", legend = c("1+", "2+", "3+"), col = 1:3, 
        lty = 1:3)
    newwindow(window)
    plot(years, winterM[, 2], ylab = "smolt Lf", bty = "n", type = "l", 
        ylim = c(90, 250), main = paste("Sizes of smolts through time", 
            titles))
    lines(years, winterM[, 4], lty = 2, col = 2)
    lines(years, winterM[, 6], lty = 3, col = 3)
    legend("topright", legend = c("1+", "2+", "3+"), col = 1:3, 
        lty = 1:3)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
