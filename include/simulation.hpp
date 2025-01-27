#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <ctime>

#include "market.hpp"

void Interface(Mercado& mkt);
bool salvarDados(Mercado& m);
void lerDados(Mercado& m);

void Menu();
void QuadroAcoes(Mercado& m);

Ativo& SelecionarAcao(Mercado& m);

void HistoricoAcao(Ativo& atv);

void ConsultarDisponibilidade(Ativo& atv);

Usuario& SelecionarUsuario(Mercado& m);

void Carteira(Usuario& usr);

void ComprarAcao(Mercado& m, Ativo& atv, Usuario& usr);

void VenderAcao(Mercado& m, Ativo& atv, Usuario& usr);

void AdicionarAtivo(Mercado& m);
void RemoverAtivo(Mercado& m, Ativo& atv);
void CadastrarUsuario(Mercado& m);
void RemoverUsuario(Mercado& m, Usuario& usr);

void AdminMenu(Mercado& m);

bool Sair();