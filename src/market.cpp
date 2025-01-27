#include "../include/market.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <ctime>


Ativo::Ativo(){}

int Ativo::getQuantidade() const { 
    return quantidade; 
}

int Ativo::getDisponivel() const { 
    return disponivel; 
}

Acao& Ativo::getAcao(){
    return acao;
}

void Ativo::setDisponivel(int quant){
    disponivel += quant;
}

void Ativo::atualizarPreco(float preco) {
    acao.setPreco(preco);
    this->setPreco(preco);
    historicoPrecos.push_back(acao.getPreco());
}
const std::vector<float>& Ativo::getHistorico() const {
    return historicoPrecos;
}

Mercado::Mercado(){}

void Mercado::addAtivo(string nome, string codigo, float valor, int quant, vector<float>& historico) {
    ativos[codigo] = Ativo(nome, codigo, valor, quant, historico);
}

void Mercado::removeAtivo(Ativo& atv){
    string cod = atv.getCodigo();
    for(auto& usr: usuarios){
        if(usr.second.getCarteira().find(atv.getAcao()) != usr.second.getCarteira().end()){
            Venda(usr.first, cod, usr.second.getCarteira()[atv.getAcao()]);
        }
    }
    ativos.erase(cod);
}

void Mercado::addUsuario(Usuario usuario) {
    usuarios[usuario.getNome()] = usuario;
}

void Mercado::removeUsuario(Usuario& user){
    for(auto& atv: user.getCarteira()){
        Venda(user.getNome(), atv.first.getCodigo(), atv.second);
    }
    usuarios.erase(user.getNome());
}

bool Mercado::Compra(string usuario, string codigo, int quantidade){
    Usuario& user = getUsuario(usuario);
    Ativo& atv = getAtivo(codigo);
    
    if(atv.getDisponivel() < quantidade){
        cout << "Essa quantidade da ação não está disponível para compra." << endl;
        return false;
    }
    float custo = atv.getPreco() * quantidade;
    float saldo = user.getSaldo();

    if(saldo < custo){
        cout << "Saldo insuficiente para comprar essa quantidade da ação." << endl;
        return false;
    }

    user.comprarAcao(atv.getAcao(), quantidade);
    atv.setDisponivel(-quantidade);
    Transacao op = Transacao(user.getNome(), atv.getAcao(), quantidade, custo, TipoTransacao::COMPRA);
    operacoes.push_back(op);
    return true;
}

bool Mercado::Venda(string usuario, string codigo, int quantidade){
    Usuario& user = getUsuario(usuario);
    Ativo& atv = getAtivo(codigo);
    
    if(user.getCarteira()[atv.getAcao()] < quantidade){
        cout << "Venda mal sucedida: Não possui essa quantidade de ações." << endl;
        return false;
    }

    float ganho = atv.getPreco() * quantidade;

    user.venderAcao(atv.getAcao(), quantidade);
    atv.setDisponivel(quantidade);
    Transacao op = Transacao(user.getNome(), atv.getAcao(), quantidade, ganho, TipoTransacao::VENDA);
    operacoes.push_back(op);

    return true;
}

void Mercado::LerTransacao(string tempo, string usuario, string tipo, string codigo, int quantidade){
    Transacao op = Transacao(tempo, usuario, tipo, ativos[codigo].getAcao(), quantidade);
    operacoes.push_back(op);
}

float calcVariacao() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(-0.05f, 0.05f);
    return distrib(gen);
}

void Mercado::atualizarMercado(){
    for(auto& atv : ativos){
        float variation = calcVariacao();
        float newPrice = atv.second.getPreco() * (1 + variation);

        atv.second.atualizarPreco(newPrice);
    }
}

Ativo& Mercado::getAtivo(const std::string& codigo) {
    return ativos.find(codigo)->second;
}

Usuario& Mercado::getUsuario(const std::string& nome) {
    return usuarios.find(nome)->second;
}

map<string, Ativo>& Mercado::getAtivos(){
    return this->ativos;
}

map<string, Usuario>& Mercado::getUsuarios(){
    return this->usuarios;
}

vector<Transacao>& Mercado::getTransacoes(){
    return this->operacoes;
}
