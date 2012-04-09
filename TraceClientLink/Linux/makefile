LIBBASEDIR := ../../NyxLibs/Lib/Linux
NYXINC := ../../NyxLibs/include

ifndef Config
	Config := Debug
endif


ifeq ($(Config),Release)
	OBJDIR := Release
	LIBDIR := $(LIBBASEDIR)/Release
	CONFIG_CFLAGS := -O3
else
	OBJDIR := Debug
	LIBDIR := $(LIBBASEDIR)/Debug
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
				-L $(LIBDIR) \
				-I /usr/include \
				-v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/Main.o \
		$(OBJDIR)/TraceLink.o


$(OBJDIR)/%.o: %.cpp
	g++ -c -fPIC -o $@ $(CXX_CFLAGS) -c $^

$(OBJDIR)/%.o: ../Source/%.cpp
	g++ -c -fPIC -o $@ $(CXX_CFLAGS) -c $^

$(LIBDIR)/TraceClientLink.so: $(OBJS)	
	g++ $(CXX_CFLAGS) $(OBJS) -shared -lpthread -lNyxNet -lNyxBase -o $(Config)/libTraceClientLink.so


all: 	$(LIBDIR)/TraceClientLink.so

clean:
	-$(RM) Debug
	-$(RM) Release


