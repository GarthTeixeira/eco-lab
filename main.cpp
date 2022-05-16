#include "AFD.hpp"
#include <fstream> // for file-access
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <algorithm>


using namespace std;

void mostrarPercurso(AFD *afd){
    std::vector<char> estadosPercorridos = afd->getPercurso();
    cout<<endl<<estadosPercorridos[0];
    for (size_t i = 1; i < estadosPercorridos.size(); i++)
    {
        cout<<"->"<<estadosPercorridos[i];
    }
}

bool testarPalavra(AFD *afd,std::string palavraAnalisada){
  
    char proximoEstado = afd->getEstadoInicial();     

    int fimSequencia = palavraAnalisada.size();

    for (size_t i = 0; i < fimSequencia; i++)
    {
        char simbolo = palavraAnalisada[i];
        afd->addPercurso(proximoEstado);
        proximoEstado = afd->getProxEstado(proximoEstado,simbolo);
    }
    afd->addPercurso(proximoEstado);
    return afd->isEstadoFinal(proximoEstado)?true:false;
    
}

void testarTodasPalavras(AFD *afd){
    int numPalavras = afd->getNumPalavras();
    cout<<"Testando as "<< numPalavras <<" palavras declaradas..."<<endl;
    for (size_t i = 0; i < numPalavras; i++)
    {
        std::string palavraAnalisada = afd->getPalavras(i);
        cout<<"\n/-----------------------------/"<<endl;
        cout<<"Palavra analisada("<<palavraAnalisada<<");\n";
        cout<<"Palavra aceita: ";
        if(testarPalavra(afd,palavraAnalisada))
            cout<<"OK!;";
        else
            cout<<"Falhou;";
        cout<<endl;
        cout<<"Estados Percorridos: ";
        mostrarPercurso(afd);
        afd->limpaPercurso();
    }
    cout<<"\n/-----------------------------/"<<endl;
    cout<<"Fim... \n";
}

void inicializar(AFD *afd ,vector<string> entradas){
    afd->setEstados(entradas[0]);
    afd->setAlfabeto(entradas[1]);
    afd->setTransicaoTabela(entradas);
}

void algoritmoAFD(AFD *afd ,vector<string> entradas){
    inicializar(afd,entradas);
    testarTodasPalavras(afd);
}

int main(int argc, char *argv[]){
    
    vector<string> entradas;
    string entradaEmLinhasTxt;
    
        int i = 0;
        for(i = 0;getline(cin, entradaEmLinhasTxt); i++)  //input from the file in.txt
            {
                entradas.push_back(entradaEmLinhasTxt);
            }

        AFD automatoFinitoDeterministico;
        algoritmoAFD(&automatoFinitoDeterministico,entradas);

    return 0;
}