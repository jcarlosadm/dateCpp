############ início da configuração ############################

# terminação dos arquivos fontes
SRC_SUFFIX= cpp
# terminação dos arquivos de cabeçalho
HPP_SUFFIX= hpp

# diretório dos objetos
OBJ_DIR= objects/
# diretório do binário principal
BIN_DIR= bin/
# diretório dos binários de testes
BIN_TESTS_DIR= bin/tests/
# diretório dos arquivos fontes de testes
SRC_TESTS_DIR= srcTests/
# diretório dos arquivos fontes
SRC_DIR= src/
# diretório dos arquivos de cabeçalho
HPP_DIR= hpp_files/

# as flags e opções usadas
# compilador
CC= g++
# opções usadas pelo compilador
CCFLAGS= -fPIC -Wall
# bibliotecas usadas no projeto
LIBDEPS=

# criar biblioteca após a compilação? YES ou NO
BUILDLIB=YES

# nome da biblioteca
LIBRARY_NAME=dateCpp

############ fim da configuração ###############################

# nome do binário principal
BIN_NAME= main

# obtém uma lista de todos os arquivos fontes
SRC_LIST= $(wildcard $(SRC_DIR)*.$(SRC_SUFFIX))
# obtém uma lista de todos os header files
HPP_LIST= $(wildcard $(HPP_DIR)*.$(HPP_SUFFIX))
# obtém uma lista de todos os arquivos objetos a serem criados
OBJ_LIST:= $(patsubst $(SRC_DIR)%.$(SRC_SUFFIX),$(OBJ_DIR)%.o, $(SRC_LIST))

# comando para criar diretórios
MK_DIR= @mkdir -p

.PHONY: makedir_objects
.PHONY: makedir_bin
.PHONY: makedir_bin_tests

# comando principal
ifeq ($(BUILDLIB),YES)
all: makedir_objects makedir_bin makedir_bin_tests $(BIN_DIR)$(BIN_NAME) buildLib
else
all: makedir_objects makedir_bin makedir_bin_tests $(BIN_DIR)$(BIN_NAME)
endif

# cria diretório dos objetos
makedir_objects:
	$(MK_DIR) $(OBJ_DIR)

# cria diretório dos binários
makedir_bin:
	$(MK_DIR) $(BIN_DIR)

# cria diretório para binário de testes
makedir_bin_tests:
	$(MK_DIR) $(BIN_TESTS_DIR)

# criação do binário principal
$(BIN_DIR)$(BIN_NAME): $(OBJ_LIST)
	$(CC) -o $@ $^ $(LIBDEPS)

# Coloca todas as informações de dependências nos arquivos '.o' existentes
-include $(OBJ_LIST:.o=.d)

# comando da construção de cada arquivo de objeto
$(OBJ_DIR)%.o: $(SRC_DIR)%.$(SRC_SUFFIX)
	$(CC) -c $(CCFLAGS) $< -o $@
	$(CC) -MM -c $(CCFLAGS) $(SRC_DIR)$*.$(SRC_SUFFIX) > $(OBJ_DIR)$*.d
	@mv -f $(OBJ_DIR)$*.d $(OBJ_DIR)$*.d.tmp
	@sed -e 's|.*:|$(OBJ_DIR)$*.o:|' < $(OBJ_DIR)$*.d.tmp > $(OBJ_DIR)$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJ_DIR)$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJ_DIR)$*.d
	@rm -f $(OBJ_DIR)$*.d.tmp

# gera biblioteca com todos os objetos do projeto
buildLib:
	$(CC) -shared $(patsubst $(HPP_DIR)%.$(HPP_SUFFIX),$(OBJ_DIR)%.o, $(HPP_LIST)) \
	-o lib$(LIBRARY_NAME).so

# comando para instalar a biblioteca no linux ubuntu/debian (use com sudo)
install:
	$(MK_DIR) /usr/local/include/$(LIBRARY_NAME)
	@cp $(HPP_LIST) /usr/local/include/$(LIBRARY_NAME)/
	@cp lib$(LIBRARY_NAME).so /usr/local/lib/
	@ln -nsf /usr/local/lib/lib$(LIBRARY_NAME).so /usr/lib/
	@echo 'done'

.PHONY: clean
# comando para limpar tudo
clean:
	rm -rf $(OBJ_DIR)*.o $(OBJ_DIR)*.d $(BIN_TESTS_DIR)* $(BIN_DIR)$(BIN_NAME) *.so \
	*.dll *.dll.a *.dylib

# exemplo de teste:
#
#(basta evocar 'make testStruct')
#
#testStruct: binNameTest
#
#binNameTest: $(OBJ_DIR)/binNameTest.o $(OBJ_LIST)
#	$(CC) -o $(BIN_DIR)/$(BIN_TESTS_DIR)/$@ $^ $(LIBDEPS)
#
#$(OBJ_DIR)/binNameTest.o: $(SRC_TESTS_DIR)/binNameTest.cpp binSrcDeps
#	$(CC) $(CPPFLAGS) $< -o $@
#
