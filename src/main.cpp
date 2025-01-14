#include <iostream>

#include "market.hpp"

using namespace std;

int main() {
    Mercado mkt = Mercado();
    mkt.addAcao("Petrobras", "PETR4", 547.0f, 100000);
    mkt.addAcao("Vale", "VALE3 ", 289.0f, 200000);

    Acao& acao = mkt.getAcao("PETR4");
    cout << acao.getEmpresa() << "(" << acao.getCodigo() << "): " << acao.getPreco() << endl;
    mkt.atualizarMercado();
    cout << acao.getEmpresa() << "(" << acao.getCodigo() << "): " << acao.getPreco() << endl;

    return 0;
}
