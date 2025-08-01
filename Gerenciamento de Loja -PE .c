#include <stdio.h>
#include <string.h>

// Estrutura para representar uma compra
typedef struct {
    float valorCompra;      // Valor total da compra
    int compraCancelada;    // 1 para sim, 0 para não
    int bonusUsado;         // Quantidade de bônus utilizados
    float valorBonus;       // Valor de 1 bônus na época da compra
} tCompra;

// Estrutura para representar um cliente
typedef struct {
    char nome[101];         // Nome do cliente (máximo 100 caracteres)
    char cpf[12];           // CPF do cliente (11 dígitos + '\0')
    char telefone[16];      // Telefone do cliente (máximo 15 caracteres + '\0')
    int bonus;              // Quantidade de bônus acumulados
    float totalCompras;     // Valor total de compras
    tCompra ultimaCompra;   // Registro da última compra
} tCliente;

// Estrutura para representar as configurações de bônus
typedef struct {
    int teto;               // Teto de bônus (inicia em 1000)
    float valor;            // Valor de 1 bônus (inicia em 0.50)
    float valorBonificado;  // Valor necessário para ganhar bônus (inicia em 100.0)
} tBonus;

// Função verificar CPF
int verificarCPF(char *cpf, tCliente *clientes, int totalClientes) {
    if (totalClientes == 0) {
        return 0; // Nenhum cliente cadastrado, CPF não duplicado
    }

    int i;
    for (i = 0; i < totalClientes; i++) {
        if (strcmp(cpf, clientes[i].cpf) == 0) {
            return 1; // CPF já cadastrado
        }
    }

    return 0; // CPF não encontrado
}

// Função buscarCliente
int buscarCliente(tCliente *clientes, int totalClientes, char *cpf) {
    int i;
    for (i = 0; i < totalClientes; i++) {
        if (strcmp(cpf, clientes[i].cpf) == 0) {
            return i; // Retorna o índice do cliente
        }
    }
    return -1; // CPF não encontrado
}

// Funções MENU de 01
void alterarTeto(tBonus *bonusConfig) {
    
    printf("Qual o novo valor do teto?\n");

    do{
        scanf("%d", &bonusConfig->teto);
        if(bonusConfig->teto < 0){
            printf("Erro: valor negativo. Digite novamente: ");
        }
    }while(bonusConfig->teto < 0);
}

void alterarValor1Bonus(tBonus *bonusConfig) {
    
    printf("Qual o novo valor de 1 bonus?\n");
    do{
        scanf("%f", &bonusConfig->valor);
        if(bonusConfig->valor < 0){
            printf("Erro: valor negativo. Digite novamente: ");
        }
    }while(bonusConfig->valor < 0);
}

void alterarValorBonificado(tBonus *bonusConfig) {
    
    printf("Qual o novo valor para receber bonus?\n");
    do{
        scanf("%f", &bonusConfig->valorBonificado);
        if(bonusConfig->valorBonificado < 0){
            printf("Erro: valor negativo. Digite novamente: ");
        }
    }while(bonusConfig->valorBonificado < 0);
}

// Funções do MENU de 03
void alterarCPF(tCliente *clientes, int totalClientes, int indice) {
    char novocpf[12];
    printf("Qual o novo CPF? ");
    scanf("%s", novocpf);

    // Verificar se o CPF já está cadastrado
    if (verificarCPF(novocpf, clientes, totalClientes)) {
        printf("Erro: CPF já cadastrado.\n");
        return;
    }

    // Atualizar o CPF
    strcpy(clientes[indice].cpf, novocpf);
    printf("CPF alterado com sucesso!\n");
}

void alterarNome(tCliente *clientes, int indice){
    printf("Qual o novo nome? ");
    scanf(" %[^\n]", clientes[indice].nome);
    printf("Nome atualizado para: %s\n", clientes[indice].nome);
}

void alterarTelefone(tCliente *clientes, int indice){
    printf("Qual o novo telefone? ");
    scanf("%s", clientes[indice].telefone);
    printf("Numero atualizado para: %s\n", clientes[indice].telefone);
}




