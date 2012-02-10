LIBBASEDIR := ../../lib/Linux

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
	CONFIG_CFLAGS := -O0
endif


$(shell [ -d $(OBJDIR) ] || mkdir -p $(OBJDIR))
$(shell [ -d $(LIBDIR) ] || mkdir -p $(LIBDIR))

RM := rm -rf

MKDIR := mkdir 

CXX_CFLAGS := 	-I ../include \
				-I ../../NyxLibs/include \
				-I ../../NyxLibs/include/Linux \
				-I ../../NyxLibs/include/NyxNet \
				-L ../../NyxLibs/Lib/Linux/$(Config) \
				-I ../Source \
				-I /usr/include \
				-v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/Main.o \
		$(OBJDIR)/TracePipeReceiver.o


$(OBJDIR)/%.o: ../Sources/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^

$(LIBDIR)/TraceViewerTcpBridge.a: $(OBJS)	
	g++ $(CXX_CFLAGS) $(OBJS) -lpthread -lNyxNet -lNyxBase -o $(Config)/TraceViewerTcpBridge


all: 	$(LIBDIR)/libTraceClientCore.a \

clean:
	-$(RM) Debug
	-$(RM) Release


