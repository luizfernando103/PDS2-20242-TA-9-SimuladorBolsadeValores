#include "market.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <stdexcept>

Ativo::Ativo(){}
Mercado::Mercado(){}

void Mercado::addAcao(string nome, string codigo, float valor, int quant) {
    ativos[codigo] = Ativo(nome, codigo, valor, quant);
}

void Mercado::addUsuario(Usuario usuario) {
    usuarios[usuario.getNome()] = usuario;
}

float calcVariacao() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(-0.05f, 0.05f);
    return distrib(gen);
}

void Mercado::atualizarMercado(){
    for(auto& stock : ativos){
        float variation = calcVariacao();
        float newPrice = stock.second.getPreco() * (1 + variation);
        stock.second.atualizarPreco(newPrice);
    }
}

Acao& Mercado::getAcao(const std::string& codigo) {
    return ativos.find(codigo)->second;
}

Usuario& Mercado::getUsuario(const std::string& nome) {
    return usuarios.find(nome)->second;
}
