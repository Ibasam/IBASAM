\name{Prepare_environment_vectors}
\alias{Prepare_environment_vectors}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Prepare_environment_vectors
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
Prepare_environment_vectors(temperature, logrelflow)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{temperature}{
%%     ~~Describe \code{temperature} here~~
}
  \item{logrelflow}{
%%     ~~Describe \code{logrelflow} here~~
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
function (temperature, logrelflow) 
{
    n <- length(temperature)
    if (length(logrelflow) == n & is.vector(temperature) & is.vector(logrelflow)) {
        .C("Prepare_environment_vectors", as.double(1:n), as.double(temperature), 
            as.double(logrelflow), as.double(n), PACKAGE = "libIbasam")
        invisible(NULL)
    }
    else {
        return("wrong entries in prepare environment vectors")
    }
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
