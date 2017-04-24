\name{newwindow}
\alias{newwindow}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
newwindow
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
newwindow(window)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{window}{
%%     ~~Describe \code{window} here~~
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
function (window) 
{
    winsys <- Sys.info()[1] == "Windows"
    linsys <- Sys.info()[1] == "Linux"
    if (window & winsys) 
        windows()
    if (window & linsys) 
        x11()
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
