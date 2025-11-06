#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>  // Para leitura de diretório (Linux/macOS - POSIX)
#include <ctype.h> // Para manipulação de caracteres (tolower)
#include <time.h>  // Para medir o tempo de busca
#define MAX_KEYWORDS 100 
#define MAX_STRING_SIZE 256 
#define MAX_DOCUMENT_SIZE 4096 
// Estrutura para representar um documento
typedef struct Document {
char id[MAX_STRING_SIZE];
char keywords[MAX_KEYWORDS][MAX_STRING_SIZE];
int num_keywords;
char content[MAX_DOCUMENT_SIZE];
}

Document;
// Estrutura para um nó da árvore
typedef struct Node {
	Document data;
	struct Node* left;
	struct Node* right;
}

Node;

// Protótipos das funções
Node* createNode(Document doc);
Node* insert(Node* root, Document doc);
void search(Node* root, const char* keyword);
int calculateHeight(Node* root);
void freeTree(Node* root);
void normalize_word(char* word);
Node* process_document(Node* root, const char* filepath, const char* filename);
Node* read_directory(Node* root, const char* dir_path);

// **** IMPLEMENTAÇÃO DAS FUNÇÕES ****
Node* createNode(Document doc) {
	Node* newNode=(Node*)malloc(sizeof(Node));

	if (newNode==NULL) {
		perror("Erro na alocação de memória");
		exit(1);
	}

	newNode->data=doc;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}

Node* insert(Node* root, Document doc) {
	if (root==NULL) {
		return createNode(doc);
	}

	int cmp=strcmp(doc.id, root->data.id);

	if (cmp < 0) {
		root->left=insert(root->left, doc);
	}

	else if (cmp > 0) {
		root->right=insert(root->right, doc);
	}

	return root;
}

void search(Node* root, const char* keyword) {
	if (root==NULL) return;
	search(root->left, keyword);

	for (int i=0; i < root->data.num_keywords; i++) {
		if (strcasecmp(root->data.keywords[i], keyword)==0) {
			printf("--- Documento encontrado ---\n");
			printf("ID: %s\n", root->data.id);
			printf("Palavra-chave: %s\n", keyword);
			printf("Conteudo: %.100s...\n", root->data.content);
			printf("----------------------------\n\n");
			break;
		}
	}

	search(root->right, keyword);
}

int calculateHeight(Node* root) {
	if (root==NULL) return 0;
	int leftHeight=calculateHeight(root->left);
	int rightHeight=calculateHeight(root->right);
	return (leftHeight > rightHeight ? leftHeight : rightHeight)+1;
}

void freeTree(Node* root) {
	if (root==NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

void normalize_word(char* word) {
	int i,
	j=0;

	for (i=0; word[i] !='\0'; i++) {
		if (isalnum((unsigned char)word[i])) {
			word[j++]=tolower((unsigned char)word[i]);
		}
	}

	word[j]='\0';
}

Node* process_document(Node* root, const char* filepath, const char* filename) {
	FILE* file=fopen(filepath, "r");

	if (file==NULL) {
		perror("Erro ao abrir o arquivo");
		return root;
	}

	Document newDoc= {
		0
	}

	;
	strcpy(newDoc.id, filename);
	newDoc.num_keywords=0;
	char word[MAX_STRING_SIZE];
	int char_count=0;

	while (fscanf(file, "%s", word)==1) {
		char temp_word[MAX_STRING_SIZE];
		strcpy(temp_word, word);
		normalize_word(temp_word);

		if (strlen(temp_word) > 0 && newDoc.num_keywords < MAX_KEYWORDS) {
			int already_exists=0;

			for(int i=0; i < newDoc.num_keywords; i++) {
				if(strcmp(newDoc.keywords[i], temp_word)==0) {
					already_exists=1;
					break;
				}

				if( !already_exists) {}
			}

			strcpy(newDoc.keywords[newDoc.num_keywords++], temp_word);
		}

		if (char_count < MAX_DOCUMENT_SIZE - strlen(word) - 1) {
			strcat(newDoc.content, word);
			strcat(newDoc.content, " ");
			char_count+=strlen(word)+1;
		}
	}

	root=insert(root, newDoc);
	fclose(file);
	printf(" [OK] Processado '%s' com %d palavras-chave.\n", filename,
		newDoc.num_keywords);
	return root;
}

Node* read_directory(Node* root, const char* dir_path) {
	DIR* dir;
	struct dirent* entry;
	char filepath[MAX_STRING_SIZE+MAX_STRING_SIZE];

	if ((dir=opendir(dir_path))==NULL) {
		perror("ERRO: Nao foi possivel abrir o diretorio.");
		return root;
	}

	printf("Lendo arquivos do diretorio: %s\n", dir_path);

	while ((entry=readdir(dir)) !=NULL) {
		size_t len=strlen(entry->d_name);

		if (len > 4 && strcmp(entry->d_name + len - 4, ".txt")==0) {
			snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);
			root=process_document(root, filepath, entry->d_name);
		}
	}

	closedir(dir);
	return root;
}

int main() {
	Node* root=NULL;
	const char* documents_dir="./docs";
	printf("=============================================\n");
	printf("Mini-buscador de Documentos\n");
	printf("=============================================\n");
	root=read_directory(root, documents_dir);

	if (root==NULL) {
		printf("\nNenhum documento inserido.\n");
		return 0;
	}

	printf("\nDocumentos processados e inseridos na arvore.\n\n");
	int height=calculateHeight(root);
	printf("------------------------------------------\n");
	printf("Altura da arvore: %d\n", height);
	printf("------------------------------------------\n\n");
	char keyword_to_search[]="programacao";
	printf("--- Iniciando busca e medindo o tempo para '%s' ---\n\n",
		keyword_to_search);
	clock_t start=clock();
	search(root, keyword_to_search);
	clock_t end=clock();
	double time_spent=(double)(end - start) / CLOCKS_PER_SEC;
	printf("\n------------------------------------------\n");
	printf("Tempo total de busca: %f segundos\n", time_spent);
	printf("------------------------------------------\n");
	freeTree(root);
	printf("\nMemoria da arvore liberada.\n");
	return 0;
}
