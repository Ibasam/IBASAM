\name{important.indicator.summer.population}
\alias{important.indicator.summer.population}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
important.indicator.summer.population
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
important.indicator.summer.population(population)
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
    grilses <- (population$Returns == 1 & population$AgeSea < 
        2)
    MSW <- (population$Returns == 1 & population$AgeSea >= 2)
    Mreturns <- (population$Returns > 1 & population$AgeSea >= 
        2)
    Parrs0imm <- (population$AgeSea == 0 & population$AgeRiver < 
        1 & population$Mature == 0)
    Parrs0mat <- (population$AgeSea == 0 & population$AgeRiver < 
        1 & population$Mature == 1)
    Parrs1pimm <- (population$AgeSea == 0 & population$AgeRiver >= 
        1 & population$Mature == 0)
    Parrs1pmat <- (population$AgeSea == 0 & population$AgeRiver >= 
        1 & population$Mature == 1)
    return(list(grilsesNB = sum(grilses), grilsesLf = mean(population[grilses, 
        "Lf"]), MSWNB = sum(MSW), MSWLf = mean(population[MSW, 
        "Lf"]), MreturnsNB = sum(Mreturns), MreturnsLf = mean(population[Mreturns, 
        "Lf"]), Parrs0immNB = sum(Parrs0imm), Parrs0immLf = mean(population[Parrs0imm, 
        "Lf"]), Parrs0matNB = sum(Parrs0mat), Parrs0matLf = mean(population[Parrs0mat, 
        "Lf"]), Parrs1pimmNB = sum(Parrs1pimm), Parrs1pimmLf = mean(population[Parrs1pimm, 
        "Lf"]), Parrs1pmatNB = sum(Parrs1pmat), Parrs1pmatLf = mean(population[Parrs1pmat, 
        "Lf"]), WiniParr0imm = mean(population[Parrs0imm, "Wini"]), 
        WiniParr0mat = mean(population[Parrs0mat, "Wini"]), spGRgrilses = mean(population[grilses, 
            "SpecificGR"]), spGRMSW = mean(population[MSW, "SpecificGR"])))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
