#include "AFD.hpp"

AFD::AFD(std::vector<std::string> entradas)
{
    this->setEstados(entradas[0]);
    this->setAlfabeto(entradas[1]);
    this->setTransicaoTabela(entradas);

}
AFD::AFD(){

}
AFD::~AFD()
{
}

void AFD::setAlfabeto(std::string alfabeto){
    std::string alfabetoPurosString = trataEntradasDasLinhas(alfabeto);
    
    this->NUM_ALFABETO = alfabetoPurosString.size();

    this->alfabeto = std::make_unique<char[]>(this->NUM_ALFABETO);
   
    strncpy( this->alfabeto.get(), alfabetoPurosString.c_str(), this->NUM_ALFABETO);
}

void AFD::setEstados(std::string estados){

    std::string estadosPurosString = trataEntradasDasLinhas(estados);

    this->NUM_ESTADOS = estadosPurosString.size();

    this->estados = std::make_unique<char[]>(this->NUM_ESTADOS);
   
    strncpy( this->estados.get(), estadosPurosString.c_str(), this->NUM_ESTADOS);
}

std::string AFD::trataEntradasDasLinhas(std::string entradaString){
    std::string entradaValoresBrutos = entradaString;
    entradaValoresBrutos.erase(std::remove_if(entradaValoresBrutos.begin(),entradaValoresBrutos.end(),::isspace),entradaValoresBrutos.end());

    return entradaValoresBrutos;
}

void AFD::setTransicaoTabela(std::vector<std::string> entradas){

    for (size_t i = 0, k = 2; i < NUM_ESTADOS; i++,k++)
    {
        auto transicoes = getTransicoes(entradas[k]);

        for (size_t j = 0; j < NUM_ALFABETO; j++)
        {
            char estado = getEstado(i);
            char simbolo = getSimbolo(j);
            std::pair<char,char> key = std::make_pair(estado,simbolo);
            char proxEstado = transicoes[j];
            this->tabelaTransicoes[key].push_back(proxEstado);
        }
        
        if (i == NUM_ESTADOS-1)
        {
            this->estadoInicial = entradas[++k][0];
            this->estadosFinais = trataEntradasDasLinhas(entradas[++k]);
            setPalavras(entradas,k);       
        }
        
    }
    
}

std::unique_ptr<char[]> AFD::getTransicoes(std::string transicao){
        std::string transicoesPuras = trataEntradasDasLinhas(transicao);
        auto transicoes = std::make_unique<char[]>(this->NUM_ALFABETO);
        strncpy(transicoes.get(), transicoesPuras.c_str(), this->NUM_ALFABETO);
        return transicoes;
}

void AFD::setPalavras(std::vector<std::string> entradas, int pos){
    this->NUM_PALAVRAS = std::stoi(entradas[++pos]);
    for (size_t i = ++pos; i < pos + NUM_PALAVRAS; i++)
    {
        std::string palavra = entradas[i];
        palavra.erase(std::remove(palavra.begin(), palavra.end(), '\r'), palavra.end() );
        this->palavras.push_back(palavra);
    }
    
}

void AFD::addPercurso(char estadoPercorrido){
    this->percurso.push_back(estadoPercorrido);
}

void AFD::limpaPercurso(){
    this->percurso.clear();
}

std::vector<char> AFD::getPercurso(){
    return this->percurso;
};


char AFD::getEstado(int i){
    return this->estados[i];
};

char AFD::getSimbolo(int j){
    return this->alfabeto[j];
};

char AFD::getProxEstado(char estado, char simbolo){
    std::pair<char,char> key = std::make_pair(estado,simbolo);    
    return this->tabelaTransicoes[key][0];
}
std::string AFD::getPalavras(int i){
    return this->palavras[i];
};

int AFD::getNumPalavras(){
    return this->NUM_PALAVRAS;
};

char AFD::getEstadoInicial(){
    return this->estadoInicial;
}

bool AFD::isEstadoFinal(char estado){
    size_t numEstadosFinais = this->estadosFinais.size();
    for (size_t i = 0; i < numEstadosFinais; i++)
        if (estado == this->estadosFinais[i])return true;
    return false;
    
}