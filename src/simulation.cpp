#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

#include "../include/simulation.hpp"

void Interface(Mercado& mkt){
    system("clear");

    char opcao='0';
    string entrada;
    bool exit = false;

    while(opcao != 'x'){
        Menu();

        cin >> opcao;
        opcao = tolower(opcao);

        system("clear"); // Limpa a tela

        switch(opcao){
            case 'q':
                QuadroAcoes(mkt);
                break;
            case 'p':
                HistoricoAcao(SelecionarAcao(mkt));
                break;
            case 'a':
                ConsultarDisponibilidade(SelecionarAcao(mkt));
                break;
            case 'u':
                Carteira(SelecionarUsuario(mkt));
                break;
            case 'b':
                ComprarAcao(mkt, SelecionarAcao(mkt), SelecionarUsuario(mkt));
                break;
            case 's':
                VenderAcao(mkt, SelecionarAcao(mkt), SelecionarUsuario(mkt));
                break;
            case 'd':
                AdminMenu(mkt);
                break;
            case 'x':
                exit = Sair();
                break;
            default:
                cout << "Opção inválida!" << endl;
                cout << "Tente novamente." << endl;
                break;
        }
        if(!exit){
            cout << "Pressione Enter para voltar ao menu" << endl;
            cin.ignore();
            cin.get(); // Aguarda o usuário pressionar Enter
            system("clear"); // Limpa a tela
        }
        else{
            return;
        }
    }
}

bool salvarDados(Mercado& m){
    ofstream arq("dados.txt");
    arq << m.getAtivos().size() << endl;

    for(const auto& p : m.getAtivos()){
        Ativo atv = p.second;
        arq << atv.getEmpresa() << "|" << atv.getCodigo() << "|" << atv.getPreco() << "|" << atv.getQuantidade() << "|";

        vector<float> precos = atv.getHistorico();
        int s = precos.size();

        for(int j = 0; j < s; ++j){
            arq << precos[j];
            if(j != s-1){
                arq << "-";
            }
        }
        arq << endl;
    }

    arq << endl;

    arq << m.getUsuarios().size() << endl;
    for(const auto& p: m.getUsuarios()){
        Usuario u = p.second;
        arq << u.getNome() << "|" << u.getSaldo() << "|" << u.getCarteira().size() << endl;
        for(const auto& p: u.getCarteira()){
            Acao acao = p.first;
            int quant = p.second;
            arq << acao.getCodigo() << "|" << quant << endl;
        }
        arq << endl;
    }

    arq << m.getTransacoes().size() << endl;
    for (const auto& op: m.getTransacoes()){
        arq << op.toString() << endl;
    }
    arq.close();

    return true;
}

