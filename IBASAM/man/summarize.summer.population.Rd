\name{summarize.summer.population}
\alias{summarize.summer.population}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
summarize.summer.population
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
summarize.summer.population(population, variables)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{population}{
%%     ~~Describe \code{population} here~~
}
  \item{variables}{
%%     ~~Describe \code{variables} here~~
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
function (population, variables) 
{
    grilses <- (population$Returns == 1 & population$AgeSea < 
        2)
    MSW <- (population$Returns >= 1 & population$AgeSea >= 2)
    Parrs0 <- (population$AgeSea == 0 & population$AgeRiver < 
        1)
    Parrs1 <- (population$AgeSea == 0 & population$AgeRiver >= 
        1)
    rr <- summarize.sub.population(population[grilses, ], variables)
    rr <- array(rr, dim = c(dim(rr), 1))
    rr <- arraybind(rr, summarize.sub.population(population[MSW, 
        ], variables))
    rr <- arraybind(rr, summarize.sub.population(population[Parrs0, 
        ], variables))
    rr <- arraybind(rr, summarize.sub.population(population[Parrs1, 
        ], variables))
    rr
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
