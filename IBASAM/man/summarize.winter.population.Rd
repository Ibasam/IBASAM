\name{summarize.winter.population}
\alias{summarize.winter.population}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
summarize.winter.population
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
summarize.winter.population(population, rr, variables)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{population}{
%%     ~~Describe \code{population} here~~
}
  \item{rr}{
%%     ~~Describe \code{rr} here~~
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
function (population, rr, variables) 
{
    smolt1 <- (population$AgeSea == 0 & population$AgeRiver < 
        2 & population$Smolt == 1)
    smolt2 <- (population$AgeSea == 0 & population$AgeRiver >= 
        2 & population$Smolt == 1)
    rr <- arraybind(rr, summarize.sub.population(population[smolt1, 
        ], variables))
    rr <- arraybind(rr, summarize.sub.population(population[smolt2, 
        ], variables))
    rr
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
