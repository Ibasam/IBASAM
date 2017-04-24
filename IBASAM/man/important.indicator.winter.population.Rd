\name{important.indicator.winter.population}
\alias{important.indicator.winter.population}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
important.indicator.winter.population
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
important.indicator.winter.population(population)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{population}{
%%     ~~Describe \code{population} here~~
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
function (population) 
{
    smolt1 <- (population$AgeSea == 0 & population$AgeRiver < 
        2 & population$Smolt == 1)
    smolt2 <- (population$AgeSea == 0 & population$AgeRiver >= 
        2 & population$AgeRiver < 3 & population$Smolt == 1)
    smolt3 <- (population$AgeSea == 0 & population$AgeRiver >= 
        3 & population$Smolt == 1)
    return(list(smolt1NB = sum(smolt1), smolt1Lf = mean(population[smolt1, 
        "Lf"]), smolt2NB = sum(smolt2), smolt2Lf = mean(population[smolt2, 
        "Lf"]), smolt3NB = sum(smolt3), smolt3Lf = mean(population[smolt3, 
        "Lf"])))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
