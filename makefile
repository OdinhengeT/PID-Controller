# Standard Compiler and Linker
CXX := g++

# Standard Compiler Flags
CXX_VERS := c++17
CXX_OPTI := O2
CXX_WARN := Wall Wextra pedantic-errors Wold-style-cast

CXXFLAGS := $(addprefix -, std=$(CXX_VERS) $(CXX_OPTI) $(CXX_WARN))

# Standard Directories
dSRC := src
dBIN := bin

# Packages
packages := process controller 

# Declaring non-file targets
.PHONY: install settings log default done 

# Programs to be Compiled and Linked
Programs := main.exe

# Defining default-target
default: install settings log $(Programs) done

main_dep := main.o process/watertank.o controller/controller.o
main.exe: $(addprefix $(dBIN)/, $(main_dep))
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@echo - Created $@

bin/%.o: $(dSRC)/%.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $^
	@echo - Created $@

# Displaying Settings
settings:
	@echo ==Settings==
	@echo - Version: $(CXX) $(CXX_VERS)
	@echo - Optimization: $(CXX_OPTI)
	@echo - Warnings: $(CXX_WARN)

# Initialize directories (empty line necessary)
define create_dir
	@if not exist "$(1)" (echo - Created \$(1))
	@if not exist "$(1)" (mkdir $(1))

endef

install:
	@echo ==Installing==
	$(call create_dir,$(dBIN))
	$(foreach p,$(packages),$(call create_dir,$(addprefix $(dBIN)\,$(p))))
	$(call create_dir,$(dSRC))
	$(foreach p,$(packages),$(call create_dir,$(addprefix $(dSRC)\,$(p))))

log: 
	@echo ==Log==

# Complete Message
done:
	@echo ==Done==