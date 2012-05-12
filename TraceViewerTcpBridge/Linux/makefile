LIBBASEDIR := ../../lib/Linux
NYXPATH := ../../../Nyx

ifndef Config
	Config := Debug
endif


ifeq ($(Config),Release)
	OBJDIR := Release
	LIBDIR := $(LIBBASEDIR)/Release
	CONFIG_CFLAGS := -O3 -fexceptions
else
	OBJDIR := Debug
	LIBDIR := $(LIBBASEDIR)/Debug
	CONFIG_CFLAGS := -O0 -fexceptions
endif


$(shell [ -d $(OBJDIR) ] || mkdir -p $(OBJDIR))
$(shell [ -d $(LIBDIR) ] || mkdir -p $(LIBDIR))

RM := rm -rf

MKDIR := mkdir 

CXX_CFLAGS := 	-I ../include \
				-I $(NYXPATH)/include \
				-I $(NYXPATH)/include/Linux \
				-I $(NYXPATH)/include/NyxNet \
				-L $(NYXPATH)/Lib/Linux/$(Config) \
				-I ../Sources \
				-I /usr/include \
				-v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/Main.o \
		$(OBJDIR)/TracePipeReceiver.o \
		$(OBJDIR)/Application.o \
		$(OBJDIR)/Application_Impl.o


$(OBJDIR)/%.o: ../Sources/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^

$(OBJDIR)/%.o: ./Sources/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^

$(LIBDIR)/TraceViewerTcpBridge.a: $(OBJS)	
	g++ $(CXX_CFLAGS) $(OBJS) -lpthread -lNyxNet -lNyxBase -o $(Config)/TraceViewerTcpBridge


all: 	$(LIBDIR)/TraceViewerTcpBridge.a \

clean:
	-$(RM) Debug
	-$(RM) Release


