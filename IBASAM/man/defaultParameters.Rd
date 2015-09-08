\name{defaultParameters}
\alias{defaultParameters}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
defaultParameters
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
defaultParameters()
}
%- maybe also 'usage' for other objects documented here.
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
function () 
{
    def <- .C("defaultParameters", as.double(1:17), as.double(1:13), 
        as.double(1:13), as.double(1:13), as.double(1:13), as.double(1:13), 
        as.double(1:87), PACKAGE = "libIbasam")
    names(def) <- c("envParam", "gParam", "parrParam", "smoltsParam", 
        "grilseParam", "mswParam", "colParam")
    return(def)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
