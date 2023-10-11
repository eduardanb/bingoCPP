#include <iostream> // Permite entrada e saí­da de dados.
#include <cstdlib> // Permite gerar números aleatórios.
#include <ctime> // Deixa a geração de números imprevisí­veis.
#include <vector> // Utiliza a classe vetor.
#include <algorithm> // Procura os números já sorteados.
using namespace std;

struct Jogador
{
    int** ficha;
    vector<int> num_sorteado; 
};

int** criar_matriz(int linhas, int colunas){
    int **mat;
    mat = new int*[linhas];
    for(int i=0; i<linhas; i++){

    
        mat[i] = new int[colunas];
    }
    return mat;
}

// Adiciona números entre 10 à 75.
void adicionar_numeros(int** mat, int linhas, int colunas){
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            mat[i][j] = rand() % 66 + 10; 
        }
    }
}

void imprimir_cartela(int** mat, int linhas, int colunas){
    for(int i=0; i<linhas; i++){
        cout<<"|  ";
        for(int j=0; j<colunas; j++){
           if(mat[i][j] == 0){
               cout<<" X  |   ";
           }else{
               cout<<mat[i][j]<<"  |   ";
           }
        }
        cout << endl;
    }
}

bool valores_na_matriz(int** mat, int linhas, int colunas, int num){ 
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            if (mat[i][j] == num) {
                return true;
            }
        }
    }
    return false;
}

bool cartela_completa(int** mat, int linhas, int colunas){
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            if (mat[i][j] != 0){
                return false;
            }
        }
    }
    return true;
}

int main()
{
    const int linhas = 5;
    const int colunas = 5;

    cout << "\033[0;33m|==========================================|\033[0m\n";
    cout << "\033[0;33m|==========================================|\033[0m\n";
    cout << "\033[0;33m|\033[0m      B      I      N      G      O       \033[0;33m|\033[0m\n";
    cout << "\033[0;33m|==========================================|\033[0m\n";
    cout << "\033[0;33m|==========================================|\033[0m\n";
    // Inicialização do gerador de números aleatórios.
    srand(static_cast<unsigned int>(time(nullptr))); 

    Jogador cartela01;
    cartela01.ficha = criar_matriz(linhas, colunas); 
    cout << endl;
    cout << "\033[0;35m--------------- CARTELA 01 ----------------\033[0m" << endl;
    adicionar_numeros(cartela01.ficha, linhas, colunas);
    imprimir_cartela(cartela01.ficha, linhas, colunas);

    Jogador cartela02;
    cartela02.ficha = criar_matriz(linhas, colunas); 
    cout << endl;
    cout << "\033[0;34m--------------- CARTELA 02 ----------------\033[0m" << endl;
    adicionar_numeros(cartela02.ficha, linhas, colunas);
    imprimir_cartela(cartela02.ficha, linhas, colunas);

    cout << endl;

    int sua_escolha;
    cout << "Escolha uma cartela [1 / 2]: ";
    cin >> sua_escolha;

    Jogador cartela_escolhida;
    if (sua_escolha == 1) {
        cout << "\033[0;31m-> Voce esta jogando com a cartela 01.\033[0m" << endl;
        cout << endl;
        cartela_escolhida = cartela01;
        imprimir_cartela(cartela01.ficha, linhas, colunas);
    } else if (sua_escolha == 2){
        cout << "\033[0;31m-> Voce esta jogando com a cartela 02.\033[0m" << endl;
        cout << endl;
        cartela_escolhida = cartela02;
        imprimir_cartela(cartela02.ficha, linhas, colunas);
    } else {
        cout << "VALOR INVALIDO!" << endl;
        cout << "Encerrando programa em 3, 2, 1..." << endl;
        return 1;
    }

    cout << "Precione Enter para iniciar o sorteio...";
    cin.ignore(); // Descarta caracteres extras.
    cin.get(); // lÃª um Ãºnico caractere do buffer de entrada.
    cout << endl;

    int num_sorteado; 
 
    while (true){
        do{
            num_sorteado = rand() % 66+10;

            // Garante que nÃ£o haverÃ¡ repetiÃ§Ã£o de nÃºmeros na lista de nÃºmeros sorteados.
        } while (find(cartela_escolhida.num_sorteado.begin(), cartela_escolhida.num_sorteado.end(), num_sorteado) != cartela_escolhida.num_sorteado.end());

        cartela_escolhida.num_sorteado.push_back(num_sorteado);
        cout << endl;
        cout << "\033[0;32m- Foi sorteado o numero [\033[0m" << num_sorteado << "\033[0;32m].\033[0m" << endl;

        if(valores_na_matriz(cartela_escolhida.ficha, linhas, colunas, num_sorteado)){
            for(int i=0; i<linhas; i++){
                for(int j=0; j<colunas; j++){
                    if (cartela_escolhida.ficha[i][j] == num_sorteado){
                        cartela_escolhida.ficha[i][j] = 0;
                    }
                }
            }
            imprimir_cartela(cartela_escolhida.ficha, linhas, colunas);
            if (cartela_completa(cartela_escolhida.ficha, linhas, colunas)){
                cout << endl;
                cout << "\033[0;32m|======================================|\033[0m" << endl;
                cout << "\033[0;32m|==== Voce ganhou:  B  I  N  G  O  ====|\033[0m" << endl;
                cout << "\033[0;32m|======================================|\033[0m" << endl;
                break;
            }

        }

        cout << "Precione Enter para continuar...";
        cin.ignore();
        cin.get();
    }

    cout << endl;
    cout << "Numeros sorteados: ";
    cout << "[ ";
    for(int num : cartela_escolhida.num_sorteado){
        cout << num << " ";
    }
    cout << "]";
    cout << endl;
    
    system("pause");
    return 0;
}