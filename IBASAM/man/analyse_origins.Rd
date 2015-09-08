\name{analyse_origins}
\alias{analyse_origins}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
analyse_origins
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
analyse_origins(pop, sex = NULL, plotting = TRUE, titles = "", complete = TRUE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{pop}{
%%     ~~Describe \code{pop} here~~
}
  \item{sex}{
%%     ~~Describe \code{sex} here~~
}
  \item{plotting}{
%%     ~~Describe \code{plotting} here~~
}
  \item{titles}{
%%     ~~Describe \code{titles} here~~
}
  \item{complete}{
%%     ~~Describe \code{complete} here~~
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
function (pop, sex = NULL, plotting = TRUE, titles = "", complete = TRUE) 
{
    if (!is.null(sex)) {
        if (sex == 0 | sex == 1) {
            pop <- pop[pop$Female == sex, ]
        }
        else {
            complete <- TRUE
        }
    }
    results <- matrix(unlist(analyse_origins_simple(pop)), nrow = 2, 
        byrow = TRUE)
    if (complete) {
        popt <- pop[pop$Female == 0, ]
        results <- rbind(results, matrix(unlist(analyse_origins_simple(popt)), 
            nrow = 2, byrow = TRUE))
        popt <- pop[pop$Female == 1, ]
        results <- rbind(results, matrix(unlist(analyse_origins_simple(popt)), 
            nrow = 2, byrow = TRUE))
        rownames(results) <- paste(rep(c("all", "males", "females"), 
            each = 2), rep(c("mother", "father"), 3))
        colnames(results) <- as.character(possibleStrategies)
        if (plotting) {
            dotchart(t(results), main = paste(titles, "N=", nrow(pop)))
        }
    }
    else {
        if (plotting) {
            rownames(results) <- c("mother", "father")
            colnames(results) <- as.character(possibleStrategies)
            dotchart(t(results), main = paste(titles, "N=", nrow(pop)))
        }
    }
    return(results)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
