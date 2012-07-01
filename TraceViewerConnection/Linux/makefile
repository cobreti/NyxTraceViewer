BASE_NYXLIB := ../../../Nyx/Lib/Linux
NYXINC := ../../../Nyx/include
BASE_LIBDIR := ../../Lib/Linux

ifndef Config
	Config := Debug
endif


ifeq ($(Config),Release)
	OBJDIR := Release
	NYXLIB := $(BASE_NYXLIB)/Release
	LIBDIR := $(BASE_LIBDIR)/Release
	CONFIG_CFLAGS := -O3
else
	OBJDIR := Debug
	NYXLIB := $(BASE_NYXLIB)/Debug
	LIBDIR := $(BASE_LIBDIR)/Debug
	CONFIG_CFLAGS := -O0 -g
endif


$(shell [ -d $(OBJDIR) ] || mkdir -p $(OBJDIR))
$(shell [ -d $(LIBDIR) ] || mkdir -p $(LIBDIR))

RM := rm -rf

MKDIR := mkdir 

CXX_CFLAGS := 	-I $(NYXINC) \
				-I $(NYXINC)/Linux \
				-I $(NYXINC)/NyxNet \
				-I ./include \
				-I ../Source \
				-L $(NYXLIB) \
				-I /usr/include \
				-v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/Main.o \
		$(OBJDIR)/TraceLink.o


$(OBJDIR)/%.o: %.cpp
	g++ -c -fPIC -o $@ $(CXX_CFLAGS) -c $^

$(OBJDIR)/%.o: ../Source/%.cpp
	g++ -c -fPIC -o $@ $(CXX_CFLAGS) -c $^

$(LIBDIR)/NyxTraceViewerConnection.so: $(OBJS)	
	g++ $(CXX_CFLAGS) $(OBJS) -shared -lpthread -lNyxNet -lNyxBase -o $(LIBDIR)/libNyxTraceViewerConnection.so


all: 	$(LIBDIR)/NyxTraceViewerConnection.so

clean:
	-$(RM) Debug
	-$(RM) Release
	-$(RM) $(BASE_LIBDIR)/Release/libNyxTraceViewerConnection.so
	-$(RM) $(BASE_LIBDIR)/Debug/libNyxTraceViewerConnection.so


