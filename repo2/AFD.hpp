#pragma once
#include<iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cstring>
#include <map>


class AFD{
private:
    int NUM_ESTADOS;
    int NUM_ALFABETO; 
    int NUM_PALAVRAS;
    
    char estadoInicial;
    std::string estadosFinais;
    
    std::unique_ptr<char[]> estados;
    std::unique_ptr<char[]> alfabeto;


    std::vector<std::string> palavras;
    std::vector<char> percurso;

    std::unique_ptr<char[]> getTransicoes(std::string transicao);
    std::string trataEntradasDasLinhas(std::string);
    void setPalavras(std::vector<std::string> entradas, int);
    char getEstado(int);
    char getSimbolo(int);

public:
    bool isEstadoFinal(char);
    char getEstadoInicial();
    char getProxEstado(char,char);
    void addPercurso(char);
    void setAlfabeto(std::string);
    void setEstados(std::string);
    void setTransicaoTabela(std::vector<std::string> entradas);
    void limpaPercurso();
    std::string getPalavras(int);
    std::vector<char> getPercurso();
    int getNumPalavras();

    AFD();
    AFD(std::vector<std::string>);
    ~AFD();
    std::map<std::pair<char,char>,std::vector<char>> tabelaTransicoes;
    
    
};

