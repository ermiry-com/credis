SLIB		:= libcredis.so

REDIS 		:= -l hiredis

CLIBS		:= -l clibs

DEVELOPMENT	:= -g

CC          := gcc

SRCDIR      := src
INCDIR      := include
BUILDDIR    := objs
TARGETDIR   := bin

TESTDIR		:= test
TESTBUILD	:= $(TESTDIR)/objs
TESTTARGET	:= $(TESTDIR)/bin

SRCEXT      := c
DEPEXT      := d
OBJEXT      := o

CFLAGS      := $(DEVELOPMENT) -Wall -Wno-unknown-pragmas -fPIC
LIB         := -L /usr/local/lib $(REDIS) $(CLIBS)
INC         := -I $(INCDIR) -I /usr/local/include
INCDEP      := -I $(INCDIR)

TESTFLAGS	:= -g $(DEFINES) -Wno-unknown-pragmas
TESTLIBS	:= $(LIB) -L ./bin -l credis

SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

TESTMPLES	:= $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
TESTOBJS	:= $(patsubst $(TESTDIR)/%,$(TESTBUILD)/%,$(TESTMPLES:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(SLIB)

install: $(SLIB)
	install -m 644 ./bin/libcredis.so /usr/local/lib/
	cp -R ./include/credis /usr/local/include

uninstall:
	rm /usr/local/lib/libcredis.so
	rm -r /usr/local/include/credis

directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

clean:
	@$(RM) -rf $(BUILDDIR) 
	@$(RM) -rf $(TARGETDIR)
	@$(RM) -rf $(TESTBUILD)
	@$(RM) -rf $(TESTTARGET)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

$(SLIB): $(OBJECTS)
	$(CC) $^ $(LIB) -shared -o $(TARGETDIR)/$(SLIB)

# compile sources
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

test: $(TESTOBJS)
	@mkdir -p ./$(TESTTARGET)
	$(CC) $(DEVELOPMENT) $(INC) ./$(TESTBUILD)/avl_test.o ./$(TESTBUILD)/user.o $(LIB) -L ./$(TARGETDIR) -l credis -o ./$(TESTTARGET)/avl_test
	$(CC) $(DEVELOPMENT) $(INC) ./$(TESTBUILD)/c_strings.o $(LIB) -L ./$(TARGETDIR) -l credis -o ./$(TESTTARGET)/c_strings
	$(CC) $(DEVELOPMENT) $(INC) ./$(TESTBUILD)/dlist_test.o $(LIB) -L ./$(TARGETDIR) -l credis -o ./$(TESTTARGET)/dlist_test
	$(CC) $(DEVELOPMENT) $(INC) ./$(TESTBUILD)/htab_test.o $(LIB) -L ./$(TARGETDIR) -l credis -o ./$(TESTTARGET)/htab_test
	$(CC) $(DEVELOPMENT) $(INC) ./$(TESTBUILD)/queue_test.o $(LIB) -L ./$(TARGETDIR) -l credis -o ./$(TESTTARGET)/queue_test
	$(CC) $(DEVELOPMENT) $(INC) ./$(TESTBUILD)/thpool_test.o $(LIB) -L ./$(TARGETDIR) -l credis -o ./$(TESTTARGET)/thpool_test

# compile tests
$(TESTBUILD)/%.$(OBJEXT): $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(TESTFLAGS) $(INC) $(TESTLIBS) -c -o $@ $<
	@$(CC) $(TESTFLAGS) $(INCDEP) -MM $(TESTDIR)/$*.$(SRCEXT) > $(TESTBUILD)/$*.$(DEPEXT)
	@cp -f $(TESTBUILD)/$*.$(DEPEXT) $(TESTBUILD)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(TESTBUILD)/$*.$(OBJEXT):|' < $(TESTBUILD)/$*.$(DEPEXT).tmp > $(TESTBUILD)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(TESTBUILD)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(TESTBUILD)/$*.$(DEPEXT)
	@rm -f $(TESTBUILD)/$*.$(DEPEXT).tmp

.PHONY: all clean test