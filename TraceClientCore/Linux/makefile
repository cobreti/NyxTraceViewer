BASE_LIBDIR := ../../Lib/Linux
NYXPATH := ../../../Nyx

ifndef Config
	Config := Debug
endif


ifeq ($(Config),Release)
	OBJDIR := Release
	LIBDIR := $(BASE_LIBDIR)/Release
	CONFIG_CFLAGS := -O3
else
	OBJDIR := Debug
	LIBDIR := $(BASE_LIBDIR)/Debug
	CONFIG_CFLAGS := -O0 -g
endif


$(shell [ -d $(OBJDIR) ] || mkdir -p $(OBJDIR))
$(shell [ -d $(LIBDIR) ] || mkdir -p $(LIBDIR))

RM := rm -rf

MKDIR := mkdir 

CXX_CFLAGS := 	-I ../include \
				-I $(NYXPATH)/include \
				-I $(NYXPATH)/include/Linux \
				-I $(NYXPATH)/include/Linux/NyxNet \
				-I $(NYXPATH)/include/NyxNet \
				-I ./Source \
				-I /usr/include \
				-I ../../openssl-1.0.1c/include/openssl \
				-I ../../openssl-1.0.1c/include \
				-I ../.. \
				-v $(CONFIG_CFLAGS)


OBJS := $(OBJDIR)/PipeTraceFeeder.o \
		$(OBJDIR)/PoolsUpdateClock.o \
		$(OBJDIR)/RepositoryObserver.o \
		$(OBJDIR)/RepositoryTraceInserter.o \
		$(OBJDIR)/TimeStamp.o \
		$(OBJDIR)/TraceClientCoreModule.o \
		$(OBJDIR)/TraceData.o \
		$(OBJDIR)/TraceDataRepository.o \
		$(OBJDIR)/TraceFeeder.o \
		$(OBJDIR)/TracesPool.o \
		$(OBJDIR)/TracesPoolCollection.o \
		$(OBJDIR)/PoolsList.o \
		$(OBJDIR)/TraceChannel.o \
		$(OBJDIR)/TraceChannels.o \
		$(OBJDIR)/TraceNxStreamReader.o \
		$(OBJDIR)/TcpModule.o \
		$(OBJDIR)/TcpNxTracesReceiver.o \
		$(OBJDIR)/TcpTxtTracesReceiver.o \
		$(OBJDIR)/TcpTracesReceiversSvr.o \
		$(OBJDIR)/TcpNxTracesReceiversSvr.o \
		$(OBJDIR)/TcpTxtTracesReceiversSvr.o \
		$(OBJDIR)/TcpTracesReceiversTable.o \
		$(OBJDIR)/TracesReceiverProtocol.o \
		$(OBJDIR)/TracesReceiverProtocol_WebSocket.o \
		$(OBJDIR)/TextTraceHandler.o


$(OBJDIR)/%.o: ../sources/%.cpp
	g++ -o $@ $(CXX_CFLAGS) -c $^

$(LIBDIR)/libTraceClientCore.a: $(OBJS)	
	ar -r $(LIBDIR)/libTraceClientCore.a $(OBJS)


all: 	$(LIBDIR)/libTraceClientCore.a \

clean:
	-$(RM) Debug
	-$(RM) Release
	-$(RM) $(BASE_LIBDIR)/Release/libTraceClientCore.a
	-$(RM) $(BASE_LIBDIR)/Debug/libTraceClientCore.a