// 01 - Função para configurar bônus
void configurarBonus(tBonus *bonusConfig) {
    int opcaoBonus;

    printf("Configuração de Bônus:\n");
    printf("1 - Alterar teto\n");
    printf("2 - Alterar valor do bônus\n");
    printf("3 - Alterar valor bonificado\n");
    printf("0 - Voltar ao menu principal\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoBonus);

    switch (opcaoBonus) {
        case 1:
            alterarTeto(bonusConfig);
            break;
        case 2:
            alterarValor1Bonus(bonusConfig);
            break;
        case 3:
            alterarValorBonificado(bonusConfig);
            break;
        case 0:
            return;
        default:
            printf("Opcao invalida!\n");
    }
}

// 02 - Função para cadastrar cliente
void cadastrarCliente(tCliente *clientes, int *totalClientes) {
    char cpfNovo[12]; // Variável para armazenar novo CPF temporário

    printf("Qual o CPF? ");
    scanf("%s", cpfNovo);

    // Verificar se o CPF já está cadastrado
    if (verificarCPF(cpfNovo, clientes, *totalClientes)) {
        printf("Erro: CPF já cadastrado.\n");
        return;
    }

    // Continuar o cadastro válido
    printf("Qual o nome? ");
    scanf(" %[^\n]", clientes[*totalClientes].nome);

    printf("Qual o telefone? ");
    scanf("%s", clientes[*totalClientes].telefone);

    // Preencher os campos padrão
    strcpy(clientes[*totalClientes].cpf, cpfNovo);
    clientes[*totalClientes].bonus = 0;
    clientes[*totalClientes].totalCompras = 0.0;
    clientes[*totalClientes].ultimaCompra = (tCompra){0.0, 0, 0, 0.0};

    // Incrementar o contador de clientes
    (*totalClientes)++;

    printf("Cliente cadastrado com sucesso!\n");
}

// 03 - Função alterar cadastro do cliente
void alterarCadastro(tCliente *clientes, int *totalClientes){
    char cpf[12];
    
    //pedir cpf ao usuario
    printf("Qual o CPF do cliente?");
    scanf("%s", cpf);

    int indice = buscarCliente(clientes, totalClientes, cpf);
    
    if (indice == -1) {
        printf("Erro: CPF nao cadastrado.\n");
        return;
    }

    int opcaoCadastro;

    printf("Configuração de Cadastro:\n");
    printf("1 - Alterar CPF\n");
    printf("2 - Alterar nome\n");
    printf("3 - Alterar telefone\n");
    printf("0 - Voltar ao menu principal\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoCadastro);

    switch (opcaoCadastro) {
        case 1:
            alterarCPF(clientes, totalClientes, indice);
            break;
        case 2:
            alterarNome(clientes, indice);
            break;
        case 3:
            alterarTelefone(clientes, indice);
            break;
        case 0:
            return;
        default:
            printf("Opcao invalida!\n");
    }
}

// 04 - Função alterar cadastro do cliente
void efetivarCompra(tCliente *clientes, int totalClientes, tBonus bonusConfig){
    char cpf[12];
    float valorCompra;
    
    //pedir cpf ao usuario
    printf("Qual o CPF do cliente?");
    scanf("%s", cpf);

    //verificar se o cpf ja esta cadastrado
    int indice = buscarCliente(clientes, totalClientes, cpf);
    
    if (indice == -1) {
        printf("Erro: CPF nao cadastrado.\n");
        return;
    }

    //exibir informações sobre bonus
    printf("BONUS = %d VALOR CORRESPONDENTE= R$ %.2f\n", clientes[indice].bonus, clientes[indice].bonus * bonusConfig.valor);
    
    printf("Qual o valor da compra?\n");
    
    do{
        float valorCompra;
        scanf("%f", &valorCompra);

        if(valorCompra < 0){
            printf("Erro: valor negativo. Digite novamente: ");
        }
    }while (valorCompra < 0);
}

// 06 - Função para consultar bônus
void consultarBonus(tCliente *clientes, int totalClientes, tBonus bonusConfig) {
    char cpf[12];
    int indice;

    printf("Qual o CPF do cliente? ");
    scanf(" %s", cpf);

    indice = buscarCliente(clientes, totalClientes, cpf);

    if (indice == -1) {
        printf("Erro: CPF nao cadastrado.\n");
        return;
    }

    // Mostrar os bônus e o valor correspondente
    printf("BONUS = %d VALOR CORRESPONDENTE = R$ %.2f\n", clientes[indice].bonus, clientes[indice].bonus * bonusConfig.valor);
}




// Função main
int main() {
    tCliente clientes[100]; // Vetor de clientes
    int totalClientes = 0;   // Contador de clientes cadastrados
    tBonus bonusConfig = {1000, 0.50, 100.0}; // Configuração inicial de bônus
    int opcao;

    do {
        printf("\nMENU PRINCIPAL:\n");
        printf("01 - Configurar bonus\n");
        printf("02 - Cadastrar cliente\n");
        printf("03 - Alterar cadastro do cliente\n");
        printf("04 - Efetivar compra\n");
        printf("05 - Cancelar compra\n");
        printf("06 - Consultar bonus\n");
        printf("07 - Listar dados de todos os clientes\n");
        printf("08 - Listar bonus de todos os clientes\n");
        printf("09 - Listar clientes pelo valor total de compras\n");
        printf("00 - Sair\n");

        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                configurarBonus(&bonusConfig);  // Chama a função para configurar bônus
                break;
            case 2:
                cadastrarCliente(clientes, &totalClientes);
                break;
            case 6:
                consultarBonus(clientes, totalClientes, bonusConfig);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }while(opcao != 0);

    return 0;
}
