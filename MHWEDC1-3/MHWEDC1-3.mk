##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=MHWEDC1-3
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=C:/Users/fes77/Documents/ProgrammingPellet
ProjectPath            :=C:/Users/fes77/Documents/ProgrammingPellet/MHWEDC1-3
IntermediateDirectory  :=../build-$(ConfigurationName)/MHWEDC1-3
OutDir                 :=../build-$(ConfigurationName)/MHWEDC1-3
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=fes77
Date                   :=10/03/2020
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
Objects0=../build-$(ConfigurationName)/MHWEDC1-3/Variable.c$(ObjectSuffix) ../build-$(ConfigurationName)/MHWEDC1-3/main.c$(ObjectSuffix) ../build-$(ConfigurationName)/MHWEDC1-3/functionMHW.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/MHWEDC1-3/.d $(Objects) 
	@if not exist "..\build-$(ConfigurationName)\MHWEDC1-3" mkdir "..\build-$(ConfigurationName)\MHWEDC1-3"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\build-$(ConfigurationName)\MHWEDC1-3" mkdir "..\build-$(ConfigurationName)\MHWEDC1-3"
	@if not exist ""..\build-$(ConfigurationName)\bin"" mkdir ""..\build-$(ConfigurationName)\bin""

../build-$(ConfigurationName)/MHWEDC1-3/.d:
	@if not exist "..\build-$(ConfigurationName)\MHWEDC1-3" mkdir "..\build-$(ConfigurationName)\MHWEDC1-3"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/MHWEDC1-3/Variable.c$(ObjectSuffix): Variable.c ../build-$(ConfigurationName)/MHWEDC1-3/Variable.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/fes77/Documents/ProgrammingPellet/MHWEDC1-3/Variable.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Variable.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/MHWEDC1-3/Variable.c$(DependSuffix): Variable.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/MHWEDC1-3/Variable.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/MHWEDC1-3/Variable.c$(DependSuffix) -MM Variable.c

../build-$(ConfigurationName)/MHWEDC1-3/Variable.c$(PreprocessSuffix): Variable.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/MHWEDC1-3/Variable.c$(PreprocessSuffix) Variable.c

../build-$(ConfigurationName)/MHWEDC1-3/main.c$(ObjectSuffix): main.c ../build-$(ConfigurationName)/MHWEDC1-3/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/fes77/Documents/ProgrammingPellet/MHWEDC1-3/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/MHWEDC1-3/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/MHWEDC1-3/main.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/MHWEDC1-3/main.c$(DependSuffix) -MM main.c

../build-$(ConfigurationName)/MHWEDC1-3/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/MHWEDC1-3/main.c$(PreprocessSuffix) main.c

../build-$(ConfigurationName)/MHWEDC1-3/functionMHW.c$(ObjectSuffix): functionMHW.c ../build-$(ConfigurationName)/MHWEDC1-3/functionMHW.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/fes77/Documents/ProgrammingPellet/MHWEDC1-3/functionMHW.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/functionMHW.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/MHWEDC1-3/functionMHW.c$(DependSuffix): functionMHW.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/MHWEDC1-3/functionMHW.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/MHWEDC1-3/functionMHW.c$(DependSuffix) -MM functionMHW.c

../build-$(ConfigurationName)/MHWEDC1-3/functionMHW.c$(PreprocessSuffix): functionMHW.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/MHWEDC1-3/functionMHW.c$(PreprocessSuffix) functionMHW.c


-include ../build-$(ConfigurationName)/MHWEDC1-3//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)

