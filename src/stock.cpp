#include "stock.hpp"

Acao::Acao(){}

Acao::Acao(const std::string& nome, const std::string& cod, float preco)
: empresa(nome), codigo(cod), valorAtual(preco) {}

void Acao::atualizarPreco(float preco) {
    historicoPrecos.push_back(valorAtual);
    valorAtual = preco;
}

std::string Acao::getCodigo() const {
    return codigo;
}

std::string Acao::getEmpresa() const {
    return empresa;
}

float Acao::getPreco() const {
    return valorAtual;
}

const std::vector<float>& Acao::getHistorico() const {
    return historicoPrecos;
}

