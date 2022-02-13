UNAME := $(shell uname -s)
HFOLDERS := -I php-src -I php-src/Zend -I php-src/main -I php-src/TSRM -I php-src/ext/spl
COMMAND := @echo Invalid operation system: $(UNAME)

ifeq ($(DEBUG), 1)
	DEBUGFLAG := -D DEBUG
else
	DEBUGFLAG :=
endif

ifeq ($(UNAME), Linux)
	COMMAND := g++ -lpthread -fPIC -shared -Wattributes $(HFOLDERS) $(DEBUGFLAG) -o library/phpthreads_linux.so library/phpthreads.cpp
endif

ifeq ($(UNAME), Darwin)
	COMMAND := clang -lpthread -shared -undefined dynamic_lookup -Wattributes $(HFOLDERS) $(DEBUGFLAG) -o library/phpthreads_darwin.dylib library/phpthreads.cpp
endif

all:
	$(COMMAND)
