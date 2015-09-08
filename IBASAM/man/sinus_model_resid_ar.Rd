\name{sinus_model_resid_ar}
\alias{sinus_model_resid_ar}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
sinus_model_resid_ar
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
sinus_model_resid_ar(m, a, cs, alp, bet, d, nbd)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{m}{
%%     ~~Describe \code{m} here~~
}
  \item{a}{
%%     ~~Describe \code{a} here~~
}
  \item{cs}{
%%     ~~Describe \code{cs} here~~
}
  \item{alp}{
%%     ~~Describe \code{alp} here~~
}
  \item{bet}{
%%     ~~Describe \code{bet} here~~
}
  \item{d}{
%%     ~~Describe \code{d} here~~
}
  \item{nbd}{
%%     ~~Describe \code{nbd} here~~
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
function (m, a, cs, alp, bet, d, nbd) 
{
    error <- numeric(length(d))
    tm <- m + a * sin(2 * pi * (d - cs)/nbd)
    error[1] <- 0
    for (dd in d[-1]) {
        error[dd] <- alp * error[dd - 1] + bet * rnorm(1)
        tm[dd] <- tm[dd] + error[dd]
    }
    return(tm)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
