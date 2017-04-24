\name{append.onereplicate}
\alias{append.onereplicate}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
append.onereplicate
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
append.onereplicate(onerepl, allrepl)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{onerepl}{
%%     ~~Describe \code{onerepl} here~~
}
  \item{allrepl}{
%%     ~~Describe \code{allrepl} here~~
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
function (onerepl, allrepl) 
{
    if (length(dim(allrepl)) > length(dim(onerepl)) && all(dim(allrepl)[1:(length(dim(allrepl)) - 
        1)] == dim(onerepl))) {
        fr <- arraybind(allrepl, onerepl)
    }
    else {
        if (length(dim(allrepl)) == length(dim(onerepl)) && all(dim(allrepl) == 
            dim(onerepl))) {
            allrepl <- array(allrepl, dim = c(dim(allrepl), 1))
            fr <- arraybind(allrepl, onerepl)
        }
        else stop("merging problem")
    }
    return(fr)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
