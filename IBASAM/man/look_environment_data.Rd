\name{look_environment_data}
\alias{look_environment_data}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
look_environment_data
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
look_environment_data()
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
    nb_day <- recall_nb_day_simulations()
    env <- .C("look_environment_data", as.integer(nb_day), as.double(1:nb_day), 
        as.double(1:nb_day), as.double(1:nb_day), PACKAGE = "libIbasam")
    res <- data.frame(days = env[[2]], Temperature = env[[3]], 
        logFlow = env[[4]])
    return(res)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