void lerDados(Mercado& m) {
    ifstream arq("dados.txt");

    if (!arq.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    string line;
    int numAtivos, numUsuarios, numTransacoes;

    // Ler o número de ativos
    getline(arq, line);
    numAtivos = stoi(line);

    // Ler os ativos
    for (int i = 0; i < numAtivos; ++i) {
        getline(arq, line);
        stringstream ss(line);
        string empresa, codigo;
        float preco;
        int quantidade;

        getline(ss, empresa, '|');
        getline(ss, codigo, '|');
        ss >> preco;
        ss.ignore(); // Ignorar o '|'
        ss >> quantidade;
        ss.ignore(); // Ignorar o '|'
        
        string valores, valor;
        
        ss >> valores;
        //cout << "PRECOS: " << valores << endl;

        vector<float> precos;

        stringstream precosStream(valores);

        while (getline(precosStream, valor, '-')){
            float p = stof(valor);
            precos.push_back(p);
        }
        
        // Criar o ativo e adicionar ao mercado
        m.addAtivo(empresa, codigo, preco, quantidade, precos);
    }

    getline(arq, line); // Pulando linha em branco

    // Ler o número de usuarios
    getline(arq, line);
    numUsuarios = stoi(line);

    if(numUsuarios != 0){
        // Ler os usuários
        for (int i = 0; i < numUsuarios; ++i) {
            getline(arq, line);
            if (line.empty()) continue;  // Pular linhas vazias
            stringstream ss(line);
            string nome;
            float saldo;
            int numAcoes;

            getline(ss, nome, '|');
            ss >> saldo;
            ss.ignore(); // Ignorar o '|'
            ss >> numAcoes;

            // Criar o usuário e adicionar ao mercado
            Usuario usuario(nome, saldo);
            m.addUsuario(usuario);

            // Ler a carteira de ações do usuário
            for (int j = 0; j < numAcoes; ++j) {
                getline(arq, line);
                if (line.empty()) getline(arq, line); // Parar se encontrar uma linha vazia inesperada
                
                stringstream ss(line);
                string codigo;
                int quantidade;

                getline(ss, codigo, '|');
                ss >> quantidade;

                // Adicionar a ação à carteira do usuário
                Ativo& ativo = m.getAtivo(codigo);  // Assume que `getAtivo` retorna um Ativo existente
                Usuario& u = m.getUsuario(nome);
                u.depositar(ativo.getPreco() * quantidade);
                u.comprarAcao(ativo.getAcao(), quantidade);
                ativo.setDisponivel(-quantidade);
            }
            getline(arq, line);
        }
    }
    else{
        getline(arq, line);
    }
    // Ler o número de transações
    getline(arq, line);
    numTransacoes = stoi(line);

    for (int i = 0; i < numTransacoes; ++i){
        getline(arq, line);
        stringstream transacao_stream(line);
        string tempo, nome, tipo, ativo;
        int quantidade;
        float valor;

        getline(transacao_stream, tempo, '|');
        getline(transacao_stream, nome, '|');
        getline(transacao_stream, tipo, '|');
        getline(transacao_stream, ativo, '|');

        transacao_stream >> quantidade;
        transacao_stream.ignore(); // Ignorar o '|'
        transacao_stream >> valor;

        m.LerTransacao(tempo, nome, tipo, ativo, quantidade);
    }

    arq.close();
}

void Menu(){
    cout << setfill ('=') << setw(45) << " " << endl;
    cout << setfill (' ') << setw(30) << "MERCADO DE AÇÕES" << endl;
    cout << setfill ('=') << setw(45) << " " << endl;
    cout << setfill (' ') << setw(7) << "Menu:" << endl;
    cout << "  q - Quadro de ações;" << endl;
    cout << "  p - Histórico de preço de uma ação;" << endl;
    cout << "  a - Consultar disponibilidade de compra;" << endl;
    cout << "  u - Visualizar carteira de usuário;" << endl;
    cout << "  b - Comprar ação;" << endl;
    cout << "  s - Vender ação;" << endl;
    cout << "  d - Menu de administrador;" << endl;
    cout << "  x - SAIR." << endl;
    cout << setfill ('=') << setw(45) << " " << endl;
    cout << "Escolha uma opção: ";
}

void QuadroAcoes(Mercado& m){
    cout << setfill ('=') << setw(55) << " " << endl;
    cout << setfill (' ') << setw(15) << "CÓDIGO" << setw(15) << "EMPRESA" << setw(20) << "VALOR (R$)\n";
    cout << setfill ('=') << setw(55) << " " << endl;

    for (const auto& pair : m.getAtivos()) {
        const Ativo& ativo = pair.second;
        cout << setfill (' ')
             << setw(13) << ativo.getCodigo()
             << setw(17) << ativo.getEmpresa()
             << setw(15) << fixed << setprecision(2) << ativo.getPreco() << "\n";
    }

    cout << setfill ('=') << setw(55) << " " << endl;
}

Ativo& SelecionarAcao(Mercado& m){
    int cont, entrada = 0, tamanho = m.getAtivos().size();
    while(entrada < 1 || entrada > tamanho){
        cout << setfill ('=') << setw(40) << " " << endl;
        cont = 1;
        for(auto& ativo : m.getAtivos()){
        cout << setfill (' ') << setw(10) << "[" << cont << "] " << setw(15) << ativo.second.getCodigo() << endl;
        cont++;
        }
        cout << setfill ('=') << setw(40) << " " << endl;
        cout << "Escolha a ação: ";
        cin >> entrada;
        if(entrada < 1 || entrada > tamanho){
            system("clear");
            cout << "Opção inválida! Tente novamente." << endl;
            entrada = 0;
        }
    }
    cont = 1;
    for(auto& ativo : m.getAtivos()){
        if(cont==entrada){
            system("clear");
            return ativo.second;
        }
        cont++;
    }
    return (*m.getAtivos().begin()).second;
}

void HistoricoAcao(Ativo& atv){
    cout << setfill ('=') << setw(55) << " " << endl;
    cout << setfill (' ') << setw(3) << "[" << atv.getCodigo() << "] " <<"ULTIMOS 10 OU MENOS PREÇOS(R$) REGISTRADOS:\n";
    cout << setfill ('=') << setw(55) << " " << endl;
    int t = atv.getHistorico().size();
    for (int i = 0; i < 9 && i <= t; i++) {
        cout << setfill(' ') << setw(18) << i+1 << setw(20) << fixed << setprecision(2) << atv.getHistorico()[t-10+i] << endl;
    }
    cout << setfill(' ') << setw(22) << "10(ATUAL)" << setw(16) << fixed << setprecision(2) << atv.getPreco() << endl;
    cout << setfill ('=') << setw(55) << " " << endl;
}

void ConsultarDisponibilidade(Ativo& atv){
    cout << setfill ('=') << setw(40) << " " << endl;
    cout << setfill (' ') << setw(11) << "[" << atv.getCodigo() << "] " << atv.getEmpresa() << ":\n";
    cout << setfill (' ') << setw(28) << "Quantidade disponível: " << atv.getDisponivel() << "/" << atv.getQuantidade() << endl;
    cout << setfill (' ') << setw(23) << "Preço atual: " << fixed << setprecision(2) << atv.getPreco() << endl;
    cout << setfill ('=') << setw(40) << " " << endl;
}

Usuario& SelecionarUsuario(Mercado& m){
    int cont, entrada = 0, tamanho = m.getUsuarios().size();
    while(entrada < 1 || entrada > tamanho){
        cout << setfill ('=') << setw(40) << " " << endl;
        cont = 1;
        for(auto& usuario : m.getUsuarios()){
        cout << setfill (' ') << setw(10) << "[" << cont << "] " << setw(15) << usuario.second.getNome() << endl;
        cont++;
        }
        cout << setfill ('=') << setw(40) << " " << endl;
        cout << "Escolha o usuário: ";
        cin >> entrada;
        if(entrada < 1 || entrada > tamanho){
            system("clear");
            cout << "Opção inválida! Tente novamente." << endl;
            entrada = 0;
        }
    }
    cont = 1;
    for(auto& usuario : m.getUsuarios()){
        if(cont==entrada){
            system("clear");
            return usuario.second;
        }
        cont++;
    }
    return (*m.getUsuarios().begin()).second;
}

void Carteira(Usuario& usr){
    cout << setfill ('=') << setw(40) << " " << endl;
    cout << setfill (' ') << setw(6) << "[" << usr.getNome() << "] " << setw(10) << "Saldo em conta: " << usr.getSaldo() << endl;
    cout << setfill ('=') << setw(40) << " " << endl;
    int num = usr.getCarteira().size();
    if(num){
        for(auto& acao: usr.getCarteira()){
        cout << setfill (' ') << setw(7) << "[" << acao.first.getCodigo() << "]: " << setw(5) << acao.second << setw(5) << "R$ " << setw(8) << fixed << setprecision(2) << acao.first.getPreco()*acao.second << endl;
        }
    }
    else{
        cout << setfill (' ') << setw(35) << "O USUÁRIO NÃO POSSUI AÇÕES." << endl;
    }
    cout << setfill ('=') << setw(40) << " " << endl;
}

void ComprarAcao(Mercado& m, Ativo& atv, Usuario& usr){
    int quantidade;
    cout << "Informe a quantidade desejada para compra: ";
    cin >> quantidade;
    bool resposta = m.Compra(usr.getNome(), atv.getCodigo(), quantidade);
    if(resposta){
        cout << "\nCompra realizada com sucesso!" << endl;
    }
}

void VenderAcao(Mercado& m, Ativo& atv, Usuario& usr){
    int quantidade;
    cout << "Informe a quantidade que deseja vender: ";
    cin >> quantidade;
    bool resposta = m.Venda(usr.getNome(), atv.getCodigo(), quantidade);
    if(resposta){
        cout << "\nVenda realizada com sucesso!" << endl;
    }
}

void AdicionarAtivo(Mercado& m){
    string codigo, empresa;
    int quantidade;
    double preco;

    cout << "Informe o código do ativo: ";
    cin >> codigo;
    cout << "Informe a empresa: ";
    cin.ignore();
    getline(cin, empresa);
    cout << "Informe o preço da ação: ";
    cin >> preco;
    cout << "Informe a quantidade de ações a serem vendidas: ";
    cin >> quantidade;

    vector<float> historico;
    historico.push_back(preco);

    m.addAtivo(empresa, codigo, preco, quantidade, historico);
    cout << "\nAtivo adicionado com sucesso!" << endl;
}

void RemoverAtivo(Mercado& m, Ativo& atv){
    m.removeAtivo(atv);
    cout << "\nAtivo de ação removido com sucesso! Os usuários que detinham dessas ações foram ressarcidos." << endl;
}

void CadastrarUsuario(Mercado& m){
    string nome;
    float saldo;

    cout << "Informe o nome do novo usuário: ";
    cin >> nome;

    cout << "Informe o valor do primeiro depósito do novo usuário: ";
    cin >> saldo;

    Usuario usr = Usuario(nome, saldo);
    m.addUsuario(usr);
    cout << "\nUsuário cadastrado com sucesso!" << endl;
}

void RemoverUsuario(Mercado& m, Usuario& usr){
    m.removeUsuario(usr);
    cout << "\nUsuário removido com sucesso! Sua carteira foi completamente vendida." << endl;
}

void AdminMenu(Mercado& m){
    char opcao = '0';
    while(opcao != 'x'){
        cout << setfill ('=') << setw(45) << " " << endl;
        cout << setfill (' ') << setw(30) << "MENU DE ADMINISTRADOR" << endl;
        cout << setfill ('=') << setw(45) << " " << endl;
        cout << "  a - Adicionar novo ativo de ação;" << endl;
        cout << "  r - Remover ativo de ação;" << endl;
        cout << "  c - Cadastrar novo usuário;" << endl;
        cout << "  e - Remover conta de usuário;" << endl;
        cout << "  x - VOLTAR." << endl;
        cout << setfill ('=') << setw(45) << " " << endl;
        cout << "Escolha uma opção: ";
         
        cin >> opcao;
        opcao = tolower(opcao);

        system("clear");

        switch(opcao){
            case 'a':
                AdicionarAtivo(m);
                break;
            case 'r':
                RemoverAtivo(m, SelecionarAcao(m));
                break;
            case 'c':
                CadastrarUsuario(m);
                break;
            case 'e':
                RemoverUsuario(m, SelecionarUsuario(m));
                break;
            case 'x':
                break;
            default:
                system("clear");
                cout << "Opção inválida! Tente novamente." << endl;
        }
        return;
    }
}

bool Sair(){
    int entrada=0, tamanho=2;
    while(entrada < 1 || entrada > tamanho){
        cout << setfill ('=') << setw(40) << " " << endl;
        cout << setfill (' ') << setw(10) << "[" << 1 << "] " << "Confirmar saída" << endl;
        cout << setfill (' ') << setw(10) << "[" << 2 << "] " << "Voltar ao menu" << endl;
        cout << setfill ('=') << setw(40) << " " << endl;
        cout << "Deseja sair do sistema? ";
        cin >> entrada;
        if(entrada < 1 || entrada > tamanho){
            system("clear");
            cout << "Opção inválida! Tente novamente." << endl;
            entrada = 0;
        }
    }
    system("clear"); // Limpa a tela
    if(entrada == 1){
        cout << "\nObrigado por utilizar nosso sistema! Até mais.\n";
        return true;
    }
    else{
        return false;
    }
}
