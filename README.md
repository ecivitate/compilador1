# Compilador G-V1

Compilador didático para a linguagem **G-V1**, desenvolvido para a disciplina de Compiladores.

O projeto utiliza:

- **Flex** para gerar o analisador léxico;
- **Bison** para gerar o analisador sintático;
- **C** para AST, tabela de símbolos, análise semântica e geração de código;
- **Assembly MIPS** como código de saída.

---

## Estrutura do projeto

```text
.
├── src/
│   ├── g-v1.l
│   ├── g-v1.y
│   ├── ast.c
│   ├── ast.h
│   ├── symtable.c
│   ├── symtable.h
│   ├── semantic.c
│   ├── semantic.h
│   ├── codegen.c
│   └── codegen.h
├── tests/
│   ├── corretos/
│   └── errados/
│       ├── sintatico/
│       └── semantico/
├── Makefile
├── test_run.sh
└── README.md 
``` 

## Como usar

```bash
make 
```  
para compilar em g-v1

```bash
make test
```  
para executar os testes e criar o assembly na pasta tests

```bash
make clean
```  
para limpar os executáveis

