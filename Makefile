############################################################################
# compile optes
############################################################################
CC = g++
CXXFLAGS = -g -w
PROGRAM = gamebox

OBJ_PROTECT = test.o 

#OBJ_DEF = CStr.o CzpDef.o Hash.o

#OBJ_BASELIB = Database.o RTbase.o




OBJ_ALL =$(OBJ_PROTECT) 


LIB = -lpthread  \


OPTES = $(PWD)

OBJECTDIR=$(OPTES)/obj

LDPATH = -L$(HOME)/lib -L$(HOME)/src/lib 

INCPATH = -I. -I$(HOME) -I$(HOME)/test 

VPATH = $(OPTES)/test 
####################################################################
# compile rule
####################################################################
.cpp.o:
	g++  -g -w   $(INCPATH) -c $< -o $(OBJECTDIR)/$(@F)
	@echo "********" $< is builded ok. "********"
	@echo ""
$(PROGRAM):$(OBJ_ALL)
	cd $(OBJECTDIR);$(CC) -o $@ $(OBJECTDIR)/$(OBJ_ALL) $(LDPATH) $(LIB) -lrt
	#cd $(OBJECTDIR)
	#$(CC) $(CXXFLAGS) -o $(OBJECTDIR)/$(PROGRAM) $(OBJECTDIR)/$(OBJ_ALL) $(LDPATH) $(LIB)
	$(CP) $(OBJECTDIR)/$(PROGRAM) $(HOME)/bin
	#$(CP) $(OBJECTDIR)/$(PROGRAM) $(HOME)/src/bin
	$(CP) $(OBJECTDIR)/$(PROGRAM) $(OPTES)/

lib:$(OBJ_OPT)
	cd $(OBJECTDIR);ar crv libopt.a $(OBJECTDIR)/$(OBJ_OPT)
	$(CP) $(OBJECTDIR)/libopt.a $(HOME)/src/lib
	$(CP) $(OBJECTDIR)/libopt.a $(HOME)/lib

.PHONY: clean cleano bin

RM = -rm -rf

CP = cp -p

cleandef:
	$(RM) $(OBJECTDIR)/$(OBJ_DEF)
cleanprotect:
	$(RM) $(OBJECTDIR)/$(OBJ_PROTECT)
cleanunits:
	$(RM) $(OBJECTDIR)/$(OBJ_UNITS)
cleanrwp:
	$(RM) $(OBJECTDIR)/$(OBJ_RWP)
cleanactions:
	$(RM) $(OBJECTDIR)/$(OBJ_ACTIONS)
cleanexperts:
	$(RM) $(OBJECTDIR)/$(OBJ_EXPERTS)
cleanmain:
	$(RM) $(OBJECTDIR)/$(OBJ_MAIN)
cleano :
	$(RM) $(OBJECTDIR)/*.o
clean :
	$(RM) $(HOME)/bin/$(PROGRAM)
	$(RM) $(OBJECTDIR)/*
	$(RM) $(OBJECTDIR)/$(PROGRAM)
	$(RM) $(OPTES)/debug_optes.log
####################################################################
# end makefile
####################################################################



