#include "../include/transaction.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

Transacao::Transacao(string user, Acao stock, int quant, float valor, TipoTransacao t):
 usuario(user), acao(stock), quantidade(quant), preco(valor), tipo(t), momento(std::time(nullptr)) {}

time_t stringParaTimeT(const std::string& dataHora) {
    struct tm tm = {0};
    
    std::stringstream ss(dataHora);
    ss >> std::get_time(&tm, "%d/%m/%Y-%H:%M:%S");
    
    if (ss.fail()) {
        std::cout << "Falha ao converter data/hora." << std::endl;
        return -1;
    }

    return mktime(&tm);
}

Transacao::Transacao(string tempo, string usuario, string tipo, Acao stock, int quant){
    this->momento = stringParaTimeT(tempo);
    this->usuario = usuario;
    this->acao = stock;
    this->quantidade = quant;
    this->tipo = (tipo == "Compra") ? TipoTransacao::COMPRA : TipoTransacao::VENDA;
    this->preco = acao.getPreco()*quant;
}

Acao Transacao::getAcao() const {
    return acao;
}

int Transacao::getQuantidade() const {
    return quantidade;
}

float Transacao::getPreco() const {
    return preco;
}

TipoTransacao Transacao::getTipo() const {
    return tipo;
}

std::time_t Transacao::getMomento() const {
    return momento;
}

std::string Transacao::toString() const {
    std::tm* local_time = std::localtime(&momento);

    std::ostringstream oss;
    oss << std::put_time(local_time, "%d/%m/%Y-%H:%M:%S") << "|"
    << usuario << "|" 
    << (tipo == TipoTransacao::COMPRA ? "Compra" : "Venda") << "|"
    << acao.getCodigo() << "|"
    << quantidade << "|"
    << std::fixed << std::setprecision(2) << preco;
    return oss.str();
}
