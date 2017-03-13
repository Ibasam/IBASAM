\name{proportions.population}
\alias{proportions.population}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
proportions.population
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
proportions.population(population, window = TRUE, plotting = TRUE, titles = "")
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{population}{
%%     ~~Describe \code{population} here~~
}
  \item{window}{
%%     ~~Describe \code{window} here~~
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
function (population, window = TRUE, plotting = TRUE, titles = "") 
{
    grilses <- (population$Returns > 0 & population$AgeSea < 
        2)
    MSW <- (population$Returns > 0 & population$AgeSea >= 2)
    OnevsMSWratio <- sum(grilses)/sum(MSW)
    sexratioGrilses <- sum(grilses & population$Female == 0)/sum(grilses & 
        population$Female == 1)
    sexratioMSW <- sum(MSW & population$Female == 0)/sum(MSW & 
        population$Female == 1)
    return(list(OnevsMSWratio = OnevsMSWratio, sexratioGrilses = sexratioGrilses, 
        sexratioMSW = sexratioMSW, nReturns = sum(grilses) + 
            sum(MSW)))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
