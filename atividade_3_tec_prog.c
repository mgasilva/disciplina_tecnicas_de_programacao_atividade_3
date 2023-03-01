/******************************************************************************
UNIFACS EAD LAUREATE
CURSO DE CIENCIA DA COMPUTACAO
DISCIPLINA TECNICAS DE PROGRAMACAO
ESTUDANTE MARCELO GOES ALVES DA SILVA
ATIVIDADE 3
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct cliente
{
    char nome[31];
    double montante;
    int ano;
};

struct cliente *lista_clientes = NULL;
int tam_lista = 10;

void inclui_cliente();
void imprime_lista();
void remove_cliente();
void atualiza_cliente();
void zera_montantes();
void lista_melhor();
void imprime_cliente();

int main()
{

    int opcao = 0;
  
//inicializa o nosso bloco inicial de 10 clientes;

    if (!(lista_clientes = (struct cliente *) malloc(tam_lista*sizeof(struct cliente))))
    {
        puts("Erro de memória");
        return 1;
    }
        for (int i = tam_lista-10; i< tam_lista; i++)
    {
    (lista_clientes+i)->ano = 0;
    }

//loop principal:
  
  do
  {
      puts("Qual o seu comando?");
      puts("1 - Incluir um novo cliente");
      puts("2 - Remover um cliente");
      puts("3 - Atualizar o montante de compras do cliente realizadas no mês corrente");
      puts("4 - Zerar todos os montantes por ocasião da virada do mês");
      puts("5 - Listar o cliente melhor comprador");
      puts("6 - Exibir um montante de compras de um cliente específico");
      puts("0 - Sair");
      
      scanf("%d", &opcao);
      getchar();
      
      switch (opcao)
      {
          case 1: inclui_cliente();
          break;
          
          case 2: remove_cliente();
          break;
          
          case 3: atualiza_cliente();
          break;
          
          case 4: zera_montantes();
          break;
          
          case 5: lista_melhor();
          break;
          
          case 6: imprime_cliente();
          break;
          
          //opção secreta (debug)
          case 7: imprime_lista();
          break;
         
      }
  }
  while (opcao !=0);

  free(lista_clientes);
  return(0);
}

void inclui_cliente()
{
    char novo_nome[31];
    float nova_despesa = 0.0;
    int novo_ano = 0;
    int posicao = 0;
    
    puts("Qual o nome do cliente?");
    do
    {
    fflush(stdin);
    fgets(novo_nome,31,stdin);
    if (!strcmp(novo_nome,"\n")) puts ("Nome inválido.  O nome não pode ser vazio.");
    } while (!strcmp(novo_nome,"\n"));
    strtok(novo_nome,"\n");
    puts("Qual o montante gasto pelo cliente?");
    scanf("%f", &nova_despesa);
    getchar();
    puts("Qual o ano de nascimento do cliente?");
    do
    {
    fflush(stdin);
    scanf("%d", &novo_ano);
    getchar();
    if (!novo_ano) puts ("Ano inválido! O ano de nascimento do cliente deve ser diferente de zero.");
    } while (!novo_ano);
    
    //vamos verificar se há posições livres: isto se denota por um ano de nascimento = 0;
    
    while ((lista_clientes+posicao)->ano)
    {
        if (posicao == tam_lista)
        {
            tam_lista+=10;
            lista_clientes = realloc(lista_clientes,tam_lista*sizeof(struct cliente));
        }
        else
        {
        ++posicao;
        }
    }
    
    strcpy((lista_clientes+posicao)->nome, novo_nome);
    (lista_clientes+posicao)->montante = nova_despesa;
    (lista_clientes+posicao)->ano = novo_ano;
    
    return;
}

void imprime_lista()
{
    int conta = 0;
    for (int i=0; i < tam_lista; ++i)
    {
        if ((lista_clientes+i)->ano)
        {
        ++conta;
        printf("Registro %d:\n", i);
        printf("Cliente: %s\n", (lista_clientes+i)->nome);
        printf("Montante: %.2f\n", (lista_clientes+i)->montante);
        printf("Ano: %d\n\n", (lista_clientes+i)->ano);
        }
    }
    printf("Quantidade de registros: %d\n", conta);
    printf("Tamanho total do vetor: %d\n", tam_lista);
    return;
}

void remove_cliente()
{
    _Bool encontrado = 0;
    char novo_nome[31];
    puts("Digite o nome do cliente que deseja remover:");
    fflush(stdin);
    fgets(novo_nome,31,stdin);
    strtok(novo_nome,"\n");
    for (int i=0; i < tam_lista; ++i)
    {
        if(!strcmp(novo_nome, (lista_clientes+i)->nome))
        {
            encontrado = 1;
            (lista_clientes+i)->ano = 0;
        }
        if (encontrado) break;
    }
    if (encontrado) printf("%s apagado com sucesso.\n", novo_nome);
    else puts("Cliente não encontrado.");
    return;
}

void atualiza_cliente()
{
    _Bool encontrado = 0;
    char novo_nome[31];
    float novo_montante;
    puts("Digite o nome do cliente que deseja atualizar:");
    fflush(stdin);
    fgets(novo_nome,31,stdin);
    strtok(novo_nome,"\n");
    puts("Digite o novo montante:");
    scanf("%f", &novo_montante);
    getchar();
    for (int i=0; i < tam_lista; ++i)
    {
        if(!strcmp(novo_nome, (lista_clientes+i)->nome))
        {
            encontrado = 1;
            (lista_clientes+i)->montante = novo_montante;
        }
        if (encontrado) break;
    }
    if (encontrado) puts("Montante atualizado com sucesso.");
    else puts("Cliente não encontrado.");
    return;
}

void zera_montantes()
{
    for (int i=0; i<tam_lista; ++i)
    {
        (lista_clientes+i)->montante = 0;
    }
    return;
}

void lista_melhor()
{
    float maior_montante = 0;
    int melhor_registro = 0;
    for (int i=0; i<tam_lista; ++i)
    {
        if ((lista_clientes+i)->montante > maior_montante)
        {
            melhor_registro = i;
            maior_montante = (lista_clientes+i)->montante;
        }
    }
    if (!maior_montante)
    {
        puts("Não houve cliente melhor comprador este mês pois não constam compras.");
    }
    else
    {
    printf("O cliente melhor comprador este mês foi %s que comprou %.2f.\n", (lista_clientes+melhor_registro)->nome, (lista_clientes+melhor_registro)->montante);
    }
    return;
}

void imprime_cliente()
{
    _Bool encontrado = 0;
    char nome_buscado[31];
    puts("Digite o nome do cliente que deseja localizar:");
    fflush(stdin);
    fgets(nome_buscado,31,stdin);
    strtok(nome_buscado,"\n");
    for (int i=0; i < tam_lista; ++i)
    {
        if(!strcmp(nome_buscado, (lista_clientes+i)->nome))
        {
            encontrado = 1;
            printf("O cliente %s comprou este mês o montante de R$ %.2f.\n", nome_buscado, (lista_clientes+i)->montante);
        }
    }
    if (!encontrado) puts("Cliente não encontrado.");
    return;
}
