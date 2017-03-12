BINDIR:=./bin
SRCDIR:=./src
HEADDIR:=./include
COMMONHEAD:=~/include
BOOSTHEADDIR:=../boost_1_62_0
CC:=g++
CFLAGS:=-g -O0 -std=c++11  -o
LIBOPTION:=-lboost_date_time -lboost_atomic -lboost_system -lboost_chrono -lboost_thread
SOURCE:=$(wildcard $(SRCDIR)/*.cpp)
OBJS:=$(addsuffix .o,$(addprefix $(BINDIR),$(basename $(subst $(SRCDIR),,$(SOURCE)))))
all:$(OBJS)
	$(CC) $(CFLAGS) $(BINDIR)/main $(OBJS) -I $(HEADDIR) -I $(COMMONHEAD) $(LIBOPTION) -I $(BOOSTHEADDIR)
$(OBJS):$(BINDIR)/%.o:$(SRCDIR)/%.cpp
	$(CC) -c  $(CFLAGS) $@ $< -I $(HEADDIR) -I $(COMMONHEAD) -I $(BOOSTHEADDIR)
.PHONY:clean
clean:
	$(RM) -f $(BINDIR)/main $(OBJS)
