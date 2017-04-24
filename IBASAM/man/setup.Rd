\name{setup}
\alias{setup}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
setup
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
setup(filename, envParam, colParam, internal = FALSE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{filename}{
%%     ~~Describe \code{filename} here~~
}
  \item{envParam}{
%%     ~~Describe \code{envParam} here~~
}
  \item{colParam}{
%%     ~~Describe \code{colParam} here~~
}
  \item{internal}{
%%     ~~Describe \code{internal} here~~
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
function (filename, envParam, colParam, internal = FALSE) 
{
    empty()
    Reset_environment()
    if (internal) {
        Prepare_environment_file(filename)
    }
    else {
        dat <- read.table(filename)
        Prepare_environment_vectors(dat$V2, dat$V3)
    }
    setup_environment_parameters(envParam)
    setup_collection_parameters(colParam)
    time_tick(90)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
