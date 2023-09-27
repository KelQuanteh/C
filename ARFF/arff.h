//O código dentro dessas diretivas condicionais só será incluído uma vez durante a compilação, mesmo que o cabeçalho seja incluído em vários arquivos fonte.
#ifndef __ARFF__
#define __ARFF__


//Esta estrutura é usada para representar as informações sobre os atributos presentes em um arquivo ARFF
typedef struct {
  char *rotulo;
  char *tipo;
  char **categorias;
} atributo;

//exibir informações sobre os atributos. Recebe como argumento um ponteiro para um vetor de estruturas atributo e a quantidade de atributos.
void exibe_atributos(atributo *infos, int quantidade);

//contar o número de atributos em um arquivo ARFF. Recebe como argumento um ponteiro para um arquivo ARFF e retorna a contagem de atributos.
int conta_atributos(FILE *arff);

//processar as categorias de um atributo nominal, dividindo-as em strings separadas e armazenando-as na estrutura atributo. 
//Recebe como argumento um ponteiro para um atributo e uma string contendo as categorias.
void processa_categorias(atributo *elemento, char *categorias);

//processar todos os atributos de um arquivo ARFF e retornar um vetor de estruturas atributo que representa esses atributos. 
//Recebe como argumento um ponteiro para um arquivo ARFF e a quantidade de atributos a serem processados.
atributo* processa_atributos(FILE *arff, int quantidade);

//Esta linha fecha as diretivas condicionais #ifndef e #define, garantindo que o conteúdo do cabeçalho seja incluído apenas uma vez.
#endif