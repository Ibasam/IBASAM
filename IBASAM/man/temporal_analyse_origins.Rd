\name{temporal_analyse_origins}
\alias{temporal_analyse_origins}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
temporal_analyse_origins
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
temporal_analyse_origins(pop, Years, plotting = FALSE, titles = "")
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{pop}{
%%     ~~Describe \code{pop} here~~
}
  \item{Years}{
%%     ~~Describe \code{Years} here~~
}
  \item{plotting}{
%%     ~~Describe \code{plotting} here~~
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
function (pop, Years, plotting = FALSE, titles = "") 
{
    results <- array(NA, c(2, length(possibleStrategies), length(Years)))
    for (y in Years) {
        popt <- pop[pop$year == y, ]
        rest <- analyse_origins(popt, plotting = FALSE, complete = FALSE)
        results[, , (1 + y - min(Years))] <- rest
    }
    dimnames(results) <- list(rownames(rest), colnames(rest), 
        as.character(Years))
    if (plotting) {
        plot(Years, results[1, 1, ], type = "l", bty = "l", ylim = c(0, 
            1), ylab = "Strategy \%", main = titles)
        lines(Years, results[1, 1, ], lty = 2)
        for (j in 2:length(possibleStrategies)) {
            lines(Years, results[1, j, ], col = j)
            lines(Years, results[2, j, ], col = j, lty = 2)
        }
        legend("topright", legend = c("mother", "father"), lty = c(1, 
            2))
        legend("topleft", legend = as.character(possibleStrategies), 
            lty = 1, col = 1:length(possibleStrategies))
    }
    return(results)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
