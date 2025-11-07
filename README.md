# 🧩 Mini Buscador de Documentos em C  

![C](https://img.shields.io/badge/Language-C-blue?logo=c)
![Status](https://img.shields.io/badge/status-concluído-success)
![License](https://img.shields.io/badge/license-MIT-green)


---

## 🧠 Sobre o Projeto  

O **Mini Buscador de Documentos** é um programa em **C** desenvolvido para criar milhares de arquivos de texto (`.txt`) com conteúdo aleatório.  
Ele foi criado com o objetivo de **simular grandes volumes de dados** e **testar o desempenho** de aplicações que lidam com leitura e indexação de arquivos.  

---

## ⚙️ Funcionalidades  

✅ Gera automaticamente **milhares de documentos `.txt`**  
✅ Cria conteúdos com **palavras técnicas de tecnologia e programação**  
✅ Exibe o **progresso no terminal**  
✅ Cria automaticamente a pasta `docs/` para armazenar os arquivos  
✅ Código leve e eficiente, sem dependências externas  

---

## 📁 Estrutura do Projeto  
gerar_docs.c
docs/
├── doc_00001.txt
├── doc_00002.txt
├── ...
└── doc_10000.txt

 ## 🚀 Como Compilar e Executar  

### 1️⃣ Requisitos  
- Compilador **GCC** instalado.  
- Sistema operacional compatível com C padrão (Windows, Linux ou macOS).  

### 2️⃣ Compilação  
No terminal, use o comando:  

gcc gerar_docs.c -o gerar_docs
3️⃣ Execução
Após compilar, execute:

```bash
Copiar código
./gerar_docs
O programa criará automaticamente a pasta docs/ e começará a gerar os arquivos.

🧾 Exemplo de Saída no Terminal
Diretório 'docs' criado para os documentos.
Iniciando a criação de 10000 documentos...
 - 1000 documentos criados.
 - 2000 documentos criados.
 - 3000 documentos criados.
 ...
 - 10000 documentos criados.

--- SUCESSO! ---
Total de 10000 documentos criados em 18.47 segundos.

📄 Exemplo de Arquivo Gerado (doc_00001.txt)
computador estrutura dados algoritmo mini sistema busca desempenho 
trabalho internet otimizacao binaria documento tempo projeto memoria 
universidade linguagem cpu analise ...
```

💡 Possíveis Aplicações

🧩 Testes de indexadores e motores de busca <br>
🧠 Simulações de processamento e leitura de arquivos <br>
📚 Criação de datasets artificiais <br>
⚙️ Análise de desempenho e otimização de I/O <br> 

