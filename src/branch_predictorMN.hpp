#include <vector>

class branch_predictorMN
{
public:
    branch_predictorMN(unsigned int m, unsigned int n);
    bool predict_MN();
    void mn_update_state(bool taken, bool hit);
    float get_predictorMN_hit_rate();
    
private:
    unsigned int tamanho_M;         // Número de bits para o histórico global
    unsigned int n_bits;            // Número de bits para o contador saturado
    unsigned int history_size;      // Tamanho da tabela de histórico
    unsigned int counter_max;       // Valor máximo para saturação do contador
    //unsigned int history;
    std::vector<int> history_table;  // Tabela de histórico global
    int c_predictions;     // Contador de predições
    int c_hits;            // Contador de acertos nas predições
    int stateMN;
    int max, aux;
    int history_global;
};
