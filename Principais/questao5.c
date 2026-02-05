//Para uma determinada edição dos jogos olímpicos, calcule o peso médio dos atletas medalhistas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questao5.h"

#define MAX_LINE 262144

int contemElemento(int *lista, int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (lista[i] == valor)
            return 1;
    }
    return 0;
}

int main(){
    //primeireo passo será guardar o ID de todos os atletas que ganharam algum jogo de determinada edição.

    double imc_total=0,qtdd_atletas=0;// esse será o que a questão pede.

    FILE *arquivo = fopen("arquivoscsvs/results/results.csv","r");//pega os arquivos com todos os jogos.
    int edicao_escolhida=9999;
    char linha[MAX_LINE];

    while (1==1){
        printf("Digite qual edição das olímpiadas você deseja calcular o peso médio:");
        scanf("%d", &edicao_escolhida);
        if(edicao_escolhida%2 != 0){
            printf("Nesse ano não ouve competição.");
            return 0;// realiza o fim do programa.
        }else{
            break;
        }
    }

    //agora precisamos fazer uma lista dinâmica para armazenar todos os ID's dos atletas que ganharma uma olípiada em determinado ano.
    int *lista = NULL;
    int tamanho = 0;

    fgets(linha, MAX_LINE, arquivo);//apenas para remover o cabeçalho.

    while(fgets(linha, MAX_LINE, arquivo)){
        char *year, *type, *discipline, *event, *as, *athlete_id, *noc, *team, *place, *tied, *medal;

        year = strtok(linha, ",");
        type = strtok(NULL, ",");
        discipline = strtok(NULL, ",");
        event = strtok(NULL, ",");
        as = strtok(NULL, ",");
        athlete_id = strtok(NULL, ",");
        noc = strtok(NULL, ",");
        team = strtok(NULL, ",");
        place = strtok(NULL, ",");
        tied = strtok(NULL, ",");
        medal = strtok(NULL, ",");

        if(edicao_escolhida!=(int)(atoi(year))){
            continue;// Se o ano da competição for direfernte, ele não deve contabilizar.
        }
        if (medal==NULL ||strlen(medal) == 0 ) {//vê se ganhou medalha.
            continue; // não ganhou medalha
        }

        if (athlete_id!=NULL && strlen(athlete_id) > 0 ) {//verifica se há String do id do atleta
            int id = atoi(athlete_id); // converte de string para int
            int *temp = realloc(lista, (tamanho + 1) * sizeof(int));//refaz a lista adicionando esse id.
            if (temp == NULL) {
                free(lista);
                printf("Erro de memória.\n");
                return 1;//precisa ter o return, pq se não dará erro.
            }
            lista = temp;
            lista[tamanho] = id;
            tamanho++;
        }
    }
    fclose(arquivo);//não é mais necessário ter esse arquivo aberto.

    FILE *bio = fopen("arquivoscsvs/athletes/bios_locs.csv","r");

    fgets(linha, MAX_LINE, bio);//apenas para remover o cabeçalho.    

    while(fgets(linha, MAX_LINE, bio)){
        //o arquivo original CSV é:
        //athlete_id,name,born_date,born_city,born_region,born_country,NOC,height_cm,weight_kg,
        char *id, *name, *born, *born_city, *born_region, *born_country, *NOC, *height, *weight;
        double peso,altura,imc;

        //aqui abaixo está o reconhecimendo dos dados:

        id = strtok(linha, ",");//parte que também nos interessa.
        name = strtok(NULL, ",");
        born = strtok(NULL, ",");
        born_city = strtok(NULL, ",");
        born_region = strtok(NULL, ",");
        born_country = strtok(NULL, ",");
        NOC = strtok(NULL, ",");
        height = strtok(NULL, ",");//parte que também nos interessa.
        weight = strtok(NULL, ",");//parte que nos interessa.

        if(height==NULL || strlen(height)==0 || weight==NULL || strlen(weight)==0 || id==NULL || strlen(id)==0){
            continue;
        }

        if(contemElemento(lista,tamanho,atoi(id)) == 1){//funçãpo para percorrer a lista e verificar se o id está presente na lista dos ganhadores.
            peso = atoi(weight);
            altura = atoi(height);
            imc = peso/(altura*altura);//fazer o calculo do imc desse atleta.
            imc_total += imc;//adicionar o imc no imc total.
            qtdd_atletas += 1;//adiciona um atleta na quantidade de atletas total daquele ano.
        }else{
            continue;
        }
    }
    fclose(bio);//não é mais necessário ter esse arquivo aberto.
    if(qtdd_atletas!=0){
        double imc_medio= imc_total/qtdd_atletas;
        printf("O IMC médio na olímpiada do ano de %lf foi de: %.2lf",edicao_escolhida,imc_medio);
    }
    return 0;
}
 