\name{random_Scorff_river}
\alias{random_Scorff_river}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
random_Scorff_river
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
random_Scorff_river(nYears)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{nYears}{
%%     ~~Describe \code{nYears} here~~
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
function (nYears) 
{
    mT <- 12.674299
    aT <- 5.909091
    csT <- 114.780948
    alpT <- 0.95184170929478
    betT <- 0.449967327959108
    mF <- -0.02
    aF <- 1.010139
    csF <- 327.836285
    alpF <- 0.964034622660953
    betF <- 0.118343974744226
    temperatures <- sinus_model_resid_ar(mT, aT, csT, alpT, betT, 
        1:(365 * nYears), 365)
    logrelflow <- sinus_model_resid_ar(mF, aF, csF, alpF, betF, 
        1:(365 * nYears), 365) - 0.2
    temperatures[temperatures < 0] <- 0.01
    logrelflow[logrelflow > 3] <- 3
    logrelflow[logrelflow < -3] <- -3
    return(list(temperatures = temperatures, logrelflow = logrelflow))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
