\name{DensEffect}
\alias{DensEffect}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
DensEffect
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
DensEffect(time_step_length, effDens)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{time_step_length}{
%%     ~~Describe \code{time_step_length} here~~
}
  \item{effDens}{
%%     ~~Describe \code{effDens} here~~
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
function (time_step_length, effDens) 
{
    return(unlist(.C("DensEffect", as.double(time_step_length), 
        as.double(effDens), as.double(0), PACKAGE = "libIbasam")[[3]]))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
