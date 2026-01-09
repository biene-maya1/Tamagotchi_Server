CC = gcc
CFLAGS = -Wall -Wextra

TYPE=tcp

SRC_SERVEUR = serveur_$(TYPE).c
EXE_SERVEUR = serveur_$(TYPE).exe

SRC_CLIENT = client_$(TYPE).c
EXE_CLIENT = client_$(TYPE).exe

all: $(EXE_SERVEUR) $(EXE_CLIENT)

client: $(EXE_CLIENT)
	@echo "\033[2m./$(EXE_CLIENT) $(ARGS)\033[0m"
	@./$(EXE_CLIENT) $(ARGS)

serveur: $(EXE_SERVEUR)
	@echo "\033[2m./$(EXE_SERVEUR)\033[0m"
	@./$(EXE_SERVEUR)

$(EXE_SERVEUR): $(SRC_SERVEUR)
	$(CC) $(CFLAGS) -o $@ $^

$(EXE_CLIENT): $(SRC_CLIENT)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	@rm -f $(EXE_SERVEUR) $(EXE_CLIENT)
	@echo "Clean : \033[92mOk !\033[0m"

clear: clean