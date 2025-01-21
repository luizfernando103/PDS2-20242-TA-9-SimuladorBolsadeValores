#include <iostream>

#include "market.hpp"
#include "simulation.hpp"

using namespace std;

// DEFINE O NÚMERO DE OSCILAÇÕES QUE CADA AÇÃO VAI TER QUANDO A BOLSA FECHAR (A OPÇÃO SAIR FOR SELECIONADA).
#define NUM_ATUALIZACOES 1

int main() {
    Mercado mkt = Mercado();
    lerDados(mkt);
    
    Interface(mkt);

    for(int i=0; i<NUM_ATUALIZACOES; i++){
        mkt.atualizarMercado();
    }

    if(salvarDados(mkt)){
        cout << "Dados salvos com sucesso!" << endl;
    }

    return 0;
}