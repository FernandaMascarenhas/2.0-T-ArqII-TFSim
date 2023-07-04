#include "branch_predictorMN.hpp"
#include <iostream>
#include <math.h>
using namespace std;

branch_predictorMN::branch_predictorMN(unsigned int m, unsigned int n): tamanho_M(m), n_bits(n)
{
    // Construtor da classe branch_predictor.
    // Inicializa as variáveis membros.
    // m_bits é o número de bits para o histórico global.
    // n_bits é o número de bits para o contador saturado.

    // Calcula o número máximo de entradas na tabela de histórico.
    cout << "Tamanho_M:" << tamanho_M << endl;
    history_size = pow(2, tamanho_M);
    cout << "history_size:" << history_size << endl;
    cout << "n_bist" << n_bits << endl;

    // Inicializa a tabela de histórico com todos os bits zerados.
    history_table.resize(history_size);
    history_global = 0;
    cout << "History global 1:" << history_global << endl;

    // Inicializa os contadores de predições e acertos.
    max = (1<<n_bits)-1;
    stateMN = 0;
    c_predictions = 0;
    c_hits = 0;

}

bool branch_predictorMN::predict_MN() {

    cout << "History global:" << history_global << endl;
    cout << "History table:" << history_table.at(history_global) << endl;

    int var = history_table.at(history_global);
    int bitMaisSignificativo = var&(1<<(n_bits-1));

    for(int cont = 0; cont < 4; cont++) {
         cout << "history_table:" << history_table[cont] << endl;
    }
   

    cout << "bitMaisSignificativo:" << bitMaisSignificativo << endl;

    c_predictions++;
    return bitMaisSignificativo;
    
}

void branch_predictorMN::mn_update_state(bool taken, bool hit)
{
    cout << "hit" << hit << endl;
    cout << "taken" << taken << endl;
    c_hits += hit;
 
    stateMN = history_table.at(history_global);

    if (taken) {

        stateMN += (stateMN < max);

    }
    else {

        stateMN -= (stateMN > 0); 

    }

    history_table.at(history_global) = stateMN;
    //histoty_table[history_global] = stateMN

    int aux = history_global << 1;

    cout << "Aux:" << aux << endl;
    cout << "Atualização historico global:" << history_global << endl;

    if(taken) {
        aux = ++aux>max?max:aux;
    }


    cout << "Aux:" << aux << endl;
    cout << "Atualização historico global:" << history_global << endl;
    history_global = aux;

}

float branch_predictorMN::get_predictorMN_hit_rate() {
    // Calcula a taxa de acertos do preditor de desvio (m, n).
    // A taxa de acertos é calculada dividindo o número de acertos (c_hits)
    // pelo número total de predições (c_predictions) e multiplicando por 100.

    if (c_predictions == 0) {
        // Verifica se não houve predições feitas para evitar divisão por zero.
        return 0.0;
    }
    cout << "Divisao" << (float)(c_hits) / (float)(c_predictions) << endl;
    cout << "C_hits" << (c_hits) << endl;
    cout << "C_pred" << (c_predictions) << endl;
    return (float)(c_hits) / (float)(c_predictions) * 100.0;
}

