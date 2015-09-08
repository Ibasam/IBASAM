\name{plot_proportions_population}
\alias{plot_proportions_population}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
plot_proportions_population
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
plot_proportions_population(ratios, window = TRUE, titles = "", startyear = 0)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{ratios}{
%%     ~~Describe \code{ratios} here~~
}
  \item{window}{
%%     ~~Describe \code{window} here~~
}
  \item{titles}{
%%     ~~Describe \code{titles} here~~
}
  \item{startyear}{
%%     ~~Describe \code{startyear} here~~
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
function (ratios, window = TRUE, titles = "", startyear = 0) 
{
    years <- startyear + (1:nrow(ratios))
    newwindow(window)
    plot(years, ratios[, 1], type = "l", ylab = "ratio", bty = "l", 
        main = paste("1 vs MSW through time", titles))
    newwindow(window)
    plot(years, ratios[, 2], type = "l", ylab = "ratio", bty = "l", 
        main = paste("sexratio Grilses through time", titles))
    newwindow(window)
    plot(years, ratios[, 3], type = "l", ylab = "ratio", bty = "l", 
        main = paste("sexratio MSW through time", titles))
    newwindow(window)
    plot(years, ratios[, 4], type = "l", ylab = "Number", bty = "l", 
        main = paste("number of returns through time", titles))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
