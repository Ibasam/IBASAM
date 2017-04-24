.onAttach <- function(lib, pkg)
{
	 data(ColNames)
	 data(ColNamesRedds)
	 data(mySummarynames)
	 data(nColObserve)
	 data(nColObserveRedds)
	 data(groupnames)
	 data(possibleStrategies)
}
.onLoad <- function(lib, pkg)
{
	 dll="Ibasam"
#   if(Sys.info()[1]=="Windows")
#   {
#     dll=paste0(dll,".dll")
#   }else{
#     dll=paste0(dll,".so")   
#   }
#   if(Sys.info()[5]=="x86-64")
#   {
#     dll=paste0("/Ibasam/libs/x64/",dll)
#   }else{
#     dll=paste0("/Ibasam/libs/i386/",dll)
#   }
#   
#   dyn.load(paste(.libPaths(),dll,sep=''))
    library.dynam(dll,dll,.libPaths())
}
