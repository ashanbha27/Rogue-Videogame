CXX ?= g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
ifdef TEST
CXXFLAGS += -DTEST=1
endif
HEADERS_EXT = hpp
INCLUDE_HEADERS = $(shell find src -name '*.$(HEADERS_EXT)' -printf '-I%h\n' | uniq)
INCLUDES = -I/usr/local/include -Ixerces-c/include $(INCLUDE_HEADERS)
LDFLAGS = -Lxerces-c/lib
LIBS = -lxerces-c -lncurses -lpanel

SRC_EXT = cpp
SRC_PATH = src
SRCS = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' -printf '%T@ %p\n' | sort -k 1nr | cut -d ' ' -f2-)
OBJECTS = $(SRCS:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
DEPS = $(OBJECTS:.o=.d)

BUILD_PATH = build
BINARY_PATH = $(BUILD_PATH)/bin
BINARY_NAME = dungeon

XML_PATH = xmlfiles
XMLFILES = $(shell find $(XML_PATH) -name '*.xml' -printf '%T@ %P\n' | sort -k 1nr | cut -d ' ' -f2-)
DEFAULT_XMLFILE = $(word 1, $(XMLFILES))

SUBMISSION_FILES = $(SRC_PATH)/ xerces-c/ xmlfiles/ Makefile
USER_ID = naraya16_ashanbha

all: $(DEFAULT_XMLFILE)

.PHONY: $(XMLFILES)
$(XMLFILES): build
	$(BINARY_PATH)/$(BINARY_NAME) $@

.PHONY: build
build: $(BINARY_PATH)/$(BINARY_NAME)

$(BINARY_PATH)/$(BINARY_NAME): $(OBJECTS)
	@mkdir -p $(@D)
	@echo "Linking: $@"
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

-include $(DEPS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@mkdir -p $(@D)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

submit:
	rm -rf $(USER_ID)*
	mkdir $(USER_ID)/
	cp -r $(SUBMISSION_FILES) -t $(USER_ID)/
	zip -0 -r $(USER_ID) $(USER_ID)/

clean:
	@echo "Deleting build directory"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(USER_ID)*
