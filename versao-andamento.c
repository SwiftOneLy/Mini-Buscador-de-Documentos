#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYWORDS 100  // Número máximo de palavras-chave por documento

// Estrutura para armazenar o documento
typedef struct Document {
    char id[256];                      // Identificação do documento (nome ou ID)
    char keywords[MAX_KEYWORDS][256];  // Palavras-chave (até MAX_KEYWORDS)
} Document;
